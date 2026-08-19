//! USB transport for the E5 control protocol.
//!
//! Full wire documentation is in `reverse/e5-control-protocol.md`.
//!
//! # Writes
//!
//! Control parameters travel as **HID SET_REPORT on the control pipe**
//! (`0x21 / 0x09 / wValue 0x0200 / wIndex 3`), a 64-byte zero-padded report
//! whose first byte is an opcode. The `(Feature, param, value)` addressing
//! in [`crate::proto`] does not appear on the wire: it collapses to a
//! single-byte *selector* plus a **big-endian** `f32` in `0.0..=1.0`,
//! linear with the Windows slider percentage.
//!
//! The selector is `parameter_id << 1`, over the id table in [`id`]. A
//! parameter that is *not* in that table is still a guess, so add one only
//! with evidence -- see `CLAUDE.md`.
//!
//! # Reads
//!
//! Not a GET_REPORT. The query goes out as an ordinary SET_REPORT and the
//! answer arrives on **interrupt IN endpoint `0x83`**. Opcode `0x26` reads
//! a parameter value ([`encode_get_param`] / [`Transport::get_float`]).
//!
//! Reads address parameters by their **raw id** -- `0x19` for bass level --
//! not the doubled write selector. Do not feed [`selector_of`] into a read.
//!
//! One query does not mean one report: the endpoint also carries a write's
//! own echo and unsolicited level-ramp reports, so read until one actually
//! matches (see [`Transport::read_matching`]).
//!
//! # SBX master
//!
//! Its own opcode rather than a `0x20` selector. Writing sends
//! `23 23 01 <flag>` then a `23 24 00` commit; sending that same
//! `23 24 00` alone reads the current state back
//! ([`Transport::set_sbx_master`] / [`Transport::get_sbx_master`]).
//!
//! Set `SBX_E5_DRY_RUN=1` (or pass `--dry-run`) to print packets instead of
//! sending them.

use crate::proto::{Feature, PID_E5, VID_CREATIVE};
use crate::{Error, Result};
use std::time::Duration;

/// HID interface the control transfers address (`wIndex = 3`).
pub const HID_INTERFACE: u8 = 3;

const TIMEOUT: Duration = Duration::from_millis(500);

// ---- HID control transfer constants --------------------------------------

/// `bmRequestType`: host->device, class, recipient = interface.
const REQ_TYPE_SET: u8 = 0x21;
/// `bRequest`: HID SET_REPORT.
const HID_SET_REPORT: u8 = 0x09;
/// `wValue`: ReportType = Output (2), ReportID = 0.
const OUT_REPORT: u16 = 0x0200;
/// Every report is padded to this length.
const REPORT_LEN: usize = 64;

/// Opcode byte selecting the report shape.
const OP_SET_PARAM: u8 = 0x20;
const OP_COMMIT: u8 = 0x26;
const OP_MASTER: u8 = 0x23;
/// `0x26` doubles as GET_PARAM when byte 3 carries a raw id with no value
/// bytes following -- same opcode as [`OP_COMMIT`], distinguished by the
/// response coming back on the interrupt IN endpoint.
const OP_GET_PARAM: u8 = 0x26;

/// Byte 3 of a `0x23` response when the device does not implement that
/// subcommand. Seen on `23 4c` and `23 4d` in `captures/read.json`, which
/// both answer `00 23 4c 80`.
pub const UNSUPPORTED_MARKER: u8 = 0x80;

/// Interrupt IN endpoint the device answers `0x26` queries on.
/// (`reverse/e5-control-protocol.md`, "Read path".)
const READ_ENDPOINT: u8 = 0x83;
/// Every read response is this long.
const READ_LEN: usize = 16;

