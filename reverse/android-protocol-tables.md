# SoundCore protocol tables (from Creative's Android software)

Creative's Android apps carry the addressing tables for the same control
protocol the E5 speaks. This file records those tables and how much of each
this project implements.

## Sources

| APK | Package | What it holds |
|---|---|---|
| `sound-blaster-services-1-00-18.apk` | `svc.creative.aidlservice` | Headless transport service. Packet framing, the command opcode list, and Creative's list of parameters third-party clients are forbidden to write. No UI, no feature semantics. |
| `Sound+Blaster+Central_1.05.23_APKPure.apk` | `com.creative.central` | The full control app. Ships Creative's `com.creative.lib.soundcoreMgr` library, which contains the module ids, the parameter enums, and each parameter's declared range. |

Decompile with `jadx -d <outdir> <apk>`. The APKs themselves are not
committed (`.gitignore`).

Both apps target the E5 explicitly: `DEVICE_ID_SB_E5 = 12860` (`0x323C`,
matching `proto::PID_E5`), USB accessory model `SB1590`, Bluetooth name
`sound blaster e5` / `sb e5`.

## Transport

The Android apps and this project reach the same DSP over two different
links, with two different framings.

| | This project | Android apps |
|---|---|---|
| Link | USB HID, interface 3 | USB accessory (AOA) bulk, or Bluetooth SPP/RFCOMM |
| Framing | 64-byte zero-padded HID Output report via `SET_REPORT` (`0x21 09 0200 0003`); replies on interrupt IN `0x83`, 16 bytes | `5A <cmd> <len> <payload[len]>`, packets concatenated back-to-back in one read |
| Opcodes | `0x20` set, `0x26` get, `0x23` SBX master | `CtSoundCoreCommands`, e.g. `SETPARAM = 0x12`, `GETPARAM = 0x11` |

The two opcode spaces are unrelated — HID `0x26` is not SoundCore `0x26`.
The HID path is the right one for a Linux host: the accessory path needs the
device switched into Android accessory mode.

## Addressing model

A parameter is addressed by a **module id** and a **parameter id**. The
parameter id is the ordinal of an entry in that module's enum.

| Module id | Constant | Parameter enum |
|---|---|---|
| `0x49` | `MALCOLM_MODULE_ID_SWEEPTONE_MGR` | `etParamSweepTone` |
| `0x80` | `MALCOLM_MODULE_ID_MASTER_CONTROL_MGR` | `etParamMasterControl` |
| `0x8F` | `MALCOLM_MODULE_ID_ROOMCALIBRATION_MGR` | `etParamRoomCalibration` |
| `0x95` | `MALCOLM_MODULE_ID_VOICEINPUT_MGR` | `etParamVIP` — microphone side |
| `0x96` | `MALCOLM_MODULE_ID_PLAYBACK_MGR` | `etParam` — the module this project drives |
| `0x97` | `MALCOLM_MODULE_ID_DOLBYDIGITALDECODER_MGR` | `etParamDDD` |

On the SoundCore framing, a get carries `(module, param)` pairs and a set
carries `(module, param, f32)` items, both preceded by an item count. Our
HID frames carry the same fields:

```
GET query     26      01      96       19
              op      count   module   param

GET response  00      26      01      00     96       19      3f000000
              status  op      count    more  module   param   value (BE f32)

SET report    20  00 16 0a d5 02 08   32           20  96       3f000000
              op  fixed framing       param << 1       module   value (BE f32)
```

Module `0x96` is the only one this project addresses.

## Playback module `0x96` — parameter table

Values are normalized `0.0..=1.0` unless the table says otherwise.
"Restricted" marks parameters Creative's own software refuses to write from
a third-party client; this project leaves them alone for the same reason.

| id | Parameter | Status here |
|---|---|---|
| `0x00` | CMSS3D enable (the "Surround" switch) | implemented |
| `0x01` | CMSS3D immersion level | implemented |
| `0x02` | Dialog Plus enable | implemented |
| `0x03` | Dialog Plus strength | implemented |
| `0x04` | Smart Volume enable | implemented |
| `0x05` | Smart Volume strength | implemented |
| `0x06` | Smart Volume mode | implemented |
| `0x07` | Crystalizer enable | implemented |
| `0x08` | Crystalizer level | implemented |
| `0x09` | Graphic EQ enable | implemented |
| `0x0A` | EQ preamp gain (dB) | id known, no API |
| `0x0B`–`0x14` | EQ band 0–9 gain (dB) | implemented |
| `0x15` | Bass management enable | not implemented |
| `0x16` | Bass management crossover (Hz) | not implemented |
| `0x17` | XBass crossover (Hz) | implemented |
| `0x18` | XBass enable ("Bass") | implemented |
| `0x19` | XBass strength | implemented |
| `0x1A`–`0x1D` | Bass management speaker sizes (FL/FR, FC/LFE, RL/RR, SL/SR) | not applicable — E5 is 2.0 |
| `0x1E` | Subwoofer boost | not implemented |
| `0x1F` | Speaker EQ enable | restricted |
| `0x20` | Calibrator centre-EQ enable | not applicable |
| `0x21`–`0x28` | Calibrator channel level, 8 channels | not applicable |
| `0x29`–`0x30` | Calibrator channel inverse, 8 channels | not applicable |
| `0x31`–`0x38` | Calibrator channel delay, 8 channels | not applicable |
| `0x39` | Master volume | restricted |
| `0x3A` | Master mute | restricted |
| `0x3B` | Speaker EQ bypass gain | restricted |
| `0x3C` | Calibrator headroom | restricted |
| `0x3D` | Speaker configuration | restricted |
| `0x3E` | Line noise reduction enable | not implemented |

