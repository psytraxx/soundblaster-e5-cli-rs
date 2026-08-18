# sbx-e5

Userspace control for the **Creative Sound Blaster E5** on Linux.

The E5's audio streams are standard USB Audio Class, so `snd-usb-audio`
already plays sound. What Linux has no access to is Creative's proprietary
DSP — SBX Surround, Crystalizer, Bass, Dialog Plus, Smart Volume and the
10-band EQ. This crate reimplements that control path: a library, a CLI, and
a TUI.

## Status

**Every effect here is confirmed working on a real E5** — bass, surround,
crystalizer, dialog plus, smart volume, the 10-band EQ, and the SBX master
switch, each verified by ear. Reading the device's current settings back
works too, so the UI opens showing what the hardware is actually set to.

Control parameters travel as HID `SET_REPORT` writes on the control pipe: a
64-byte report, a one-byte parameter selector, and a big-endian `f32` value.
Reads pose a query the same way and collect the answer on the interrupt
endpoint. Full wire documentation is in
[reverse/e5-control-protocol.md](reverse/e5-control-protocol.md); run
`sbx-e5 selectors` for the parameter table.

## Usage

Run with no arguments to open the interactive UI:

```sh
sbx-e5
```

![The interactive UI: one line per effect with its on/off switch, level bar
and value, over a 10-band graphic equalizer](docs/ui.png)

Each effect is one row: space switches it on and off, left/right move its
level. An effect that is off keeps its level on screen, dimmed, so it is
clear what it will go back to. On the equalizer, left/right pick a band --
which then shows its gain in place of its frequency -- and `+`/`-` adjust
it.

Or drive it a parameter at a time:

```sh
sbx-e5 info                    # attached Creative devices + interfaces
sbx-e5 selectors               # parameter id/selector table
sbx-e5 bass 0.3                # SBX bass strength (Creative default)
sbx-e5 bass off                # disable without losing the stored level
sbx-e5 bass 0.3 --crossover 80
sbx-e5 treble -4.5             # dB applied to upper EQ bands
sbx-e5 surround 0.12
sbx-e5 crystalizer 0.5
sbx-e5 dialog-plus 0.5
sbx-e5 smart-volume 0.74
sbx-e5 eq --band 9 --gain 6
sbx-e5 sbx on|off              # SBX master switch
```

Every level command also accepts `on`/`off` in place of a number, to disable
an effect without touching its stored level.

Add `--dry-run` (or set `SBX_E5_DRY_RUN=1`) to print the packets that would
be sent instead of sending them. This works with no device attached:

```
$ sbx-e5 --dry-run bass 0.3
SET HidReport feature=0x10000020 param=1 value=Float(0.3)
    [20, 00, 16, 0A, D5, 02, 08, 32, 20, 96, 3E, 99, 99, 9A, 00, ...]
    commit [26, 01, 96, 19]
bass = 0.3
```

Levels are normalized `0.0..=1.0`; EQ/treble gains are in dB. The defaults
above are the values Creative's own shipped profiles use.

There is **no dedicated treble parameter** in the protocol — the Windows
GUI's treble slider drives the upper graphic-EQ bands, and `sbx-e5 treble`
does the same (bands 6–9).

## Permissions

```sh
sudo cp 60-sbx-e5.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
sudo usermod -aG plugdev "$USER"   # log out and back in
```

## Protocol

Control is addressed as a `(Feature, param, value)` triple in the library
API, which the transport layer collapses onto the wire as a single selector
byte (`parameter_id << 1`) plus a big-endian `f32`. `Feature` is a packed id:
high nibble = category, low bits = a one-hot mask.

| Target | Feature | Params |
|---|---|---|
| Bass | `0x1000_0020` | `Enable=0`, `Strength=1`, `Freq_Hz=2` |
| Graphic EQ | `0x1000_0010` | `PreampGain=1`, `Band0..9_Gain=2..11` |
| Surround | `0x1000_0200` | `Enable=0`, `Level=1` |
| Crystalizer | `0x1000_0008` | `Enable=0`, `Level=1` |
| Dialog Plus | `0x1000_0002` | `Enable=0`, `Strength=1` |
| Smart Volume | `0x1000_0004` | `Enable=0`, `Strength=1`, `Mode=2` |
| SBX master | `0x6000_0001` | `SBXMasterOnOff=7` |

All recovered constants live in `src/proto.rs`.

Supported device IDs (VID `041e`): E5 `323c`, E1 `323b`, E3 `323e`,
X7 `323a`, G5 `3243`. Only the E5 is wired up in `PID_E5`.

## Provenance

This is an independent, interoperability-only reimplementation. It contains
no Creative code, no Creative binaries, and no decompiled output.

The wire format was determined by capturing USB traffic to and from a device
the author owns, using USBPcap -- the analysis and its test vectors are in
[reverse/e5-control-protocol.md](reverse/e5-control-protocol.md), with the
raw captures in `reverse/captures/`. Parameter identifiers are numeric
constants read out of the driver's published metadata; constants are facts
about a protocol, not authorship.

Creative's Windows driver is Creative Technology Ltd's and is available only
from Creative. Sound Blaster and SBX are trademarks of Creative Technology
Ltd, used here only to say what hardware this controls. This project is not
affiliated with, authorized by, or endorsed by Creative.

## Development

```sh
cargo fmt
cargo clippy --all-targets
cargo test      # framing/encoding unit tests, no hardware needed
```

## License

Licensed under either of [Apache License, Version 2.0](LICENSE-APACHE) or
[MIT license](LICENSE-MIT) at your option. This covers this project's own
code only -- see [Provenance](#provenance) above.

## TODO

### Unimplemented features

Each needs its selector byte pinned down before it can be added. Evidence
and leads for all of these are in
[reverse/e5-control-protocol.md](reverse/e5-control-protocol.md).

The microphone side of the device is entirely unimplemented, and is the
largest gap — Creative's own E5 profiles configure every one of these:

- **Mic noise reduction** — shipped enabled in every stock profile.
- **Mic echo cancellation (AEC)**.
- **Mic smart volume** — auto-leveling.
- **VoiceFX** — voice presets (pitch/formant), nine tunable parameters.
- **Mic EQ** — eight-band parametric, per-band level/frequency/width.

Preset selection for VoiceFX and Mic EQ may need a different report shape
than the `0x20` float path, since an index is not a level.

Device-hardware features, plausible but less certain:

- **LED control** — on/off, mode, intensity, pulsation.
- **USB power overdrive** — enable plus off/on current limits.
- **Device I/O configuration** — line-out and mic configuration, S/PDIF
  routing, jack detection, headphone impedance selection.
- **Direct monitoring** — per-input enables with separate mic levels.
- **Bluetooth auto-connect**.
- **Battery level and status** — the least certain of these.

Not worth pursuing: Dolby/DTS decode and encode, EAX/EAX3, CMSS3D, reverb
and pitch shift, speaker calibration, bass management, karaoke, and mic
array beamforming. These belong to other Creative products that share this
driver; the E5 has no hardware path for them.
