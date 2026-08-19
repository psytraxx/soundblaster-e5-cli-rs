# Sound Blaster E5 — control protocol (USB capture analysis)

Derived from USBPcap captures of `KsUSBaud.sys` on Windows, 2026-08-17.
Device `041e:323c`. USB topology is not stable across replug/reboot — the E5
has been seen at device address 17 (bus 2 / USBPcap2) and address 9 (bus 4 /
USBPcap4). Always re-derive the address per capture: filter
`usbhid.setup.wIndex == 3 && usbhid.setup.bRequest == 0x09` and read
`usb.device_address` off any E5 write.

## Transport

Control parameters are sent as **HID SET_REPORT over the control pipe** — not
vendor control transfers, not interrupt OUT. `KsUSBaud.sys` reformats the
`(feature, param, value)` triple from the README into its own report format;
the 32-bit feature ids do **not** appear on the wire.

Every control write is a USB control transfer with this setup packet:

| Field | Value | Meaning |
|---|---|---|
| `bmRequestType` | `0x21` | host→device, class, recipient=interface |
| `bRequest` | `0x09` | HID SET_REPORT |
| `wValue` | `0x0200` | ReportType=Output (2), ReportID=0 |
| `wIndex` | `3` | HID interface number |
| `wLength` | `64` | fixed report length |

The 64-byte report payload is zero-padded; only a short prefix is meaningful.
The first byte is an opcode that selects the report shape.

## Report shapes

### `0x20` — SET_PARAM (the value path)

Carries a parameter value as a **big-endian IEEE-754 f32**, range 0.0–1.0,
linear with the UI slider percentage.

```
offset  bytes                meaning
0       20                   opcode = SET_PARAM
1..6    00 16 0a d5 02 08    fixed framing (constant on every param write)
7       PP                   param selector (see table)
8..9    20 96                fixed; the 96 is the playback module id
10..13  <f32 big-endian>     value, 0.0 .. 1.0
14..63  00                   zero pad
```

Confirmed against a full Bass 0→100% slider sweep: the float climbs
monotonically from 0.01 to exactly 1.0000, one write per drag increment.
Slider at 50% → `0.5000`; at 100% → `1.0000`.

**Note the byte order:** value is BIG-endian. `0.5` on the wire is
`3f 00 00 00`, not `00 00 00 3f`.

#### Param selectors (confirmed)

| Selector | Effect |
|---|---|
| `0x02` | Surround |
| `0x32` | Bass |

Other effects (Crystalizer, Smart Volume, Dialog Plus, …) not yet captured.
Method to extend: toggle one effect, capture, read byte 7.

### `0x26` — level/state (NOT the value path)

```
offset  bytes         meaning
0       26            opcode
1       01            item count
2       96            module id = playback manager
3       VV            level byte
```

Observed pinned at `19` (25 decimal) and constant across an entire 274-packet
Bass sweep — it does **not** track the slider. Treated as a mode/keepalive the
control panel re-asserts, interleaved 1:1 with the `0x20` writes. Not required
per value. May need to be sent once at init; test empirically.

### `0x23` — device control (many subcommands)

`0x23` is not one command but a subcommand space, selected by byte 1. The
panel-open capture exercises sixteen of them:

| Sub | Query | Response body | Meaning |
|---|---|---|---|
| `04` | `23 04 00` | `00 02 00 …` | undecoded |
| `05` | `23 05 00` | `00 00 01 31 3c 01 50` | undecoded |
| `05` | `23 05 01` | `00 01 02 3f 3f` | undecoded |
| `06` | `23 06 01` | `00 00 …` | undecoded |
| `0a` | `23 0a 00` | `00 02 …` | undecoded |
| `12` | `23 12 00` | `00 00 …` | undecoded |
| `23` | `23 23 01 <EN>` | echoes flag | SBX master enable/disable |
| `24` | `23 24 00` | `00 01 00 01` | SBX master commit / read |
| `25` | `23 25 00` | `00 03 00 01` | undecoded |
| `26` | `23 26 00` | `00 03 00` | undecoded |
| `27` | `23 27 01` | `00 00 64` | keepalive / master-sync |
| `28` | `23 28 01` / `02` | `00 00` / `00 03` | undecoded |
| `2a` | `23 2a 00` | streams parameter ranges | **parameter info** (below) |
| `4c`, `4d` | `23 4c 00` | `80 00 …` | **not supported** |

