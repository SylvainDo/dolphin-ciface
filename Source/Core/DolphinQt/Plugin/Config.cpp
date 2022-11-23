#include "Export.h"
#include "PluginUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Config.h"

#include "Core/Config/DefaultLocale.h"
#include "Core/Config/FreeLookSettings.h"
#include "Core/Config/GraphicsSettings.h"
#include "Core/Config/MainSettings.h"
#include "Core/Config/NetplaySettings.h"
#include "Core/Config/SYSCONFSettings.h"
#include "Core/Config/SessionSettings.h"
#include "Core/Config/UISettings.h"
#include "Core/Config/WiimoteSettings.h"

enum class PropertyType
{
  Boolean,
  Integer,
  AspectMode,
  AudioCommon_DPL2Quality,
  Config_ShowCursor,
  DiscIO_Region,
  ExpansionInterface_EXIDeviceType,
  FreeLook_ControlType,
  HSP_HSPDeviceType,
  PowerPC_CPUCore,
  SerialInterface_SIDevices,
  ShaderCompilationMode,
  StereoMode,
  TriState,
  WiimoteSource,
  String,
  Float,
  Unsigned16,
  Unsigned32
};

struct Property
{
  void* info;
  PropertyType type;
};
static Property _temp_property;

// clang-format off
#define PropertyEraseType(x) const_cast<void*>(static_cast<const void*>(&x))
#define PropertyDeclare(name, type) { #name, { PropertyEraseType(Config::name), PropertyType::type } }

