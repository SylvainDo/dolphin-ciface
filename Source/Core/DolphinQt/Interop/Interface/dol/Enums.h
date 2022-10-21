#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum dolAspectMode
{
  dolAspectMode_Auto,
  dolAspectMode_AnalogWide,
  dolAspectMode_Analog,
  dolAspectMode_Stretch
};

enum dolAudioCommonDPL2Quality
{
  dolAudioCommonDPL2Quality_Lowest = 0,
  dolAudioCommonDPL2Quality_Low = 1,
  dolAudioCommonDPL2Quality_High = 2,
  dolAudioCommonDPL2Quality_Highest = 3
};

enum dolConfigGPUDeterminismMode
{
  dolConfigGPUDeterminismMode_Auto,
  dolConfigGPUDeterminismMode_Disabled,
  dolConfigGPUDeterminismMode_FakeCompletion
};

enum dolConfigLayerType
{
  dolConfigLayerType_Base,
  dolConfigLayerType_CommandLine,
  dolConfigLayerType_GlobalGame,
  dolConfigLayerType_LocalGame,
  dolConfigLayerType_Movie,
  dolConfigLayerType_Netplay,
  dolConfigLayerType_CurrentRun,
  dolConfigLayerType_Meta
};

enum dolConfigShowCursor
{
  dolConfigShowCursor_Never,
  dolConfigShowCursor_Constantly,
  dolConfigShowCursor_OnMovement
};

enum dolConfigSystem
{
  dolConfigSystem_Main,
  dolConfigSystem_SYSCONF,
  dolConfigSystem_GCPad,
  dolConfigSystem_WiiPad,
  dolConfigSystem_GCKeyboard,
  dolConfigSystem_GFX,
  dolConfigSystem_Logger,
  dolConfigSystem_Debugger,
  dolConfigSystem_DualShockUDPClient,
  dolConfigSystem_FreeLook,
  dolConfigSystem_Session
};

enum dolDiscIOLanguage
{
  dolDiscIOLanguage_Japanese = 0,
  dolDiscIOLanguage_English = 1,
  dolDiscIOLanguage_German = 2,
  dolDiscIOLanguage_French = 3,
  dolDiscIOLanguage_Spanish = 4,
  dolDiscIOLanguage_Italian = 5,
  dolDiscIOLanguage_Dutch = 6,
  dolDiscIOLanguage_SimplifiedChinese = 7,
  dolDiscIOLanguage_TraditionalChinese = 8,
  dolDiscIOLanguage_Korean = 9,
  dolDiscIOLanguage_Unknown
};

enum dolDiscIORegion
{
  dolDiscIORegion_NTSC_J = 0,
  dolDiscIORegion_NTSC_U = 1,
  dolDiscIORegion_PAL = 2,
  dolDiscIORegion_Unknown = 3,
  dolDiscIORegion_NTSC_K = 4
};

enum dolExpansionInterfaceEXIDeviceType
{
  dolExpansionInterfaceEXIDeviceType_Dummy,
  dolExpansionInterfaceEXIDeviceType_MemoryCard,
  dolExpansionInterfaceEXIDeviceType_MaskROM,
  dolExpansionInterfaceEXIDeviceType_AD16,
  dolExpansionInterfaceEXIDeviceType_Microphone,
  dolExpansionInterfaceEXIDeviceType_Ethernet,
  dolExpansionInterfaceEXIDeviceType_AMBaseboard,
  dolExpansionInterfaceEXIDeviceType_Gecko,
  dolExpansionInterfaceEXIDeviceType_MemoryCardFolder,
  dolExpansionInterfaceEXIDeviceType_AGP,
  dolExpansionInterfaceEXIDeviceType_EthernetXLink,
  dolExpansionInterfaceEXIDeviceType_EthernetTapServer,
  dolExpansionInterfaceEXIDeviceType_EthernetBuiltIn,
  dolExpansionInterfaceEXIDeviceType_None = 0xFF
};

enum dolExpansionInterfaceSlot
{
  dolExpansionInterfaceSlot_A,
  dolExpansionInterfaceSlot_B,
  dolExpansionInterfaceSlot_SP1
};

enum dolFreeLookControlType
{
  dolFreeLookControlType_SixAxis,
  dolFreeLookControlType_FPS,
  dolFreeLookControlType_Orbital
};

enum dolHSPHSPDeviceType
{
  dolHSPHSPDeviceType_None,
  dolHSPHSPDeviceType_ARAMExpansion
};

enum dolPowerPCCPUCore
{
  dolPowerPCCPUCore_Interpreter = 0,
  dolPowerPCCPUCore_JIT64 = 1,
  dolPowerPCCPUCore_JITARM64 = 4,
  dolPowerPCCPUCore_CachedInterpreter = 5
};

enum dolSerialInterfaceSIDevices
{
  dolSerialInterfaceSIDevices_SIDEVICE_NONE,
  dolSerialInterfaceSIDevices_SIDEVICE_N64_MIC,
  dolSerialInterfaceSIDevices_SIDEVICE_N64_KEYBOARD,
  dolSerialInterfaceSIDevices_SIDEVICE_N64_MOUSE,
  dolSerialInterfaceSIDevices_SIDEVICE_N64_CONTROLLER,
  dolSerialInterfaceSIDevices_SIDEVICE_GC_GBA,
  dolSerialInterfaceSIDevices_SIDEVICE_GC_CONTROLLER,
  dolSerialInterfaceSIDevices_SIDEVICE_GC_KEYBOARD,
  dolSerialInterfaceSIDevices_SIDEVICE_GC_STEERING,
  dolSerialInterfaceSIDevices_SIDEVICE_DANCEMAT,
  dolSerialInterfaceSIDevices_SIDEVICE_GC_TARUKONGA,
  dolSerialInterfaceSIDevices_SIDEVICE_AM_BASEBOARD,
  dolSerialInterfaceSIDevices_SIDEVICE_WIIU_ADAPTER,
  dolSerialInterfaceSIDevices_SIDEVICE_GC_GBA_EMULATED,
  dolSerialInterfaceSIDevices_SIDEVICE_COUNT
};

enum dolShaderCompilationMode
{
  dolShaderCompilationMode_Synchronous,
  dolShaderCompilationMode_SynchronousUberShaders,
  dolShaderCompilationMode_AsynchronousUberShaders,
  dolShaderCompilationMode_AsynchronousSkipRendering
};

enum dolStereoMode
{
  dolStereoMode_Off,
  dolStereoMode_SBS,
  dolStereoMode_TAB,
  dolStereoMode_Anaglyph,
  dolStereoMode_QuadBuffer,
  dolStereoMode_Passive
};

enum dolWiimoteSource
{
  dolWiimoteSource_None = 0,
  dolWiimoteSource_Emulated = 1,
  dolWiimoteSource_Real = 2
};

#ifdef __cplusplus
}
#endif
