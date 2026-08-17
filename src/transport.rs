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
//! The read path is confirmed and is **not** a GET_REPORT: the query goes
//! out as an ordinary SET_REPORT and the answer arrives on **interrupt IN
//! endpoint `0x83`**. Opcode `0x26` reads a parameter value -- confirmed
//! against every id in a panel-open state sync, values matching plausible
//! slider positions. See [`encode_get_param`] / [`Transport::get_float`].
//!
//! The read path addresses parameters by their **raw id** -- `0x19` for bass
//! level -- not by the `id << 1` selector the `0x20` write path uses. Do not
//! feed [`selector_of`] into a read.
//!
//! The SBX master switch is confirmed both ways: writing it sends
//! `23 23 01 <flag>` followed by a `23 24 00` commit
//! ([`encode_set_sbx_master`] / [`Transport::set_sbx_master`]), and reading
//! it sends the same `23 24 00` commit report on its own -- it doubles as a
//! standalone status query, answering with the current state on the same
//! response shape either way ([`decode_master_commit_response`] /
//! [`Transport::get_sbx_master`]). See `reverse/e5-control-protocol.md`.
//!
//! Still open: whether the `0x26` and `0x23` *write* reports are required or
//! merely re-asserted by the control panel.
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
/// `0x26` doubles as GET_PARAM when byte 3 carries a raw id with no value
/// bytes following -- same opcode as [`OP_COMMIT`], distinguished by the
/// response coming back on the interrupt IN endpoint.
const OP_GET_PARAM: u8 = 0x26;

/// Interrupt IN endpoint the device answers `0x26` queries on.
/// (`reverse/e5-control-protocol.md`, "Read path".)
const READ_ENDPOINT: u8 = 0x83;
/// Every captured read response is this long.
const READ_LEN: usize = 16;

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

/// Map a `(Feature, param)` pair to its **raw** parameter id and how well it
/// is known. This is the id the `0x26` read path addresses;
/// [`selector_with_confidence`] shifts it left one bit for the write path.
///
/// Returns `None` only for parameters with no id in the table at all.
pub fn id_with_confidence(feature: Feature, param: u32) -> Option<(u8, Confidence)> {
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
    Some((id, conf))
}

/// Map a `(Feature, param)` pair to its selector byte and how well it is
/// known -- the write-path counterpart of [`id_with_confidence`].
pub fn selector_with_confidence(feature: Feature, param: u32) -> Option<(u8, Confidence)> {
    id_with_confidence(feature, param).map(|(id, conf)| (selector_of(id), conf))
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
const KS_FLAG_SET: u32 = 2;

/// Vendor request code for the superseded [`Framing::VendorTriple`] path.
const REQ_SET_PARAM: u8 = 0x03;

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

/// Build a `0x26` GET_PARAM query report for a raw parameter id.
///
/// Wire-confirmed in `reverse/captures/read.json`: `26 01 96 <id>` sent as a normal
/// SET_REPORT, answered on interrupt IN endpoint `0x83` with
/// `00 26 01 96 00 <id> <f32 big-endian>`. `id` here is the **raw** id
/// (e.g. `0x19` for bass level), not `id << 1`.
pub fn encode_get_param(id: u8) -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_GET_PARAM;
    r[1] = 0x01;
    r[2] = 0x96;
    r[3] = id;
    r
}

/// Build the `0x23 0x23` SBX master enable/disable report.
///
/// Wire-confirmed in `reverse/captures/sbx.json` across two full on/off cycles:
/// `23 23 01 01` precedes each fade-in, `23 23 01 00` precedes each
/// fade-out. See `reverse/e5-control-protocol.md`, "`0x23` -- SBX master
/// enable / keepalive".
pub fn encode_set_sbx_master(on: bool) -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_MASTER;
    r[1] = 0x23;
    r[2] = 0x01;
    r[3] = u8::from(on);
    r
}

/// Build the `0x23 0x24` commit report that follows an `0x23 0x23`
/// enable/disable write.
///
/// Wire-confirmed alongside [`encode_set_sbx_master`]: the panel always
/// sends this immediately after the enable/disable write, never on its own.
/// Whether the device actually requires it (versus `0x23 0x23` alone being
/// sufficient) is untested -- see the open item in
/// `reverse/e5-control-protocol.md`.
pub fn encode_master_commit() -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_MASTER;
    r[1] = 0x24;
    r
}

/// Parse a `0x23 0x24` commit response (16 bytes from the interrupt
/// endpoint) for the state bit it echoes back.
///
/// Wire-confirmed in `reverse/captures/sbx.json` across all four toggles in two
/// on/off cycles: the commit that follows `encode_set_sbx_master` always
/// answers with the master state at offset 4 -- `00 23 24 00 01 00 01`
/// after turning on, `00 23 24 00 00 00 01` after turning off. This is the
/// SBX master read: it rides on the write's own commit response rather
/// than needing a separate query.
pub fn decode_master_commit_response(buf: &[u8]) -> Option<bool> {
    if buf.len() < 5 || buf[1] != OP_MASTER || buf[2] != 0x24 {
        return None;
    }
    Some(buf[4] != 0)
}