/// DSP module a parameter belongs to -- report byte 2 of a `0x26` query,
/// and byte 9 of a `0x20` write.
///
/// Only [`module::PLAYBACK`] is ever written. [`module::VOICE_INPUT`] is
/// wire-confirmed for *reads*: `captures/read.json` has the Windows panel
/// query `26 01 95 06` and the device answer with `00 26 01 00 95 06`.
/// Nothing has ever been written to it.
pub mod module {
    /// Playback effects: the SBX suite and the EQ.
    pub const PLAYBACK: u8 = 0x96;
    /// Microphone chain (CrystalVoice). Read-only as far as we know.
    pub const VOICE_INPUT: u8 = 0x95;
    /// Room calibration. Creative blocks third-party writes here.
    pub const ROOM_CALIBRATION: u8 = 0x8F;
    /// Master control (volume, mute). Creative blocks writes here.
    pub const MASTER_CONTROL: u8 = 0x80;
}

/// Fixed framing bytes at offsets 1..7 of every `0x20` report.
const SET_PARAM_HDR: [u8; 6] = [0x00, 0x16, 0x0a, 0xd5, 0x02, 0x08];
/// Fixed bytes at offsets 8..10, between the selector and the value. The
/// `0x96` is the playback module id -- see `reverse/e5-control-protocol.md`.
const SET_PARAM_TAIL: [u8; 2] = [0x20, 0x96];

/// Device parameter ids.
///
/// A read addresses one of these directly; a write uses [`selector_of`] to
/// double it into report byte 7.
///
/// Every id here is verified on an E5, with one exception noted below:
/// [`BASS_CROSSOVER_HZ`] was read off the device in a capture but has never
/// been written to it.
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
    /// SBX Bass crossover, in Hz -- the one id here that is *not* a
    /// normalized `0.0..=1.0` level.
    pub const BASS_CROSSOVER_HZ: u8 = 0x17;
    pub const BASS_ENABLE: u8 = 0x18;
    pub const BASS_LEVEL: u8 = 0x19;

    /// Every id above with a human-readable name, for `sbx-e5 selectors`.
    ///
    /// The EQ bands are omitted: they run consecutively from [`EQ_BAND0`]
    /// and are generated rather than listed.
    pub const TABLE: &[(&str, u8)] = &[
        ("surround enable", SURROUND_ENABLE),
        ("surround level", SURROUND_LEVEL),
        ("dialog+ enable", DIALOG_PLUS_ENABLE),
        ("dialog+ level", DIALOG_PLUS_LEVEL),
        ("smart volume enable", SMART_VOLUME_ENABLE),
        ("smart volume level", SMART_VOLUME_LEVEL),
        ("smart volume mode", SMART_VOLUME_MODE),
        ("crystalizer enable", CRYSTALIZER_ENABLE),
        ("crystalizer level", CRYSTALIZER_LEVEL),
        ("eq enable", EQ_ENABLE),
        ("eq preamp", EQ_PREAMP),
        ("bass enable", BASS_ENABLE),
        ("bass level", BASS_LEVEL),
        ("bass crossover Hz", BASS_CROSSOVER_HZ),
    ];
}

/// Turn a parameter id into its report byte 7.
pub const fn selector_of(id: u8) -> u8 {
    id << 1
}

