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
