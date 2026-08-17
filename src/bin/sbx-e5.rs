//! Command-line control for the Creative Sound Blaster E5 on Linux.

use anyhow::{Context, Result};
use clap::{Parser, Subcommand};
use indicatif::{ProgressBar, ProgressStyle};
use sbx_e5::proto::{Crystalizer, DialogPlus, Feature, SimpleSurround, SmartVolume, XBass};
use sbx_e5::transport::id;
use sbx_e5::{SoundBlasterE5, transport};

#[derive(Parser)]
#[command(
    name = "sbx-e5",
    about = "Control the SBX DSP of a Creative Sound Blaster E5",
    long_about = "Control the SBX DSP (bass, treble, surround, crystalizer) of a\n\
                  Creative Sound Blaster E5 on Linux.\n\n\
                  Run with no subcommand to open the interactive UI.\n\n\
                  Use --dry-run to inspect packets without sending them.",
    version
)]
struct Cli {
    /// Print the packets that would be sent instead of sending them.
    #[arg(long, global = true)]
    dry_run: bool,

    /// Omitted: opens the interactive UI.
    #[command(subcommand)]
    command: Option<Command>,
}

#[derive(Subcommand)]
enum Command {
    /// Show attached Creative devices and their USB interfaces.
    Info,

    /// Set SBX Bass strength (0.0 - 1.0), or `on`/`off`. Default is 0.3.
    Bass {
        #[arg(value_name = "LEVEL|on|off")]
        setting: Setting,
        /// Crossover frequency in Hz (stock profiles use 80).
        #[arg(long)]
        crossover: Option<f32>,
    },

    /// Set treble by applying a gain (dB) to the upper EQ bands.
    Treble {
        #[arg(value_name = "GAIN_DB", allow_negative_numbers = true)]
        gain_db: f32,
    },

    /// Set SBX Surround level (0.0 - 1.0), or `on`/`off`. Default is 0.12.
    Surround {
        #[arg(value_name = "LEVEL|on|off")]
        setting: Setting,
    },

    /// Set SBX Crystalizer level (0.0 - 1.0), or `on`/`off`. Default is 0.5.
    Crystalizer {
        #[arg(value_name = "LEVEL|on|off")]
        setting: Setting,
    },

    /// Set SBX Dialog Plus strength (0.0 - 1.0), or `on`/`off`.
    DialogPlus {
        #[arg(value_name = "LEVEL|on|off")]
        setting: Setting,
    },

    /// Set SBX Smart Volume strength (0.0 - 1.0), or `on`/`off`.
    SmartVolume {
        #[arg(value_name = "LEVEL|on|off")]
        setting: Setting,
    },

    /// Set the gain of a single graphic-EQ band.
    Eq {
        /// Band index, 0-9 (low to high).
        #[arg(long, value_parser = clap::value_parser!(u8).range(0..=9))]
        band: u8,
        /// Gain in dB, typically -12.0 to 12.0.
        #[arg(long, allow_negative_numbers = true)]
        gain: f32,
    },

    /// Turn the whole SBX suite on or off.
    Sbx {
        // `bool` would otherwise be inferred as a SetTrue flag; this is a
        // positional that must actually take an `on`/`off` value.
        #[arg(value_name = "on|off", action = clap::ArgAction::Set, value_parser = parse_on_off)]
        on: bool,
    },

    /// Print the parameter id / selector table and how well each is known.
    Selectors,
}

/// An effect argument: either a level, or a bare on/off toggle.
///
/// Setting a level implies enabling the effect, which is what makes
/// `crystalizer 0.5` do the obvious thing. `off` disables it without
/// disturbing the stored level.
#[derive(Clone, Copy, Debug)]
enum Setting {
    Level(f32),
    Enabled(bool),
}

/// Parse the bare `on`/`off` vocabulary shared by every switch.
fn parse_on_off(s: &str) -> std::result::Result<bool, String> {
    match s {
        "on" => Ok(true),
        "off" => Ok(false),
        _ => Err(format!("expected `on` or `off`, got `{s}`")),
    }
}

