//! Creative Sound Blaster E5 control protocol constants.
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
/// Top-level feature selector (argument 1 of `SetParamValue`).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum Feature {
    Invalid = 0x00000000,
    SystemMalcolmDeviceControl = 0x01000001,
    SystemProcessingControl = 0x01000002,
    SystemHWProfileControl = 0x01000003,
    SystemProductInfo = 0x01000004,
    DirectMonitorControl = 0x01000005,
    SystemMicrophoneConfig = 0x01000006,
    DeviceMicrophoneControl = 0x01000007,
    EffectsCMSS3D = 0x10000001,
    EffectsDialogPlus = 0x10000002,
    EffectsSmartVolume = 0x10000004,
    EffectsCrystalizer = 0x10000008,
    EffectsGraphicEQ = 0x10000010,
    EffectsXBass = 0x10000020,
    EffectsBassManagement = 0x10000040,
    EffectsSpeakerEnhancement = 0x10000080,
    EffectsSpeakerCalibrator = 0x10000100,
    EffectsSimpleSurround = 0x10000200,
    EffectsEAXEnvironment = 0x10000400,
    EffectsEAX3 = 0x10000800,
    EffectsLineNoiseReduction = 0x10001000,
    EffectsANC = 0x10002000,
    EffectsVIPVoiceFX = 0x20000001,
    EffectsVIPSilencer = 0x20000002,
    EffectsVIPNoiseReduction = 0x20000004,
    EffectsVIPAEC = 0x20000008,
    EffectsVIPMicSmartVolume = 0x20000010,
    EffectsVIPMicArray = 0x20000020,
    EffectsVIPMicEQ = 0x20000040,
    EffectsVIPDualMicEndFiring = 0x20000080,
    EffectsVIPMic2VoiceFX = 0x20000100,
    EffectsVIPMic2SmartVolume = 0x20000200,
    EffectsVIPMic2EQ = 0x20000400,
    EffectsReverb = 0x30000001,
    EffectsPitchShift = 0x30000002,
    EffectsMicReverb = 0x30000004,
    EffectsMic2Reverb = 0x30000008,
    DecoderDolbyDigital = 0x40000001,
    DecoderDTS = 0x40000002,
    DecoderDolbyTrueHD = 0x40000004,
    EncoderDDLiveObsolete = 0x50000001,
    EncoderDTSInteractive = 0x50000002,
    EncoderDDLive = 0x50000003,
    EfxMasterControl = 0x60000001,
    KaraokeControl = 0x60000002,
    USBPowerOverdrive = 0x70000001,
    EffectsProfile = 0x70000002,
    DeviceControlPermission = 0x70000004,
    BluetoothAutoConnect = 0x70000008,
    Xena2Control = 0x70000010,
    Battery = 0x70000020,
    LEDControl = 0x70000040,
    SirenControl = 0x70000080,
    Miscellaneous = 0x70000100,
    WaveTest = 0x70000200,
    SurroundType = 0x80000001,
}

/// SBX Bass. Use with [`Feature::EffectsXBass`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum XBass {
    Enable = 0x00000000,
    Strength = 0x00000001,
    FreqHz = 0x00000002,
}

/// SBX Crystalizer. Use with [`Feature::EffectsCrystalizer`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum Crystalizer {
    Enable = 0x00000000,
    Level = 0x00000001,
}

/// SBX Surround. Use with [`Feature::EffectsSimpleSurround`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum SimpleSurround {
    Enable = 0x00000000,
    Level = 0x00000001,
}

/// SBX Dialog Plus. Use with [`Feature::EffectsDialogPlus`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum DialogPlus {
    Enable = 0x00000000,
    Strength = 0x00000001,
}

/// SBX Smart Volume. Use with [`Feature::EffectsSmartVolume`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum SmartVolume {
    Enable = 0x00000000,
    Strength = 0x00000001,
    Mode = 0x00000002,
}