static std::unordered_map<std::string_view, Property> _properties
{
  // FreeLookSettings
  PropertyDeclare(FREE_LOOK_ENABLED, Boolean),
  PropertyDeclare(FREE_LOOK_BACKGROUND_INPUT, Boolean),
  // FreeLook.Controller1
  PropertyDeclare(FL1_CONTROL_TYPE, FreeLook_ControlType),

  // GraphicsSettings
  // Graphics.Hardware
  PropertyDeclare(GFX_VSYNC, Boolean),
  PropertyDeclare(GFX_ADAPTER, Integer),
  // Graphics.Settings
  PropertyDeclare(GFX_WIDESCREEN_HACK, Boolean),
  PropertyDeclare(GFX_ASPECT_RATIO, AspectMode),
  PropertyDeclare(GFX_SUGGESTED_ASPECT_RATIO, AspectMode),
  PropertyDeclare(GFX_CROP, Boolean),
  PropertyDeclare(GFX_SAFE_TEXTURE_CACHE_COLOR_SAMPLES, Integer),
  PropertyDeclare(GFX_SHOW_FPS, Boolean),
  PropertyDeclare(GFX_SHOW_NETPLAY_PING, Boolean),
  PropertyDeclare(GFX_SHOW_NETPLAY_MESSAGES, Boolean),
  PropertyDeclare(GFX_LOG_RENDER_TIME_TO_FILE, Boolean),
  PropertyDeclare(GFX_OVERLAY_STATS, Boolean),
  PropertyDeclare(GFX_OVERLAY_PROJ_STATS, Boolean),
  PropertyDeclare(GFX_OVERLAY_SCISSOR_STATS, Boolean),
  PropertyDeclare(GFX_DUMP_TEXTURES, Boolean),
  PropertyDeclare(GFX_DUMP_MIP_TEXTURES, Boolean),
  PropertyDeclare(GFX_DUMP_BASE_TEXTURES, Boolean),
  PropertyDeclare(GFX_HIRES_TEXTURES, Boolean),
  PropertyDeclare(GFX_CACHE_HIRES_TEXTURES, Boolean),
  PropertyDeclare(GFX_DUMP_EFB_TARGET, Boolean),
  PropertyDeclare(GFX_DUMP_XFB_TARGET, Boolean),
  PropertyDeclare(GFX_DUMP_FRAMES_AS_IMAGES, Boolean),
  PropertyDeclare(GFX_USE_FFV1, Boolean),
  PropertyDeclare(GFX_DUMP_FORMAT, String),
  PropertyDeclare(GFX_DUMP_CODEC, String),
  PropertyDeclare(GFX_DUMP_PIXEL_FORMAT, String),
  PropertyDeclare(GFX_DUMP_ENCODER, String),
  PropertyDeclare(GFX_DUMP_PATH, String),
  PropertyDeclare(GFX_BITRATE_KBPS, Integer),
  PropertyDeclare(GFX_INTERNAL_RESOLUTION_FRAME_DUMPS, Boolean),
  PropertyDeclare(GFX_PNG_COMPRESSION_LEVEL, Integer),
  PropertyDeclare(GFX_ENABLE_GPU_TEXTURE_DECODING, Boolean),
  PropertyDeclare(GFX_ENABLE_PIXEL_LIGHTING, Boolean),
  PropertyDeclare(GFX_FAST_DEPTH_CALC, Boolean),
  PropertyDeclare(GFX_MSAA, Unsigned32),
  PropertyDeclare(GFX_SSAA, Boolean),
  PropertyDeclare(GFX_EFB_SCALE, Integer),
  PropertyDeclare(GFX_MAX_EFB_SCALE, Integer),
  PropertyDeclare(GFX_TEXFMT_OVERLAY_ENABLE, Boolean),
  PropertyDeclare(GFX_TEXFMT_OVERLAY_CENTER, Boolean),
  PropertyDeclare(GFX_ENABLE_WIREFRAME, Boolean),
  PropertyDeclare(GFX_DISABLE_FOG, Boolean),
  PropertyDeclare(GFX_BORDERLESS_FULLSCREEN, Boolean),
  PropertyDeclare(GFX_ENABLE_VALIDATION_LAYER, Boolean),
  PropertyDeclare(GFX_BACKEND_MULTITHREADING, Boolean),
  PropertyDeclare(GFX_COMMAND_BUFFER_EXECUTE_INTERVAL, Integer),
  PropertyDeclare(GFX_SHADER_CACHE, Boolean),
  PropertyDeclare(GFX_WAIT_FOR_SHADERS_BEFORE_STARTING, Boolean),
  PropertyDeclare(GFX_SHADER_COMPILATION_MODE, ShaderCompilationMode),
  PropertyDeclare(GFX_SHADER_COMPILER_THREADS, Integer),
  PropertyDeclare(GFX_SHADER_PRECOMPILER_THREADS, Integer),
  PropertyDeclare(GFX_SAVE_TEXTURE_CACHE_TO_STATE, Boolean),
  PropertyDeclare(GFX_PREFER_VS_FOR_LINE_POINT_EXPANSION, Boolean),
  PropertyDeclare(GFX_MTL_MANUALLY_UPLOAD_BUFFERS, TriState),
  PropertyDeclare(GFX_MTL_USE_PRESENT_DRAWABLE, Boolean),
  PropertyDeclare(GFX_SW_DUMP_OBJECTS, Boolean),
  PropertyDeclare(GFX_SW_DUMP_TEV_STAGES, Boolean),
  PropertyDeclare(GFX_SW_DUMP_TEV_TEX_FETCHES, Boolean),
  PropertyDeclare(GFX_PREFER_GLES, Boolean),
  PropertyDeclare(GFX_MODS_ENABLE, Boolean),
  // Graphics.Enhancements
  PropertyDeclare(GFX_ENHANCE_FORCE_FILTERING, Boolean),
  PropertyDeclare(GFX_ENHANCE_MAX_ANISOTROPY, Integer),
  PropertyDeclare(GFX_ENHANCE_POST_SHADER, String),
  PropertyDeclare(GFX_ENHANCE_FORCE_TRUE_COLOR, Boolean),
  PropertyDeclare(GFX_ENHANCE_DISABLE_COPY_FILTER, Boolean),
  PropertyDeclare(GFX_ENHANCE_ARBITRARY_MIPMAP_DETECTION, Boolean),
  PropertyDeclare(GFX_ENHANCE_ARBITRARY_MIPMAP_DETECTION_THRESHOLD, Float),
  // Graphics.Stereoscopy
  PropertyDeclare(GFX_STEREO_MODE, StereoMode),
  PropertyDeclare(GFX_STEREO_DEPTH, Integer),
  PropertyDeclare(GFX_STEREO_CONVERGENCE_PERCENTAGE, Integer),
  PropertyDeclare(GFX_STEREO_SWAP_EYES, Boolean),
  PropertyDeclare(GFX_STEREO_CONVERGENCE, Integer),
  PropertyDeclare(GFX_STEREO_EFB_MONO_DEPTH, Boolean),
  PropertyDeclare(GFX_STEREO_DEPTH_PERCENTAGE, Integer),
  // Graphics.Hacks
  PropertyDeclare(GFX_HACK_EFB_ACCESS_ENABLE, Boolean),
  PropertyDeclare(GFX_HACK_EFB_DEFER_INVALIDATION, Boolean),
  PropertyDeclare(GFX_HACK_EFB_ACCESS_TILE_SIZE, Integer),
  PropertyDeclare(GFX_HACK_BBOX_ENABLE, Boolean),
  PropertyDeclare(GFX_HACK_FORCE_PROGRESSIVE, Boolean),
  PropertyDeclare(GFX_HACK_SKIP_EFB_COPY_TO_RAM, Boolean),
  PropertyDeclare(GFX_HACK_SKIP_XFB_COPY_TO_RAM, Boolean),
  PropertyDeclare(GFX_HACK_DISABLE_COPY_TO_VRAM, Boolean),
  PropertyDeclare(GFX_HACK_DEFER_EFB_COPIES, Boolean),
  PropertyDeclare(GFX_HACK_IMMEDIATE_XFB, Boolean),
  PropertyDeclare(GFX_HACK_SKIP_DUPLICATE_XFBS, Boolean),
  PropertyDeclare(GFX_HACK_EARLY_XFB_OUTPUT, Boolean),
  PropertyDeclare(GFX_HACK_COPY_EFB_SCALED, Boolean),
  PropertyDeclare(GFX_HACK_EFB_EMULATE_FORMAT_CHANGES, Boolean),
  PropertyDeclare(GFX_HACK_VERTEX_ROUNDING, Boolean),
  PropertyDeclare(GFX_HACK_MISSING_COLOR_VALUE, Unsigned32),
  PropertyDeclare(GFX_HACK_FAST_TEXTURE_SAMPLING, Boolean),
  // Graphics.GameSpecific
  PropertyDeclare(GFX_PERF_QUERIES_ENABLE, Boolean),

  // MainSettings
  // Main.Core
  PropertyDeclare(MAIN_SKIP_IPL, Boolean),
  PropertyDeclare(MAIN_CPU_CORE, PowerPC_CPUCore),
  PropertyDeclare(MAIN_JIT_FOLLOW_BRANCH, Boolean),
  PropertyDeclare(MAIN_FASTMEM, Boolean),
  PropertyDeclare(MAIN_DSP_HLE, Boolean),
  PropertyDeclare(MAIN_TIMING_VARIANCE, Integer),
  PropertyDeclare(MAIN_CPU_THREAD, Boolean),
  PropertyDeclare(MAIN_SYNC_ON_SKIP_IDLE, Boolean),
  PropertyDeclare(MAIN_DEFAULT_ISO, String),
  PropertyDeclare(MAIN_ENABLE_CHEATS, Boolean),
  PropertyDeclare(MAIN_GC_LANGUAGE, Integer),
  PropertyDeclare(MAIN_OVERRIDE_REGION_SETTINGS, Boolean),
  PropertyDeclare(MAIN_DPL2_DECODER, Boolean),
  PropertyDeclare(MAIN_DPL2_QUALITY, AudioCommon_DPL2Quality),
  PropertyDeclare(MAIN_AUDIO_LATENCY, Integer),
  PropertyDeclare(MAIN_AUDIO_STRETCH, Boolean),
  PropertyDeclare(MAIN_AUDIO_STRETCH_LATENCY, Integer),
  PropertyDeclare(MAIN_MEMCARD_A_PATH, String),
  PropertyDeclare(MAIN_MEMCARD_B_PATH, String),
  PropertyDeclare(MAIN_AGP_CART_A_PATH, String),
  PropertyDeclare(MAIN_AGP_CART_B_PATH, String),
  PropertyDeclare(MAIN_GCI_FOLDER_A_PATH_OVERRIDE, String),
  PropertyDeclare(MAIN_GCI_FOLDER_B_PATH_OVERRIDE, String),
  PropertyDeclare(MAIN_MEMORY_CARD_SIZE, Integer),
  PropertyDeclare(MAIN_SLOT_A, ExpansionInterface_EXIDeviceType),
  PropertyDeclare(MAIN_SLOT_B, ExpansionInterface_EXIDeviceType),
  PropertyDeclare(MAIN_SERIAL_PORT_1, ExpansionInterface_EXIDeviceType),
  PropertyDeclare(MAIN_BBA_MAC, String),
  PropertyDeclare(MAIN_BBA_XLINK_IP, String),
  PropertyDeclare(MAIN_BBA_XLINK_CHAT_OSD, Boolean),
  PropertyDeclare(MAIN_BBA_BUILTIN_DNS, String),
  PropertyDeclare(MAIN_BBA_BUILTIN_IP, String),
  PropertyDeclare(MAIN_WII_SD_CARD, Boolean),
  PropertyDeclare(MAIN_WII_SD_CARD_ENABLE_FOLDER_SYNC, Boolean),
  PropertyDeclare(MAIN_WII_KEYBOARD, Boolean),
  PropertyDeclare(MAIN_WIIMOTE_CONTINUOUS_SCANNING, Boolean),
  PropertyDeclare(MAIN_WIIMOTE_ENABLE_SPEAKER, Boolean),
  PropertyDeclare(MAIN_CONNECT_WIIMOTES_FOR_CONTROLLER_INTERFACE, Boolean),
  PropertyDeclare(MAIN_MMU, Boolean),
  PropertyDeclare(MAIN_PAUSE_ON_PANIC, Boolean),
  PropertyDeclare(MAIN_BB_DUMP_PORT, Integer),
  PropertyDeclare(MAIN_SYNC_GPU, Boolean),
  PropertyDeclare(MAIN_SYNC_GPU_MAX_DISTANCE, Integer),
  PropertyDeclare(MAIN_SYNC_GPU_MIN_DISTANCE, Integer),
  PropertyDeclare(MAIN_SYNC_GPU_OVERCLOCK, Float),
  PropertyDeclare(MAIN_FAST_DISC_SPEED, Boolean),
  PropertyDeclare(MAIN_LOW_DCBZ_HACK, Boolean),
  PropertyDeclare(MAIN_FLOAT_EXCEPTIONS, Boolean),
  PropertyDeclare(MAIN_DIVIDE_BY_ZERO_EXCEPTIONS, Boolean),
  PropertyDeclare(MAIN_FPRF, Boolean),
  PropertyDeclare(MAIN_ACCURATE_NANS, Boolean),
  PropertyDeclare(MAIN_DISABLE_ICACHE, Boolean),
  PropertyDeclare(MAIN_EMULATION_SPEED, Float),
  PropertyDeclare(MAIN_OVERCLOCK, Float),
  PropertyDeclare(MAIN_OVERCLOCK_ENABLE, Boolean),
  PropertyDeclare(MAIN_RAM_OVERRIDE_ENABLE, Boolean),
  PropertyDeclare(MAIN_MEM1_SIZE, Unsigned32),
  PropertyDeclare(MAIN_MEM2_SIZE, Unsigned32),
  PropertyDeclare(MAIN_GFX_BACKEND, String),
  PropertyDeclare(MAIN_HSP_DEVICE, HSP_HSPDeviceType),
  PropertyDeclare(MAIN_ARAM_EXPANSION_SIZE, Unsigned32),
  PropertyDeclare(MAIN_GPU_DETERMINISM_MODE, String),
  PropertyDeclare(MAIN_OVERRIDE_BOOT_IOS, Unsigned32),
  PropertyDeclare(MAIN_PERF_MAP_DIR, String),
  PropertyDeclare(MAIN_CUSTOM_RTC_ENABLE, Boolean),
  PropertyDeclare(MAIN_CUSTOM_RTC_VALUE, Unsigned32),
  PropertyDeclare(MAIN_FALLBACK_REGION, DiscIO_Region),
  PropertyDeclare(MAIN_AUTO_DISC_CHANGE, Boolean),
  PropertyDeclare(MAIN_ALLOW_SD_WRITES, Boolean),
  PropertyDeclare(MAIN_ENABLE_SAVESTATES, Boolean),
  PropertyDeclare(MAIN_REAL_WII_REMOTE_REPEAT_REPORTS, Boolean),
  PropertyDeclare(MAIN_WII_NUS_SHOP_URL, String),
  // Main.Display
  PropertyDeclare(MAIN_FULLSCREEN_DISPLAY_RES, String),
  PropertyDeclare(MAIN_FULLSCREEN, Boolean),
  PropertyDeclare(MAIN_RENDER_TO_MAIN, Boolean),
  PropertyDeclare(MAIN_RENDER_WINDOW_XPOS, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_YPOS, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_WIDTH, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_HEIGHT, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_AUTOSIZE, Boolean),
  PropertyDeclare(MAIN_KEEP_WINDOW_ON_TOP, Boolean),
  PropertyDeclare(MAIN_DISABLE_SCREENSAVER, Boolean),
  // Main.DSP
  PropertyDeclare(MAIN_DSP_THREAD, Boolean),
  PropertyDeclare(MAIN_DSP_CAPTURE_LOG, Boolean),
  PropertyDeclare(MAIN_DSP_JIT, Boolean),
  PropertyDeclare(MAIN_DUMP_AUDIO, Boolean),
  PropertyDeclare(MAIN_DUMP_AUDIO_SILENT, Boolean),
  PropertyDeclare(MAIN_DUMP_UCODE, Boolean),
  PropertyDeclare(MAIN_AUDIO_BACKEND, String),
  PropertyDeclare(MAIN_AUDIO_VOLUME, Integer),
  PropertyDeclare(MAIN_AUDIO_MUTED, Boolean),
#ifdef _WIN32
  PropertyDeclare(MAIN_WASAPI_DEVICE, String),
#endif
  // Main.General
  PropertyDeclare(MAIN_DUMP_PATH, String),
  PropertyDeclare(MAIN_LOAD_PATH, String),
  PropertyDeclare(MAIN_RESOURCEPACK_PATH, String),
  PropertyDeclare(MAIN_FS_PATH, String),
  PropertyDeclare(MAIN_WII_SD_CARD_IMAGE_PATH, String),
  PropertyDeclare(MAIN_WII_SD_CARD_SYNC_FOLDER_PATH, String),
  PropertyDeclare(MAIN_WFS_PATH, String),
  PropertyDeclare(MAIN_SHOW_LAG, Boolean),
  PropertyDeclare(MAIN_SHOW_FRAME_COUNT, Boolean),
  PropertyDeclare(MAIN_WIRELESS_MAC, String),
  PropertyDeclare(MAIN_GDB_SOCKET, String),
  PropertyDeclare(MAIN_GDB_PORT, Integer),
  PropertyDeclare(MAIN_ISO_PATH_COUNT, Integer),
  // Main.GBA
#ifdef HAS_LIBMGBA
  PropertyDeclare(MAIN_GBA_BIOS_PATH, String),
  PropertyDeclare(MAIN_GBA_SAVES_PATH, String),
  PropertyDeclare(MAIN_GBA_SAVES_IN_ROM_PATH, Boolean),
  PropertyDeclare(MAIN_GBA_THREADS, Boolean),
#endif
  // Main.Network
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_READ, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_WRITE, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_VERIFY_CERTIFICATES, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_ROOT_CA, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_PEER_CERT, Boolean),
  PropertyDeclare(MAIN_NETWORK_DUMP_BBA, Boolean),
  PropertyDeclare(MAIN_NETWORK_DUMP_AS_PCAP, Boolean),
  PropertyDeclare(MAIN_NETWORK_TIMEOUT, Integer),
  // Main.Interface
  PropertyDeclare(MAIN_USE_HIGH_CONTRAST_TOOLTIPS, Boolean),
  PropertyDeclare(MAIN_USE_PANIC_HANDLERS, Boolean),
  PropertyDeclare(MAIN_ABORT_ON_PANIC_ALERT, Boolean),
  PropertyDeclare(MAIN_OSD_MESSAGES, Boolean),
  PropertyDeclare(MAIN_SKIP_NKIT_WARNING, Boolean),
  PropertyDeclare(MAIN_CONFIRM_ON_STOP, Boolean),
  PropertyDeclare(MAIN_SHOW_CURSOR, Config_ShowCursor),
  PropertyDeclare(MAIN_LOCK_CURSOR, Boolean),
  PropertyDeclare(MAIN_INTERFACE_LANGUAGE, String),
  PropertyDeclare(MAIN_EXTENDED_FPS_INFO, Boolean),
  PropertyDeclare(MAIN_SHOW_ACTIVE_TITLE, Boolean),
  PropertyDeclare(MAIN_USE_BUILT_IN_TITLE_DATABASE, Boolean),
  PropertyDeclare(MAIN_THEME_NAME, String),
  PropertyDeclare(MAIN_PAUSE_ON_FOCUS_LOST, Boolean),
  PropertyDeclare(MAIN_ENABLE_DEBUGGING, Boolean),
  // Main.Analytics
  PropertyDeclare(MAIN_ANALYTICS_ID, String),
  PropertyDeclare(MAIN_ANALYTICS_ENABLED, Boolean),
  PropertyDeclare(MAIN_ANALYTICS_PERMISSION_ASKED, Boolean),
  // Main.GameList
  PropertyDeclare(MAIN_GAMELIST_LIST_DRIVES, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_WAD, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_ELF_DOL, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_WII, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_GC, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_JPN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_PAL, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_USA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_AUSTRALIA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_FRANCE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_GERMANY, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_ITALY, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_KOREA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_NETHERLANDS, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_RUSSIA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_SPAIN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_TAIWAN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_WORLD, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_UNKNOWN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_SORT, Integer),
  PropertyDeclare(MAIN_GAMELIST_LIST_SORT_SECONDARY, Integer),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_PLATFORM, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_DESCRIPTION, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_BANNER, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_TITLE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_MAKER, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_NAME, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_PATH, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_GAME_ID, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_REGION, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_SIZE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_FORMAT, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_BLOCK_SIZE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_COMPRESSION, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_TAGS, Boolean),
  // Main.FifoPlayer
  PropertyDeclare(MAIN_FIFOPLAYER_LOOP_REPLAY, Boolean),
  PropertyDeclare(MAIN_FIFOPLAYER_EARLY_MEMORY_UPDATES, Boolean),
  // Main.AutoUpdate
  PropertyDeclare(MAIN_AUTOUPDATE_UPDATE_TRACK, String),
  PropertyDeclare(MAIN_AUTOUPDATE_HASH_OVERRIDE, String),
  // Main.Movie
  PropertyDeclare(MAIN_MOVIE_PAUSE_MOVIE, Boolean),
  PropertyDeclare(MAIN_MOVIE_MOVIE_AUTHOR, String),
  PropertyDeclare(MAIN_MOVIE_DUMP_FRAMES, Boolean),
  PropertyDeclare(MAIN_MOVIE_DUMP_FRAMES_SILENT, Boolean),
  PropertyDeclare(MAIN_MOVIE_SHOW_INPUT_DISPLAY, Boolean),
  PropertyDeclare(MAIN_MOVIE_SHOW_RTC, Boolean),
  PropertyDeclare(MAIN_MOVIE_SHOW_RERECORD, Boolean),
  // Main.Input
  PropertyDeclare(MAIN_INPUT_BACKGROUND_INPUT, Boolean),
  // Main.Debug
  PropertyDeclare(MAIN_DEBUG_JIT_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_LXZ_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_LWZ_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_LBZX_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_FLOATING_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_PAIRED_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_FLOATING_POINT_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_INTEGER_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_PAIRED_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_SYSTEM_REGISTERS_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_BRANCH_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_REGISTER_CACHE_OFF, Boolean),
  // Main.BluetoothPassthrough
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_ENABLED, Boolean),
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_VID, Integer),
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_PID, Integer),
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_LINK_KEYS, String),
  // Main.USBPassthrough
  PropertyDeclare(MAIN_USB_PASSTHROUGH_DEVICES, String),

  PropertyDeclare(MAIN_HIDE_FPS_INFO, Boolean),
  PropertyDeclare(MAIN_PLAY_MODE, Boolean),

  // NetplaySettings
  // Main.NetPlay
  PropertyDeclare(NETPLAY_TRAVERSAL_SERVER, String),
  PropertyDeclare(NETPLAY_TRAVERSAL_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_TRAVERSAL_CHOICE, String),
  PropertyDeclare(NETPLAY_INDEX_URL, String),
  PropertyDeclare(NETPLAY_USE_INDEX, Boolean),
  PropertyDeclare(NETPLAY_INDEX_NAME, String),
  PropertyDeclare(NETPLAY_INDEX_REGION, String),
  PropertyDeclare(NETPLAY_INDEX_PASSWORD, String),
  PropertyDeclare(NETPLAY_HOST_CODE, String),
  PropertyDeclare(NETPLAY_HOST_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_ADDRESS, String),
  PropertyDeclare(NETPLAY_CONNECT_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_LISTEN_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_NICKNAME, String),
  PropertyDeclare(NETPLAY_USE_UPNP, Boolean),
  PropertyDeclare(NETPLAY_ENABLE_QOS, Boolean),
  PropertyDeclare(NETPLAY_ENABLE_CHUNKED_UPLOAD_LIMIT, Boolean),
  PropertyDeclare(NETPLAY_CHUNKED_UPLOAD_LIMIT, Unsigned32),
  PropertyDeclare(NETPLAY_BUFFER_SIZE, Unsigned32),
  PropertyDeclare(NETPLAY_CLIENT_BUFFER_SIZE, Unsigned32),
  PropertyDeclare(NETPLAY_SAVEDATA_LOAD, Boolean),
  PropertyDeclare(NETPLAY_SAVEDATA_WRITE, Boolean),
  PropertyDeclare(NETPLAY_SAVEDATA_SYNC_ALL_WII, Boolean),
  PropertyDeclare(NETPLAY_SYNC_CODES, Boolean),
  PropertyDeclare(NETPLAY_RECORD_INPUTS, Boolean),
  PropertyDeclare(NETPLAY_STRICT_SETTINGS_SYNC, Boolean),
  PropertyDeclare(NETPLAY_NETWORK_MODE, String),
  PropertyDeclare(NETPLAY_GOLF_MODE_OVERLAY, Boolean),
  PropertyDeclare(NETPLAY_HIDE_REMOTE_GBAS, Boolean),

  // SessionSettings
  PropertyDeclare(SESSION_USE_FMA, Boolean),
  PropertyDeclare(SESSION_LOAD_IPL_DUMP, Boolean),
  PropertyDeclare(SESSION_GCI_FOLDER_CURRENT_GAME_ONLY, Boolean),
  PropertyDeclare(SESSION_CODE_SYNC_OVERRIDE, Boolean),
  PropertyDeclare(SESSION_SAVE_DATA_WRITABLE, Boolean),
  PropertyDeclare(SESSION_SHOULD_FAKE_ERROR_001, Boolean),

  // SYSCONFSettings
  // SYSCONF.IPL
  PropertyDeclare(SYSCONF_SCREENSAVER, Boolean),
  PropertyDeclare(SYSCONF_LANGUAGE, Unsigned32),
  PropertyDeclare(SYSCONF_COUNTRY, Unsigned32),
  PropertyDeclare(SYSCONF_WIDESCREEN, Boolean),
  PropertyDeclare(SYSCONF_PROGRESSIVE_SCAN, Boolean),
  PropertyDeclare(SYSCONF_PAL60, Boolean),
  PropertyDeclare(SYSCONF_SOUND_MODE, Unsigned32),
  // SYSCONF.BT
  PropertyDeclare(SYSCONF_SENSOR_BAR_POSITION, Unsigned32),
  PropertyDeclare(SYSCONF_SENSOR_BAR_SENSITIVITY, Unsigned32),
  PropertyDeclare(SYSCONF_SPEAKER_VOLUME, Unsigned32),
  PropertyDeclare(SYSCONF_WIIMOTE_MOTOR, Boolean),

  // UISettings
  // UI.General
  PropertyDeclare(MAIN_USE_DISCORD_PRESENCE, Boolean),
  PropertyDeclare(MAIN_USE_GAME_COVERS, Boolean),
  PropertyDeclare(MAIN_FOCUSED_HOTKEYS, Boolean),
  PropertyDeclare(MAIN_RECURSIVE_ISO_PATHS, Boolean),

  // WiimoteSettings
  PropertyDeclare(WIIMOTE_1_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_2_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_3_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_4_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_BB_SOURCE, WiimoteSource)
};
// clang-format on

