# Changelog

All notable changes to this project are documented here, newest first.
Dates are `YYYY-MM-DD`.

## [Unreleased]

### 2026-08-14

#### Added
- Protocol constants (`src/proto.rs`), generated from the .NET metadata of
  `Interop.CtSndCr.dll` — 443 recovered constants covering every SBX
  feature, parameter id, datatype and context.
- `reverse/gen_proto.py` to regenerate those constants reproducibly from
  `reverse/enums/ctsndcr_enums.txt`.
- `SoundBlasterE5` library API (`src/lib.rs`): bass, treble, surround,
  crystalizer, dialog plus, smart volume, per-band EQ, SBX master switch.
- USB transport (`src/transport.rs`) with a swappable `Framing` strategy
  (`VendorTriple`, `KsProperty`), dry-run mode, and `dump_descriptors()`.
- `sbx-e5` CLI with `info`, `bass`, `treble`, `surround`, `crystalizer`,
  `dialog-plus`, `smart-volume`, `eq` and `sbx` subcommands, plus a global
  `--dry-run` flag (also honours `SBX_E5_DRY_RUN`).
- Progress reporting via `indicatif` for multi-write operations, so a
  partially applied EQ change is visible.
- Unit tests covering wire encoding and the recovered feature ids; these
  run with no hardware attached.
- udev rule (`60-sbx-e5.rules`) for the E5 and related E-Series devices.
- `README.md` and `CLAUDE.md`.
- `docs/usb-capture.md` — procedure for capturing the E5 control protocol
  with Wireshark/USBPcap on Windows (and verifying with `usbmon` on Linux),
  including the display filters and the known little-endian `f32` byte
  patterns to search for, plus how to feed results back into
  `src/transport.rs`.

#### Fixed
- Level range validation now runs *before* any USB write, so an
  out-of-range argument can no longer leave the device half-configured
  (previously `bass 5.0` sent the enable write before failing).

#### Notes
- The USB wire framing is **not yet verified against hardware**. The
  parameter model is exact, but the Windows stack reaches the device via
  Kernel Streaming properties (`IOCTL_KS_PROPERTY`) handled by
  `KsUSBaud.sys`, and the byte layout that driver emits is still unproven.
- Reverse engineering inputs extracted and decompiled from Creative's
  signed redistributable `SBE_PCDRV_L9_1_05_04.exe` (1.05.04, driver
  1.14.1.5); kept under `reverse/` as the provenance record.