/// Map a `(Feature, param)` pair to its **raw** parameter id. This is the id
/// the `0x26` read path addresses; [`selector`] shifts it left one bit for
/// the write path.
///
/// Returns `None` only for parameters with no id in the table at all.
pub fn id_of(feature: Feature, param: u32) -> Option<u8> {
    use crate::proto::{Crystalizer, DialogPlus, GraphicEq, SimpleSurround, SmartVolume, XBass};

    let id = match (feature, param) {
        (Feature::EffectsXBass, p) if p == XBass::Strength as u32 => id::BASS_LEVEL,
        (Feature::EffectsXBass, p) if p == XBass::Enable as u32 => id::BASS_ENABLE,
        (Feature::EffectsXBass, p) if p == XBass::FreqHz as u32 => id::BASS_CROSSOVER_HZ,

        (Feature::EffectsSimpleSurround, p) if p == SimpleSurround::Level as u32 => {
            id::SURROUND_LEVEL
        }
        (Feature::EffectsSimpleSurround, p) if p == SimpleSurround::Enable as u32 => {
            id::SURROUND_ENABLE
        }

        (Feature::EffectsCrystalizer, p) if p == Crystalizer::Level as u32 => id::CRYSTALIZER_LEVEL,
        (Feature::EffectsCrystalizer, p) if p == Crystalizer::Enable as u32 => {
            id::CRYSTALIZER_ENABLE
        }

        (Feature::EffectsDialogPlus, p) if p == DialogPlus::Strength as u32 => {
            id::DIALOG_PLUS_LEVEL
        }
        (Feature::EffectsDialogPlus, p) if p == DialogPlus::Enable as u32 => id::DIALOG_PLUS_ENABLE,

        (Feature::EffectsSmartVolume, p) if p == SmartVolume::Strength as u32 => {
            id::SMART_VOLUME_LEVEL
        }
        (Feature::EffectsSmartVolume, p) if p == SmartVolume::Enable as u32 => {
            id::SMART_VOLUME_ENABLE
        }
        (Feature::EffectsSmartVolume, p) if p == SmartVolume::Mode as u32 => id::SMART_VOLUME_MODE,

        (Feature::EffectsGraphicEQ, p) if p == GraphicEq::Enable as u32 => id::EQ_ENABLE,
        (Feature::EffectsGraphicEQ, p) if p == GraphicEq::PreampGain as u32 => id::EQ_PREAMP,
        (Feature::EffectsGraphicEQ, p) => {
            let band = p.checked_sub(GraphicEq::Band0Gain as u32)?;
            if band > 9 {
                return None;
            }
            id::EQ_BAND0 + band as u8
        }

        _ => return None,
    };
    Some(id)
}

/// Map a `(Feature, param)` pair to its selector byte -- the write-path
/// counterpart of [`id_of`].
pub fn selector(feature: Feature, param: u32) -> Option<u8> {
    id_of(feature, param).map(selector_of)
}

/// How a parameter value is encoded on the wire.
///
/// Booleans ride the same big-endian float field as everything else, as
/// `0.0` / `1.0`.
#[derive(Debug, Clone, Copy)]
pub enum Value {
    Float(f32),
    Bool(bool),
}

impl Value {
    /// The `f32` this value carries on the wire.
    fn as_f32(self) -> f32 {
        match self {
            Value::Float(v) => v,
            Value::Bool(v) => f32::from(u8::from(v)),
        }
    }
}

/// Build a `0x20` SET_PARAM report: 64 bytes, big-endian `f32` value.
///
/// See `reverse/e5-control-protocol.md` for the byte layout.
pub fn encode_set_param(param: u8, value: f32) -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_SET_PARAM;
    r[1..7].copy_from_slice(&SET_PARAM_HDR);
    r[7] = param;
    r[8..10].copy_from_slice(&SET_PARAM_TAIL);
    r[10..14].copy_from_slice(&value.to_be_bytes());
    r
}

/// Build a `0x26` commit report for a parameter id: `26 01 96 <id>`, the
/// commit half of a "set value, then commit it" pair.
///
/// Windows sends one after every `0x20` write. Whether the E5 requires it
/// is unproven -- a bass write lands audibly without one -- so
/// [`Transport::set_commit`] can turn it off for A/B testing.
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

/// Build a `0x26` GET_PARAM query report for a raw parameter id in a
/// module.
///
/// `26 01 <module> <id>` goes out as a normal SET_REPORT; the answer
/// arrives on interrupt IN `0x83` as
/// `00 26 01 00 <module> <id> <f32 big-endian>`. `id` is the **raw** id
/// (`0x19` for bass level), not `id << 1`.
pub fn encode_get_param_in(module: u8, id: u8) -> [u8; REPORT_LEN] {
    let mut r = [0u8; REPORT_LEN];
    r[0] = OP_GET_PARAM;
    r[1] = 0x01;
    r[2] = module;
    r[3] = id;
    r
}

