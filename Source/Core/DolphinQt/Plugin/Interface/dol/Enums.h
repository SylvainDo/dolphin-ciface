#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum dol_AddressSpace_Type
{
  dol_AddressSpace_Type_Effective,
  dol_AddressSpace_Type_Auxiliary,
  dol_AddressSpace_Type_Physical,
  dol_AddressSpace_Type_Mem1,
  dol_AddressSpace_Type_Mem2,
  dol_AddressSpace_Type_Fake
};

enum dol_AspectMode
{
  dol_AspectMode_Auto,
  dol_AspectMode_AnalogWide,
  dol_AspectMode_Analog,
  dol_AspectMode_Stretch
};

enum dol_AudioCommon_DPL2Quality
{
  dol_AudioCommon_DPL2Quality_Lowest = 0,
  dol_AudioCommon_DPL2Quality_Low = 1,
  dol_AudioCommon_DPL2Quality_High = 2,
  dol_AudioCommon_DPL2Quality_Highest = 3
};

enum dol_Config_GPUDeterminismMode
{
  dol_Config_GPUDeterminismMode_Auto,
  dol_Config_GPUDeterminismMode_Disabled,
  dol_Config_GPUDeterminismMode_FakeCompletion
};

enum dol_Config_LayerType
{
  dol_Config_LayerType_Base,
  dol_Config_LayerType_CommandLine,
  dol_Config_LayerType_GlobalGame,
  dol_Config_LayerType_LocalGame,
  dol_Config_LayerType_Movie,
  dol_Config_LayerType_Netplay,
  dol_Config_LayerType_CurrentRun,
  dol_Config_LayerType_Meta
};

enum dol_Config_ShowCursor
{
  dol_Config_ShowCursor_Never,
  dol_Config_ShowCursor_Constantly,
  dol_Config_ShowCursor_OnMovement
};

enum dol_Config_System
{
  dol_Config_System_Main,
  dol_Config_System_SYSCONF,
  dol_Config_System_GCPad,
  dol_Config_System_WiiPad,
  dol_Config_System_GCKeyboard,
  dol_Config_System_GFX,
  dol_Config_System_Logger,
  dol_Config_System_Debugger,
  dol_Config_System_DualShockUDPClient,
  dol_Config_System_FreeLook,
  dol_Config_System_Session
};

enum dol_Core_State
{
  dol_Core_State_Uninitialized,
  dol_Core_State_Paused,
  dol_Core_State_Running,
  dol_Core_State_Stopping,
  dol_Core_State_Starting
};

enum dol_DiscIO_BlobType
{
  dol_DiscIO_BlobType_PLAIN,
  dol_DiscIO_BlobType_DRIVE,
  dol_DiscIO_BlobType_DIRECTORY,
  dol_DiscIO_BlobType_GCZ,
  dol_DiscIO_BlobType_CISO,
  dol_DiscIO_BlobType_WBFS,
  dol_DiscIO_BlobType_TGC,
  dol_DiscIO_BlobType_WIA,
  dol_DiscIO_BlobType_RVZ,
  dol_DiscIO_BlobType_MOD_DESCRIPTOR,
  dol_DiscIO_BlobType_NFS
};

enum dol_DiscIO_Country
{
  dol_DiscIO_Country_Europe = 0,
  dol_DiscIO_Country_Japan,
  dol_DiscIO_Country_USA,
  dol_DiscIO_Country_Australia,
  dol_DiscIO_Country_France,
  dol_DiscIO_Country_Germany,
  dol_DiscIO_Country_Italy,
  dol_DiscIO_Country_Korea,
  dol_DiscIO_Country_Netherlands,
  dol_DiscIO_Country_Russia,
  dol_DiscIO_Country_Spain,
  dol_DiscIO_Country_Taiwan,
  dol_DiscIO_Country_World,
  dol_DiscIO_Country_Unknown,
  dol_DiscIO_Country_NumberOfCountries
};

enum dol_DiscIO_DataSizeType
{
  dol_DiscIO_DataSizeType_Accurate,
  dol_DiscIO_DataSizeType_LowerBound,
  dol_DiscIO_DataSizeType_UpperBound
};

enum dol_DiscIO_Language
{
  dol_DiscIO_Language_Japanese = 0,
  dol_DiscIO_Language_English = 1,
  dol_DiscIO_Language_German = 2,
  dol_DiscIO_Language_French = 3,
  dol_DiscIO_Language_Spanish = 4,
  dol_DiscIO_Language_Italian = 5,
  dol_DiscIO_Language_Dutch = 6,
  dol_DiscIO_Language_SimplifiedChinese = 7,
  dol_DiscIO_Language_TraditionalChinese = 8,
  dol_DiscIO_Language_Korean = 9,
  dol_DiscIO_Language_Unknown
};

enum dol_DiscIO_Platform
{
  dol_DiscIO_Platform_GameCubeDisc = 0,
  dol_DiscIO_Platform_WiiDisc,
  dol_DiscIO_Platform_WiiWAD,
  dol_DiscIO_Platform_ELFOrDOL,
  dol_DiscIO_Platform_NumberOfPlatforms
};

