//! Command-line control for the Creative Sound Blaster E5 on Linux.

use anyhow::{Context, Result};
use clap::{Parser, Subcommand};
use indicatif::{ProgressBar, ProgressStyle};
use sbx_e5::{SoundBlasterE5, transport};

#[derive(Parser)]
#[command(
    name = "sbx-e5",
    about = "Control the SBX DSP of a Creative Sound Blaster E5",
    long_about = "Control the SBX DSP (bass, treble, surround, crystalizer) of a\n\
                  Creative Sound Blaster E5 on Linux.\n\n\
                  NOTE: the USB wire format is reconstructed from the Windows\n\
                  driver and is not yet verified against hardware. Use --dry-run\n\
                  to inspect what would be sent.",
    version
)]
struct Cli {
    /// Print the packets that would be sent instead of sending them.
    #[arg(long, global = true)]
    dry_run: bool,

    #[command(subcommand)]
    command: Command,
}

#[derive(Subcommand)]
enum Command {
    /// Show attached Creative devices and their USB interfaces.
    Info,

    /// Set SBX Bass strength (0.0 - 1.0). Creative's default is 0.3.
    Bass {
        #[arg(value_name = "LEVEL")]
        level: f32,
        /// Crossover frequency in Hz (stock profiles use 80).
        #[arg(long)]
        crossover: Option<f32>,
    },

    /// Set treble by applying a gain (dB) to the upper EQ bands.
    Treble {
        #[arg(value_name = "GAIN_DB", allow_negative_numbers = true)]
        gain_db: f32,
    },

    /// Set SBX Surround level (0.0 - 1.0). Creative's default is 0.12.
    Surround {
        #[arg(value_name = "LEVEL")]
        level: f32,
    },

    /// Set SBX Crystalizer level (0.0 - 1.0). Creative's default is 0.5.
    Crystalizer {
        #[arg(value_name = "LEVEL")]
        level: f32,
    },

    /// Set SBX Dialog Plus strength (0.0 - 1.0).
    DialogPlus {
        #[arg(value_name = "LEVEL")]
        level: f32,
    },

    /// Set SBX Smart Volume strength (0.0 - 1.0).
    SmartVolume {
        #[arg(value_name = "LEVEL")]
        level: f32,
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
}

impl Command {
    /// The normalized `0.0..=1.0` level this command carries, if any.
    ///
    /// EQ and treble gains are in dB and deliberately excluded.
    fn level(&self) -> Option<f32> {
        match *self {
            Command::Bass { level, .. }
            | Command::Surround { level }
            | Command::Crystalizer { level }
            | Command::DialogPlus { level }
            | Command::SmartVolume { level } => Some(level),
            _ => None,
        }
    }
}

fn main() -> Result<()> {
    let cli = Cli::parse();

    if let Command::Info = cli.command {
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

    let mut dev = SoundBlasterE5::open(cli.dry_run)
        .map_err(|e| anyhow::anyhow!(e))
        .context("opening the Sound Blaster E5")?;

    if dev.is_dry_run() {
        eprintln!("(dry run: nothing is sent to any device)\n");
    }

    // Reject an out-of-range level before writing anything, so a bad
    // argument can never leave the device half-configured.
    if let Some(level) = cli.command.level() {
        anyhow::ensure!(
            (0.0..=1.0).contains(&level),
            "level {level} outside 0.0..=1.0"
        );
    }

    match cli.command {
        Command::Info => unreachable!("handled above"),

        Command::Bass { level, crossover } => {
            dev.set_bass_enabled(true).map_err(err)?;
            dev.set_bass(level).map_err(err)?;
            if let Some(hz) = crossover {
                dev.set_bass_crossover(hz).map_err(err)?;
            }
            println!("bass = {level}");
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

        Command::Surround { level } => {
            dev.set_surround_enabled(true).map_err(err)?;
            dev.set_surround(level).map_err(err)?;
            println!("surround = {level}");
        }

        Command::Crystalizer { level } => {
            dev.set_crystalizer_enabled(true).map_err(err)?;
            dev.set_crystalizer(level).map_err(err)?;
            println!("crystalizer = {level}");
        }

        Command::DialogPlus { level } => {
            dev.set_dialog_plus(level).map_err(err)?;
            println!("dialog plus = {level}");
        }

        Command::SmartVolume { level } => {
            dev.set_smart_volume(level).map_err(err)?;
            println!("smart volume = {level}");
        }

        Command::Eq { band, gain } => {
            dev.set_eq_enabled(true).map_err(err)?;
            dev.set_eq_band(band, gain).map_err(err)?;
            println!("eq band {band} = {gain:+} dB");
        }

        Command::Sbx { state } => {
            let on = state == "on";
            dev.set_sbx_master(on).map_err(err)?;
            println!("sbx = {state}");
        }
    }

    Ok(())
}

/// Convert a device error into an `anyhow` error, preserving the message.
fn err(e: sbx_e5::Error) -> anyhow::Error {
    anyhow::anyhow!(e.to_string())
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