static void* dol_Config_findInfo1(const char* name)
{
  auto it = _properties.find(name);
  return it != _properties.end() ? static_cast<void*>(&it->second) : nullptr;
}

static void* dol_Config_findInfo2(dol_Config_System system, const char* section, const char* key)
{
  // clang-format off
  auto it = std::find_if(_properties.begin(), _properties.end(),
    [system, section, key](std::pair<const std::string_view, Property>& p) {

#define HandleCase(t1, t2) \
    if (p.second.type == PropertyType::t1) \
    { \
      auto i = static_cast<Config::Info<t2>*>(p.second.info); \
      auto l = i->GetLocation(); \
      return system == static_cast<dol_Config_System>(-1) && l.section == section && l.key == key \
        || l.system == static_cast<Config::System>(system) && l.section == section && l.key == key; \
    }

    HandleCase(Boolean, bool)
    else HandleCase(Integer, int)
    else HandleCase(AspectMode, AspectMode)
    else HandleCase(AudioCommon_DPL2Quality, AudioCommon::DPL2Quality)
    else HandleCase(Config_ShowCursor, Config::ShowCursor)
    else HandleCase(DiscIO_Region, DiscIO::Region)
    else HandleCase(ExpansionInterface_EXIDeviceType, ExpansionInterface::EXIDeviceType)
    else HandleCase(FreeLook_ControlType, FreeLook::ControlType)
    else HandleCase(HSP_HSPDeviceType, HSP::HSPDeviceType)
    else HandleCase(PowerPC_CPUCore, PowerPC::CPUCore)
    else HandleCase(SerialInterface_SIDevices, SerialInterface::SIDevices)
    else HandleCase(ShaderCompilationMode, ShaderCompilationMode)
    else HandleCase(StereoMode, StereoMode)
    else HandleCase(TriState, TriState)
    else HandleCase(WiimoteSource, WiimoteSource)
    else HandleCase(String, std::string)
    else HandleCase(Float, float)
    else HandleCase(Unsigned16, uint16_t)
    else HandleCase(Unsigned32, uint32_t)
    
    return false;
  });

#undef HandleCase
  // clang-format on

  return it != _properties.end() ? static_cast<void*>(&it->second) : nullptr;
}

