//! USB transport for the E5 control protocol.
//!
//! # What is known, and what is not
//!
//! The `(Feature, param, value)` addressing in [`crate::proto`] is **exact** --
//! it was recovered from typed .NET metadata, not inferred.
//!
//! A USBPcap capture of `KsUSBaud.sys` (see
//! `reverse/e5-control-protocol.md`) established the wire format:
//! control parameters travel as **HID SET_REPORT on the control pipe**, and
//! the 32-bit feature ids never appear on the wire. `KsUSBaud.sys` collapses
//! a triple into a single-byte *param selector* plus a big-endian `f32`.
//!
//! What the capture proves, from an E5:
//!
//! * the setup packet (`0x21 / 0x09 / wValue 0x0200 / wIndex 3`, 64-byte report),
//! * the `0x20` SET_PARAM report layout, byte for byte,
//! * the bass selector, `0x32`,
//! * that the value is a **big-endian** `f32` in `0.0..=1.0`, linear with the
//!   Windows slider percentage.
//!
//! Every other selector in [`selector_with_confidence`] is *derived*: the
//! driver builds the selector as `parameter_id << 1`
//! (`FUN_00486670` in the decompiled sources), and the ids come from the
//! table published for the Sound Blaster G6 -- same vendor and driver
//! family, a different device. `Confidence::Captured` vs `Derived` tracks
//! which is which; see `sbx-e5 selectors`.
//!
//! Still open: whether the `0x26` and `0x23` reports are required or merely
//! re-asserted by the control panel, and the GET_REPORT read path (there is
//! no confirmed way to read a parameter back from the device).
//!
//! The pre-capture guesses are kept as [`Framing::VendorTriple`] and
//! [`Framing::KsProperty`] so the reconstruction is still inspectable, but
//! [`Framing::HidReport`] is the default and the only one backed by hardware
//! traffic.
//!
//! Set `SBX_E5_DRY_RUN=1` (or pass `--dry-run`) to print packets instead of
//! sending them.

use crate::proto::{Feature, PID_E5, VID_CREATIVE};
use crate::{Error, Result};
use std::time::Duration;

/// Vendor interface the pre-capture reconstruction claimed (`MI_00`).
const VENDOR_INTERFACE: u8 = 0;

/// HID interface the captured control transfers address (`wIndex = 3`).
pub const HID_INTERFACE: u8 = 3;

const TIMEOUT: Duration = Duration::from_millis(500);

// ---- HID control transfer constants (captured) --------------------------

/// `bmRequestType`: host->device, class, recipient = interface.
const REQ_TYPE_SET: u8 = 0x21;
/// `bRequest`: HID SET_REPORT.
const HID_SET_REPORT: u8 = 0x09;
/// `wValue`: ReportType = Output (2), ReportID = 0.
const OUT_REPORT: u16 = 0x0200;
/// Every captured report is padded to this length.
const REPORT_LEN: usize = 64;

/// Opcode byte selecting the report shape.
const OP_SET_PARAM: u8 = 0x20;
const OP_COMMIT: u8 = 0x26;
const OP_MASTER: u8 = 0x23;

/// Fixed framing bytes at offsets 1..7 of every `0x20` report.
const SET_PARAM_HDR: [u8; 6] = [0x00, 0x16, 0x0a, 0xd5, 0x02, 0x08];
/// Fixed bytes at offsets 8..10, between the selector and the value.
const SET_PARAM_TAIL: [u8; 2] = [0x20, 0x96];

/// Device parameter ids.
///
/// `KsUSBaud_x86.sys` builds report byte 7 as `id << 1` (`FUN_00486670`, at
/// `reverse/decompiled/KsUSBaud_x86.sys.c:108296`):
///
/// ```text
/// cVar2 = param_1._1_1_ << 1;   // -> report[7]
/// ```
///
/// The id values themselves match the table published for the Sound Blaster
/// G6 (same vendor and driver family) at
/// <https://github.com/dreamzone-cc/soundblaster-g6x-linux-controller>.
pub mod id {
    pub const SURROUND_ENABLE: u8 = 0x00;
    pub const SURROUND_LEVEL: u8 = 0x01;
    pub const DIALOG_PLUS_ENABLE: u8 = 0x02;
    pub const DIALOG_PLUS_LEVEL: u8 = 0x03;
    pub const SMART_VOLUME_ENABLE: u8 = 0x04;
    pub const SMART_VOLUME_LEVEL: u8 = 0x05;
    pub const SMART_VOLUME_MODE: u8 = 0x06;
    pub const CRYSTALIZER_ENABLE: u8 = 0x07;
    pub const CRYSTALIZER_LEVEL: u8 = 0x08;
    pub const EQ_ENABLE: u8 = 0x09;
    pub const EQ_PREAMP: u8 = 0x0a;
    /// EQ band 0 (31 Hz); bands run consecutively to band 9 (16 kHz).
    pub const EQ_BAND0: u8 = 0x0b;
    pub const BASS_ENABLE: u8 = 0x18;
    pub const BASS_LEVEL: u8 = 0x19;
}