enum dol_DiscIO_Region
{
  dol_DiscIO_Region_NTSC_J = 0,
  dol_DiscIO_Region_NTSC_U = 1,
  dol_DiscIO_Region_PAL = 2,
  dol_DiscIO_Region_Unknown = 3,
  dol_DiscIO_Region_NTSC_K = 4
};

enum dol_ExpansionInterface_EXIDeviceType
{
  dol_ExpansionInterface_EXIDeviceType_Dummy,
  dol_ExpansionInterface_EXIDeviceType_MemoryCard,
  dol_ExpansionInterface_EXIDeviceType_MaskROM,
  dol_ExpansionInterface_EXIDeviceType_AD16,
  dol_ExpansionInterface_EXIDeviceType_Microphone,
  dol_ExpansionInterface_EXIDeviceType_Ethernet,
  dol_ExpansionInterface_EXIDeviceType_AMBaseboard,
  dol_ExpansionInterface_EXIDeviceType_Gecko,
  dol_ExpansionInterface_EXIDeviceType_MemoryCardFolder,
  dol_ExpansionInterface_EXIDeviceType_AGP,
  dol_ExpansionInterface_EXIDeviceType_EthernetXLink,
  dol_ExpansionInterface_EXIDeviceType_EthernetTapServer,
  dol_ExpansionInterface_EXIDeviceType_EthernetBuiltIn,
  dol_ExpansionInterface_EXIDeviceType_None = 0xFF
};

enum dol_ExpansionInterface_Slot
{
  dol_ExpansionInterface_Slot_A,
  dol_ExpansionInterface_Slot_B,
  dol_ExpansionInterface_Slot_SP1
};

enum dol_FreeLook_ControlType
{
  dol_FreeLook_ControlType_SixAxis,
  dol_FreeLook_ControlType_FPS,
  dol_FreeLook_ControlType_Orbital
};

enum dol_HSP_HSPDeviceType
{
  dol_HSP_HSPDeviceType_None,
  dol_HSP_HSPDeviceType_ARAMExpansion
};

enum dol_PadButton
{
  dol_PadButton_Left = 0x0001,
  dol_PadButton_Right = 0x0002,
  dol_PadButton_Down = 0x0004,
  dol_PadButton_Up = 0x0008,
  dol_PadTrigger_Z = 0x0010,
  dol_PadTrigger_R = 0x0020,
  dol_PadTrigger_L = 0x0040,
  dol_PadButton_A = 0x0100,
  dol_PadButton_B = 0x0200,
  dol_PadButton_X = 0x0400,
  dol_PadButton_Y = 0x0800,
  dol_PadButton_Start = 0x1000
};

enum dol_PowerPC_CPUCore
{
  dol_PowerPC_CPUCore_Interpreter = 0,
  dol_PowerPC_CPUCore_JIT64 = 1,
  dol_PowerPC_CPUCore_JITARM64 = 4,
  dol_PowerPC_CPUCore_CachedInterpreter = 5
};

enum dol_SerialInterface_SIDevices
{
  dol_SerialInterface_SIDevices_None,
  dol_SerialInterface_SIDevices_N64Mic,
  dol_SerialInterface_SIDevices_N64Keyboard,
  dol_SerialInterface_SIDevices_N64Mouse,
  dol_SerialInterface_SIDevices_N64Controller,
  dol_SerialInterface_SIDevices_GC_GBA,
  dol_SerialInterface_SIDevices_GCController,
  dol_SerialInterface_SIDevices_GCKeyboard,
  dol_SerialInterface_SIDevices_GCSteering,
  dol_SerialInterface_SIDevices_DanceMat,
  dol_SerialInterface_SIDevices_GCTaruKonga,
  dol_SerialInterface_SIDevices_AMBaseboard,
  dol_SerialInterface_SIDevices_WiiUAdapter,
  dol_SerialInterface_SIDevices_GC_GBA_Emulated,
  dol_SerialInterface_SIDevices_Count
};

enum dol_ShaderCompilationMode
{
  dol_ShaderCompilationMode_Synchronous,
  dol_ShaderCompilationMode_SynchronousUberShaders,
  dol_ShaderCompilationMode_AsynchronousUberShaders,
  dol_ShaderCompilationMode_AsynchronousSkipRendering
};

enum dol_StereoMode
{
  dol_StereoMode_Off,
  dol_StereoMode_SBS,
  dol_StereoMode_TAB,
  dol_StereoMode_Anaglyph,
  dol_StereoMode_QuadBuffer,
  dol_StereoMode_Passive
};

enum dol_TriState
{
  dol_TriState_Off,
  dol_TriState_On,
  dol_TriState_Auto
};

enum dol_UICommon_GameFile_Variant
{
  dol_UICommon_GameFile_Variant_LongAndPossiblyCustom,
  dol_UICommon_GameFile_Variant_LongAndNotCustom,
  dol_UICommon_GameFile_Variant_ShortAndNotCustom
};

enum dol_WiimoteSource
{
  dol_WiimoteSource_None = 0,
  dol_WiimoteSource_Emulated = 1,
  dol_WiimoteSource_Real = 2
};

#ifdef __cplusplus
}
#endif