/// Parse a `0x26` GET_PARAM response (16 bytes from the interrupt endpoint).
///
/// Returns `(id, value)`, or `None` if the response doesn't echo the
/// GET_PARAM opcode shape.
pub fn decode_get_param_response(buf: &[u8]) -> Option<(u8, f32)> {
    if buf.len() < 10 || buf[1] != OP_GET_PARAM || buf[2] != 0x01 {
        return None;
    }
    let id = buf[5];
    let value = f32::from_be_bytes(buf[6..10].try_into().ok()?);
    Some((id, value))
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

    /// Send a raw `0x26` GET_PARAM query and read back the response.
    ///
    /// Wire-confirmed in `reverse/captures/read.json`: the query is an ordinary
    /// SET_REPORT, the answer arrives on interrupt IN endpoint `0x83`. `id`
    /// is the raw parameter id, not the `id << 1` write selector.
    pub fn get_param_raw(&mut self, id: u8) -> Result<f32> {
        let query = encode_get_param(id);

        if self.dry_run {
            println!("GET id=0x{id:02X} (dry run -> 0.0)\n    {query:02X?}");
            return Ok(0.0);
        }

        self.write_raw(&query)?;
        self.read_matching(id, |buf| match decode_get_param_response(buf) {
            Some((got_id, value)) if got_id == id => Some(value),
            _ => None,
        })
    }

    /// Read a float-typed parameter back from the device.
    pub fn get_float(&mut self, feature: Feature, param: u32) -> Result<f32> {
        let (id, _) =
            id_with_confidence(feature, param).ok_or(Error::Unsupported { feature, param })?;
        self.get_param_raw(id)
    }

    /// Write the SBX master switch: `0x23 0x23` enable/disable followed by
    /// the `0x23 0x24` commit the panel always sends after it. Both are
    /// wire-confirmed in `reverse/captures/sbx.json` -- see [`encode_set_sbx_master`].
    ///
    /// The commit's own response echoes the resulting state (see
    /// [`decode_master_commit_response`]), so this returns what the device
    /// actually reports afterward rather than assuming the write took.
    pub fn set_sbx_master(&mut self, on: bool) -> Result<bool> {
        let write = encode_set_sbx_master(on);
        let commit = encode_master_commit();

        if self.dry_run {
            println!("SET sbx-master = {on}\n    {write:02X?}\n    commit {commit:02X?}");
            return Ok(on);
        }

        self.write_raw(&write)?;
        self.write_raw(&commit)?;
        self.read_matching(0, decode_master_commit_response)
    }

    /// Read the SBX master switch without changing it.
    ///
    /// Wire-confirmed in `reverse/captures/read.json`: the panel-open sync sends a
    /// bare `0x23 0x24` commit query with no preceding `0x23 0x23` write,
    /// and gets the current master state back on the same response shape
    /// [`Self::set_sbx_master`] reads. So `0x23 0x24` alone is a standalone
    /// status query, not only a write's commit half.
    pub fn get_sbx_master(&mut self) -> Result<bool> {
        let query = encode_master_commit();

        if self.dry_run {
            println!("GET sbx-master (dry run -> false)\n    {query:02X?}");
            return Ok(false);
        }

        self.write_raw(&query)?;
        self.read_matching(0, decode_master_commit_response)
    }

    /// Read interrupt reports until `decode` accepts one, or the endpoint
    /// runs dry.
    ///
    /// The device does not answer one query with exactly one report. A
    /// master toggle, for instance, emits the `0x23 0x23` write's own echo
    /// *and* a burst of unsolicited `0x26` level-ramp reports before the
    /// `0x23 0x24` response the caller is waiting for. Taking the first
    /// report off the endpoint therefore grabs the wrong one and leaves the
    /// rest queued, so every later read is answered by a stale report.
    ///
    /// Reading until a report actually matches keeps the queue drained and
    /// each query paired with its own answer.
    fn read_matching<T>(&mut self, id: u8, decode: impl Fn(&[u8]) -> Option<T>) -> Result<T> {
        // Generous enough for the ramp bursts seen in the captures, while
        // still terminating if the device answers with something we cannot
        // parse at all.
        const MAX_REPORTS: usize = 32;

        for _ in 0..MAX_REPORTS {
            let buf = match self.read_interrupt() {
                Ok(buf) => buf,
                // A timeout means the endpoint is drained and the answer
                // never came, which is a mismatch rather than a USB fault.
                Err(Error::Usb(rusb::Error::Timeout)) => break,
                Err(e) => return Err(e),
            };
            if let Some(value) = decode(&buf) {
                return Ok(value);
            }
        }
        Err(Error::UnexpectedResponse { id })
    }

    /// Read one 16-byte HID input report from the interrupt endpoint the
    /// device answers `0x26`/`0x23` queries on.
    fn read_interrupt(&mut self) -> Result<[u8; READ_LEN]> {
        let handle = self.handle.as_mut().ok_or(Error::DeviceNotFound)?;
        let mut buf = [0u8; READ_LEN];
        handle.read_interrupt(READ_ENDPOINT, &mut buf, TIMEOUT)?;
        Ok(buf)
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
    fn get_param_query_matches_captured_vectors() {
        // reverse/e5-control-protocol.md, "0x26 -- GET_PARAM": `26019619`
        // queries bass level (raw id 0x19, not the 0x32 write selector).
        assert_eq!(prefix(&encode_get_param(id::BASS_LEVEL), 4), "26019619");
        assert_eq!(prefix(&encode_get_param(id::SURROUND_LEVEL), 4), "26019601");
    }

    #[test]
    fn get_param_response_decodes_captured_vectors() {
        // Same section: `002601009619 3f000000` -> bass level 0.5.
        let buf = hex("002601009619 3f000000 000000".replace(' ', ""));
        assert_eq!(decode_get_param_response(&buf), Some((id::BASS_LEVEL, 0.5)));

        // `002601009601 3df5c28f` -> surround level 0.12.
        let buf = hex("002601009601 3df5c28f 000000".replace(' ', ""));
        let (got_id, value) = decode_get_param_response(&buf).unwrap();
        assert_eq!(got_id, id::SURROUND_LEVEL);
        assert!((value - 0.12).abs() < 1e-6);
    }

    #[test]
    fn get_param_response_rejects_wrong_opcode() {
        let buf = hex("00230100961943000000000000".to_string());
        assert_eq!(decode_get_param_response(&buf), None);
    }

    #[test]
    fn set_sbx_master_matches_captured_vectors() {
        // reverse/e5-control-protocol.md, "0x23 -- SBX master enable / keepalive".
        assert_eq!(prefix(&encode_set_sbx_master(true), 4), "23230101");
        assert_eq!(prefix(&encode_set_sbx_master(false), 4), "23230100");
        assert_eq!(prefix(&encode_master_commit(), 2), "2324");
    }

    #[test]
    fn master_commit_response_decodes_captured_vectors() {
        // reverse/e5-control-protocol.md, "0x23 -- SBX master enable / keepalive".
        let after_on = hex("002324000100010000000000".to_string());
        assert_eq!(decode_master_commit_response(&after_on), Some(true));

        let after_off = hex("002324000000010000000000".to_string());
        assert_eq!(decode_master_commit_response(&after_off), Some(false));
    }

    #[test]
    fn master_commit_response_rejects_wrong_opcode() {
        let buf = hex("00260100961943000000000000".to_string());
        assert_eq!(decode_master_commit_response(&buf), None);
    }

    /// One master toggle produces four interrupt reports, and the one the
    /// caller wants is last. Taking the first -- as the code originally did
    /// -- picks the `0x23 0x23` write echo, fails to decode it as a commit
    /// response, and leaves three reports queued to desync every later read.
    ///
    /// Exact sequence from `reverse/captures/sbx.json`, frames 1138-1146.
    #[test]
    fn master_commit_response_is_found_past_the_reports_that_precede_it() {
        let burst = [
            hex("002323000101000000000000".to_string()), // 0x23 0x23 write echo
            hex("0026010096073f8000000000".to_string()), // unsolicited level ramp
            hex("0026010096183f8000000000".to_string()), // unsolicited level ramp
            hex("002324000100010000000000".to_string()), // the commit response
        ];

        // Everything before the commit response must be skipped, not accepted
        // and not treated as a hard error.
        for buf in &burst[..3] {
            assert_eq!(decode_master_commit_response(buf), None);
        }
        assert_eq!(decode_master_commit_response(&burst[3]), Some(true));

        // Scanning the burst in order finds exactly one answer.
        let found: Vec<bool> = burst
            .iter()
            .filter_map(|b| decode_master_commit_response(b))
            .collect();
        assert_eq!(found, vec![true]);
    }

    /// The same desync hazard on the value-read path: a queued response for
    /// a different id must be skipped rather than aborting the read.
    #[test]
    fn get_param_response_for_another_id_is_skipped_not_fatal() {
        let stale = hex("0026010096083f23d70a0000".to_string()); // id 0x08
        let wanted = hex("0026010096193f0000000000".to_string()); // id 0x19

        let want = id::BASS_LEVEL;
        let matching = |b: &[u8]| match decode_get_param_response(b) {
            Some((got, v)) if got == want => Some(v),
            _ => None,
        };

        assert_eq!(matching(&stale), None);
        assert_eq!(matching(&wanted), Some(0.5));
    }

    /// Decode a hex string (no separators) into bytes, for response fixtures.
    fn hex(s: String) -> Vec<u8> {
        (0..s.len())
            .step_by(2)
            .map(|i| u8::from_str_radix(&s[i..i + 2], 16).unwrap())
            .collect()
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