**A subcommand the device does not implement answers with `0x80` in byte
3.** `23 4c` and `23 4d` both come back `00 23 4c 80`. That makes the space
safe to sweep: a bare `23 <sub>` query with no payload either returns a
status report or is refused. `sbx-e5 probe` does exactly that.

Creative's SoundCore protocol has a `FEATURECONTROL` command carrying
headphone high gain, direct mode, S/PDIF direct and restore-defaults as a
bitmask (see `android-protocol-tables.md`). On this HID transport it is
most likely one of the undecoded `0x23` subcommands above. Which one is not
yet known — it needs either a capture of the Windows panel toggling one of
those switches, or a `probe` run on hardware.

The master-switch subcommands, in detail:

**`23 23` — SBX enable/disable.** Byte 3 is the flag.

```
offset  bytes     meaning
0       23         opcode = SBX master
1       23         subcommand = enable/disable
2       01         fixed
3       EN         01 = ON, 00 = OFF
4..63   00         pad
```

| State | Report prefix |
|---|---|
| SBX ON | `23230101` |
| SBX OFF | `23230100` |

`23 23 01 01` precedes each fade-in, `23 23 01 00` precedes each fade-out.
Its own response on interrupt IN echoes the flag: `00 23 23 00 01 <EN>`.

**`23 24` — commit / read.** Always sent immediately after `23 23`, but also
works as a **standalone status query** with no preceding write: sent alone
(`23 24 00`, no flag byte) it returns the current master state on the same
response shape, making it the read half of this switch.

```
offset  bytes     meaning
0       23         opcode = SBX master
1       24         subcommand = commit / read
2..63   00         pad (query has no payload)
```

Response (interrupt IN, ep `0x83`, 16 bytes):

```
offset  bytes     meaning
0       00         leading zero / status
1       23         echoes opcode
2       24         echoes subcommand
3       00
4       ST         current master state: 01 = ON, 00 = OFF
5       00
6       01
7..     00         pad
```

| Query | Response | Meaning |
|---|---|---|
| `23 24 00` | `00 23 24 00 01 00 01` | master is ON |
| `23 24 00` | `00 23 24 00 00 00 01` | master is OFF |

**`23 27 01` — keepalive/master-sync.** Fires periodically on its own, not
correlated to any value or toggle.

After each toggle the panel also replays the `0x26 01 96 xx` level ramp
(`00 02 04 07 09 18`) — cosmetic fade to/from the effect setpoint, not part of
the enable state.

### `0x23 0x2a` — parameter info (ranges)

A single `23 2a 00` query makes the device stream one report per
(parameter, field). This is the device's own declared range table, and it
overrides Creative's cross-product Android library wherever the two differ.

```
offset  bytes              meaning
0       00                 leading zero / status
1       23                 echoes opcode
2       2a                 echoes subcommand
3       00
4       KK                 field: 80 = max, 90 = min, a0 = step
5       MM                 module id (96 = playback)
6       II                 parameter id
7..10   <f32 LITTLE-endian> the value
```

**Note the byte order.** Unlike the `0x20`/`0x26` value path, this report
carries the float **little**-endian. `00 00 96 43` is `300.0`.

Decoded from `captures/read.json`:

| Parameter | min | max | step |
|---|---|---|---|
| EQ preamp (`0x0a`) | `-6.0` | `6.0` | `1.0` |
| EQ band 0 (`0x0b`) | `-12.0` | `12.0` | — |
| XBass crossover (`0x17`) | `10.0` | `300.0` | `1.0` |

Only the parameters the panel happened to query appear. Creative's Android
library declares `-24..24` for a band, `-12..12` for the preamp and
`10..1000` for the crossover — those are the generic Sound Blaster figures;
the E5's own answers above are the ones this crate enforces.

## Read path (query → interrupt IN) — CONFIRMED