static int dol_Config_getInfo1(void* prop, bool base)
{
  auto p = static_cast<Property*>(prop);

  // clang-format off
#define HandleCase(t1, t2) \
  if (p->type == PropertyType::t1) \
  { \
    auto i = static_cast<Config::Info<t2>*>(p->info); \
    if (base) \
      return static_cast<int>(Config::GetBase<t2>(*i)); \
    else \
      return static_cast<int>(Config::GetUncached<t2>(*i)); \
  }

  HandleCase(Boolean, bool)
  else HandleCase(Integer, int)
  else HandleCase(AspectMode, AspectMode)
  else HandleCase(AudioCommon_DPL2Quality, AudioCommon::DPL2Quality)
  else HandleCase(Config_ShowCursor, Config::ShowCursor)
  else HandleCase(DiscIO_Region, DiscIO::Region)
  else HandleCase(ExpansionInterface_EXIDeviceType, ExpansionInterface::EXIDeviceType)
  else HandleCase(FreeLook_ControlType, FreeLook::ControlType)
  else HandleCase(HSP_HSPDeviceType, HSP::HSPDeviceType)
  else HandleCase(PowerPC_CPUCore, PowerPC::CPUCore)
  else HandleCase(SerialInterface_SIDevices, SerialInterface::SIDevices)
  else HandleCase(ShaderCompilationMode, ShaderCompilationMode)
  else HandleCase(StereoMode, StereoMode)
  else HandleCase(TriState, TriState)
  else HandleCase(WiimoteSource, WiimoteSource)

#undef HandleCase

  return 0;
}
// clang-format on

