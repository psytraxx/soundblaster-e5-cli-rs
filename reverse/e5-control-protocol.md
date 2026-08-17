# Sound Blaster E5 — control protocol (USB capture analysis)

Derived from USBPcap captures of `KsUSBaud.sys` on Windows, 2026-08-17.
Device `041e:323c`, USBPcap device address 17, bus 2.

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

- Fill the param-selector table for remaining effects (capture each in isolation).
- Determine whether `0x26`/`0x23` reports are required at init or purely cosmetic
  (send only the `0x20` float and listen).
- GET_REPORT round-trip read (`bRequest=0x01`) as a parse-confirmation signal.
- Audible A/B (`bass 0.0` vs `bass 1.0`) before dropping "unverified" caveats.

## Captures

- `capture.pcapng` — mixed session: SBX Studio toggle, Surround→55%, Bass enable→26%→disable.
- Bass 0→100% sweep (JSON export) — the definitive value-path capture.
