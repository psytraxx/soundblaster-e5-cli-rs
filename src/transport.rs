//! USB transport for the E5 vendor control protocol.
//!
//! # What is known, and what is not
//!
//! The `(Feature, param, value)` addressing in [`crate::proto`] is **exact** --
//! it was recovered from typed .NET metadata, not inferred.
//!
//! The *framing* in this module is **not yet verified against hardware.**
//! Decompiling the Windows stack showed the control path is:
//!
//! ```text
//! SBE.exe -> Interop.CtSndCr -> SndCrUSB.DLL -> KsMalcCtl.DLL
//!   -> IOCTL_KS_PROPERTY (0x2F0003) -> KsUSBaud.sys -> USB
//! ```
//!
//! So Windows does not issue USB vendor requests from userspace at all: it
//! sets Kernel Streaming properties, and `KsUSBaud.sys` translates those
//! into USB traffic. On Linux there is no such driver, so we must speak
//! whatever `KsUSBaud.sys` emits -- and that layout is still unproven.
//!
//! Because of that, framing is expressed as a swappable [`Framing`]
//! strategy rather than baked into the call sites, and any operation
//! against a real device must be confirmed by a round-trip read plus an
//! audible check before it is trusted.
//!
//! Set `SBX_E5_DRY_RUN=1` (or pass `--dry-run`) to print packets instead of
//! sending them. With no device attached this is the only mode available.

use crate::proto::{Feature, PID_E5, VID_CREATIVE};
use crate::{Error, Result};
use std::time::Duration;

/// Vendor interface the control panel claims (`MI_00` in `ksusbaud.inf`).
const VENDOR_INTERFACE: u8 = 0;

const TIMEOUT: Duration = Duration::from_millis(500);

/// Candidate wire layouts.
///
/// Selecting a different variant changes only how a triple is serialized,
/// never how callers address parameters.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum Framing {
    /// `[feature: u32le][param: u32le][value: u32le]` sent as a vendor
    /// interface request. The simplest layout consistent with the driver
    /// containing vendor request types `0x40`/`0xC0`.
    #[default]
    VendorTriple,

    /// Mirrors the `KSPROPERTY` buffer observed at `KSUSBSPI32.dll.c:67441`:
    /// a 16-byte property-set GUID, a 4-byte `Id`, a 4-byte `Flags`
    /// (1 = GET, 2 = SET), followed by an 8-byte payload -- 32 bytes total.
    KsProperty,
}

/// `KSPROPERTY.Flags` values used by the Windows stack.
const KS_FLAG_GET: u32 = 1;
const KS_FLAG_SET: u32 = 2;

/// Vendor request codes. Unverified; see the module docs.
const REQ_SET_PARAM: u8 = 0x03;
const REQ_GET_PARAM: u8 = 0x04;

/// How a parameter value is encoded on the wire.
#[derive(Debug, Clone, Copy)]
pub enum Value {
    Float(f32),
    Bool(bool),
}

impl Value {
    fn to_le_bytes(self) -> [u8; 4] {
        match self {
            Value::Float(v) => v.to_le_bytes(),
            Value::Bool(v) => u32::from(v).to_le_bytes(),
        }
    }
}

/// Serialize one parameter write into its on-the-wire payload.
///
/// Kept free-standing (and public to the crate) so it can be unit-tested
/// without a device present.
pub fn encode(framing: Framing, feature: Feature, param: u32, value: Value) -> Vec<u8> {
    match framing {
        Framing::VendorTriple => {
            let mut buf = Vec::with_capacity(12);
            buf.extend_from_slice(&(feature as u32).to_le_bytes());
            buf.extend_from_slice(&param.to_le_bytes());
            buf.extend_from_slice(&value.to_le_bytes());
            buf
        }
        Framing::KsProperty => {
            // 16-byte property-set GUID. The real GUID still has to be
            // lifted out of KsMalcCtl.DLL; zeroed here so the layout is
            // testable without pretending we know the value.
            let mut buf = Vec::with_capacity(32);
            buf.extend_from_slice(&[0u8; 16]);
            buf.extend_from_slice(&param.to_le_bytes()); // Id
            buf.extend_from_slice(&KS_FLAG_SET.to_le_bytes()); // Flags
            buf.extend_from_slice(&(feature as u32).to_le_bytes());
            buf.extend_from_slice(&value.to_le_bytes());
            buf
        }
    }
}