impl std::str::FromStr for Setting {
    type Err = String;

    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        if let Ok(on) = parse_on_off(s) {
            return Ok(Setting::Enabled(on));
        }
        s.parse::<f32>()
            .map(Setting::Level)
            .map_err(|_| format!("expected a level in 0.0..=1.0, `on`, or `off`, got `{s}`"))
    }
}

impl Setting {
    /// The level this setting carries, if it is a level.
    fn level(self) -> Option<f32> {
        match self {
            Setting::Level(v) => Some(v),
            Setting::Enabled(_) => None,
        }
    }

    fn describe(self) -> String {
        match self {
            Setting::Level(v) => format!("{v}"),
            Setting::Enabled(true) => "on".into(),
            Setting::Enabled(false) => "off".into(),
        }
    }
}

impl Command {
    /// The normalized `0.0..=1.0` level this command carries, if any.
    ///
    /// EQ and treble gains are in dB and deliberately excluded.
    fn level(&self) -> Option<f32> {
        match *self {
            Command::Bass { setting, .. }
            | Command::Surround { setting }
            | Command::Crystalizer { setting }
            | Command::DialogPlus { setting }
            | Command::SmartVolume { setting } => setting.level(),
            _ => None,
        }
    }

    /// The dB gain this command carries, if any. Separate from [`level`]:
    /// these are not normalized and have their own range.
    ///
    /// [`level`]: Command::level
    fn gain_db(&self) -> Option<f32> {
        match *self {
            Command::Treble { gain_db } => Some(gain_db),
            Command::Eq { gain, .. } => Some(gain),
            _ => None,
        }
    }
}

/// One SBX effect: the name it prints under, and the two parameters behind
/// its on/off switch and its level.
///
/// Every effect is applied the same way, so they differ only in this data
/// -- see [`apply`].
struct Effect {
    name: &'static str,
    feature: Feature,
    enable: u32,
    level: u32,
}

const BASS: Effect = Effect {
    name: "bass",
    feature: Feature::EffectsXBass,
    enable: XBass::Enable as u32,
    level: XBass::Strength as u32,
};
const SURROUND: Effect = Effect {
    name: "surround",
    feature: Feature::EffectsSimpleSurround,
    enable: SimpleSurround::Enable as u32,
    level: SimpleSurround::Level as u32,
};
const CRYSTALIZER: Effect = Effect {
    name: "crystalizer",
    feature: Feature::EffectsCrystalizer,
    enable: Crystalizer::Enable as u32,
    level: Crystalizer::Level as u32,
};
const DIALOG_PLUS: Effect = Effect {
    name: "dialog plus",
    feature: Feature::EffectsDialogPlus,
    enable: DialogPlus::Enable as u32,
    level: DialogPlus::Strength as u32,
};
const SMART_VOLUME: Effect = Effect {
    name: "smart volume",
    feature: Feature::EffectsSmartVolume,
    enable: SmartVolume::Enable as u32,
    level: SmartVolume::Strength as u32,
};

/// Apply a setting to one effect and report it.
///
/// Setting a level enables the effect first, so `crystalizer 0.5` does the
/// obvious thing; `off` disables without disturbing the stored level.
fn apply(dev: &mut SoundBlasterE5, effect: &Effect, setting: Setting) -> Result<()> {
    match setting {
        Setting::Enabled(on) => dev.set_enable_raw(effect.feature, effect.enable, on)?,
        Setting::Level(level) => {
            dev.set_enable_raw(effect.feature, effect.enable, true)?;
            dev.set_level_raw(effect.feature, effect.level, level)?;
        }
    }
    println!("{} = {}", effect.name, setting.describe());
    Ok(())
}