static char* dol_Config_getInfo2(void* prop, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::String)
  {
    auto i = static_cast<Config::Info<std::string>*>(p->info);
    if (base)
      return PluginUtil::dupStdString(Config::GetBase(*i));
    else
      return PluginUtil::dupStdString(Config::GetUncached(*i));
  }
  return nullptr;
}

static float dol_Config_getInfo3(void* prop, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::Float)
  {
    auto i = static_cast<Config::Info<float>*>(p->info);
    if (base)
      return Config::GetBase(*i);
    else
      return Config::GetUncached(*i);
  }
  return 0;
}

static uint16_t dol_Config_getInfo4(void* prop, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::Unsigned16)
  {
    auto i = static_cast<Config::Info<uint16_t>*>(p->info);
    if (base)
      return Config::GetBase(*i);
    else
      return Config::GetUncached(*i);
  }
  return 0;
}

static uint32_t dol_Config_getInfo5(void* prop, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::Unsigned32)
  {
    auto i = static_cast<Config::Info<uint32_t>*>(p->info);
    if (base)
      return Config::GetBase(*i);
    else
      return Config::GetUncached(*i);
  }
  return 0;
}

static void dol_Config_setInfo1(void* prop, int value, bool base)
{
  auto p = static_cast<Property*>(prop);

  // clang-format off
#define HandleCase(t1, t2) \
  if (p->type == PropertyType::t1) \
  { \
    auto i = static_cast<Config::Info<t2>*>(p->info); \
    if (base) \
      Config::SetBase(*i, static_cast<t2>(value)); \
    else \
      Config::SetCurrent(*i, static_cast<t2>(value)); \
  }

  HandleCase(Boolean, bool)
  else HandleCase(Integer, int)
  else HandleCase(AspectMode, AspectMode)
  else HandleCase(AudioCommon_DPL2Quality, AudioCommon::DPL2Quality)
  else HandleCase(Config_ShowCursor, Config::ShowCursor)
  else HandleCase(DiscIO_Region, DiscIO::Region)
  else HandleCase(ExpansionInterface_EXIDeviceType, ExpansionInterface::EXIDeviceType)
  else HandleCase(FreeLook_ControlType, FreeLook::ControlType)
  else HandleCase(HSP_HSPDeviceType, HSP::HSPDeviceType)
  else HandleCase(PowerPC_CPUCore, PowerPC::CPUCore)
  else HandleCase(SerialInterface_SIDevices, SerialInterface::SIDevices)
  else HandleCase(ShaderCompilationMode, ShaderCompilationMode)
  else HandleCase(StereoMode, StereoMode)
  else HandleCase(TriState, TriState)
  else HandleCase(WiimoteSource, WiimoteSource)

#undef HandleCase
  // clang-format on
}

