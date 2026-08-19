# Changelog

All notable changes to this project are documented here, newest first.
Dates are `YYYY-MM-DD`. See the README's TODO section for known gaps.

## [Unreleased]

### 2026-08-19 — bass crossover and EQ preamp

#### Added
- **The bass crossover frequency can now be set.** `sbx-e5 bass 0.3
  --crossover 90` picks the frequency below which the bass boost applies,
  anywhere from 10 to 300 Hz. The device's own default is 80 Hz. Until now
  this option existed but always reported that it could not be sent.
- **The EQ preamp can now be set**, with `sbx-e5 preamp -3`. It lifts or
  lowers the whole curve by up to 6 dB either way. Turning it down is how
  you make room for boosted bands without the sound distorting.
- **A new `probe` command** asks the device which of its control messages it
  understands and prints the answers. It only ever reads, never changes a
  setting. It is a tool for working out how to reach the features that are
  still missing — headphone high-gain mode, direct mode, optical
  passthrough — not something needed for everyday use.

#### Changed
- The accepted ranges for EQ gain and the bass crossover now come from the
  device itself rather than from Creative's general documentation, so they
  match what an E5 will actually accept: EQ bands ±12 dB, EQ preamp ±6 dB,
  crossover 10-300 Hz.

### 2026-08-19 — smart volume profiles

#### Added
- Smart Volume can now be switched between its three profiles: **normal**,
  **loud** and **night**. Night compresses the loudest passages hardest, so
  quiet dialogue stays audible without peaks waking the neighbours; loud
  favours a consistently high level; normal is the even setting the device
  ships with.
- Pick a profile from the command line with `--mode`, or on the interactive
  screen with the left and right arrows on the new line under Smart Volume.
  The screen shows the profile the device is actually set to when it opens.

#### Note
- The three profile names come from Creative's own control panel. Which
  name goes with which of the device's three settings is a very well-founded
  reading, but it has not yet been checked by ear on real hardware — so if
  night and loud seem swapped, that is the thing to report.

### 2026-08-18 — open source release

#### Changed
- The project is now published under the MIT and Apache 2.0 licenses.
- Reference material copied from Creative's Windows driver is no longer
  included, along with the tooling that read it. The recordings of how the
  device responds, and the notes describing how it is controlled, remain.

### 2026-08-18 — interactive UI rework

#### Changed
- The interactive terminal UI is about half as tall as it was. Each effect
  now lives on one line — its on/off switch, its level and its value
  together — instead of taking a separate checkbox line above the slider.
  It fits on a short terminal without scrolling.
- The equalizer's on/off switch moved onto the equalizer's own title, and
  the redundant "see panel below" line is gone. The band being edited now
  shows its gain in place of its frequency, so the reading is where you are
  looking.
- The equalizer grows to fill whatever height is left over, and its bands
  now spread across the full width instead of leaving a gap on the right.
- An effect that is switched off still shows its level, dimmed, so it is
  clear what it will return to when switched back on.
- The README now shows a screenshot of the interactive UI.

#### Fixed
- Longer names such as "Smart Volume on" were cut off, and the equalizer's
  band readout was clipped mid-word. Columns are now sized to fit.
- Level bars had a blank gap in the middle of the filled part, and the
  unfilled part of the bar was drawn in the bar's own colour, which made it
  almost invisible against the background. The track is now dim.
- On a narrow terminal the top of the list scrolled out of view even when
  there was room for it.
- The interactive UI now reads the equalizer's band settings from the
  device on startup, like everything else. It used to always open showing a
  flat equalizer no matter how the device was actually set.


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