/// An open handle to the device's vendor control interface.
pub struct Transport {
    handle: Option<rusb::DeviceHandle<rusb::GlobalContext>>,
    dry_run: bool,
    framing: Framing,
}

impl Transport {
    /// Open the first E5 found, claiming its vendor interface.
    ///
    /// If `dry_run` is set -- explicitly, or via `SBX_E5_DRY_RUN` -- no
    /// device is opened and packets are printed instead of sent.
    pub fn open(dry_run: bool) -> Result<Self> {
        let dry_run = dry_run || std::env::var_os("SBX_E5_DRY_RUN").is_some();
        if dry_run {
            return Ok(Self {
                handle: None,
                dry_run,
                framing: Framing::default(),
            });
        }

        let handle =
            rusb::open_device_with_vid_pid(VID_CREATIVE, PID_E5).ok_or(Error::DeviceNotFound)?;

        // snd-usb-audio binds the audio interfaces; detaching only the
        // vendor interface leaves playback running.
        let _ = handle.set_auto_detach_kernel_driver(true);
        handle.claim_interface(VENDOR_INTERFACE)?;

        Ok(Self {
            handle: Some(handle),
            dry_run,
            framing: Framing::default(),
        })
    }

    /// Select a different wire layout.
    pub fn with_framing(mut self, framing: Framing) -> Self {
        self.framing = framing;
        self
    }

    /// True if this transport only prints packets.
    pub fn is_dry_run(&self) -> bool {
        self.dry_run
    }

    /// Build and send one parameter write.
    fn send(&mut self, feature: Feature, param: u32, value: Value) -> Result<()> {
        let payload = encode(self.framing, feature, param, value);

        if self.dry_run {
            println!(
                "SET {:?} feature=0x{:08X} param={} value={:?}\n    {:02X?}",
                self.framing, feature as u32, param, value, payload
            );
            return Ok(());
        }

        let handle = self.handle.as_mut().ok_or(Error::DeviceNotFound)?;
        let request_type = rusb::request_type(
            rusb::Direction::Out,
            rusb::RequestType::Vendor,
            rusb::Recipient::Interface,
        );
        handle.write_control(
            request_type,
            REQ_SET_PARAM,
            0,
            u16::from(VENDOR_INTERFACE),
            &payload,
            TIMEOUT,
        )?;
        Ok(())
    }

    /// Write a float-typed parameter.
    pub fn set_float(&mut self, feature: Feature, param: u32, value: f32) -> Result<()> {
        self.send(feature, param, Value::Float(value))
    }

    /// Write a bool-typed parameter.
    pub fn set_bool(&mut self, feature: Feature, param: u32, value: bool) -> Result<()> {
        self.send(feature, param, Value::Bool(value))
    }

    /// Read a float-typed parameter back from the device.
    ///
    /// This is the check that distinguishes "the device accepted the write"
    /// from "the device silently ignored an unrecognised request", so it is
    /// the first thing to exercise once hardware is available.
    pub fn get_float(&mut self, feature: Feature, param: u32) -> Result<f32> {
        if self.dry_run {
            println!(
                "GET feature=0x{:08X} param={} (dry run -> 0.0)",
                feature as u32, param
            );
            return Ok(0.0);
        }

        let handle = self.handle.as_mut().ok_or(Error::DeviceNotFound)?;
        let request_type = rusb::request_type(
            rusb::Direction::In,
            rusb::RequestType::Vendor,
            rusb::Recipient::Interface,
        );
        let mut buf = [0u8; 4];
        handle.read_control(
            request_type,
            REQ_GET_PARAM,
            0,
            u16::from(VENDOR_INTERFACE),
            &mut buf,
            TIMEOUT,
        )?;
        let _ = KS_FLAG_GET; // used by the KsProperty read path once proven
        Ok(f32::from_le_bytes(buf))
    }
}

