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
rather than "added `set_bass_enabled`/`id_of` to
`transport.rs`". If an entry needs a code reference to make sense, it
belongs in the commit message or a doc comment, not here.

**Documentation states the status quo, not the history of getting there.**
Every markdown file except `CHANGELOG.md` describes what is true now: here
is the protocol, here is what we implement, here is what we do not support
yet. Never narrate the investigation. No "this used to say", no "previously
believed", no "confirmed what we suspected", no "finding 1 / finding 2", no
references to earlier analysis passes or to what a previous document
claimed. When new evidence changes a document, rewrite the affected part so
it simply reads as correct — do not leave a correction notice behind. The
history lives in git and in `CHANGELOG.md`, which is the sole exception
because a changelog is by definition a record of change.

Do keep statements about *verification status* — "read off the device but
never written to it", "confirmed by ear", "not yet captured". Those describe
how much we currently trust a fact, which is status quo, not history.

## Architecture

```
src/proto.rs      protocol constants -- hand-maintained
src/transport.rs  HID wire framing + dry-run
src/lib.rs        SoundBlasterE5 API surface
src/bin/sbx-e5.rs clap CLI
src/tui.rs        interactive UI (no subcommand)
reverse/          USBPcap captures and the protocol analysis they produced
```

`src/proto.rs` holds the recovered protocol constants. It is maintained by
hand; there is no generator in the tree.

## The one thing to be careful about

Every effect currently implemented — bass, surround, crystalizer, dialog
plus, smart volume, the EQ, and the SBX master switch — is confirmed on
real hardware, in both directions where a read exists. Do not reintroduce
"unverified"/"derived" caveats for these.

That does **not** extend to anything not yet implemented. Only bass and the
SBX master switch were ever seen in a capture; the rest of the selector
table follows the driver's `id << 1` rule over the Sound Blaster G6 id
table and was confirmed by listening. So the rule is well established for
this device, but a *new* parameter taken from that same table is still a
guess until it is either captured or verified on hardware. Say which of the
two happened, and do not describe an untested selector as confirmed.

See the README's TODO for what is still open — the microphone-side
controls are the largest unimplemented area.

## Testing

```sh
cargo run -- --dry-run bass 0.3
SBX_E5_DRY_RUN=1 cargo run -- treble -4.5
```

Encoding is unit-tested in `src/transport.rs` (`mod tests`) against the
captured test vectors in `reverse/e5-control-protocol.md` — no
device needed. Prefer adding tests there over manual verification.

The TUI renders without a device too. `cargo test writes_ui_snapshot` draws
several states to `target/ui-snapshot.txt`. It is a dump, not a golden file
— it asserts only that a frame rendered, so it never blocks a deliberate UI
change.

`docs/ui.png` is the README's screenshot of that same UI. It is a committed
image with no generator kept in the tree, so a UI change makes it stale —
retake it by hand when the layout changes visibly.


Error paths must fail cleanly with a message and exit 1 — never panic when
no device is present.

## Conventions

- Validate arguments **before** issuing any write, so a bad input cannot
  leave the device half-configured (see `Command::level()` in the CLI).
- Levels are normalized `0.0..=1.0`; EQ and treble gains are dB.
- Library code returns the typed `sbx_e5::Error`; the CLI binary uses
  `anyhow` with context.
- Keep `reverse/` intact — it is the provenance record for every constant.
