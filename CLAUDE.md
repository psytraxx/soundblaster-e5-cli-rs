# CLAUDE.md

Guidance for working in this repository.

## What this is

Userspace control for the Creative Sound Blaster E5 on Linux, reimplementing
the SBX DSP control path (bass, treble, surround, crystalizer) that the
Windows-only Creative control panel provides.

## Non-negotiable conventions

**Always run before considering a change done:**

```sh
cargo fmt
cargo clippy --all-targets
cargo test
```

All three must be clean. Do not report work as complete otherwise.

**Always keep `CHANGELOG.md` up to date.** Every user-visible change gets a
dated entry (`YYYY-MM-DD`) under the current version. Add the entry in the
same change that makes the code change, not afterwards.

## Architecture

```
src/proto.rs      generated protocol constants  -- DO NOT EDIT BY HAND
src/transport.rs  USB framing (unverified) + dry-run
src/lib.rs        SoundBlasterE5 API surface
src/bin/sbx-e5.rs clap CLI
reverse/          extracted Windows driver, decompiled sources, generator
```

`src/proto.rs` is generated. To change it, edit the generator and regenerate:

```sh
python3 reverse/gen_proto.py > src/proto.rs
```

The source of truth is `reverse/enums/ctsndcr_enums.txt`, extracted from the
.NET metadata of `Interop.CtSndCr.dll`.

## The one thing to be careful about

**The USB wire framing in `src/transport.rs` is NOT verified against
hardware.** The parameter model is exact (typed metadata), but how a
`(Feature, param, value)` triple becomes bytes is reconstructed.

Windows does not use USB vendor requests from userspace — it sets Kernel
Streaming properties (`IOCTL_KS_PROPERTY`, `0x2F0003`) and `KsUSBaud.sys`
translates them. We must speak whatever that driver emits.

Do not describe the transport as working, tested, or confirmed. Keep
candidate layouts behind the `transport::Framing` enum rather than editing
call sites. A `usbmon`/Wireshark capture from Windows would resolve this.

## Testing without hardware

No E5 is currently available for testing. Everything must stay exercisable
via dry-run:

```sh
cargo run -- --dry-run bass 0.3
SBX_E5_DRY_RUN=1 cargo run -- treble -4.5
```

Encoding is unit-tested in `src/transport.rs` (`mod tests`) with no device.
Prefer adding tests there over manual verification.

Error paths must fail cleanly with a message and exit 1 — never panic when
no device is present.

## Conventions

- Validate arguments **before** issuing any write, so a bad input cannot
  leave the device half-configured (see `Command::level()` in the CLI).
- Levels are normalized `0.0..=1.0`; EQ and treble gains are dB.
- Library code returns the typed `sbx_e5::Error`; the CLI binary uses
  `anyhow` with context.
- Keep `reverse/` intact — it is the provenance record for every constant.