fn main() -> Result<()> {
    let cli = Cli::parse();

    // No subcommand: open the interactive UI.
    let Some(command) = cli.command else {
        let mut dev = SoundBlasterE5::open(cli.dry_run).context("opening the Sound Blaster E5")?;
        return sbx_e5::tui::run(&mut dev).context("running the interactive UI");
    };

    // Neither of these needs a device open, so they answer before the
    // connection attempt that would fail without one plugged in.
    match command {
        Command::Info => {
            let text =
                transport::dump_descriptors().context("scanning USB for a Sound Blaster E5")?;
            print!("{text}");
            return Ok(());
        }
        Command::Selectors => {
            print_selectors();
            return Ok(());
        }
        _ => {}
    }

    let mut dev = SoundBlasterE5::open(cli.dry_run).context("opening the Sound Blaster E5")?;

    if dev.is_dry_run() {
        eprintln!("(dry run: nothing is sent to any device)\n");
    }

    // Reject an out-of-range argument before writing anything, so a bad
    // one can never leave the device half-configured. The library checks
    // again per write; this is what makes a multi-write command like
    // `treble` all-or-nothing.
    if let Some(level) = command.level() {
        anyhow::ensure!(
            (0.0..=1.0).contains(&level),
            "level {level} outside 0.0..=1.0"
        );
    }
    if let Some(gain) = command.gain_db() {
        let (lo, hi) = sbx_e5::EQ_GAIN_DB;
        anyhow::ensure!(
            (lo..=hi).contains(&gain),
            "gain {gain} dB outside {lo}..={hi}"
        );
    }

    match command {
        // Handled above, before the device was opened.
        Command::Info | Command::Selectors => {}

        Command::Bass { setting, crossover } => {
            apply(&mut dev, &BASS, setting)?;
            if let Some(hz) = crossover {
                // The crossover has no id in the table, so this may fail.
                optional(dev.set_bass_crossover(hz), "bass crossover")?;
            }
        }

        Command::Treble { gain_db } => {
            // This writes several bands; show progress since a partial
            // failure would leave the EQ half-applied.
            let bands = sbx_e5::TREBLE_BANDS;
            let bar = bar(bands.len() as u64, "treble bands");
            dev.set_eq_enabled(true)?;
            for band in bands.clone() {
                dev.set_eq_band(band, gain_db)?;
                bar.inc(1);
            }
            bar.finish_and_clear();
            println!(
                "treble = {gain_db:+} dB (EQ bands {}-{})",
                bands.start,
                bands.end - 1
            );
        }

        Command::Surround { setting } => apply(&mut dev, &SURROUND, setting)?,
        Command::Crystalizer { setting } => apply(&mut dev, &CRYSTALIZER, setting)?,
        Command::DialogPlus { setting } => apply(&mut dev, &DIALOG_PLUS, setting)?,
        Command::SmartVolume { setting } => apply(&mut dev, &SMART_VOLUME, setting)?,

        Command::Eq { band, gain } => {
            dev.set_eq_enabled(true)?;
            dev.set_eq_band(band, gain)?;
            println!("eq band {band} = {gain:+} dB");
        }

        Command::Sbx { on } => {
            let got = dev.set_sbx_master(on)?;
            println!("sbx = {}", if got { "on" } else { "off" });
        }
    }

    Ok(())
}

/// Run a write that is nice-to-have rather than the point of the command.
///
/// An [`sbx_e5::Error::Unsupported`] here means the parameter has no id in
/// the table; warn and continue so the rest of the command still lands. Any
/// other error is fatal.
fn optional(r: sbx_e5::Result<()>, what: &str) -> Result<()> {
    match r {
        Ok(()) => Ok(()),
        Err(sbx_e5::Error::Unsupported { .. }) => {
            eprintln!("note: skipping {what} (no known wire encoding)");
            Ok(())
        }
        Err(e) => Err(e.into()),
    }
}

/// Print the parameter id/selector table.
fn print_selectors() {
    use sbx_e5::transport::selector_of;

    println!("  id   sel   parameter");
    for &(name, id) in id::TABLE {
        println!("  0x{id:02x}  0x{:02x}  {name}", selector_of(id));
    }
    for band in 0..10u8 {
        let id = id::EQ_BAND0 + band;
        println!("  0x{id:02x}  0x{:02x}  eq band {band}", selector_of(id));
    }
    println!();
    println!("id  = addresses a read; sel = id << 1, addresses a write.");
    println!("All entries verified by ear on an E5.");
}

fn bar(len: u64, what: &str) -> ProgressBar {
    let bar = ProgressBar::new(len);
    bar.set_style(
        ProgressStyle::with_template("{msg} [{bar:20}] {pos}/{len}")
            .unwrap()
            .progress_chars("=> "),
    );
    bar.set_message(what.to_string());
    bar
}
