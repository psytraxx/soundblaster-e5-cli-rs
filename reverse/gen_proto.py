#!/usr/bin/env python3
"""Generate src/proto.rs from the constants recovered from Interop.CtSndCr.dll.

Usage:  python3 reverse/gen_proto.py > src/proto.rs

Source of truth is reverse/enums/ctsndcr_enums.txt, which was extracted by
parsing the .NET metadata Constant table of Interop.CtSndCr.dll (Sound
Blaster E-Series Web Release 1.05.04).
"""
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(HERE, "enums", "ctsndcr_enums.txt")

consts = {}
with open(SRC) as fh:
    for line in fh:
        m = re.match(r"^(\w+) = (-?\d+)$", line.strip())
        if m:
            consts.setdefault(m.group(1), int(m.group(2)))


def camel(s):
    return "".join(p[0].upper() + p[1:] for p in s.split("_") if p)


out = sys.stdout

out.write('''//! Creative Sound Blaster E5 control protocol constants.
//!
//! AUTO-GENERATED from the .NET metadata of `Interop.CtSndCr.dll`
//! (Sound Blaster E-Series Web Release 1.05.04, driver 1.14.1.5).
//!
//! The device is controlled by a `(Feature, param, value)` triple.
//! `Feature` is a packed id: the high nibble selects a category and the
//! low bits are a one-hot mask within it, e.g.
//! `EffectsXBass = 0x1000_0020`.
//!
//! Do not edit by hand -- regenerate with `python3 reverse/gen_proto.py`.

#![allow(dead_code)]
#![allow(clippy::upper_case_acronyms)]
''')


def emit(name, prefix, doc):
    items = [(k, v) for k, v in consts.items() if k.startswith(prefix)]
    if not items:
        return
    # Rust forbids duplicate discriminants in an enum; the Windows headers
    # do contain aliases (e.g. eContext_Invalid == eContext_Current == 0).
    # Those groups are emitted as plain constants instead.
    seen_vals = {}
    dup = False
    for k, v in items:
        if v in seen_vals:
            dup = True
        seen_vals[v] = k

    out.write("/// %s\n" % doc)
    if dup:
        out.write("pub mod %s {\n" % name.lower())
        emitted = set()
        for k, v in items:
            ident = camel(k[len(prefix):])
            if not ident or ident in emitted:
                continue
            emitted.add(ident)
            out.write("    pub const %s: u32 = 0x%08X;\n" % (
                re.sub(r"(?<!^)(?=[A-Z])", "_", ident).upper(), v & 0xFFFFFFFF))
        out.write("}\n\n")
        return

    out.write("#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]\n")
    out.write("#[repr(u32)]\n")
    out.write("pub enum %s {\n" % name)
    emitted = set()
    for k, v in items:
        ident = camel(k[len(prefix):])
        if not ident or ident in emitted:
            continue
        emitted.add(ident)
        out.write("    %s = 0x%08X,\n" % (ident, v & 0xFFFFFFFF))
    out.write("}\n\n")


emit("Feature", "eFeature_", "Top-level feature selector (argument 1 of `SetParamValue`).")
for name, prefix, doc in [
    ("XBass", "eParamXBass_", "SBX Bass. Use with [`Feature::EffectsXBass`]."),
    ("Crystalizer", "eParamCrystalizer_", "SBX Crystalizer. Use with [`Feature::EffectsCrystalizer`]."),
    ("SimpleSurround", "eParamSimpleSurround_", "SBX Surround. Use with [`Feature::EffectsSimpleSurround`]."),
    ("DialogPlus", "eParamDialogPlus_", "SBX Dialog Plus. Use with [`Feature::EffectsDialogPlus`]."),
    ("SmartVolume", "eParamSmartVolume_", "SBX Smart Volume. Use with [`Feature::EffectsSmartVolume`]."),
    ("GraphicEq", "eParamGraphicEQ_", "10-band graphic EQ; treble is the upper bands."),
    ("EfxMaster", "eParamEfxMasterControl_", "Master effect on/off switches (SBX master)."),
    ("ProcessingControl", "eParamProcessingControl_", "Device-level processing control."),
    ("BassManagement", "eParamBassManagement_", "Bass management / crossover."),
]:
    emit(name, prefix, doc)
emit("ParamType", "eParamType_", "Declared datatype of a parameter, from `GetParamInfo`.")
emit("Context", "eContext_", "Effect context / preset bank.")

out.write('''/// USB vendor id: Creative Technology Ltd.
pub const VID_CREATIVE: u16 = 0x041E;

/// USB product id of the Sound Blaster E5 (board SB1590).
pub const PID_E5: u16 = 0x323C;

/// Other E-Series / related devices sharing this protocol.
pub const PID_E1: u16 = 0x323B;
pub const PID_E3: u16 = 0x323E;
pub const PID_X7: u16 = 0x323A;
pub const PID_G5: u16 = 0x3243;
''')
