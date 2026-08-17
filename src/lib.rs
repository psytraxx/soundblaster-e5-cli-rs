//! Userspace control for the Creative Sound Blaster E5 on Linux.
//!
//! The E5 exposes its audio streams as standard USB Audio Class endpoints,
//! which ALSA already drives. What ALSA does *not* expose is Creative's
//! proprietary DSP: SBX Surround, Crystalizer, Bass, Dialog Plus, Smart
//! Volume and the 10-band EQ. Those live behind a vendor protocol addressed
//! as a `(Feature, param, value)` triple.
//!
//! [`proto`] holds the addressing constants; [`transport`] turns a triple
//! into bytes on the wire.

pub mod proto;
pub mod transport;
pub mod tui;

use proto::{Crystalizer, DialogPlus, Feature, SimpleSurround, SmartVolume, XBass};
use transport::Transport;

/// Errors from talking to the device.
#[derive(Debug)]
pub enum Error {
    /// No E5 present on any USB bus.
    DeviceNotFound,
    /// The kernel refused access; usually a missing udev rule.
    AccessDenied,
    /// Underlying USB failure.
    Usb(rusb::Error),
    /// A level argument was outside `0.0..=1.0`.
    OutOfRange(f32),
    /// The parameter has no known wire encoding, and guessing a selector
    /// could set something else entirely.
    Unsupported { feature: Feature, param: u32 },
    /// Terminal I/O failed while running the interactive UI.
    Io(std::io::Error),
    /// A read query got a response that didn't match the expected shape or
    /// echoed a different id than the one queried.
    UnexpectedResponse { id: u8 },
}

impl From<std::io::Error> for Error {
    fn from(e: std::io::Error) -> Self {
        Error::Io(e)
    }
}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Error::DeviceNotFound => write!(f, "no Sound Blaster E5 found (041e:323c)"),
            Error::AccessDenied => write!(
                f,
                "permission denied opening the E5; install the udev rule (see README)"
            ),
            Error::Usb(e) => write!(f, "usb error: {e}"),
            Error::OutOfRange(v) => write!(f, "level {v} outside 0.0..=1.0"),
            Error::Io(e) => write!(f, "terminal error: {e}"),
            Error::Unsupported { feature, param } => write!(
                f,
                "{feature:?} param {param} has no id in the selector table \
                 (see `sbx-e5 selectors`)"
            ),
            Error::UnexpectedResponse { id } => write!(
                f,
                "read query for id 0x{id:02x} got an unexpected or mismatched response"
            ),
        }
    }
}

impl std::error::Error for Error {}

impl From<rusb::Error> for Error {
    fn from(e: rusb::Error) -> Self {
        match e {
            rusb::Error::Access => Error::AccessDenied,
            rusb::Error::NoDevice => Error::DeviceNotFound,
            other => Error::Usb(other),
        }
    }
}

pub type Result<T> = std::result::Result<T, Error>;

/// A connected Sound Blaster E5.
pub struct SoundBlasterE5 {
    transport: Transport,
}

impl SoundBlasterE5 {
    /// Find and open the first E5 on the system.
    ///
    /// With `dry_run` (or `SBX_E5_DRY_RUN` set) no device is opened and
    /// every write is printed instead of sent.
    pub fn open(dry_run: bool) -> Result<Self> {
        Ok(Self {
            transport: Transport::open(dry_run)?,
        })
    }

    /// True if this handle only prints packets.
    pub fn is_dry_run(&self) -> bool {
        self.transport.is_dry_run()
    }

    /// Set a normalized effect level, `0.0..=1.0`.
    fn set_level(&mut self, feature: Feature, param: u32, level: f32) -> Result<()> {
        if !(0.0..=1.0).contains(&level) {
            return Err(Error::OutOfRange(level));
        }
        self.transport.set_float(feature, param, level)
    }

    fn set_enable(&mut self, feature: Feature, param: u32, on: bool) -> Result<()> {
        self.transport.set_bool(feature, param, on)
    }

    /// Set any normalized level by `(feature, param)`.
    ///
    /// The generic form behind the named setters; the TUI drives its rows
    /// through this rather than matching on every effect.
    pub fn set_level_raw(&mut self, feature: Feature, param: u32, level: f32) -> Result<()> {
        self.set_level(feature, param, level)
    }

    /// Set any boolean parameter by `(feature, param)`.
    pub fn set_enable_raw(&mut self, feature: Feature, param: u32, on: bool) -> Result<()> {
        self.set_enable(feature, param, on)
    }

    /// Read any normalized level or boolean by `(feature, param)`.
    ///
    /// Booleans ride the same float field as `0.0`/`1.0`, same as writes.
    pub fn get_level_raw(&mut self, feature: Feature, param: u32) -> Result<f32> {
        self.transport.get_float(feature, param)
    }

    /// Toggle the SBX master switch.
    ///
    /// Sends `23 23 01 <flag>` followed by the `23 24 00` commit, and
    /// returns the state the device actually reports afterward (from the
    /// commit's own response) rather than assuming the write took.
    pub fn set_sbx_master(&mut self, on: bool) -> Result<bool> {
        self.transport.set_sbx_master(on)
    }