static void dol_Config_setInfo2(void* prop, const char* value, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::String)
  {
    auto i = static_cast<Config::Info<std::string>*>(p->info);
    if (base)
      Config::SetBase(*i, std::string(value));
    else
      Config::SetCurrent(*i, std::string(value));
  }
}

static void dol_Config_setInfo3(void* prop, float value, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::Float)
  {
    auto i = static_cast<Config::Info<float>*>(p->info);
    if (base)
      Config::SetBase(*i, static_cast<float>(value));
    else
      Config::SetCurrent(*i, static_cast<float>(value));
  }
}

static void dol_Config_setInfo4(void* prop, uint16_t value, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::Unsigned16)
  {
    auto i = static_cast<Config::Info<uint16_t>*>(p->info);
    if (base)
      Config::SetBase(*i, static_cast<uint16_t>(value));
    else
      Config::SetCurrent(*i, static_cast<uint16_t>(value));
  }
}

static void dol_Config_setInfo5(void* prop, uint32_t value, bool base)
{
  auto p = static_cast<Property*>(prop);
  if (p->type == PropertyType::Unsigned32)
  {
    auto i = static_cast<Config::Info<uint32_t>*>(p->info);
    if (base)
      Config::SetBase(*i, static_cast<uint32_t>(value));
    else
      Config::SetCurrent(*i, static_cast<uint32_t>(value));
  }
}