/// Build a GET_PARAM query for the playback module, which is the only one
/// this crate drives.
pub fn encode_get_param(id: u8) -> [u8; REPORT_LEN] {
    encode_get_param_in(module::PLAYBACK, id)
}

/// Build the `0x23 0x23` SBX master enable/disable report: `23 23 01 01`
/// to enable, `23 23 01 00` to disable.
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
/// endpoint) for the master state it carries at offset 4:
/// `00 23 24 00 01 00 01` for on, `00 23 24 00 00 00 01` for off.
///
/// This is the SBX master read. It answers both the commit that follows a
/// write and a bare `23 24 00` sent on its own.
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

/// Serialize one parameter write into its on-the-wire report.
///
/// Kept free-standing so it can be unit-tested without a device present.
/// Fails when the parameter has no selector.
pub fn encode(feature: Feature, param: u32, value: Value) -> Result<[u8; REPORT_LEN]> {
    let sel = selector(feature, param).ok_or(Error::Unsupported { feature, param })?;
    Ok(encode_set_param(sel, value.as_f32()))
}

/// An open handle to the device's HID control interface.
pub struct Transport {
    handle: Option<rusb::DeviceHandle<rusb::GlobalContext>>,
    dry_run: bool,
}

impl Transport {
    /// Open the first E5 found, claiming its HID control interface.
    ///
    /// If `dry_run` is set -- explicitly, or via `SBX_E5_DRY_RUN` -- no
    /// device is opened and packets are printed instead of sent.
    pub fn open(dry_run: bool) -> Result<Self> {
        let dry_run = dry_run || std::env::var_os("SBX_E5_DRY_RUN").is_some();
        if dry_run {
            return Ok(Self {
                handle: None,
                dry_run,
            });
        }

        let handle =
            rusb::open_device_with_vid_pid(VID_CREATIVE, PID_E5).ok_or(Error::DeviceNotFound)?;

        // snd-usb-audio binds the audio interfaces; detaching only the
        // control interface leaves playback running.
        let _ = handle.set_auto_detach_kernel_driver(true);
        handle.claim_interface(HID_INTERFACE)?;

        Ok(Self {
            handle: Some(handle),
            dry_run,
        })
    }

    /// True if this transport only prints packets.
    pub fn is_dry_run(&self) -> bool {
        self.dry_run
    }

    /// Build and send one parameter write, followed by its commit.
    fn send(&mut self, feature: Feature, param: u32, value: Value) -> Result<()> {
        let id = id_of(feature, param).ok_or(Error::Unsupported { feature, param })?;
        let payload = encode_set_param(selector_of(id), value.as_f32());

        if self.dry_run {
            println!(
                "SET feature=0x{:08X} param={} value={:?}\n    {:02X?}",
                feature as u32, param, value, payload
            );
        }
        self.write_raw(&payload)?;

        // Mirror what Windows does: every value write is followed by a
        // commit for the same id.
        let commit = encode_commit(id);
        if self.dry_run {
            println!("    commit {:02X?}", &commit[..4]);
        }
        self.write_raw(&commit)
    }