/// Turn a parameter id into its report byte 7.
pub const fn selector_of(id: u8) -> u8 {
    id << 1
}

/// How well a selector is established.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Confidence {
    /// Seen on the wire in a capture from this device.
    Captured,
    /// Derived from the driver's `id << 1` rule plus the G6 id table, but not
    /// yet observed on an E5.
    Derived,
}

/// Bass level: the one selector proven by capture *and* by listening.
pub const SEL_BASS: u8 = selector_of(id::BASS_LEVEL);
/// Surround level: `0x02`, matching the G6 id table.
pub const SEL_SURROUND: u8 = selector_of(id::SURROUND_LEVEL);

/// Map a `(Feature, param)` pair to its selector byte and how well it is known.
///
/// Returns `None` only for parameters with no id in the table at all.
pub fn selector_with_confidence(feature: Feature, param: u32) -> Option<(u8, Confidence)> {
    use crate::proto::{Crystalizer, DialogPlus, GraphicEq, SimpleSurround, SmartVolume, XBass};
    use Confidence::{Captured, Derived};

    let (id, conf) = match (feature, param) {
        (Feature::EffectsXBass, p) if p == XBass::Strength as u32 => (id::BASS_LEVEL, Captured),
        (Feature::EffectsXBass, p) if p == XBass::Enable as u32 => (id::BASS_ENABLE, Derived),

        (Feature::EffectsSimpleSurround, p) if p == SimpleSurround::Level as u32 => {
            (id::SURROUND_LEVEL, Derived)
        }
        (Feature::EffectsSimpleSurround, p) if p == SimpleSurround::Enable as u32 => {
            (id::SURROUND_ENABLE, Derived)
        }

        (Feature::EffectsCrystalizer, p) if p == Crystalizer::Level as u32 => {
            (id::CRYSTALIZER_LEVEL, Derived)
        }
        (Feature::EffectsCrystalizer, p) if p == Crystalizer::Enable as u32 => {
            (id::CRYSTALIZER_ENABLE, Derived)
        }

        (Feature::EffectsDialogPlus, p) if p == DialogPlus::Strength as u32 => {
            (id::DIALOG_PLUS_LEVEL, Derived)
        }
        (Feature::EffectsDialogPlus, p) if p == DialogPlus::Enable as u32 => {
            (id::DIALOG_PLUS_ENABLE, Derived)
        }

        (Feature::EffectsSmartVolume, p) if p == SmartVolume::Strength as u32 => {
            (id::SMART_VOLUME_LEVEL, Derived)
        }
        (Feature::EffectsSmartVolume, p) if p == SmartVolume::Enable as u32 => {
            (id::SMART_VOLUME_ENABLE, Derived)
        }
        (Feature::EffectsSmartVolume, p) if p == SmartVolume::Mode as u32 => {
            (id::SMART_VOLUME_MODE, Derived)
        }

        (Feature::EffectsGraphicEQ, p) if p == GraphicEq::Enable as u32 => (id::EQ_ENABLE, Derived),
        (Feature::EffectsGraphicEQ, p) if p == GraphicEq::PreampGain as u32 => {
            (id::EQ_PREAMP, Derived)
        }
        (Feature::EffectsGraphicEQ, p) => {
            let band = p.checked_sub(GraphicEq::Band0Gain as u32)?;
            if band > 9 {
                return None;
            }
            (id::EQ_BAND0 + band as u8, Derived)
        }

        _ => return None,
    };
    Some((selector_of(id), conf))
}

/// Map a `(Feature, param)` pair to its selector byte.
pub fn selector(feature: Feature, param: u32) -> Option<u8> {
    selector_with_confidence(feature, param).map(|(s, _)| s)
}