static dol_DiscIO_Language dol_Config_getDefaultLanguage()
{
  return static_cast<dol_DiscIO_Language>(Config::GetDefaultLanguage());
}

static bool dol_Config_getOptionalDefaultCountry(uint8_t* defaultCountry)
{
  auto opt = Config::GetOptionalDefaultCountry();
  if (opt.has_value())
  {
    *defaultCountry = opt.value();
    return true;
  }
  return false;
}

static uint8_t dol_Config_getDefaultCountry()
{
  return Config::GetDefaultCountry();
}

static dol_DiscIO_Region dol_Config_getDefaultRegion()
{
  return static_cast<dol_DiscIO_Region>(Config::GetDefaultRegion());
}

static void* dol_Config_getInfoForMemcardPath(dol_ExpansionInterface_Slot slot)
{
  _temp_property.info =
      PropertyEraseType(Config::GetInfoForMemcardPath(static_cast<ExpansionInterface::Slot>(slot)));
  _temp_property.type = PropertyType::String;
  return static_cast<void*>(&_temp_property);
}

static void* dol_Config_getInfoForAGPCartPath(dol_ExpansionInterface_Slot slot)
{
  _temp_property.info =
      PropertyEraseType(Config::GetInfoForAGPCartPath(static_cast<ExpansionInterface::Slot>(slot)));
  _temp_property.type = PropertyType::String;
  return static_cast<void*>(&_temp_property);
}

static void* dol_Config_getInfoForGCIPathOverride(dol_ExpansionInterface_Slot slot)
{
  _temp_property.info = PropertyEraseType(
      Config::GetInfoForGCIPathOverride(static_cast<ExpansionInterface::Slot>(slot)));
  _temp_property.type = PropertyType::String;
  return static_cast<void*>(&_temp_property);
}

static void* dol_Config_getInfoForEXIDevice(dol_ExpansionInterface_Slot slot)
{
  _temp_property.info =
      PropertyEraseType(Config::GetInfoForEXIDevice(static_cast<ExpansionInterface::Slot>(slot)));
  _temp_property.type = PropertyType::ExpansionInterface_EXIDeviceType;
  return static_cast<void*>(&_temp_property);
}

static void* dol_Config_getInfoForSIDevice(int channel)
{
  _temp_property.info = PropertyEraseType(Config::GetInfoForSIDevice(channel));
  _temp_property.type = PropertyType::SerialInterface_SIDevices;
  return static_cast<void*>(&_temp_property);
}

static void* dol_Config_getInfoForAdapterRumble(int channel)
{
  _temp_property.info = PropertyEraseType(Config::GetInfoForAdapterRumble(channel));
  _temp_property.type = PropertyType::Boolean;
  return static_cast<void*>(&_temp_property);
}

static void* dol_Config_getInfoForSimulateKonga(int channel)
{
  _temp_property.info = PropertyEraseType(Config::GetInfoForSimulateKonga(channel));
  _temp_property.type = PropertyType::Boolean;
  return static_cast<void*>(&_temp_property);
}

static dol_Config_GPUDeterminismMode dol_Config_getGPUDeterminismMode()
{
  return static_cast<dol_Config_GPUDeterminismMode>(Config::GetGPUDeterminismMode());
}

static bool dol_Config_shouldUseDPL2Decoder()
{
  return Config::ShouldUseDPL2Decoder();
}

static char** dol_Config_getIsoPaths(int* numPaths)
{
  auto paths = Config::GetIsoPaths();
  auto v = static_cast<char**>(interop_malloc(sizeof(char*) * paths.size()));
  for (size_t i{}; i < paths.size(); ++i)
    v[i] = PluginUtil::dupStdString(paths[i]);
  *numPaths = static_cast<int>(paths.size());
  return v;
}

static void dol_Config_setIsoPaths(const char** paths, int numPaths)
{
  std::vector<std::string> v;
  for (int i{}; i < numPaths; ++i)
    v.push_back(paths[i]);
  Config::SetIsoPaths(v);
}