    /// Send an already-encoded report over the control pipe.
    fn write_raw(&mut self, payload: &[u8]) -> Result<()> {
        if self.dry_run {
            println!("RAW {payload:02X?}");
            return Ok(());
        }

        let handle = self.handle.as_mut().ok_or(Error::DeviceNotFound)?;
        handle.write_control(
            REQ_TYPE_SET,
            HID_SET_REPORT,
            OUT_REPORT,
            u16::from(HID_INTERFACE),
            payload,
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

    /// Send a raw `0x26` GET_PARAM query and read back the response.
    ///
    /// `id` is the raw parameter id, not the `id << 1` write selector.
    pub fn get_param_raw(&mut self, id: u8) -> Result<f32> {
        self.get_param_raw_in(module::PLAYBACK, id)
    }

    /// Send a raw `0x26` GET_PARAM query against a specific module.
    ///
    /// Reads are non-destructive, which is what makes this safe to point at
    /// a module we do not otherwise drive.
    pub fn get_param_raw_in(&mut self, module: u8, id: u8) -> Result<f32> {
        let query = encode_get_param_in(module, id);

        if self.dry_run {
            println!("GET module=0x{module:02X} id=0x{id:02X} (dry run -> 0.0)\n    {query:02X?}");
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
        let id = id_of(feature, param).ok_or(Error::Unsupported { feature, param })?;
        self.get_param_raw(id)
    }

    /// Write the SBX master switch: `0x23 0x23` enable/disable followed by
    /// the `0x23 0x24` commit that always accompanies it.
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
    /// A bare `0x23 0x24` with no preceding `0x23 0x23` write answers with
    /// the current state, on the same response shape
    /// [`Self::set_sbx_master`] reads.
    pub fn get_sbx_master(&mut self) -> Result<bool> {
        let query = encode_master_commit();

        if self.dry_run {
            println!("GET sbx-master (dry run -> false)\n    {query:02X?}");
            return Ok(false);
        }

        self.write_raw(&query)?;
        self.read_matching(0, decode_master_commit_response)
    }

    /// Send an arbitrary query report and return the first response that
    /// echoes its opcode and subcommand.
    ///
    /// This is the discovery primitive behind `sbx-e5 probe`. It exists
    /// because the read path is non-destructive: a query the device does
    /// not implement is answered with the unsupported marker rather than
    /// doing anything, so the subcommand space can be swept safely.
    ///
    /// `Ok(None)` means the endpoint drained without a matching answer.
    pub fn query_raw(&mut self, op: u8, sub: u8) -> Result<Option<[u8; READ_LEN]>> {
        let mut query = [0u8; REPORT_LEN];
        query[0] = op;
        query[1] = sub;

        if self.dry_run {
            println!("QUERY {op:02X} {sub:02X} (dry run -> no response)");
            return Ok(None);
        }

        self.write_raw(&query)?;
        match self.read_matching(0, |buf| {
            (buf.len() >= READ_LEN && buf[1] == op && buf[2] == sub).then(|| {
                let mut out = [0u8; READ_LEN];
                out.copy_from_slice(&buf[..READ_LEN]);
                out
            })
        }) {
            Ok(buf) => Ok(Some(buf)),
            Err(Error::UnexpectedResponse { .. }) => Ok(None),
            Err(e) => Err(e),
        }
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
            let _ = h.release_interface(HID_INTERFACE);
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

    /// Bass level, `0x32`.
    const SEL_BASS: u8 = selector_of(id::BASS_LEVEL);
    /// Surround level, `0x02`.
    const SEL_SURROUND: u8 = selector_of(id::SURROUND_LEVEL);

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
        // report[7] = id << 1.
        assert_eq!(selector_of(id::BASS_LEVEL), 0x32);
        assert_eq!(selector_of(id::SURROUND_LEVEL), 0x02);
        assert_eq!(selector_of(id::CRYSTALIZER_LEVEL), 0x10);
        assert_eq!(selector_of(id::BASS_ENABLE), 0x30);
    }

    #[test]
    fn smart_volume_modes_round_trip_through_their_wire_values() {
        use crate::proto::SmartVolumeMode;

        // Declaration order is the wire order; `Normal` is the stock value
        // every shipped profile carries.
        assert_eq!(SmartVolumeMode::Normal.value(), 0.0);
        assert_eq!(SmartVolumeMode::Loud.value(), 1.0);
        assert_eq!(SmartVolumeMode::Night.value(), 2.0);
        assert_eq!(SmartVolumeMode::default(), SmartVolumeMode::Normal);

        for mode in SmartVolumeMode::ALL {
            assert_eq!(SmartVolumeMode::from_value(mode.value()), Some(mode));
            assert_eq!(mode.name().parse(), Ok(mode));
        }

        // The mode rides the same float path as every level, so a value
        // that comes back a hair off still has to resolve.
        assert_eq!(
            SmartVolumeMode::from_value(1.999),
            Some(SmartVolumeMode::Night)
        );
        assert_eq!(SmartVolumeMode::from_value(3.0), None);
        assert_eq!(SmartVolumeMode::from_value(-1.0), None);
        assert!("quiet".parse::<SmartVolumeMode>().is_err());
    }

    #[test]
    fn smart_volume_mode_encodes_on_its_own_selector() {
        use crate::proto::{SmartVolume, SmartVolumeMode};

        let id = id_of(Feature::EffectsSmartVolume, SmartVolume::Mode as u32)
            .expect("smart volume mode has a selector");
        assert_eq!(id, id::SMART_VOLUME_MODE);
        // Distinct from the enable and level either side of it, so picking a
        // profile cannot be mistaken for switching the effect.
        assert_ne!(id, id::SMART_VOLUME_ENABLE);
        assert_ne!(id, id::SMART_VOLUME_LEVEL);

        let r = encode_set_param(selector_of(id), SmartVolumeMode::Night.value());
        assert_eq!(prefix(&r, 14), "2000160ad502080c209640000000");
    }

    #[test]
    fn eq_bands_map_to_consecutive_selectors() {
        use crate::proto::GraphicEq;
        for band in 0..10u32 {
            let param = GraphicEq::Band0Gain as u32 + band;
            let sel = selector(Feature::EffectsGraphicEQ, param).unwrap();
            assert_eq!(sel, selector_of(id::EQ_BAND0 + band as u8));
        }
        // Band 10 does not exist.
        let past_end = GraphicEq::Band0Gain as u32 + 10;
        assert!(selector(Feature::EffectsGraphicEQ, past_end).is_none());
    }

    /// Reads address the raw id, writes the doubled selector. Mixing the two
    /// up would silently talk to the wrong parameter, so pin both.
    #[test]
    fn reads_use_the_raw_id_and_writes_the_doubled_selector() {
        use crate::proto::XBass;
        assert_eq!(
            id_of(Feature::EffectsXBass, XBass::Strength as u32),
            Some(id::BASS_LEVEL)
        );
        assert_eq!(
            selector(Feature::EffectsXBass, XBass::Strength as u32),
            Some(0x32)
        );
        assert_eq!(
            selector(Feature::EffectsXBass, XBass::Enable as u32),
            Some(0x30)
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
    fn encode_routes_effects_to_their_selectors() {
        let bass = encode(
            Feature::EffectsXBass,
            crate::proto::XBass::Strength as u32,
            Value::Float(0.5),
        )
        .unwrap();
        assert_eq!(bass[7], SEL_BASS);

        let surround = encode(
            Feature::EffectsSimpleSurround,
            crate::proto::SimpleSurround::Level as u32,
            Value::Float(0.5),
        )
        .unwrap();
        assert_eq!(surround[7], SEL_SURROUND);

        let crystalizer = encode(
            Feature::EffectsCrystalizer,
            crate::proto::Crystalizer::Level as u32,
            Value::Float(0.5),
        )
        .unwrap();
        assert_eq!(crystalizer[7], 0x10);
    }

    #[test]
    fn parameters_with_no_id_are_rejected_not_guessed() {
        // Bass management has no id in the table, so there is no selector
        // to build and the write must be refused rather than guessed at.
        let e = encode(
            Feature::EffectsBassManagement,
            crate::proto::BassManagement::CrossOverFreqHz as u32,
            Value::Float(80.0),
        );
        assert!(matches!(e, Err(Error::Unsupported { .. })));
    }

    /// The voice-input module is addressable on the read path: the Windows
    /// panel queries `26 01 95 06` in `captures/read.json`.
    #[test]
    fn get_param_can_address_another_module() {
        let q = encode_get_param_in(module::VOICE_INPUT, 0x06);
        assert_eq!(&q[..4], &[0x26, 0x01, 0x95, 0x06]);
        // The default helper still targets playback.
        assert_eq!(encode_get_param(0x19)[2], module::PLAYBACK);
    }

    #[test]
    fn eq_preamp_maps_to_its_own_id() {
        let id = id_of(
            Feature::EffectsGraphicEQ,
            crate::proto::GraphicEq::PreampGain as u32,
        );
        assert_eq!(id, Some(id::EQ_PREAMP));
        // The preamp must not collide with band 0.
        assert_ne!(id::EQ_PREAMP, id::EQ_BAND0);
    }

    /// The crossover is the one parameter that is not a normalized level:
    /// it carries a frequency in Hz on the same big-endian float field.
    #[test]
    fn bass_crossover_encodes_hz_at_its_own_selector() {
        let r = encode(
            Feature::EffectsXBass,
            crate::proto::XBass::FreqHz as u32,
            Value::Float(80.0),
        )
        .unwrap();
        assert_eq!(r[7], selector_of(0x17), "crossover selector is 0x17 << 1");
        assert_eq!(&r[10..14], &80.0f32.to_be_bytes());
    }

    /// Booleans ride the same big-endian float field as levels, as 1.0 / 0.0.
    #[test]
    fn bools_encode_as_floats() {
        let on = encode(
            Feature::EffectsXBass,
            crate::proto::XBass::Enable as u32,
            Value::Bool(true),
        )
        .unwrap();
        assert_eq!(&on[10..14], &1.0f32.to_be_bytes());

        let off = encode(
            Feature::EffectsXBass,
            crate::proto::XBass::Enable as u32,
            Value::Bool(false),
        )
        .unwrap();
        assert_eq!(&off[10..14], &0.0f32.to_be_bytes());
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

    /// `id::TABLE` is what `sbx-e5 selectors` prints, and it is maintained by
    /// hand alongside the constants. Pin it so a named id cannot be added
    /// without being listed.
    ///
    /// Note this cannot be a scan of `0x00..=BASS_LEVEL`: ids `0x15` and
    /// `0x16` are bass management, which the E5 has no hardware path for,
    /// so they are identified but deliberately absent from the table.
    #[test]
    fn selector_table_lists_every_named_id_exactly_once() {
        let named = [
            id::SURROUND_ENABLE,
            id::SURROUND_LEVEL,
            id::DIALOG_PLUS_ENABLE,
            id::DIALOG_PLUS_LEVEL,
            id::SMART_VOLUME_ENABLE,
            id::SMART_VOLUME_LEVEL,
            id::SMART_VOLUME_MODE,
            id::CRYSTALIZER_ENABLE,
            id::CRYSTALIZER_LEVEL,
            id::EQ_ENABLE,
            id::EQ_PREAMP,
            id::BASS_CROSSOVER_HZ,
            id::BASS_ENABLE,
            id::BASS_LEVEL,
        ];
        let listed: Vec<u8> = id::TABLE.iter().map(|&(_, id)| id).collect();

        assert_eq!(
            listed.len(),
            named.len(),
            "id::TABLE has an entry that is not a named constant, or is missing one"
        );
        for want in named {
            assert_eq!(
                listed.iter().filter(|&&got| got == want).count(),
                1,
                "id 0x{want:02x} should appear exactly once in id::TABLE"
            );
        }

        // The EQ bands are generated by the printer, not listed here.
        for band_id in id::EQ_BAND0..id::EQ_BAND0 + 10 {
            assert!(
                !listed.contains(&band_id),
                "id 0x{band_id:02x} belongs to an EQ band and is generated, not listed"
            );
        }
    }

    /// Each name in the table should describe the id it is paired with;
    /// a copy-paste slip that duplicated a name would print two identical
    /// rows and mislabel a parameter.
    #[test]
    fn selector_table_names_are_unique() {
        let mut names: Vec<&str> = id::TABLE.iter().map(|&(n, _)| n).collect();
        names.sort_unstable();
        let before = names.len();
        names.dedup();
        assert_eq!(before, names.len(), "duplicate name in id::TABLE");
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