Wire-confirmed 2026-08-17 (`captures/read.json`, device address 9, bus 4 /
USBPcap4).
The driver does **not** use GET_REPORT (`bRequest=0x01`). Instead:

1. Write a query as a normal SET_REPORT (`0x21 09 0200 0003`, 64-byte report).
2. Read the response on the **interrupt IN endpoint `0x83`** (interface 3),
   16-byte HID input report. (This is what `HidD_GetInputReport` maps to — the
   HID input pipe, not a control read.)

The response echoes the query opcode in byte 1, so responses pair to queries.

**One query does not mean one report.** The endpoint carries unsolicited
reports too, so the next report off the pipe is often not the answer to the
query just sent. Around a master toggle the device emits four in a row:

```
OUT 23 23 01 01           enable write
IN  00 23 23 00 01 01     the write's own echo
OUT 23 24 00              commit / read query
IN  00 26 01 96 07 ...    unsolicited level ramp (crystalizer)
IN  00 26 01 96 18 ...    unsolicited level ramp (bass)
IN  00 23 24 00 01 00 01  the commit response -- fourth in the queue
```

A reader that takes the first report gets the `0x23 0x23` echo instead of
the `0x23 0x24` answer, and leaves three reports queued so every later read
is answered by a stale one. Read until a report actually matches the query
(echoed opcode, and for `0x26` the echoed parameter id), discarding the
rest, and treat a timeout as "the answer never came".

### Query report (out)

```
offset  bytes     meaning
0       <op>       query opcode: 0x3f, 0x22, 0x25 (observed)
1..     <sel>      optional selector byte(s) (0x25 uses 01, or 01 01)
...     00         zero pad to 64
```

### Response (interrupt IN, ep 0x83, 16 bytes)

```
offset  bytes     meaning
0       00         leading zero / status
1       <op>       echoes query opcode
2       <sel>      echoes selector
3..     <payload>  read-back value
...     00         pad
```

### `0x26` — GET_PARAM (the value read path)

This is the counterpart to `0x20` SET_PARAM, and the answer to "how do I read
a slider value back".

Query (SET_REPORT, 64 bytes, zero-padded):

```
offset  bytes     meaning
0       26        opcode = GET_PARAM
1       01        item count (we only ever ask for one)
2       96        module id = playback manager
3       II        parameter id  -- RAW id, not the id<<1 write selector
4..63   00        zero pad
```

`0x96` is `MALCOLM_MODULE_ID_PLAYBACK_MGR`, the module a parameter belongs
to. `0x95` is the microphone / voice-input module, `0x8F` room calibration,
`0x80` master control. Full tables in `android-protocol-tables.md`.

Response (interrupt IN, ep `0x83`, 16 bytes):

```
offset  bytes              meaning
0       00                 leading zero / status
1       26                 echoes opcode
2       01                 item count
3       00                 more-items flag (00 in every observed response)
4       96                 echoes module id
5       II                 echoes parameter id
6..9    <f32 big-endian>   the value
10..15  00                 pad
```

**Critical difference from the write path:** the query carries the *raw*
parameter id (`BASS_LEVEL` = `0x19`), **not** the `id << 1` selector the
`0x20` write path uses (`0x32`). The read path does not double the id.

**The module byte is substitutable.** Byte 2 is not fixed at `0x96`: the
same capture has the panel query `26 01 95 06` — module `0x95`
(voice input), parameter `0x06` (VoiceFocus enable) — and the device answer
`00 26 01 00 95 06 00000000`. So the whole microphone parameter table is
*readable* today by changing that byte. Whether it is writable the same way
is untested, and a write is not reversible the way a read is.

#### Decoded panel-open state sync

Every id below maps 1:1 onto `transport::id::*`, and every value is a clean,
plausible control-panel reading — enables are exact `0.0`/`1.0`, levels are
sane slider positions:

