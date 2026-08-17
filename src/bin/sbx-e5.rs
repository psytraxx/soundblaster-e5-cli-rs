//! Command-line control for the Creative Sound Blaster E5 on Linux.

use anyhow::{Context, Result};
use clap::{Parser, Subcommand};
use indicatif::{ProgressBar, ProgressStyle};
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
        #[arg(value_parser = ["on", "off"])]
        state: String,
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

impl std::str::FromStr for Setting {
    type Err = String;

    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        match s {
            "on" => Ok(Setting::Enabled(true)),
            "off" => Ok(Setting::Enabled(false)),
            _ => s
                .parse::<f32>()
                .map(Setting::Level)
                .map_err(|_| format!("expected a level in 0.0..=1.0, `on`, or `off`, got `{s}`")),
        }
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
}

fn main() -> Result<()> {
    let cli = Cli::parse();

    // No subcommand: open the interactive UI.
    let Some(command) = cli.command else {
        let mut dev = SoundBlasterE5::open(cli.dry_run)
            .map_err(|e| anyhow::anyhow!(e.to_string()))
            .context("opening the Sound Blaster E5")?;
        return sbx_e5::tui::run(&mut dev).map_err(|e| anyhow::anyhow!(e.to_string()));
    };

    if let Command::Info = command {
        match transport::dump_descriptors() {
            Ok(text) => {
                print!("{text}");
                return Ok(());
            }
            Err(e) => {
                return Err(anyhow::anyhow!(e)).context("scanning USB for a Sound Blaster E5");
            }
        }
    }

    if let Command::Selectors = command {
        print_selectors();
        return Ok(());
    }

    let mut dev = SoundBlasterE5::open(cli.dry_run)
        .map_err(|e| anyhow::anyhow!(e))
        .context("opening the Sound Blaster E5")?;

    if dev.is_dry_run() {
        eprintln!("(dry run: nothing is sent to any device)\n");
    }

    // Reject an out-of-range level before writing anything, so a bad
    // argument can never leave the device half-configured.
    if let Some(level) = command.level() {
        anyhow::ensure!(
            (0.0..=1.0).contains(&level),
            "level {level} outside 0.0..=1.0"
        );
    }

    match command {
        Command::Info => unreachable!("handled above"),

        Command::Bass { setting, crossover } => {
            match setting {
                Setting::Enabled(on) => dev.set_bass_enabled(on).map_err(err)?,
                Setting::Level(level) => {
                    dev.set_bass_enabled(true).map_err(err)?;
                    dev.set_bass(level).map_err(err)?;
                }
            }
            if let Some(hz) = crossover {
                // The crossover has no id in the table, so this may fail.
                optional(dev.set_bass_crossover(hz), "bass crossover")?;
            }
            println!("bass = {}", setting.describe());
        }

        Command::Treble { gain_db } => {
            // set_treble writes several bands; show progress since a
            // partial failure leaves the EQ half-applied.
            let bar = bar(4, "treble bands");
            dev.set_eq_enabled(true).map_err(err)?;
            for band in 6..10u8 {
                dev.set_eq_band(band, gain_db).map_err(err)?;
                bar.inc(1);
            }
            bar.finish_and_clear();
            println!("treble = {gain_db:+} dB (EQ bands 6-9)");
        }

        Command::Surround { setting } => {
            match setting {
                Setting::Enabled(on) => dev.set_surround_enabled(on).map_err(err)?,
                Setting::Level(level) => {
                    dev.set_surround_enabled(true).map_err(err)?;
                    dev.set_surround(level).map_err(err)?;
                }
            }
            println!("surround = {}", setting.describe());
        }

        Command::Crystalizer { setting } => {
            match setting {
                Setting::Enabled(on) => dev.set_crystalizer_enabled(on).map_err(err)?,
                Setting::Level(level) => {
                    dev.set_crystalizer_enabled(true).map_err(err)?;
                    dev.set_crystalizer(level).map_err(err)?;
                }
            }
            println!("crystalizer = {}", setting.describe());
        }

        Command::DialogPlus { setting } => {
            match setting {
                Setting::Enabled(on) => dev.set_dialog_plus_enabled(on).map_err(err)?,
                Setting::Level(level) => {
                    dev.set_dialog_plus_enabled(true).map_err(err)?;
                    dev.set_dialog_plus(level).map_err(err)?;
                }
            }
            println!("dialog plus = {}", setting.describe());
        }

        Command::SmartVolume { setting } => {
            match setting {
                Setting::Enabled(on) => dev.set_smart_volume_enabled(on).map_err(err)?,
                Setting::Level(level) => {
                    dev.set_smart_volume_enabled(true).map_err(err)?;
                    dev.set_smart_volume(level).map_err(err)?;
                }
            }
            println!("smart volume = {}", setting.describe());
        }

        Command::Eq { band, gain } => {
            dev.set_eq_enabled(true).map_err(err)?;
            dev.set_eq_band(band, gain).map_err(err)?;
            println!("eq band {band} = {gain:+} dB");
        }

        Command::Sbx { state } => {
            let on = state == "on";
            let got = dev.set_sbx_master(on).map_err(err)?;
            println!("sbx = {}", if got { "on" } else { "off" });
        }

        Command::Selectors => unreachable!("handled above"),
    }

    Ok(())
}

/// Convert a device error into an `anyhow` error, preserving the message.
fn err(e: sbx_e5::Error) -> anyhow::Error {
    anyhow::anyhow!(e.to_string())
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
        Err(e) => Err(err(e)),
    }
}

/// Print the parameter id/selector table.
fn print_selectors() {
    use sbx_e5::transport::selector_of;

    let rows: &[(&str, u8)] = &[
        ("surround enable", id::SURROUND_ENABLE),
        ("surround level", id::SURROUND_LEVEL),
        ("dialog+ enable", id::DIALOG_PLUS_ENABLE),
        ("dialog+ level", id::DIALOG_PLUS_LEVEL),
        ("smart volume enable", id::SMART_VOLUME_ENABLE),
        ("smart volume level", id::SMART_VOLUME_LEVEL),
        ("smart volume mode", id::SMART_VOLUME_MODE),
        ("crystalizer enable", id::CRYSTALIZER_ENABLE),
        ("crystalizer level", id::CRYSTALIZER_LEVEL),
        ("eq enable", id::EQ_ENABLE),
        ("eq preamp", id::EQ_PREAMP),
        ("bass enable", id::BASS_ENABLE),
        ("bass level", id::BASS_LEVEL),
    ];

    println!("  id   sel   parameter");
    for (name, id) in rows {
        println!("  0x{id:02x}  0x{:02x}  {name}", selector_of(*id));
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
