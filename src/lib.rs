//! Userspace control for the Creative Sound Blaster E5 on Linux.
//!
//! The E5 exposes its audio streams as standard USB Audio Class endpoints,
//! which ALSA already drives. What ALSA does *not* expose is Creative's
//! proprietary DSP: SBX Surround, Crystalizer, Bass, Dialog Plus, Smart
//! Volume and the 10-band EQ. Those live behind a vendor protocol addressed
//! as a `(Feature, param, value)` triple.
//!
//! The constants in [`proto`] were recovered from the Windows driver's
//! `Interop.CtSndCr.dll` type metadata and are exact. The *transport* --
//! how a triple becomes bytes on the wire -- is the part still being
//! established; see [`transport`].

pub mod proto;
pub mod transport;

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

    /// Set Dialog Plus strength, `0.0..=1.0`.
    pub fn set_dialog_plus(&mut self, level: f32) -> Result<()> {
        self.set_level(
            Feature::EffectsDialogPlus,
            DialogPlus::Strength as u32,
            level,
        )
    }

    /// Set Smart Volume strength, `0.0..=1.0`.
    pub fn set_smart_volume(&mut self, level: f32) -> Result<()> {
        self.set_level(
            Feature::EffectsSmartVolume,
            SmartVolume::Strength as u32,
            level,
        )
    }

    /// Master switch for the whole SBX suite.
    pub fn set_sbx_master(&mut self, on: bool) -> Result<()> {
        self.set_enable(
            Feature::EfxMasterControl,
            proto::EfxMaster::SBXMasterOnOff as u32,
            on,
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
