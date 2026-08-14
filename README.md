# sbx-e5

Userspace control for the **Creative Sound Blaster E5** on Linux.

The E5's audio streams are standard USB Audio Class, so `snd-usb-audio`
already plays sound. What Linux has no access to is Creative's proprietary
DSP — SBX Surround, Crystalizer, Bass, Dialog Plus, Smart Volume and the
10-band EQ. This crate reimplements that control path.

## Status

| Layer | State |
|---|---|
| Parameter model (`src/proto.rs`) | **Exact.** Recovered from typed .NET metadata. |
| Library + CLI | **Working**, fully exercisable in dry-run. |
| USB wire framing (`src/transport.rs`) | **Unverified.** Not yet tested on hardware. |

The framing is the honest gap. Decompiling the Windows driver showed the
control path is:

```
SBE.exe (.NET) → Interop.CtSndCr → SndCrUSB.DLL
  → KsMalcCtl.DLL → IOCTL_KS_PROPERTY (0x2F0003) → KsUSBaud.sys → USB
```

Windows never issues USB vendor requests from userspace — it sets Kernel
Streaming properties and lets `KsUSBaud.sys` translate them. There is no
such driver on Linux, so we have to speak whatever that driver emits, and
that byte layout has not been proven yet. Candidate layouts are expressed as
a swappable `transport::Framing` strategy.

**Nothing here is confirmed to change audio output on a real E5.** A
Wireshark capture of one bass-slider move on Windows would settle it
outright — see **[docs/usb-capture.md](docs/usb-capture.md)** for the
step-by-step procedure.

## Usage

```sh
sbx-e5 info                    # attached Creative devices + interfaces
sbx-e5 bass 0.3                # SBX bass strength (Creative default)
sbx-e5 bass 0.3 --crossover 80
sbx-e5 treble -4.5             # dB applied to upper EQ bands
sbx-e5 surround 0.12
sbx-e5 crystalizer 0.5
sbx-e5 dialog-plus 0.5
sbx-e5 smart-volume 0.74
sbx-e5 eq --band 9 --gain 6
sbx-e5 sbx on|off              # SBX master switch
```

Add `--dry-run` (or set `SBX_E5_DRY_RUN=1`) to print the packets that would
be sent instead of sending them. This works with no device attached:

```
$ sbx-e5 --dry-run bass 0.3
SET VendorTriple feature=0x10000020 param=0 value=Bool(true)
    [20, 00, 00, 10, 00, 00, 00, 00, 01, 00, 00, 00]
SET VendorTriple feature=0x10000020 param=1 value=Float(0.3)
    [20, 00, 00, 10, 01, 00, 00, 00, 9A, 99, 99, 3E]
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

Control is a `(Feature, param, value)` triple. `Feature` is a packed id:
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
via DigiCert. Interoperability research only; no Creative code ships in this
crate.

## Development

```sh
cargo test      # framing/encoding unit tests, no hardware needed
cargo clippy --all-targets
```
