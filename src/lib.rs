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

use proto::{
    Crystalizer, DialogPlus, Feature, SimpleSurround, SmartVolume, SmartVolumeMode, XBass,
};
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
    /// A numeric argument was outside the range the parameter accepts:
    /// the value, then the inclusive bounds it had to fall between.
    OutOfRange { value: f32, lo: f32, hi: f32 },
    /// An EQ band index was outside `0..=9`.
    NoSuchBand(u8),
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
            Error::OutOfRange { value, lo, hi } => {
                write!(f, "value {value} outside {lo}..={hi}")
            }
            Error::NoSuchBand(band) => {
                write!(f, "no EQ band {band}; the equalizer has bands 0..=9")
            }
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

/// Inclusive dB bounds accepted for an EQ band gain and for the treble
/// shelf built on top of it.
///
/// The E5's own answer, read off the device: it reports its ranges through
/// the `23 2a` parameter-info query, and gives `-12.0 .. 12.0` for an EQ
/// band. Creative's cross-product Android library declares a wider
/// `-24 .. 24` for the same parameter; the device's own report wins.
pub const EQ_GAIN_DB: (f32, f32) = (-12.0, 12.0);

/// Inclusive dB bounds accepted for the EQ preamp gain.
///
/// Half the band range, and separately reported by the device: `23 2a`
/// gives `-6.0 .. 6.0` step `1.0` for the preamp. The preamp scales the
/// whole curve, so pulling it down is what makes room for boosted bands.
pub const EQ_PREAMP_GAIN_DB: (f32, f32) = (-6.0, 6.0);

/// Inclusive bounds in Hz accepted for the SBX Bass crossover frequency.
///
/// The E5 reports `10.0 .. 300.0` step `1.0` through `23 2a`, and defaults
/// to `80.0`. Creative's Android library declares a wider `10 .. 1000` for
/// the shared parameter; the device's own report wins.
pub const BASS_CROSSOVER_HZ: (f32, f32) = (10.0, 300.0);

/// The EQ bands the treble shelf drives -- the top four, matching what the
/// Creative control panel's treble slider moves.
pub const TREBLE_BANDS: std::ops::Range<u8> = 6..10;