| id | Parameter | Value read |
|---|---|---|
| `0x00` | Surround enable | `0.0` (off) |
| `0x01` | Surround level | `0.12` |
| `0x02` | Dialog Plus enable | `0.0` (off) |
| `0x03` | Dialog Plus level | `0.5` |
| `0x04` | Smart Volume enable | `0.0` (off) |
| `0x05` | Smart Volume level | `0.74` |
| `0x06` | Smart Volume mode | `0.0` |
| `0x07` | Crystalizer enable | `1.0` (on) |
| `0x08` | Crystalizer level | `0.64` |
| `0x17` | Bass crossover (Hz) | `80.0` — the device default; not normalized |
| `0x18` | Bass enable | `1.0` (on) |
| `0x19` | Bass level | `0.5` |

Raw vectors:

| Query prefix | Response prefix | Decoded |
|---|---|---|
| `26019619` | `002601009619 3f000000` | Bass level = 0.5 |
| `26019618` | `002601009618 3f800000` | Bass enable = 1.0 |
| `26019608` | `002601009608 3f23d70a` | Crystalizer level = 0.64 |
| `26019605` | `002601009605 3f3d70a4` | Smart Volume level = 0.74 |
| `26019601` | `002601009601 3df5c28f` | Surround level = 0.12 |
| `26019617` | `002601009617 42a00000` | Bass crossover = 80.0 Hz |

The `0x17` reading is the one value that is not normalized `0..1`: it is
the SBX Bass crossover in Hz, at its default of `80.0` (range `10..=1000`,
step 1). The read is capture-confirmed; the *write* has never been
exercised on hardware.

### Other status reads

| Query | Response (`usbhid.data`) |
|---|---|
| `3f 00` | `00 3f 00 01 01 00…` |
| `22 00` | `00 22 00 00 00 00…` |
| `25 01` | `00 25 01 00 01 00…` |
| `25 01 01` | `00 25 01 00 01 01 00…` |

**Scope caveat:** `3f 00`, `22 00`, and `25 01`/`25 01 01` are small
status/flag reads (likely `GetContext`/`GetFeatureInfo`-style) whose
semantics remain undecoded — they are not the SBX master switch, which
uses `23 24` (see above). The read opcodes seen on the wire are `0x26`
(parameter values), `0x23` (master), and `0x3f`/`0x22`/`0x25` (undecoded
status).

### Rust read path

```rust
// write_control(0x21, 0x09, 0x0200, 3, &query, TIMEOUT);
// read_interrupt(0x83, &mut buf16, TIMEOUT);   // NOT a control GET_REPORT
```

## Verified test vectors

Exact bytes captured from the driver (first 14 bytes of the report):

| Meaning | Report prefix (hex) |
|---|---|
| Bass 0.50 | `2000160ad502083220963f000000` |
| Bass 0.55 | `2000160ad502083220963f0ccccd` |
| Bass 1.00 | `2000160ad502083220963f800000` |
| Surround 0.55 | `2000160ad502080220963f0ccccd` |
| `0x26` level 25 | `26019619` |
| `0x23` master | `2327010000000000` |

## Encoder (reference)

```rust
const REQ_TYPE:   u8  = 0x21;   // host→device, class, interface
const SET_REPORT: u8  = 0x09;
const OUT_REPORT: u16 = 0x0200; // Output report, ID 0
const HID_IFACE:  u16 = 3;

const HDR:  [u8; 6] = [0x00, 0x16, 0x0a, 0xd5, 0x02, 0x08];
const TAIL: [u8; 2] = [0x20, 0x96]; // 0x96 = playback module id

fn encode_set_param(param: u8, value: f32) -> [u8; 64] {
    let mut r = [0u8; 64];
    r[0] = 0x20;
    r[1..7].copy_from_slice(&HDR);
    r[7] = param;                                 // 0x02 Surround, 0x32 Bass
    r[8..10].copy_from_slice(&TAIL);
    r[10..14].copy_from_slice(&value.to_be_bytes()); // BIG-endian f32
    r
}

// write_control(REQ_TYPE, SET_REPORT, OUT_REPORT, HID_IFACE, &report, TIMEOUT)
```

## Open items

- Identify which `0x23` subcommand carries Creative's feature-control block
  (headphone high gain, direct mode, S/PDIF direct, restore defaults).
  `sbx-e5 probe` sweeps the space read-only; the alternative is a capture of
  the Windows panel toggling one of those switches.