    /// Read the SBX master switch without changing it.
    pub fn get_sbx_master(&mut self) -> Result<bool> {
        self.transport.get_sbx_master()
    }

    /// True when `feature`/`param` has a known wire encoding.
    ///
    /// Callers use this to skip an optional write rather than fail the whole
    /// command. Parameters outside the id table -- the microphone controls,
    /// say -- return `false`.
    pub fn supports(&self, feature: Feature, param: u32) -> bool {
        transport::selector(feature, param).is_some()
    }

    // ---- SBX Bass -------------------------------------------------------

    /// Enable or disable SBX Bass.
    pub fn set_bass_enabled(&mut self, on: bool) -> Result<()> {
        self.set_enable(Feature::EffectsXBass, XBass::Enable as u32, on)
    }

    /// Set bass strength, `0.0..=1.0`. Creative's own default profile uses `0.30`.
    pub fn set_bass(&mut self, level: f32) -> Result<()> {
        self.set_level(Feature::EffectsXBass, XBass::Strength as u32, level)
    }

    /// Set the bass crossover frequency in Hz. Stock profiles use `80.0`.
    pub fn set_bass_crossover(&mut self, hz: f32) -> Result<()> {
        self.transport
            .set_float(Feature::EffectsXBass, XBass::FreqHz as u32, hz)
    }

    // ---- Other SBX effects ---------------------------------------------

    /// Enable or disable SBX Surround.
    pub fn set_surround_enabled(&mut self, on: bool) -> Result<()> {
        self.set_enable(
            Feature::EffectsSimpleSurround,
            SimpleSurround::Enable as u32,
            on,
        )
    }

    /// Set surround level, `0.0..=1.0`. Stock default is `0.12`.
    pub fn set_surround(&mut self, level: f32) -> Result<()> {
        self.set_level(
            Feature::EffectsSimpleSurround,
            SimpleSurround::Level as u32,
            level,
        )
    }

    /// Enable or disable SBX Crystalizer.
    pub fn set_crystalizer_enabled(&mut self, on: bool) -> Result<()> {
        self.set_enable(Feature::EffectsCrystalizer, Crystalizer::Enable as u32, on)
    }

    /// Set crystalizer level, `0.0..=1.0`. Stock default is `0.50`.
    pub fn set_crystalizer(&mut self, level: f32) -> Result<()> {
        self.set_level(
            Feature::EffectsCrystalizer,
            Crystalizer::Level as u32,
            level,
        )
    }

    /// Enable or disable SBX Dialog Plus.
    pub fn set_dialog_plus_enabled(&mut self, on: bool) -> Result<()> {
        self.set_enable(Feature::EffectsDialogPlus, DialogPlus::Enable as u32, on)
    }

    /// Set Dialog Plus strength, `0.0..=1.0`.
    pub fn set_dialog_plus(&mut self, level: f32) -> Result<()> {
        self.set_level(
            Feature::EffectsDialogPlus,
            DialogPlus::Strength as u32,
            level,
        )
    }

    /// Enable or disable SBX Smart Volume.
    pub fn set_smart_volume_enabled(&mut self, on: bool) -> Result<()> {
        self.set_enable(Feature::EffectsSmartVolume, SmartVolume::Enable as u32, on)
    }

    /// Set Smart Volume strength, `0.0..=1.0`.
    pub fn set_smart_volume(&mut self, level: f32) -> Result<()> {
        self.set_level(
            Feature::EffectsSmartVolume,
            SmartVolume::Strength as u32,
            level,
        )
    }

    // ---- Graphic EQ (treble) -------------------------------------------

    /// Enable or disable the 10-band graphic EQ.
    pub fn set_eq_enabled(&mut self, on: bool) -> Result<()> {
        self.set_enable(
            Feature::EffectsGraphicEQ,
            proto::GraphicEq::Enable as u32,
            on,
        )
    }

    /// Set the gain of one EQ band, `band` in `0..10`, `gain_db` typically `-12.0..=12.0`.
    ///
    /// The device has no separate "treble" control: the Windows GUI's treble
    /// slider drives the upper EQ bands. See [`Self::set_treble`].
    pub fn set_eq_band(&mut self, band: u8, gain_db: f32) -> Result<()> {
        let param = proto::GraphicEq::Band0Gain as u32 + u32::from(band.min(9));
        self.transport
            .set_float(Feature::EffectsGraphicEQ, param, gain_db)
    }

    /// Convenience treble shelf: apply `gain_db` to the top four EQ bands.
    ///
    /// This mirrors what the Creative control panel does -- there is no
    /// dedicated treble parameter in the protocol.
    pub fn set_treble(&mut self, gain_db: f32) -> Result<()> {
        self.set_eq_enabled(true)?;
        for band in 6..10 {
            self.set_eq_band(band, gain_db)?;
        }
        Ok(())
    }
}