### Declared ranges

These are Creative's generic figures, shared across the Sound Blaster line.
Where the E5 reports its own range through the `23 2a` query it disagrees,
and the device wins — see `e5-control-protocol.md`. Known conflicts: EQ band
gain (device `±12`, not `±24`), EQ preamp (device `±6`, not `±12`), XBass
crossover (device max `300 Hz`, not `1000`).

Defaults are `min 0.0`, `max 1.0`, `step 1.0`, `default 0.0` unless listed.

| Parameter | min | max | default | step |
|---|---|---|---|---|
| Crystalizer enable | | | 1.0 (on) | |
| Crystalizer level | 0.0 | 1.0 | 0.0 | 0.01 |
| CMSS3D enable | | | 1.0 (on) | |
| CMSS3D immersion level | 0.0 | 1.0 | 0.0 | 0.01 |
| Dialog Plus strength | 0.0 | 1.0 | 0.0 | 0.01 |
| Smart Volume strength | 0.0 | 1.0 | 0.0 | 0.01 |
| Smart Volume mode | 0.0 | 1.0 | 0.0 | 1.0 |
| XBass strength | 0.0 | 1.0 | 0.5 | 0.01 |
| XBass / bass-management crossover | 10 Hz | 1000 Hz | 80 Hz | 1 |
| EQ preamp gain | −12 dB | +12 dB | 0 | 1 |
| EQ band gain | −24 dB | +24 dB | 0 | 1 |
| Mic EQ band gain | −24 dB | +24 dB | 0 | 1 |
| VoiceFocus wedge angle | 20 | 180 | 30 | 1 |

Smart Volume mode is declared over `0.0..=1.0` at step `1.0`, so Creative's
Android app only ever writes 0 or 1. `proto::SmartVolumeMode` carries a
third value, `Night = 2`, taken from the Windows control panel; that value
remains unconfirmed on hardware.

## Voice-input module `0x95` — parameter table

The microphone chain (CrystalVoice). None of it is implemented, and no write
to module `0x95` has ever been attempted from this project — every captured
write targets `0x96`. Probe with non-destructive `0x26` reads before writing
anything here.

| id | Parameter | id | Parameter |
|---|---|---|---|
| `0x00` | ACE enable | `0x13` | Mic EQ enable |
| `0x01` | ACE reference delay *(restricted)* | `0x14`–`0x1B` | Mic EQ gain 0–7 |
| `0x02` | AEC system reference delay *(restricted)* | `0x1C`–`0x23` | Mic EQ centre frequency 0–7 |
| `0x03` | AEC auto reference delay enable *(restricted)* | `0x24`–`0x2B` | Mic EQ bandwidth 0–7 |
| `0x04` | Noise reduction enable | `0x2C` | Mic smart volume enable |
| `0x05` | Noise reduction strength *(restricted)* | `0x2D` | Mic smart volume strength |
| `0x06` | VoiceFocus enable | `0x2E` | Mic reverb enable |
| `0x07` | VoiceFocus mic distance | `0x2F` | Mic reverb preset |
| `0x08` | VoiceFocus wedge angle | `0x30`, `0x31` | Mic reverb level, mic 1 / mic 2 |
| `0x09` | VoiceFocus source angle *(restricted)* | `0x32`, `0x33` | Mic reverb pan, mic 1 / mic 2 |
| `0x0A` | VoiceFX enable | `0x34`, `0x35` | Mic reverb effect send, mic 1 / mic 2 |
| `0x0B`–`0x0D` | VoiceFX formant 1–3 frequency | `0x36` | Dual-mic end-firing enable |
| `0x0E` | VoiceFX pitch modulation | | |
| `0x0F` | VoiceFX envelope modulation | | |
| `0x10` | VoiceFX pitch variability | | |
| `0x11` | VoiceFX quiver depth | | |
| `0x12` | VoiceFX contour depth | | |

VoiceFX is nine continuous parameters, not a preset index — the presets in
Creative's UI are bundles of these values, so they ride the ordinary float
path.

## Command set

`com.creative.protocol.definitions.CtSoundCoreCommands`. "Not applicable"
means the E5 has no hardware path for it; the command exists because the
protocol is shared across the Sound Blaster line.

