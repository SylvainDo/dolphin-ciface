#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dolGuiSettings
{
  void (*unregisterDevicesChangedCallback)(void);
  // UI
  void (*setThemeName)(const char* theme_name);
  void (*setCurrentUserStyle)(const char* stylesheet_name);
  char* (*getCurrentUserStyle)(void);
  void (*setUserStylesEnabled)(bool enabled);
  bool (*areUserStylesEnabled)(void);
  bool (*isLogVisible)(void);
  void (*setLogVisible)(bool visible);
  bool (*isLogConfigVisible)(void);
  void (*setLogConfigVisible)(bool visible);
  void (*setToolBarVisible)(bool visible);
  bool (*isToolBarVisible)(void);
  void (*setWidgetsLocked)(bool locked);
  bool (*areWidgetsLocked)(void);
  void (*refreshWidgetVisibility)(void);
  // GameList
  char** (*getPaths)(int* numPaths);
  void (*addPath)(const char* path);
  void (*removePath)(const char* path);
  bool (*getPreferredView)(void);
  void (*setPreferredView)(bool list);
  char* (*getDefaultGame)(void);
  void (*setDefaultGame)(const char* path);
  void (*refreshGameList)(void);
  void (*notifyRefreshGameListStarted)(void);
  void (*notifyRefreshGameListComplete)(void);
  void (*refreshMetadata)(void);
  void (*notifyMetadataRefreshComplete)(void);
  void (*reloadTitleDB)(void);
  bool (*isAutoRefreshEnabled)(void);
  void (*setAutoRefreshEnabled)(bool enabled);
  // Emulation
  int (*getStateSlot)(void);
  void (*setStateSlot)(int slot);
  bool (*isBatchModeEnabled)(void);
  void (*setBatchModeEnabled)(bool batch);
  bool (*isSDCardInserted)(void);
  void (*setSDCardInserted)(bool inserted);
  bool (*isUSBKeyboardConnected)(void);
  void (*setUSBKeyboardConnected)(bool connected);
  // Graphics
  void (*setCursorVisibility)(dolConfigShowCursor hideCursor);
  dolConfigShowCursor (*getCursorVisibility)(void);
  void (*setLockCursor)(bool lock_cursor);
  bool (*getLockCursor)(void);
  void (*setKeepWindowOnTop)(bool top);
  bool (*isKeepWindowOnTopEnabled)(void);
  bool (*getGraphicModsEnabled)(void);
  void (*setGraphicModsEnabled)(bool enabled);
  // Audio
  int (*getVolume)(void);
  void (*setVolume)(int volume);
  void (*increaseVolume)(int volume);
  void (*decreaseVolume)(int volume);
  // Cheats
  bool (*getCheatsEnabled)(void);
  void (*setCheatsEnabled)(bool enabled);
  // Debug
  void (*setDebugModeEnabled)(bool enabled);
  bool (*isDebugModeEnabled)(void);
  void (*setRegistersVisible)(bool enabled);
  bool (*isRegistersVisible)(void);
  void (*setThreadsVisible)(bool enabled);
  bool (*isThreadsVisible)(void);
  void (*setWatchVisible)(bool enabled);
  bool (*isWatchVisible)(void);
  void (*setBreakpointsVisible)(bool enabled);
  bool (*isBreakpointsVisible)(void);
  void (*setCodeVisible)(bool enabled);
  bool (*isCodeVisible)(void);
  void (*setMemoryVisible)(bool enabled);
  bool (*isMemoryVisible)(void);
  void (*setNetworkVisible)(bool enabled);
  bool (*isNetworkVisible)(void);
  void (*setJITVisible)(bool enabled);
  bool (*isJITVisible)(void);
  // Auto-Update
  char* (*getAutoUpdateTrack)(void);
  void (*setAutoUpdateTrack)(const char* mode);
  // Fallback Region
  dolDiscIORegion (*getFallbackRegion)(void);
  void (*setFallbackRegion)(dolDiscIORegion region);
  // Analytics
  bool (*isAnalyticsEnabled)(void);
  void (*setAnalyticsEnabled)(bool enabled);
};

typedef dolGuiSettings* (*dolGuiSettings_newInterface_t)(void);

#ifdef __cplusplus
}
#endif