impl Drop for Transport {
    fn drop(&mut self) {
        if let Some(h) = self.handle.as_mut() {
            let _ = h.release_interface(VENDOR_INTERFACE);
        }
    }
}

/// Describe every Creative device on the bus and its interfaces.
///
/// This is the first thing to run against real hardware: it shows whether a
/// vendor-specific interface exists alongside the standard USB Audio Class
/// ones, which is what confirms or refutes the framing above.
pub fn dump_descriptors() -> Result<String> {
    use std::fmt::Write as _;
    let mut out = String::new();

    for device in rusb::devices()?.iter() {
        let desc = device.device_descriptor()?;
        if desc.vendor_id() != VID_CREATIVE {
            continue;
        }
        writeln!(
            out,
            "device {:04x}:{:04x}  bus {} addr {}",
            desc.vendor_id(),
            desc.product_id(),
            device.bus_number(),
            device.address()
        )
        .ok();

        for n in 0..desc.num_configurations() {
            let config = device.config_descriptor(n)?;
            for iface in config.interfaces() {
                for d in iface.descriptors() {
                    let kind = match d.class_code() {
                        0x01 => "audio (UAC)",
                        0x03 => "HID",
                        0xff => "vendor-specific  <-- control interface",
                        _ => "other",
                    };
                    writeln!(
                        out,
                        "  if {} alt {}  class {:#04x} sub {:#04x} proto {:#04x}  eps {}  {}",
                        d.interface_number(),
                        d.setting_number(),
                        d.class_code(),
                        d.sub_class_code(),
                        d.protocol_code(),
                        d.num_endpoints(),
                        kind
                    )
                    .ok();
                }
            }
        }
    }

    if out.is_empty() {
        return Err(Error::DeviceNotFound);
    }
    Ok(out)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn vendor_triple_layout_is_stable() {
        // SBX bass strength = 0.3, the value Creative's own Default.xml ships.
        let buf = encode(
            Framing::VendorTriple,
            Feature::EffectsXBass,
            crate::proto::XBass::Strength as u32,
            Value::Float(0.3),
        );
        assert_eq!(buf.len(), 12);
        // feature 0x10000020, little endian
        assert_eq!(&buf[0..4], &[0x20, 0x00, 0x00, 0x10]);
        // param 1
        assert_eq!(&buf[4..8], &[0x01, 0x00, 0x00, 0x00]);
        // 0.3f32
        assert_eq!(&buf[8..12], &0.3f32.to_le_bytes());
    }

    #[test]
    fn bools_encode_as_u32() {
        let buf = encode(
            Framing::VendorTriple,
            Feature::EffectsXBass,
            crate::proto::XBass::Enable as u32,
            Value::Bool(true),
        );
        assert_eq!(&buf[8..12], &[0x01, 0x00, 0x00, 0x00]);
    }

    #[test]
    fn ks_property_buffer_is_32_bytes() {
        let buf = encode(
            Framing::KsProperty,
            Feature::EffectsGraphicEQ,
            crate::proto::GraphicEq::Band0Gain as u32,
            Value::Float(0.0),
        );
        // Matches the 0x20-byte buffer seen at KSUSBSPI32.dll.c:67441.
        assert_eq!(buf.len(), 32);
        // Flags field is SET.
        assert_eq!(&buf[20..24], &KS_FLAG_SET.to_le_bytes());
    }

    #[test]
    fn feature_ids_match_the_windows_driver() {
        // Spot-check the packed one-hot encoding recovered from metadata.
        assert_eq!(Feature::EffectsXBass as u32, 0x1000_0020);
        assert_eq!(Feature::EffectsGraphicEQ as u32, 0x1000_0010);
        assert_eq!(Feature::EffectsCrystalizer as u32, 0x1000_0008);
        assert_eq!(Feature::EffectsSimpleSurround as u32, 0x1000_0200);
    }
}
