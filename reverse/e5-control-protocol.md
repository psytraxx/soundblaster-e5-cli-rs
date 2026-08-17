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
8..9    20 96                fixed
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
1       01            subcommand
2       96            scale/max = 150
3       VV            level byte, 0..150
```

Observed pinned at `19` (25 decimal) and constant across an entire 274-packet
Bass sweep — it does **not** track the slider. Treated as a mode/keepalive the
control panel re-asserts, interleaved 1:1 with the `0x20` writes. Not required
per value. May need to be sent once at init; test empirically.

### `0x23` — master/keepalive

```
23 27 01 00 00 00 00 00
```

Appears periodically (roughly every ~80–160 param writes), not correlated to
any value. Master enable / heartbeat.

## Read path (query → interrupt IN) — CONFIRMED

Wire-confirmed 2026-08-17 (`read.json`, device address 9, bus 4 / USBPcap4).
The driver does **not** use GET_REPORT (`bRequest=0x01`). Instead:

1. Write a query as a normal SET_REPORT (`0x21 09 0200 0003`, 64-byte report).
2. Read the response on the **interrupt IN endpoint `0x83`** (interface 3),
   16-byte HID input report. (This is what `HidD_GetInputReport` maps to — the
   HID input pipe, not a control read.)

The response echoes the query opcode in byte 1, so responses pair to queries.

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

### `0x26` — GET_PARAM (the value read path) — CONFIRMED

This is the counterpart to `0x20` SET_PARAM, and the answer to "how do I read
a slider value back".

Query (SET_REPORT, 64 bytes, zero-padded):

```
offset  bytes     meaning
0       26        opcode = GET_PARAM
1       01        subcommand (matches the 0x26 write shape)
2       96        scale/max = 150
3       II        parameter id  -- RAW id, not the id<<1 write selector
4..63   00        zero pad
```

Response (interrupt IN, ep `0x83`, 16 bytes):

```
offset  bytes              meaning
0       00                 leading zero / status
1       26                 echoes opcode
2       01                 echoes subcommand
3       96                 echoes scale
4       ??                 (00 in every observed response)
5       II                 echoes parameter id
6..9    <f32 big-endian>   the value
10..15  00                 pad
```

**Critical difference from the write path:** the query carries the *raw*
parameter id (`BASS_LEVEL` = `0x19`), **not** the `id << 1` selector the
`0x20` write path uses (`0x32`). The read path does not double the id.

#### Decoded panel-open state sync (`read.json`)

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
| `0x17` | (unmapped) | `80.0` — note: not 0..1, likely a gain/dB or Hz |
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
| `26019617` | `002601009617 42a00000` | id 0x17 = 80.0 |

The `0x17 = 80.0` reading is the one value that is not normalized `0..1`;
it is not in the current `id` table and its meaning is unresolved.

### `0x25` — status/master query — response shape confirmed, semantics partial

```
query:     25 01 SS 00…          SS = sub-selector byte (offset 2)
response:  00 25 01 00 VV 01 …   VV = state byte at offset 4
```

Two distinct sub-queries observed in the same panel-open poll sequence
(~0.14s apart, both in one session -- **not** a before/after toggle):

| Time | Query | Response | Byte @ offset 4 |
|---|---|---|---|
| 4.5854 | `25 01 00` | `00 25 01 00 00 01` | `0x00` |
| 4.7244 | `25 01 01` | `00 25 01 00 01 01` | `0x01` |

The response shape (echo opcode/sub at 1-2, single state byte at 4) is
solid. What's *not* established: whether `SS` selects "which switch"
(master vs. some other on/off) or the state byte is what changed and `SS`
is incidental -- these were captured back-to-back in one poll batch, not
across a user action, so there is no before/after to pin the meaning down.
Treat this as "a `0x25 01 xx` query returns a boolean," not yet as
"confirmed SBX master read." Needs a capture with the SBX button toggled
mid-session and the same `SS` value queried both before and after.

**Tried on real hardware 2026-08-17: does not work.** `sbx-e5 sbx on|off`
both reads the wrong thing and fails to write anything -- confirming the
caveat above was not just theoretical. `id::get_sbx_master`'s `SS=0x01`
guess is not actually the master switch (or is, but the write guess
`encode_set_sbx_master_guess` does nothing), and there is still no captured
SET for this switch at all. See "Capturing the SBX master toggle" below.

### Other status reads (decoded shape, semantics open)

| Query | Response | Note |
|---|---|---|
| `3f00` | `003f00010100…` | probed first on every panel open — likely a version/hello |
| `2200` | `002200000000…` | all-zero response |
| `232701` | `00232701006400…` | `0x64`=100 — polled ~28x, a level/keepalive poll |
| `232a00` | `00232a008096 17 0000 9643…` | carries id+f32 pairs (`0x17`→300.0, `0x0a`, `0x0b`); an EQ-band or range table |
| `230500` | `002305000001313c0150…` | fixed blob, appears twice per open |

The static-disassembly opcode guess (`0x8001000`, `0x50`/`0x52`) is
**disproven** — real read opcodes are `0x26` (values), `0x25` (SBX master),
and `0x23`/`0x3f`/`0x22` (status).

### Rust read path

```rust
// write_control(0x21, 0x09, 0x0200, 3, &query, TIMEOUT);
// read_interrupt(0x83, &mut buf16, TIMEOUT);   // NOT a control GET_REPORT
```

## Capturing the SBX master toggle (open, needed)

Every other opcode in this document was resolved from a **panel-open state
sync** or a **slider sweep** -- neither exercises the master on/off button.
To get the write (and pin down what the `0x25` read actually reads), the
capture has to bracket a manual click on the SBX button itself.

1. Follow the general Wireshark/USBPcap setup used for every other capture
   in this file: install USBPcap, start Wireshark, filter on the E5's
   `usb.device_address` (re-derive it per session -- see the note at the
   top of this doc), start capturing *before* touching anything in the
   Windows control panel.
2. Open the Creative control panel with the capture already running, and
   let it sit for a second or two -- this reproduces the `read.json`
   panel-open poll sequence, which is useful as a landmark to line up
   against.
3. Click the SBX master button **off**, wait ~1s, click it **on**, wait
   ~1s, click it **off** again. Isolate this from every other action --
   don't touch a slider or another toggle in the same capture, so there's
   no ambiguity about which write did what.
4. Stop the capture, export as JSON (`File > Export Packet Dissections >
   As JSON`, or `tshark -r capture.pcapng -T json`), and save it as
   `reverse/read.json` (or a new file) so the decode script pattern used
   for the panel-open sync applies unchanged.
5. In the export, look at the `SET_REPORT` (`usb.bmRequestType == 0x21`)
   writes issued right after each click -- filter on
   `usbhid.setup.wIndex == 3 && usbhid.setup.bRequest == 0x09` and
   `usb.data_fragment` for the payload. Compare the write immediately after
   the "off" click against the one after "on": whatever byte(s) differ
   between those two are the real write opcode and its off/on encoding.
6. Cross-check against the interrupt-IN responses (`usb.endpoint_address
   == 0x83`) that follow: if the control panel re-queries state right after
   the click (as it does on open), the response should now visibly change
   between the pre-click and post-click reads on whatever opcode/sub-byte
   this doc currently calls `0x25 01 01`. If it's a *different* sub-byte or
   a wholly different opcode, that supersedes the guess in
   `transport::encode_set_sbx_master_guess` and
   `transport::encode_get_status`.
7. Update this section and `src/transport.rs`'s `encode_set_sbx_master_guess`/
   `encode_get_status` with the confirmed bytes, move the row from
   `Confidence::Derived`-as-a-guess to `Captured`, and note it in
   `CHANGELOG.md`.

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
const TAIL: [u8; 2] = [0x20, 0x96];

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

- **TODO: SBX master read + write.** Confirmed not working on real hardware
  (2026-08-17) -- both `sbx-e5 sbx on|off` and the TUI's SBX master row are
  guesses that don't hold up. Needs the dedicated capture in "Capturing the
  SBX master toggle" above.
- Fill the param-selector table for remaining effects (capture each in isolation).
- Determine whether `0x26`/`0x23` reports are required at init or purely cosmetic
  (send only the `0x20` float and listen).
- Identify parameter id `0x17` (reads back `80.0`, not normalized `0..1`).
- Decode the `0x3f`/`0x22`/`0x23 0x2a` status reads (map to Get* semantics).
- Confirm the `0x25` sub-selector byte: both `25 01 00` and `25 01 01` were
  seen; whether the second byte selects *which* master or is a sequence
  counter is unresolved (state is unambiguously the response byte at off 4).
- Cross-check read ids against the write selector table: reads use the **raw**
  id, writes use `id << 1`. The read capture therefore independently confirms
  the raw-id half of every selector currently marked `Derived` — but not the
  doubling rule itself, which stays confirmed only for Bass/Surround.
- Audible A/B (`bass 0.0` vs `bass 1.0`) before dropping "unverified" caveats.

## Captures

- `capture.pcapng` — mixed session: SBX Studio toggle, Surround→55%, Bass enable→26%→disable.
- Bass 0→100% sweep (JSON export) — the definitive value-path capture.
- `read.json` — panel-open state sync, address 9 / USBPcap4. Contains the
  confirmed read handshake (query out → interrupt IN on ep 0x83).