/// Candidate wire layouts.
///
/// Selecting a different variant changes only how a triple is serialized,
/// never how callers address parameters.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum Framing {
    /// The captured HID output report: opcode `0x20`, one selector byte, and
    /// a big-endian `f32`, zero-padded to 64 bytes.
    #[default]
    HidReport,

    /// Pre-capture guess: `[feature: u32le][param: u32le][value: u32le]` as a
    /// vendor interface request. Superseded by [`Framing::HidReport`]; kept
    /// only so the reconstruction stays inspectable.
    VendorTriple,

    /// Pre-capture guess mirroring the `KSPROPERTY` buffer at
    /// `KSUSBSPI32.dll.c:67441`: a 16-byte property-set GUID, a 4-byte `Id`,
    /// a 4-byte `Flags` (1 = GET, 2 = SET), then an 8-byte payload.
    /// Superseded by [`Framing::HidReport`].
    KsProperty,
}

/// `KSPROPERTY.Flags` values used by the Windows stack.
const KS_FLAG_GET: u32 = 1;
const KS_FLAG_SET: u32 = 2;

/// Vendor request codes for the superseded [`Framing::VendorTriple`] path.
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

    /// The `f32` this value carries on the HID path, where booleans ride the
    /// same float field as `0.0` / `1.0`.
    fn as_f32(self) -> f32 {
        match self {
            Value::Float(v) => v,
            Value::Bool(v) => f32::from(u8::from(v)),
        }
    }
}

/// Build a `0x20` SET_PARAM report: 64 bytes, big-endian `f32` value.
///
/// Reproduces the captured vectors exactly; see `reverse/e5-control-protocol.md`.
pub fn encode_set_param(param: u8, value: f32) -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_SET_PARAM;
    r[1..7].copy_from_slice(&SET_PARAM_HDR);
    r[7] = param;
    r[8..10].copy_from_slice(&SET_PARAM_TAIL);
    r[10..14].copy_from_slice(&value.to_be_bytes());
    r
}

/// Build a `0x26` commit report for a parameter id.
///
/// The bass capture shows `26 01 96 19` sent once after every `0x20` write,
/// 135 times for 135 value writes. Byte 3 is `0x19` -- the *same* parameter
/// id the value write addressed, not a level. The `01 96` matches the magic
/// `0x0196` the G6 protocol carries in its DATA and COMMIT commands, where
/// the pattern is likewise "set value, then commit it".
///
/// So this is read as the commit half of a DATA+COMMIT pair. Whether the E5
/// actually requires it is unproven: a bass write lands audibly without one.
pub fn encode_commit(id: u8) -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_COMMIT;
    r[1] = 0x01;
    r[2] = 0x96;
    r[3] = id;
    r
}

/// Build the `0x23` master/keepalive report.
pub fn encode_master() -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_MASTER;
    r[1] = 0x27;
    r[2] = 0x01;
    r
}

/// Serialize one parameter write into its on-the-wire payload.
///
/// Kept free-standing (and public to the crate) so it can be unit-tested
/// without a device present. Fails for [`Framing::HidReport`] when the
/// parameter has no captured selector.
pub fn encode(framing: Framing, feature: Feature, param: u32, value: Value) -> Result<Vec<u8>> {
    match framing {
        Framing::HidReport => {
            let sel = selector(feature, param).ok_or(Error::Unsupported { feature, param })?;
            Ok(encode_set_param(sel, value.as_f32()).to_vec())
        }
        Framing::VendorTriple => {
            let mut buf = Vec::with_capacity(12);
            buf.extend_from_slice(&(feature as u32).to_le_bytes());
            buf.extend_from_slice(&param.to_le_bytes());
            buf.extend_from_slice(&value.to_le_bytes());
            Ok(buf)
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
            Ok(buf)
        }
    }
}

/// An open handle to the device's vendor control interface.
pub struct Transport {
    handle: Option<rusb::DeviceHandle<rusb::GlobalContext>>,
    dry_run: bool,
    framing: Framing,
    /// Interface currently claimed, so `Drop` releases the right one.
    claimed: u8,
    /// Send a `0x26` commit after each value write, as Windows does.
    commit: bool,
}

impl Framing {
    /// The USB interface this layout addresses.
    fn interface(self) -> u8 {
        match self {
            Framing::HidReport => HID_INTERFACE,
            Framing::VendorTriple | Framing::KsProperty => VENDOR_INTERFACE,
        }
    }
}