| Cmd | Name | Status here |
|---|---|---|
| `0x01` | `PROTOCOLVER` | not implemented |
| `0x02` | `ACKNOWLEDGE` | not implemented — the HID path uses the interrupt-IN echo |
| `0x03` | `MAXPAYLOAD` | not implemented |
| `0x05` | `FEATURESUPPORT` | not implemented — support is a hardcoded table here |
| `0x06` | `CONTROLREQ` | not implemented |
| `0x07` | `DEVICEINFO` | not implemented — `sbx-e5 info` reports USB descriptors only |
| `0x08` | `COMMITSETTING` | partial — only the SBX master switch is committed |
| `0x10` | `SUBFEATURESUPPORT` | not implemented |
| `0x11` | `GETPARAM` | implemented, as HID `0x26` |
| `0x12` | `SETPARAM` | implemented, as HID `0x20` |
| `0x13` | `GETPARAMDEFAULT` | not implemented |
| `0x14` | `GETPARAMCONFIG` | not implemented — would supply ranges instead of assuming them |
| `0x15` | `GETPARAMCUSTOMIZATIONQUERY` | not implemented |
| `0x16`, `0x19`, `0x1A`, `0x1C` | profile data / info / activate / modify | not implemented |
| `0x1D` | `AVATARID` | restricted |
| `0x1E` | `GETDEFAULTPROFILE` | not implemented |
| `0x1F` | `GETPROFILEDETAILS` | restricted |
| `0x20` | `HARDWARESUBFEATURE` | not implemented |
| `0x21` | `GETAUDIOCONTROLINFORMATION` | not implemented |
| `0x22` | `GETAUDIOLEVELRANGES` | not implemented |
| `0x23` | `AUDIOLEVEL` | not implemented — hardware volume |
| `0x24` | `AUDIOMUTE` | not implemented |
| `0x25` | `GETAUDIOCONTROLNAME` | not implemented |
| `0x26` | `HARDWAREBUTTON` | not implemented — physical button events |
| `0x27` | `BATTERYLEVEL` | not implemented — the E5 has a battery, so this is real |
| `0x28` | `BATTERYSTATUS` | not implemented — charge/discharge mask |
| `0x29`–`0x2B` | speaker configuration / model / preset | not applicable |
| `0x30` | `ADVANCEDSUBFEATURE` | not implemented |
| `0x31` | `BLUETOOTHAUTOCONNECT` | not implemented — real on the E5 |
| `0x32`–`0x36`, `0x38` | room calibration | not applicable, restricted |
| `0x37` | `I2CPASSTHROUGH` | restricted — raw bus access |
| `0x39` | `FEATURECONTROL` | not implemented |
| `0x3A` | `LEDCONTROL` | not implemented — real on the E5 |
| `0x3C` | `JACKSELECTORCONTROL` | not implemented — real on the E5 |
| `0x3D` | `WHITENOISECONTROL` | not implemented |
| `0x41`–`0x4D` | `MSS_*`, multi-speaker party/link | not applicable |
| `0x51` | `DATASTORE` | not implemented |

Two commands are implemented, and they are the two that carry every audio
parameter. The gaps are device management and other products' features.

## Restricted parameters

`assets/command_block_list.json` in the transport service names what
Creative refuses to let a third-party client write:

- Module `0x96`: `1F`, `39`, `3A`, `3B`, `3C`, `3D` — speaker EQ enable,
  master volume, master mute, speaker EQ bypass gain, calibrator headroom,
  speaker configuration.
- Module `0x95`: `01`, `02`, `03`, `05`, `09` — AEC delay internals, noise
  reduction strength, VoiceFocus source angle.
- Modules `0x49` and `0x8F` in full — sweep tone and room calibration.
- Whole commands: `5A1D`, `5A1F`, `5A32`–`5A35`, `5A37`, and all `5A4x`.

These are the parameters that can damage speakers or destroy a calibration.
This project does not implement them.

## Control-app features

From `com.creative.central.device.*`.

| Feature | Status here |
|---|---|
| SBX Crystalizer | implemented |
| SBX Surround (CMSS3D) | implemented |
| SBX Bass — enable, strength, crossover | implemented |
| SBX Dialog Plus | implemented |
| SBX Smart Volume, with mode | implemented |
| SBX master on/off | implemented |
| 10-band graphic EQ | implemented |
| EQ preamp | not implemented |
| Named EQ presets | not implemented |
| CrystalVoice — the whole mic chain | not implemented |
| Master volume and mute | restricted |
| Battery monitor | not implemented |
| LED control | not implemented |
| Jack selector — line/mic/optical routing | not implemented |
| Bluetooth auto-connect | not implemented |
| Hardware button handling | not implemented |
| Named user profiles, save/load/export | not implemented |
| VoiceFX and Mic EQ presets | not implemented |
| Scout mode | not implemented |
| Dolby Digital decode | not applicable |
| Room calibration, speaker setup, polarity | not applicable |
| X-Fi settings | not applicable |
| Alarm clock, Bluetooth device control | not applicable — Roar family |