/// 10-band graphic EQ; treble is the upper bands.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum GraphicEq {
    Enable = 0x00000000,
    PreampGain = 0x00000001,
    Band0Gain = 0x00000002,
    Band1Gain = 0x00000003,
    Band2Gain = 0x00000004,
    Band3Gain = 0x00000005,
    Band4Gain = 0x00000006,
    Band5Gain = 0x00000007,
    Band6Gain = 0x00000008,
    Band7Gain = 0x00000009,
    Band8Gain = 0x0000000A,
    Band9Gain = 0x0000000B,
    EnumPreset = 0x00000100,
    EnumAllPresets = 0x00000101,
    ActivePreset = 0x00000102,
    SavePreset = 0x00000103,
    RemovePreset = 0x00000104,
}

/// Master effect on/off switches (SBX master).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum EfxMaster {
    THXMasterOnOffFeatures = 0x00000000,
    THXMasterOnOffFeaturesLastState = 0x00000001,
    THXMasterOnOff = 0x00000002,
    VIPMasterOnOffFeatures = 0x00000003,
    VIPMasterOnOffFeaturesLastState = 0x00000004,
    VIPMasterOnOff = 0x00000005,
    SCOUTModeMasterOnOff = 0x00000006,
    SBXMasterOnOff = 0x00000007,
    SBXMasterOnOffFeatures = 0x00000008,
    SBXMasterOnOffFeaturesLastState = 0x00000009,
}

/// Device-level processing control.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum ProcessingControl {
    SpeakerConfig = 0x00000000,
    PhysicalSpeakerConfig = 0x00000001,
    SizeSpeakerConfig = 0x00000002,
    EnumSpeakerConfig = 0x00000003,
    VIPSourceSelect = 0x00000004,
    MasterSampleRate = 0x00000005,
    EnumVIPSource = 0x00000006,
    DirectMode = 0x00000007,
    StereoDirectMode = 0x00000008,
    SPDIFInPassThrough = 0x00000009,
    SPDIFOutPassThrough = 0x0000000A,
    HighPowerAmplifier = 0x0000000B,
    EnumSpeakersModel = 0x0000000C,
    SpeakersModelInfo = 0x0000000D,
    SpeakersModel = 0x0000000E,
    EnumSpeakersPreset = 0x0000000F,
    SpeakersPreset = 0x00000010,
    SpeakersHRTFMode = 0x00000011,
}

/// Bass management / crossover.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum BassManagement {
    Enable = 0x00000000,
    CrossOverFreqHz = 0x00000001,
    SpeakerSizeFLFR = 0x00000002,
    SpeakerSizeFCSW = 0x00000003,
    SpeakerSizeRLRR = 0x00000004,
    SpeakerSizeSLSR = 0x00000005,
    SubwooferBoost = 0x00000006,
}

/// Declared datatype of a parameter, from `GetParamInfo`.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u32)]
pub enum ParamType {
    Float = 0x00000000,
    Bool = 0x00000001,
    Dword = 0x00000002,
    LongInt = 0x00000003,
    Select = 0x00000004,
    VarSize = 0x00000005,
}

/// Effect context / preset bank.
pub mod context {
    pub const INVALID: u32 = 0x00000000;
    pub const CURRENT: u32 = 0x00000000;
    pub const STANDARD: u32 = 0x00000001;
    pub const ENTERTAINMENT: u32 = 0x00000002;
    pub const KARAOKE: u32 = 0x00000004;
    pub const T_H_X2: u32 = 0x00000008;
}

/// USB vendor id: Creative Technology Ltd.
pub const VID_CREATIVE: u16 = 0x041E;

/// USB product id of the Sound Blaster E5 (board SB1590).
pub const PID_E5: u16 = 0x323C;

/// Other E-Series / related devices sharing this protocol.
pub const PID_E1: u16 = 0x323B;
pub const PID_E3: u16 = 0x323E;
pub const PID_X7: u16 = 0x323A;
pub const PID_G5: u16 = 0x3243;