impl Transport {
    /// Open the first E5 found, claiming its vendor interface.
    ///
    /// If `dry_run` is set -- explicitly, or via `SBX_E5_DRY_RUN` -- no
    /// device is opened and packets are printed instead of sent.
    pub fn open(dry_run: bool) -> Result<Self> {
        let dry_run = dry_run || std::env::var_os("SBX_E5_DRY_RUN").is_some();
        let framing = Framing::default();
        if dry_run {
            return Ok(Self {
                handle: None,
                dry_run,
                framing,
                claimed: framing.interface(),
                commit: true,
            });
        }

        let handle =
            rusb::open_device_with_vid_pid(VID_CREATIVE, PID_E5).ok_or(Error::DeviceNotFound)?;

        // snd-usb-audio binds the audio interfaces; detaching only the
        // control interface leaves playback running.
        let _ = handle.set_auto_detach_kernel_driver(true);
        let claimed = framing.interface();
        handle.claim_interface(claimed)?;

        Ok(Self {
            handle: Some(handle),
            dry_run,
            framing,
            claimed,
            commit: true,
        })
    }

    /// Enable or disable the `0x26` commit that follows each value write.
    pub fn set_commit(&mut self, on: bool) {
        self.commit = on;
    }

    /// Select a different wire layout, re-claiming the interface it uses.
    pub fn with_framing(mut self, framing: Framing) -> Result<Self> {
        let want = framing.interface();
        if want != self.claimed
            && let Some(h) = self.handle.as_mut()
        {
            let _ = h.release_interface(self.claimed);
            h.claim_interface(want)?;
        }
        self.claimed = want;
        self.framing = framing;
        Ok(self)
    }

    /// True if this transport only prints packets.
    pub fn is_dry_run(&self) -> bool {
        self.dry_run
    }

    /// Build and send one parameter write.
    fn send(&mut self, feature: Feature, param: u32, value: Value) -> Result<()> {
        let payload = encode(self.framing, feature, param, value)?;

        if self.dry_run {
            println!(
                "SET {:?} feature=0x{:08X} param={} value={:?}\n    {:02X?}",
                self.framing, feature as u32, param, value, payload
            );
        } else {
            self.write_raw(&payload)?;
        }

        // Mirror what Windows does: every value write is followed by a
        // commit for the same id. Bass lands without it, so it may be
        // redundant -- `commit(false)` turns it off for A/B testing.
        if self.commit && self.framing == Framing::HidReport {
            let sel = selector(feature, param).ok_or(Error::Unsupported { feature, param })?;
            let r = encode_commit(sel >> 1);
            if self.dry_run {
                println!("    commit {:02X?}", &r[..4]);
            } else {
                self.write_raw(&r)?;
            }
        }
        Ok(())
    }