- Decode the remaining `0x23` subcommands: `04`, `05`, `06`, `0a`, `12`,
  `25`, `26`, `28`.
- Determine whether writes accept a module byte other than `0x96`, which
  would make the microphone table reachable. Reads already do.
- Determine whether `0x26`/`0x23 27` reports are required at init or purely
  cosmetic (send only the `0x20` float, or only `0x23 23`/`0x23 24`, and
  listen).
- Decode the `0x3f`/`0x22`/`0x25` status reads (map to Get* semantics).

The `id << 1` rule is settled for the implemented table: every effect in it
was toggled on an E5 and heard to do the right thing. Ids *outside* that
table are known — they are ordinals of Creative's own parameter enum, see
`android-protocol-tables.md` — but no write to one has been exercised on an
E5, so each is still unproven on this transport.

## Unimplemented features (leads)

Each still needs its addressing on this transport pinned down, either by a
capture of the Windows panel exercising the control or by `sbx-e5 probe`.

Microphone side (CrystalVoice) — the largest gap. Every stock E5 profile
sets values for all of these, so they are real controls on this hardware
rather than driver-family leftovers:

| Feature | Evidence |
|---|---|
| Mic noise reduction | Shipped `enable="true"` in every profile; driver carries matched `NoiseReductionState`/`NoiseReductionLevel` properties |
| Mic AEC | `aec` present in every profile |
| Mic smart volume | `vip_svm` with a real level (`0.74`) |
| VoiceFX | `voicefx` with a preset index; nine tunable params in the enums |
| Mic EQ | `mic_eq` with a preset; per-band level/frequency/width |

Every one of these has a known parameter id in the voice-input module
(`0x95`) — see `android-protocol-tables.md` — and all of them are already
*readable*, because the `0x26` query takes the module byte directly. What is
missing is whether a `0x20` write accepts the same substitution; every
captured write targets the playback module (`0x96`). VoiceFX and Mic EQ
presets are bundles of continuous parameters, so they ride the ordinary
`0x20` float path.

Output-side switches. Creative groups these four into one feature-control
message, so whichever `0x23` subcommand carries it reaches all four at once:

| Feature | Ordinal in the feature-control bitmask |
|---|---|
| Restore defaults | 3 |
| Direct mode (bypass the DSP) | 5 |
| Headphone high gain | 6 |
| S/PDIF input direct | 7 |

Other device hardware:

| Feature | Evidence |
|---|---|
| LED control | Driver sets `XoutLedState` at init/mute/active transitions with small ints (1/2/3); meaning of each value unknown |
| USB power overdrive | Registered by name in the driver's subdevice table, alongside known-real entries |
| Jack selector | Creative exposes line-in / mic-in / optical-in selection; input side only |
| Direct monitoring | Per-input enables plus `Mic1Level`/`Mic2Level` |
| Bluetooth auto-connect | One `BluetoothAutoConnect_isEnabled` property in the driver's constant table |
| Battery | No hits in the driver's constants, but the SoundCore command set carries `BATTERYLEVEL` and `BATTERYSTATUS`, with an E5-specific response quirk |

Not applicable to the E5 — these belong to other products sharing this
driver, and the hardware has no path for them: Dolby/DTS decode and encode,
EAX/EAX3, reverb, pitch shift, speaker calibration, bass management,
karaoke, mic-array beamforming.

Deliberately excluded: master volume and mute, speaker EQ, calibrator
headroom and speaker configuration. Creative's own software forbids
third-party clients from writing these.

The E5's own device constructor is selected by a per-PID factory that
gives it a larger context than sibling products get, and fills in a
handler table -- the best available answer to which features this device
really implements.

## Captures

All in `captures/` (JSON exports of Wireshark/USBPcap sessions):

- `capture_bass.json` — Bass 0→100% slider sweep, 274 packets, selector
  `0x32` only. The definitive `0x20` SET_PARAM value-path capture.
- `read.json` — panel-open state sync, address 9 / USBPcap4. Contains the
  confirmed read handshake (query out → interrupt IN on ep 0x83).
- `sbx.json` — two full SBX master on/off cycles. Contains the confirmed
  `23 23 01 <flag>` write and its `23 24 00` commit.
