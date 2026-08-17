# Capturing the SBX master on/off switch

The goal of this document is narrow and concrete: **determine the exact
bytes the Windows driver puts on the USB bus when you click the SBX master
button**, and confirm what the `0x25` status query actually reads.

Everything else about the control protocol is already resolved — see
`reverse/e5-control-protocol.md` for the full picture. The master switch is
the one piece that has resisted every capture so far, because every capture
taken until now happened to avoid it:

- The **slider-sweep captures** (Bass 0→100%, etc.) only ever moved levels,
  never touched the master button.
- The **panel-open capture** (`reverse/read.json`) recorded the poll
  sequence a fresh window issues on open, which includes a `0x25 01 <sub>`
  status query — but the button was never clicked *during* that capture, so
  there's no before/after to compare.

`sbx-e5 sbx on|off` currently sends a guessed write built on the `0x25`
read's shape (`transport::encode_set_sbx_master_guess` in `src/transport.rs`)
and it does not work on real hardware. This document is how to fix that with
a real capture.

## Prerequisites

- A Windows machine with the Creative Sound Blaster E-Series control panel
  installed and the E5 recognized.
- Wireshark with **USBPcap** installed (tick it during the Wireshark
  installer; it's off by default). Reboot after installing.
- Run Wireshark **as Administrator** — USBPcap needs it.

If you've captured this device before, skip to "Capture" — the setup below
is the same steps `reverse/e5-control-protocol.md`'s existing captures used.

## Find the right interface and device address

1. Open Wireshark as Administrator. You'll see `USBPcap1`, `USBPcap2`, … —
   one per root hub, not per device.
2. Plug in (or replug) the E5, open the Creative control panel, and watch
   which `USBPcapN` interface shows traffic when you move a slider. That's
   the one to capture on.
3. **The E5's `usb.device_address` is not stable across replugs or
   reboots** — it has been seen as both 17 and 9 in past captures. Don't
   hardcode it; re-derive it from the capture itself (see step 2 under
   "Capture" below).

## Capture

Keep this capture **short and isolated**. Every previous capture in this
repo mixed multiple actions together, which is exactly what makes the
master switch ambiguous — don't repeat that here.

1. Start capturing on the correct `USBPcapN` interface.
2. Open the Creative control panel with the capture already running, and
   let it sit for a second or two. This reproduces the panel-open poll
   sequence documented in `reverse/e5-control-protocol.md` ("Read path"),
   which gives you a landmark to line up against — you'll see the same
   `3f 00`, `23 27 01`, `22 00`, `25 01 …` pattern.
3. Click the SBX master button **off**. Wait ~1 second.
4. Click it **on**. Wait ~1 second.
5. Click it **off** again. Wait ~1 second.
6. Stop the capture. **Do not touch any other slider or toggle** in this
   capture — if the master click is the only user action, there's no
   ambiguity about which write did it.

## Filter down to the relevant traffic

First, find the device address. Filter on any known-good write to confirm
it:

```
usbhid.setup.wIndex == 3 && usbhid.setup.bRequest == 0x09
```

Note the `usb.device_address` on those packets — that's your E5 for this
session. Then narrow everything below to it, e.g. `usb.addr contains
"4.9"` for bus 4, device 9.

**Outbound writes** (what the click sends):

```
usb.bmRequestType == 0x21 && usbhid.setup.wIndex == 3
```

This is every `SET_REPORT` on the HID control interface — the same shape
every `0x20`/`0x25`/`0x26`/`0x23` write in this protocol uses. Look at
`usb.data_fragment` for the payload.

**Inbound reads** (what the panel hears back), if the panel re-queries
state after a click the way it does on open:

```
usb.endpoint_address == 0x83
```

This is the interrupt IN endpoint every `0x26`/`0x25` response arrives on
— **not** a control transfer, and **not** `bRequest == 0x01` GET_REPORT.
See `usbhid.data` for the payload.

## What to look for

You're hunting for **exactly one new SET_REPORT** appearing at each click,
distinct from the panel-open poll sequence you already recognize from step
2. Note, for the write right after each click:

- The full payload (`usb.data_fragment`, right-click → Copy → as Hex
  Stream).
- Whether it reuses opcode `0x25` (like the read) or a different byte
  entirely — `0x20` is taken (SET_PARAM/value writes) and `0x26` is taken
  (GET_PARAM/commit), so a plausible guess is a new use of `0x25`, `0x23`,
  or a byte not seen at all yet.

Then **diff the "off" write against the "on" write** byte for byte. The
bytes that differ are the write's payload encoding; everything constant
around them is fixed framing, matching the pattern every other opcode in
`reverse/e5-control-protocol.md` follows (opcode, echo/subcommand bytes,
then the field that actually varies).

If the panel also re-queries status after the click, do the same diff on
the **response** that follows — compare it against the two `0x25 01 <sub>`
responses already documented (`00 25 01 00 00 01 …` vs `00 25 01 00 01 01
…`). If the state byte at offset 4 now visibly flips in step with your
clicks, that confirms (or replaces) the existing guess for what `SS` in
`25 01 SS` actually selects.

## Save it

`File → Save As` → pcapng, or export as JSON for the same decode-script
workflow the panel-open capture used
(`File → Export Packet Dissections → As JSON`, or `tshark -r capture.pcapng
-T json`). Save it under `reverse/captures/` with a name that says what it
contains, e.g.:

```
reverse/captures/sbx-master-off-on-off.pcapng
```

## Feeding the result back into the code

Once you have the confirmed write bytes:

1. Open `src/transport.rs`.
2. Replace the body of `encode_set_sbx_master_guess` with the real payload,
   and rename it (drop `_guess`) once it's confirmed rather than
   extrapolated.
3. If the read semantics changed too, update `encode_get_status` and
   `decode_get_status_response` to match.
4. Add a unit test in `mod tests` asserting the encoder reproduces the
   captured bytes exactly — paste the hex stream straight from Wireshark,
   following the style of `get_param_query_matches_captured_vectors` and
   `get_status_query_and_response_match_captured_vectors` already in that
   module.
5. Update `reverse/e5-control-protocol.md`'s `0x25` section: move it from
   "response shape confirmed, semantics partial" to fully `Captured`, and
   remove the "Tried on real hardware... does not work" note once it does.
6. Update `README.md`'s TODO list and add a dated `CHANGELOG.md` entry.
7. Verify on hardware:

   ```sh
   sbx-e5 sbx off   # click SBX button on the Windows side beforehand? no —
                    # run this on Linux and confirm the panel light / audible
                    # effect actually changes.
   sbx-e5 sbx on
   ```

   A device that silently ignores a malformed write looks identical to
   success from the host side, so the read-back check already wired into
   `set_sbx_master_guess` (compare the value sent against what `0x25`
   reads afterward) is the best available signal short of listening for
   the audible SBX effect toggling.

## Troubleshooting

**No `USBPcap` interfaces in Wireshark.** It wasn't installed, or
Wireshark isn't elevated. Re-run the Wireshark installer and tick USBPcap;
launch as Administrator.

**Capture is empty.** Wrong root hub, or the device wasn't attached after
USBPcap's filter driver loaded. Replug the E5 after starting the capture.

**No new write appears at the click, only the same poll sequence.** The
panel may debounce or batch the click, or query state without writing
anything if the master switch is actually stored client-side and only
applied by re-sending every parameter's current value as `0x20` writes.
If that's the case, look for a burst of `0x20` SET_PARAM writes
immediately after the click instead of a single dedicated opcode.

**The state byte doesn't change on click.** The `SS` sub-selector in
`25 01 SS` may address something else entirely (there were two different
`SS` values in the panel-open poll — `0x00` and `0x01` — and this document
assumed one of them was master without confirmation). Try both sub-bytes
against the click, and check whether a *third*, uncaptured `SS` value
appears once the panel has something to report after a real toggle.