    /// Send an already-encoded report over the control pipe.
    fn write_raw(&mut self, payload: &[u8]) -> Result<()> {
        if self.dry_run {
            println!("RAW {:02X?}", payload);
            return Ok(());
        }

        let handle = self.handle.as_mut().ok_or(Error::DeviceNotFound)?;
        match self.framing {
            Framing::HidReport => {
                handle.write_control(
                    REQ_TYPE_SET,
                    HID_SET_REPORT,
                    OUT_REPORT,
                    u16::from(HID_INTERFACE),
                    payload,
                    TIMEOUT,
                )?;
            }
            Framing::VendorTriple | Framing::KsProperty => {
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
                    payload,
                    TIMEOUT,
                )?;
            }
        }
        Ok(())
    }

    /// Send a `0x26` commit report for `id`.
    pub fn send_commit(&mut self, id: u8) -> Result<()> {
        let r = encode_commit(id);
        self.write_raw(&r)
    }

    /// Send the `0x23` master/keepalive report.
    pub fn send_master(&mut self) -> Result<()> {
        let r = encode_master();
        self.write_raw(&r)
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
    /// The capture never exercised a GET_REPORT round trip, so the read path
    /// remains unproven for every framing; it stays here as the check that
    /// would distinguish "the device accepted the write" from "the device
    /// silently ignored it".
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
            let _ = h.release_interface(self.claimed);
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

    /// Hex of the first `n` bytes, for comparing against the captured vectors.
    fn prefix(buf: &[u8], n: usize) -> String {
        buf[..n].iter().map(|b| format!("{b:02x}")).collect()
    }

    #[test]
    fn set_param_matches_captured_vectors() {
        // reverse/e5-control-protocol.md, "Verified test vectors".
        assert_eq!(
            prefix(&encode_set_param(SEL_BASS, 0.50), 14),
            "2000160ad502083220963f000000"
        );
        assert_eq!(
            prefix(&encode_set_param(SEL_BASS, 0.55), 14),
            "2000160ad502083220963f0ccccd"
        );
        assert_eq!(
            prefix(&encode_set_param(SEL_BASS, 1.00), 14),
            "2000160ad502083220963f800000"
        );
        assert_eq!(
            prefix(&encode_set_param(SEL_SURROUND, 0.55), 14),
            "2000160ad502080220963f0ccccd"
        );
    }

    #[test]
    fn reports_are_64_bytes_and_zero_padded() {
        let r = encode_set_param(SEL_BASS, 1.0);
        assert_eq!(r.len(), 64);
        assert!(r[14..].iter().all(|&b| b == 0));
    }

    #[test]
    fn commit_and_master_match_captured_vectors() {
        // The captured commit is `26 01 96 19`; byte 3 is the bass level id
        // (0x19 = 25), the same id the value write addressed.
        assert_eq!(prefix(&encode_commit(id::BASS_LEVEL), 4), "26019619");
        assert_eq!(prefix(&encode_master(), 8), "2327010000000000");
    }

    #[test]
    fn selector_is_id_shifted_left_one() {
        // The rule lifted from FUN_00486670: report[7] = id << 1.
        assert_eq!(selector_of(id::BASS_LEVEL), 0x32);
        assert_eq!(selector_of(id::SURROUND_LEVEL), 0x02);
        assert_eq!(selector_of(id::CRYSTALIZER_LEVEL), 0x10);
        assert_eq!(selector_of(id::BASS_ENABLE), 0x30);
    }

    #[test]
    fn eq_bands_map_to_consecutive_selectors() {
        use crate::proto::GraphicEq;
        for band in 0..10u32 {
            let param = GraphicEq::Band0Gain as u32 + band;
            let (sel, _) = selector_with_confidence(Feature::EffectsGraphicEQ, param).unwrap();
            assert_eq!(sel, selector_of(id::EQ_BAND0 + band as u8));
        }
        // Band 10 does not exist.
        let past_end = GraphicEq::Band0Gain as u32 + 10;
        assert!(selector_with_confidence(Feature::EffectsGraphicEQ, past_end).is_none());
    }

    #[test]
    fn only_bass_level_is_marked_captured() {
        use crate::proto::XBass;
        assert_eq!(
            selector_with_confidence(Feature::EffectsXBass, XBass::Strength as u32),
            Some((0x32, Confidence::Captured))
        );
        assert_eq!(
            selector_with_confidence(Feature::EffectsXBass, XBass::Enable as u32),
            Some((0x30, Confidence::Derived))
        );
    }

    #[test]
    fn bass_zero_is_all_zero_bytes() {
        // The `bass 0` end of the sweep: an f32 of exactly 0.0.
        assert_eq!(
            prefix(&encode_set_param(SEL_BASS, 0.0), 14),
            "2000160ad5020832209600000000"
        );
    }

    #[test]
    fn hid_framing_routes_bass_and_surround_to_their_selectors() {
        let bass = encode(
            Framing::HidReport,
            Feature::EffectsXBass,
            crate::proto::XBass::Strength as u32,
            Value::Float(0.5),
        )
        .unwrap();
        assert_eq!(bass[7], SEL_BASS);

        let surround = encode(
            Framing::HidReport,
            Feature::EffectsSimpleSurround,
            crate::proto::SimpleSurround::Level as u32,
            Value::Float(0.5),
        )
        .unwrap();
        assert_eq!(surround[7], SEL_SURROUND);
    }

    #[test]
    fn crystalizer_encodes_to_its_derived_selector() {
        let buf = encode(
            Framing::HidReport,
            Feature::EffectsCrystalizer,
            crate::proto::Crystalizer::Level as u32,
            Value::Float(0.5),
        )
        .unwrap();
        assert_eq!(buf[7], 0x10);
    }

    #[test]
    fn parameters_with_no_id_are_rejected_not_guessed() {
        // XBass Freq_Hz has no id in the G6 table, so there is nothing to
        // derive a selector from.
        let e = encode(
            Framing::HidReport,
            Feature::EffectsXBass,
            crate::proto::XBass::FreqHz as u32,
            Value::Float(80.0),
        );
        assert!(matches!(e, Err(Error::Unsupported { .. })));
    }

    #[test]
    fn vendor_triple_layout_is_stable() {
        // SBX bass strength = 0.3, the value Creative's own Default.xml ships.
        let buf = encode(
            Framing::VendorTriple,
            Feature::EffectsXBass,
            crate::proto::XBass::Strength as u32,
            Value::Float(0.3),
        )
        .unwrap();
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
        )
        .unwrap();
        assert_eq!(&buf[8..12], &[0x01, 0x00, 0x00, 0x00]);
    }

    #[test]
    fn ks_property_buffer_is_32_bytes() {
        let buf = encode(
            Framing::KsProperty,
            Feature::EffectsGraphicEQ,
            crate::proto::GraphicEq::Band0Gain as u32,
            Value::Float(0.0),
        )
        .unwrap();
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
