# sbx-e5

Userspace control for the **Creative Sound Blaster E5** on Linux.

The E5's audio streams are standard USB Audio Class, so `snd-usb-audio`
already plays sound. What Linux has no access to is Creative's proprietary
DSP — SBX Surround, Crystalizer, Bass, Dialog Plus, Smart Volume and the
10-band EQ. This crate reimplements that control path: a library, a CLI, and
a TUI.

## Status

The wire format was recovered from a USBPcap capture of the Windows driver
(`KsUSBaud.sys`) — see
[reverse/e5-control-protocol.md](reverse/e5-control-protocol.md).
Control parameters travel as HID `SET_REPORT` writes on the control pipe: a
64-byte report, a one-byte parameter selector, and a big-endian `f32` value.

**Bass is confirmed on real hardware** — `bass 0` vs `bass 1` is audibly
different on an E5. Every other effect's selector is *derived*: the driver
builds the selector byte as `parameter_id << 1`, and the ids come from the
published table for the Sound Blaster G6 (same vendor and driver family, a
different device). Both selectors independently known for the E5 — bass and
surround — fall out of that rule exactly, which is good evidence, not proof.
Run `sbx-e5 selectors` to see the full table and which entries are which.

## Usage

Run with no arguments to open the interactive UI:

```sh
sbx-e5
```

Arrows select a row and adjust its value, space toggles on/off rows, and on
the `EQ bands` row, left/right pick a band and `+`/`-` adjust its gain.

Or drive it a parameter at a time:

```sh
sbx-e5 info                    # attached Creative devices + interfaces
sbx-e5 selectors               # parameter id/selector table + confidence
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

All 443 recovered constants are in `reverse/enums/ctsndcr_enums.txt`.
Regenerate `src/proto.rs` with:

```sh
python3 reverse/gen_proto.py > src/proto.rs
```

Supported device IDs (VID `041e`): E5 `323c`, E1 `323b`, E3 `323e`,
X7 `323a`, G5 `3243`. Only the E5 is wired up in `PID_E5`.

## Provenance

Everything under `reverse/` derives from Creative's own redistributable
Windows driver `SBE_PCDRV_L9_1_05_04.exe` (1.05.04, driver 1.14.1.5),
downloaded from `files.creative.com` and signed by Creative Technology Ltd
via DigiCert, plus a USBPcap capture of that driver's traffic.
Interoperability research only; no Creative code ships in this crate.

## Development

```sh
cargo fmt
cargo clippy --all-targets
cargo test      # framing/encoding unit tests, no hardware needed
```

## TODO

- **Profile loading.** Creative ships several stock profiles (see
  `reverse/profiles/E5/Default.xml`); there is no way yet to load one as a
  single operation instead of setting each parameter by hand.