/// Reject a value outside its parameter's inclusive range, before any write
/// goes out. NaN fails too: it compares false against both bounds.
fn check_range(value: f32, lo: f32, hi: f32) -> Result<()> {
    if !(lo..=hi).contains(&value) {
        return Err(Error::OutOfRange { value, lo, hi });
    }
    Ok(())
}

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
        check_range(level, 0.0, 1.0)?;
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

    /// Send a bare `<op> <sub>` query and return the device's answer, or
    /// `None` if nothing matching came back.
    ///
    /// Discovery only -- reads are non-destructive, so this is how an
    /// unmapped subcommand gets identified without writing anything. See
    /// `sbx-e5 probe`.
    pub fn query_raw(&mut self, op: u8, sub: u8) -> Result<Option<[u8; 16]>> {
        self.transport.query_raw(op, sub)
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

    /// Set the bass crossover frequency in Hz. The device default is `80.0`.
    ///
    /// Unlike every other parameter here this one is *not* normalized: it
    /// carries a frequency in Hz on the same big-endian float field.
    ///
    /// The range is the device's own, read back off it. The read side is
    /// capture-confirmed -- the device returned `80.0` for this id -- but
    /// the write has never been exercised on hardware.
    pub fn set_bass_crossover(&mut self, hz: f32) -> Result<()> {
        check_range(hz, BASS_CROSSOVER_HZ.0, BASS_CROSSOVER_HZ.1)?;
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

    /// Select the Smart Volume profile.
    ///
    /// Unlike the levels either side of it this is an enumerated choice, so
    /// it bypasses [`Self::set_level`]'s `0.0..=1.0` check -- `Night` writes
    /// `2.0`.
    pub fn set_smart_volume_mode(&mut self, mode: SmartVolumeMode) -> Result<()> {
        self.transport.set_float(
            Feature::EffectsSmartVolume,
            SmartVolume::Mode as u32,
            mode.value(),
        )
    }

    /// Read back the Smart Volume profile.
    ///
    /// A value the device reports that is not one of the three known modes
    /// is [`Error::UnexpectedResponse`] rather than a silent `Normal`.
    pub fn get_smart_volume_mode(&mut self) -> Result<SmartVolumeMode> {
        let raw = self.get_level_raw(Feature::EffectsSmartVolume, SmartVolume::Mode as u32)?;
        SmartVolumeMode::from_value(raw).ok_or(Error::UnexpectedResponse {
            id: transport::id::SMART_VOLUME_MODE,
        })
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

    /// Set the EQ preamp gain in dB, within [`EQ_PREAMP_GAIN_DB`].
    ///
    /// The preamp scales the whole curve before the bands are applied.
    /// Pulling it down is how you make headroom for boosted bands without
    /// clipping the DSP, so it is the companion to [`Self::set_eq_band`]
    /// rather than an alternative to it.
    pub fn set_eq_preamp(&mut self, gain_db: f32) -> Result<()> {
        let (lo, hi) = EQ_PREAMP_GAIN_DB;
        check_range(gain_db, lo, hi)?;
        self.transport.set_float(
            Feature::EffectsGraphicEQ,
            proto::GraphicEq::PreampGain as u32,
            gain_db,
        )
    }

    /// Read the EQ preamp gain in dB.
    pub fn get_eq_preamp(&mut self) -> Result<f32> {
        self.get_level_raw(
            Feature::EffectsGraphicEQ,
            proto::GraphicEq::PreampGain as u32,
        )
    }

    /// Set the gain of one EQ band, `band` in `0..=9`, `gain_db` in
    /// [`EQ_GAIN_DB`].
    ///
    /// The device has no separate "treble" control: the Windows GUI's treble
    /// slider drives the upper EQ bands. See [`Self::set_treble`].
    pub fn set_eq_band(&mut self, band: u8, gain_db: f32) -> Result<()> {
        if band > 9 {
            return Err(Error::NoSuchBand(band));
        }
        let (lo, hi) = EQ_GAIN_DB;
        check_range(gain_db, lo, hi)?;
        let param = proto::GraphicEq::Band0Gain as u32 + u32::from(band);
        self.transport
            .set_float(Feature::EffectsGraphicEQ, param, gain_db)
    }

    /// Convenience treble shelf: apply `gain_db` to the top four EQ bands.
    ///
    /// This mirrors what the Creative control panel does -- there is no
    /// dedicated treble parameter in the protocol.
    pub fn set_treble(&mut self, gain_db: f32) -> Result<()> {
        // Check once up front: this writes four bands, and a gain rejected
        // on the way through would leave the EQ half-applied.
        let (lo, hi) = EQ_GAIN_DB;
        check_range(gain_db, lo, hi)?;

        self.set_eq_enabled(true)?;
        for band in TREBLE_BANDS {
            self.set_eq_band(band, gain_db)?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn range_check_accepts_the_endpoints() {
        assert!(check_range(0.0, 0.0, 1.0).is_ok());
        assert!(check_range(1.0, 0.0, 1.0).is_ok());
        let (lo, hi) = EQ_GAIN_DB;
        assert!(check_range(lo, lo, hi).is_ok());
        assert!(check_range(hi, lo, hi).is_ok());
    }

    #[test]
    fn range_check_rejects_values_past_either_end() {
        assert!(matches!(
            check_range(1.5, 0.0, 1.0),
            Err(Error::OutOfRange { .. })
        ));
        assert!(matches!(
            check_range(-0.001, 0.0, 1.0),
            Err(Error::OutOfRange { .. })
        ));
    }

    /// NaN passes neither comparison, so it must be rejected rather than
    /// reaching the device as a garbage float.
    #[test]
    fn range_check_rejects_nan() {
        assert!(matches!(
            check_range(f32::NAN, 0.0, 1.0),
            Err(Error::OutOfRange { .. })
        ));
        assert!(matches!(
            check_range(f32::INFINITY, 0.0, 1.0),
            Err(Error::OutOfRange { .. })
        ));
    }

    /// The treble shelf drives real bands; if it ever ran past band 9 the
    /// writes would address whatever id follows the EQ block.
    #[test]
    fn treble_bands_are_real_eq_bands() {
        for band in TREBLE_BANDS {
            assert!(band <= 9, "treble would write band {band}, past the EQ");
        }
        assert_eq!(TREBLE_BANDS.len(), 4);
    }
}
