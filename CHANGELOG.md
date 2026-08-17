# Changelog

All notable changes to this project are documented here, newest first.
Dates are `YYYY-MM-DD`. See the README's TODO section for known gaps.

## [Unreleased]

### 2026-08-17 — first working version

#### Added
- Control bass, surround, crystalizer, dialog plus, smart volume, and the
  10-band equalizer, each with its own on/off switch — from the command
  line or a full interactive terminal UI (just run `sbx-e5` with no
  arguments).
- Every effect can be set to a level or simply switched `on`/`off`.
- A `--dry-run` mode that shows exactly what would be sent, so the tool
  can be tried out safely without a device connected.
- Every effect is confirmed working by ear on real hardware. Since nothing
  is unverified any more, the "unconfirmed" markers are gone from the
  terminal UI and from `sbx-e5 selectors`.
- The interactive terminal UI now opens showing each effect's actual
  current setting on the device, instead of a built-in guess. Levels and
  on/off switches are read back on startup.
- The SBX master switch can now be switched on and off from the command
  line and the terminal UI, and its current state is shown on startup like
  every other effect.

#### Fixed
- Equalizer and treble settings are now checked before anything is sent.
  Asking for an absurd gain — `treble 500` — used to be passed straight to
  the device; it is now refused with a message, as out-of-range levels
  already were. The accepted range is -12 to +12 dB.
- Asking for an equalizer band that does not exist is now refused instead
  of quietly changing the highest band instead.
- If the interactive UI ever crashes, it now puts the terminal back the way
  it found it. Previously a crash could leave the shell with no cursor and
  no echo, needing a `reset` to recover.
- Toggling the SBX master switch reported an error and left the display
  stuck on the old state, even though the switch itself had changed. The
  device sends several status messages at once when it switches, and only
  the first was being looked at; now they are read until the relevant one
  turns up. The same problem could make any value read return a stale
  answer.
- The SBX master switch is now drawn as a checkbox in the terminal UI, like
  every other on/off switch, instead of as a slider bar.
