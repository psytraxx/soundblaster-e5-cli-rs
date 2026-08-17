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

**`CHANGELOG.md` is for a non-technical audience.** Write what changed, not
how — no file paths, struct/function names, byte layouts, crate names, or
implementation detail. "Bass and surround can now be switched on and off"
rather than "added `set_bass_enabled`/`selector_with_confidence` to
`transport.rs`". If an entry needs a code reference to make sense, it
belongs in the commit message or a doc comment, not here.

## Architecture

```
src/proto.rs      generated protocol constants  -- DO NOT EDIT BY HAND
src/transport.rs  HID wire framing + dry-run
src/lib.rs        SoundBlasterE5 API surface
src/bin/sbx-e5.rs clap CLI
src/tui.rs        interactive UI (no subcommand)
reverse/          extracted Windows driver, decompiled sources, generator,
                   and the USBPcap capture that resolved the wire format
```

`src/proto.rs` is generated. To change it, edit the generator and regenerate:

```sh
python3 reverse/gen_proto.py > src/proto.rs
```

The source of truth is `reverse/enums/ctsndcr_enums.txt`, extracted from the
.NET metadata of `Interop.CtSndCr.dll`.

## The one thing to be careful about

**Only bass is confirmed on real hardware.** The wire format itself —
opcode, header bytes, big-endian `f32` — comes from a USBPcap capture of
`KsUSBaud.sys` and is not in question. What's still open is the *selector
table*: each parameter's one-byte id is derived from the driver's
`id << 1` rule plus the id table published for the Sound Blaster G6 (same
vendor and driver family, a different device), not captured from an E5.
`sbx-e5 selectors` shows which entries are `Captured` versus `Derived`.

Do not describe a `Derived` selector as confirmed. When a capture resolves
one, move it to `Captured` in `transport::selector_with_confidence` and say
so in the changelog. See the README's protocol section and TODO list for
what's still open (reading device state, SBX master, profile loading).

## Testing

```sh
cargo run -- --dry-run bass 0.3
SBX_E5_DRY_RUN=1 cargo run -- treble -4.5
```

Encoding is unit-tested in `src/transport.rs` (`mod tests`) against the
captured test vectors in `reverse/e5-control-protocol.md` — no
device needed. Prefer adding tests there over manual verification.

Error paths must fail cleanly with a message and exit 1 — never panic when
no device is present.

## Conventions

- Validate arguments **before** issuing any write, so a bad input cannot
  leave the device half-configured (see `Command::level()` in the CLI).
- Levels are normalized `0.0..=1.0`; EQ and treble gains are dB.
- Library code returns the typed `sbx_e5::Error`; the CLI binary uses
  `anyhow` with context.
- Keep `reverse/` intact — it is the provenance record for every constant.