static void dol_Config_getUSBDeviceWhitelist(uint16_t** devices_first, uint16_t** devices_second,
                                             int* numDevices)
{
  auto devices = Config::GetUSBDeviceWhitelist();
  *devices_first = static_cast<uint16_t*>(interop_malloc(sizeof(uint16_t) * devices.size()));
  *devices_second = static_cast<uint16_t*>(interop_malloc(sizeof(uint16_t) * devices.size()));
  size_t i{};
  for (const auto& p : devices)
  {
    (*devices_first)[i] = p.first;
    (*devices_second)[i] = p.second;
    ++i;
  }
  *numDevices = static_cast<int>(devices.size());
}

static void dol_Config_setUSBDeviceWhitelist(uint16_t* devices_first, uint16_t* devices_second,
                                             int numDevices)
{
  std::set<std::pair<u16, u16>> v;
  for (int i{}; i < numDevices; ++i)
    v.insert({devices_first[i], devices_second[i]});
  Config::SetUSBDeviceWhitelist(v);
}

static dol_DiscIO_Region dol_Config_toGameCubeRegion(dol_DiscIO_Region region)
{
  return static_cast<dol_DiscIO_Region>(
      Config::ToGameCubeRegion(static_cast<DiscIO::Region>(region)));
}

static char* dol_Config_getDirectoryForRegion(dol_DiscIO_Region region)
{
  return PluginUtil::dupStdString(
      Config::GetDirectoryForRegion(static_cast<DiscIO::Region>(region)));
}

static char* dol_Config_getBootROMPath(const char* region_directory)
{
  return PluginUtil::dupStdString(Config::GetBootROMPath(region_directory));
}

static char* dol_Config_getMemcardPath1(dol_ExpansionInterface_Slot slot, dol_DiscIO_Region* region,
                                        uint16_t size_mb)
{
  return PluginUtil::dupStdString(Config::GetMemcardPath(
      static_cast<ExpansionInterface::Slot>(slot),
      region ? std::optional(static_cast<DiscIO::Region>(*region)) : std::nullopt, size_mb));
}

static char* dol_Config_getMemcardPath2(const char* configured_filename,
                                        dol_ExpansionInterface_Slot slot, dol_DiscIO_Region* region,
                                        uint16_t size_mb)
{
  return PluginUtil::dupStdString(Config::GetMemcardPath(
      configured_filename, static_cast<ExpansionInterface::Slot>(slot),
      region ? std::optional(static_cast<DiscIO::Region>(*region)) : std::nullopt, size_mb));
}

static bool dol_Config_isDefaultMemcardPathConfigured(dol_ExpansionInterface_Slot slot)
{
  return Config::IsDefaultMemcardPathConfigured(static_cast<ExpansionInterface::Slot>(slot));
}

static void* dol_Config_getInfoForWiimoteSource(int index)
{
  _temp_property.info = PropertyEraseType(Config::GetInfoForWiimoteSource(index));
  _temp_property.type = PropertyType::WiimoteSource;
  return static_cast<void*>(&_temp_property);
}

EXPORT dol_Config* dol_Config_newInterface()
{
  auto iface = static_cast<dol_Config*>(interop_calloc(1, sizeof(dol_Config)));
  iface->findInfo1 = dol_Config_findInfo1;
  iface->findInfo2 = dol_Config_findInfo2;
  iface->getInfo1 = dol_Config_getInfo1;
  iface->getInfo2 = dol_Config_getInfo2;
  iface->getInfo3 = dol_Config_getInfo3;
  iface->getInfo4 = dol_Config_getInfo4;
  iface->getInfo5 = dol_Config_getInfo5;
  iface->setInfo1 = dol_Config_setInfo1;
  iface->setInfo2 = dol_Config_setInfo2;
  iface->setInfo3 = dol_Config_setInfo3;
  iface->setInfo4 = dol_Config_setInfo4;
  iface->setInfo5 = dol_Config_setInfo5;
  iface->getDefaultLanguage = dol_Config_getDefaultLanguage;
  iface->getOptionalDefaultCountry = dol_Config_getOptionalDefaultCountry;
  iface->getDefaultCountry = dol_Config_getDefaultCountry;
  iface->getDefaultRegion = dol_Config_getDefaultRegion;
  iface->getInfoForMemcardPath = dol_Config_getInfoForMemcardPath;
  iface->getInfoForAGPCartPath = dol_Config_getInfoForAGPCartPath;
  iface->getInfoForGCIPathOverride = dol_Config_getInfoForGCIPathOverride;
  iface->getInfoForEXIDevice = dol_Config_getInfoForEXIDevice;
  iface->getInfoForSIDevice = dol_Config_getInfoForSIDevice;
  iface->getInfoForAdapterRumble = dol_Config_getInfoForAdapterRumble;
  iface->getInfoForSimulateKonga = dol_Config_getInfoForSimulateKonga;
  iface->getGPUDeterminismMode = dol_Config_getGPUDeterminismMode;
  iface->shouldUseDPL2Decoder = dol_Config_shouldUseDPL2Decoder;
  iface->getIsoPaths = dol_Config_getIsoPaths;
  iface->setIsoPaths = dol_Config_setIsoPaths;
  iface->getUSBDeviceWhitelist = dol_Config_getUSBDeviceWhitelist;
  iface->setUSBDeviceWhitelist = dol_Config_setUSBDeviceWhitelist;
  iface->toGameCubeRegion = dol_Config_toGameCubeRegion;
  iface->getDirectoryForRegion = dol_Config_getDirectoryForRegion;
  iface->getBootROMPath = dol_Config_getBootROMPath;
  iface->getMemcardPath1 = dol_Config_getMemcardPath1;
  iface->getMemcardPath2 = dol_Config_getMemcardPath2;
  iface->isDefaultMemcardPathConfigured = dol_Config_isDefaultMemcardPathConfigured;
  iface->getInfoForWiimoteSource = dol_Config_getInfoForWiimoteSource;

  return iface;
}
