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
- Bass is confirmed working by ear on real hardware. The other effects
  are expected to work the same way but haven't been individually
  confirmed yet — `sbx-e5 selectors` shows which is which.
- The interactive terminal UI now opens showing each effect's actual
  current setting on the device, instead of a built-in guess. Levels and
  on/off switches are read back on startup.
- The SBX master switch can now be switched on and off from the command
  line and the terminal UI, and its current state is shown on startup like
  every other effect.

#### Fixed
- Toggling the SBX master switch reported an error and left the display
  stuck on the old state, even though the switch itself had changed. The
  device sends several status messages at once when it switches, and only
  the first was being looked at; now they are read until the relevant one
  turns up. The same problem could make any value read return a stale
  answer.
- The SBX master switch is now drawn as a checkbox in the terminal UI, like
  every other on/off switch, instead of as a slider bar.
