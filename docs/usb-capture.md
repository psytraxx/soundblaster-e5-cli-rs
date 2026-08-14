# Capturing the E5 control protocol with Wireshark

The goal of this document is narrow and concrete: **determine the exact
bytes the Windows driver puts on the USB bus when you move the Bass
slider.** That single fact is the only thing blocking `src/transport.rs`
from being real.

Everything else about the protocol is already known — the
`(Feature, param, value)` triple, every feature id, every parameter id. See
the README. What we cannot derive statically is how a triple is framed into
a USB control transfer, because on Windows that translation happens inside
`KsUSBaud.sys`.

## Why Windows, not Linux

You can only capture what something is already sending. On Linux nothing
speaks this protocol yet — that's the whole problem. The Creative control
panel on Windows *does*, so that's where the ground truth is.

A Linux `usbmon` capture is still useful later, to verify our own output
matches. That's covered at the end.

---

## Part 1 — Windows capture (the important one)

### Setup

1. A Windows machine (a VM works **only** if you can pass the physical USB
   device through — VirtualBox/VMware USB passthrough is fine; WSL2 is not).
2. Install Creative's driver: `SBE_PCDRV_L9_1_05_04.exe`. Confirm the
   Sound Blaster E-Series control panel opens and shows the E5.
3. Install [Wireshark](https://www.wireshark.org/download.html). During
   setup, **tick "Install USBPcap"** — it is not selected by default and is
   what makes USB capture possible on Windows.
4. Reboot. USBPcap installs a filter driver on the USB stack.

### Find the right interface

Open Wireshark as **Administrator**. In the interface list you'll see
`USBPcap1`, `USBPcap2`, … — one per root hub, not per device.

To find which one the E5 is on, click each and watch for traffic while
moving a slider, or use USBPcap's own listing:

```
"C:\Program Files\USBPcap\USBPcapCMD.exe"
```

It prints each root hub with the devices beneath it. Note the hub with the
E5 and its **device address** (e.g. `\\.\USBPcap2`, device 5).

> If the E5 doesn't appear, unplug and replug it — USBPcap enumerates at
> attach time. Capturing on a hub the device joined *before* the capture
> started can miss the descriptor exchange.

### Capture

1. Start capturing on the correct `USBPcapN` interface.
2. Let it sit ~2 seconds without touching anything (establishes a baseline
   of idle/polling traffic).
3. In the Creative control panel, move **only the Bass slider**, to a value
   you write down — pick something with a distinctive float encoding, e.g.
   **0.5**.
4. Wait ~2 seconds. Stop the capture.

Keep it short. A few seconds of audio streaming is thousands of isochronous
packets; you want the control transfers to stand out.

### Filter down to control transfers

Audio streaming is isochronous noise. Paste this display filter:

```
usb.transfer_type == 0x02
```

That's control transfers only. To narrow to vendor-specific requests — which
is what the driver's `0x40`/`0xC0` request types imply:

```
usb.bmRequestType == 0x40 || usb.bmRequestType == 0xc0
```

| `bmRequestType` | Meaning |
|---|---|
| `0x40` | host→device, vendor, recipient = device |
| `0x41` | host→device, vendor, recipient = interface |
| `0xC0` | device→host, vendor, recipient = device |
| `0xC1` | device→host, vendor, recipient = interface |
| `0x21` / `0xA1` | class request (audio) — probably *not* what we want |

Combine with the device address to exclude other hardware:

```
usb.device_address == 5 && usb.transfer_type == 0x02
```

### The shortcut: search for the value you set

This is the fastest way to find the packet, and it works because we already
know how the value is encoded — little-endian `f32`.

If you set Bass to **0.5**, the payload contains `00 00 00 3F`. Filter:

```
usb.capdata contains 00:00:00:3f
```

Better still, search for the **feature id**, which is fixed for bass
(`0x1000_0020`, little-endian `20 00 00 10`):

```
usb.capdata contains 20:00:00:10
```

Useful float encodings for setting sliders to round values:

| Value | LE bytes |
|---|---|
| `0.0` | `00 00 00 00` |
| `0.25` | `00 00 80 3E` |
| `0.3` | `9A 99 99 3E` |
| `0.5` | `00 00 00 3F` |
| `1.0` | `00 00 80 3F` |

If neither the feature id nor the float appears anywhere, that itself is a
finding: the value is not passed as a raw LE float, and is likely scaled to
an integer (try `0..100`, `0..255`, or a fixed-point Q-format) or the
transport is not control transfers at all — check for interrupt OUT
(`usb.transfer_type == 0x01`) or HID reports.

### What to record

For the packet you identify, note every field in the **URB Setup** tree:

- `bmRequestType`
- `bRequest` ← the vendor request code, currently guessed as `0x03`
- `wValue`
- `wIndex` ← likely the interface number
- `wLength`
- the full data payload (right-click → Copy → …as a Hex Stream)

Then **repeat with a second value** (e.g. Bass 1.0) and diff the two
packets. Only the bytes that changed encode the value; everything constant
is framing. This one comparison resolves most ambiguity.

Do the same for a different effect — Surround, feature `0x1000_0200`
(`00 02 00 10`) — to confirm which field carries the feature id.

### Save it

`File → Save As` → pcapng. Drop it in `reverse/captures/` and note in the
filename what was changed:

```
reverse/captures/bass-0.5-then-1.0.pcapng
```

---

## Part 2 — Linux verification (later)

Once `sbx-e5` sends something, capture our own traffic and compare it to the
Windows reference.

```sh
sudo modprobe usbmon
# find the bus the E5 is on
lsusb | grep 041e
# e.g. "Bus 001 Device 007: ID 041e:323c"
```

Capture bus 1 in Wireshark (interface `usbmon1`), or headless:

```sh
sudo tcpdump -i usbmon1 -w e5.pcap
```

Then run a command and compare against the Windows capture:

```sh
sbx-e5 bass 0.5
```

The same display filters apply. If our packet is byte-identical to the
Windows one, the transport is correct.

You can also see control traffic without Wireshark:

```sh
sudo cat /sys/kernel/debug/usb/usbmon/1u
```

---

## Part 3 — Feeding results back into the code

Once the framing is known:

1. Open `src/transport.rs`.
2. Set `REQ_SET_PARAM` / `REQ_GET_PARAM` to the observed `bRequest`.
3. Adjust the `encode()` arm for the correct layout, or add a new
   `Framing` variant if it matches neither existing candidate.
4. Fix `write_control`'s `wValue` / `wIndex` to match.
5. Add a unit test in `mod tests` asserting the encoder reproduces the
   captured bytes exactly — paste the hex stream straight from Wireshark.
6. Update `CHANGELOG.md` with a dated entry, and drop the "unverified"
   caveats from `README.md` / `CLAUDE.md` **only after** an audible A/B test
   confirms it.

Verify on hardware in this order:

```sh
sbx-e5 info                 # is there a vendor-specific (0xff) interface?
sbx-e5 --dry-run bass 0.5   # do our bytes match the capture?
sbx-e5 bass 0.0             # play music, listen
sbx-e5 bass 1.0             # audible difference?
```

A round-trip read is the strongest signal that the device *parsed* the
request rather than ignoring a malformed one — a device that silently drops
unknown control transfers looks identical to success from the host side.

---

## Troubleshooting

**No `USBPcap` interfaces in Wireshark.** It wasn't installed, or Wireshark
isn't elevated. Re-run the Wireshark installer and tick USBPcap; launch as
Administrator.

**Capture is empty.** Wrong root hub. Try each `USBPcapN`, or replug the
device after starting the capture.

**Drowning in isochronous packets.** Apply the display filter *before*
scrolling, and stop playback while capturing — the control transfers still
work with no audio playing.

**Slider moves but no control transfer appears.** The control panel may
batch writes, or only commit on release. Try toggling the effect on/off
instead, which must produce a discrete write.

**Nothing looks like our feature ids.** `KsUSBaud.sys` may reformat the
triple entirely rather than forwarding it. In that case capture becomes the
*primary* source of truth and the metadata only tells us the semantics —
map observed packets to slider identities empirically, one effect at a time.
