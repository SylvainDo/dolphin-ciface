#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Settings.h"

#include "DolphinQt/Settings.h"

static void dol_Gui_Settings_unregisterDevicesChangedCallback()
{
  Settings::Instance().UnregisterDevicesChangedCallback();
}

// UI

static void dol_Gui_Settings_setThemeName(const char* theme_name)
{
  Settings::Instance().SetThemeName(QString::fromUtf8(theme_name));
}

static void dol_Gui_Settings_setCurrentUserStyle(const char* stylesheet_name)
{
  Settings::Instance().SetCurrentUserStyle(QString::fromUtf8(stylesheet_name));
}

static char* dol_Gui_Settings_getCurrentUserStyle()
{
  return InteropUtil::dupStdString(Settings::Instance().GetCurrentUserStyle().toStdString());
}

static void dol_Gui_Settings_setUserStylesEnabled(bool enabled)
{
  Settings::Instance().SetUserStylesEnabled(enabled);
}

static bool dol_Gui_Settings_areUserStylesEnabled()
{
  return Settings::Instance().AreUserStylesEnabled();
}

static bool dol_Gui_Settings_isLogVisible()
{
  return Settings::Instance().IsLogVisible();
}

static void dol_Gui_Settings_setLogVisible(bool visible)
{
  Settings::Instance().SetLogVisible(visible);
}

static bool dol_Gui_Settings_isLogConfigVisible()
{
  return Settings::Instance().IsLogConfigVisible();
}

static void dol_Gui_Settings_setLogConfigVisible(bool visible)
{
  Settings::Instance().SetLogConfigVisible(visible);
}

static void dol_Gui_Settings_setToolBarVisible(bool visible)
{
  Settings::Instance().SetToolBarVisible(visible);
}

static bool dol_Gui_Settings_isToolBarVisible()
{
  return Settings::Instance().IsToolBarVisible();
}

static void dol_Gui_Settings_setWidgetsLocked(bool locked)
{
  Settings::Instance().SetWidgetsLocked(locked);
}

static bool dol_Gui_Settings_areWidgetsLocked()
{
  return Settings::Instance().AreWidgetsLocked();
}

static void dol_Gui_Settings_refreshWidgetVisibility()
{
  Settings::Instance().RefreshWidgetVisibility();
}

// GameList

static char** dol_Gui_Settings_getPaths(int* numPaths)
{
  auto paths = Settings::Instance().GetPaths();
  auto v = static_cast<char**>(interop_malloc(sizeof(char*) * paths.size()));
  for (qsizetype i{}; i < paths.size(); ++i)
    v[i] = InteropUtil::dupStdString(paths[i].toStdString());
  *numPaths = static_cast<int>(paths.size());
  return v;
}

static void dol_Gui_Settings_addPath(const char* path)
{
  Settings::Instance().AddPath(QString::fromUtf8(path));
}

static void dol_Gui_Settings_removePath(const char* path)
{
  Settings::Instance().RemovePath(QString::fromUtf8(path));
}

static bool dol_Gui_Settings_getPreferredView()
{
  return Settings::Instance().GetPreferredView();
}

static void dol_Gui_Settings_setPreferredView(bool list)
{
  Settings::Instance().SetPreferredView(list);
}

static char* dol_Gui_Settings_getDefaultGame()
{
  return InteropUtil::dupStdString(Settings::Instance().GetDefaultGame().toStdString());
}

static void dol_Gui_Settings_setDefaultGame(const char* path)
{
  Settings::Instance().SetDefaultGame(QString::fromUtf8(path));
}

static void dol_Gui_Settings_refreshGameList()
{
  Settings::Instance().RefreshGameList();
}

static void dol_Gui_Settings_notifyRefreshGameListStarted()
{
  Settings::Instance().NotifyRefreshGameListStarted();
}

static void dol_Gui_Settings_notifyRefreshGameListComplete()
{
  Settings::Instance().NotifyRefreshGameListComplete();
}

static void dol_Gui_Settings_refreshMetadata()
{
  Settings::Instance().RefreshMetadata();
}

static void dol_Gui_Settings_notifyMetadataRefreshComplete()
{
  Settings::Instance().NotifyMetadataRefreshComplete();
}

static void dol_Gui_Settings_reloadTitleDB()
{
  Settings::Instance().ReloadTitleDB();
}

static bool dol_Gui_Settings_isAutoRefreshEnabled()
{
  return Settings::Instance().IsAutoRefreshEnabled();
}

static void dol_Gui_Settings_setAutoRefreshEnabled(bool enabled)
{
  Settings::Instance().SetAutoRefreshEnabled(enabled);
}

// Emulation

static int dol_Gui_Settings_getStateSlot()
{
  return Settings::Instance().GetStateSlot();
}

static void dol_Gui_Settings_setStateSlot(int slot)
{
  Settings::Instance().SetStateSlot(slot);
}

static bool dol_Gui_Settings_isBatchModeEnabled()
{
  return Settings::Instance().IsBatchModeEnabled();
}

static void dol_Gui_Settings_setBatchModeEnabled(bool batch)
{
  Settings::Instance().SetBatchModeEnabled(batch);
}

static bool dol_Gui_Settings_isSDCardInserted()
{
  return Settings::Instance().IsSDCardInserted();
}

static void dol_Gui_Settings_setSDCardInserted(bool inserted)
{
  Settings::Instance().SetSDCardInserted(inserted);
}

static bool dol_Gui_Settings_isUSBKeyboardConnected()
{
  return Settings::Instance().IsUSBKeyboardConnected();
}

static void dol_Gui_Settings_setUSBKeyboardConnected(bool connected)
{
  Settings::Instance().SetUSBKeyboardConnected(connected);
}

// Graphics

static void dol_Gui_Settings_setCursorVisibility(dol_Config_ShowCursor hideCursor)
{
  Settings::Instance().SetCursorVisibility(static_cast<Config::ShowCursor>(hideCursor));
}

static dol_Config_ShowCursor dol_Gui_Settings_getCursorVisibility()
{
  return static_cast<dol_Config_ShowCursor>(Settings::Instance().GetCursorVisibility());
}

static void dol_Gui_Settings_setLockCursor(bool lock_cursor)
{
  Settings::Instance().SetLockCursor(lock_cursor);
}

static bool dol_Gui_Settings_getLockCursor()
{
  return Settings::Instance().GetLockCursor();
}

static void dol_Gui_Settings_setKeepWindowOnTop(bool top)
{
  Settings::Instance().SetKeepWindowOnTop(top);
}

static bool dol_Gui_Settings_isKeepWindowOnTopEnabled()
{
  return Settings::Instance().IsKeepWindowOnTopEnabled();
}

static bool dol_Gui_Settings_getGraphicModsEnabled()
{
  return Settings::Instance().GetGraphicModsEnabled();
}

static void dol_Gui_Settings_setGraphicModsEnabled(bool enabled)
{
  Settings::Instance().SetGraphicModsEnabled(enabled);
}

// Audio

static int dol_Gui_Settings_getVolume()
{
  return Settings::Instance().GetVolume();
}

static void dol_Gui_Settings_setVolume(int volume)
{
  Settings::Instance().SetVolume(volume);
}

static void dol_Gui_Settings_increaseVolume(int volume)
{
  Settings::Instance().IncreaseVolume(volume);
}

static void dol_Gui_Settings_decreaseVolume(int volume)
{
  Settings::Instance().DecreaseVolume(volume);
}

// Cheats

static bool dol_Gui_Settings_getCheatsEnabled()
{
  return Settings::Instance().GetCheatsEnabled();
}

static void dol_Gui_Settings_setCheatsEnabled(bool enabled)
{
  Settings::Instance().SetCheatsEnabled(enabled);
}

// Debug

static void dol_Gui_Settings_setDebugModeEnabled(bool enabled)
{
  Settings::Instance().SetDebugModeEnabled(enabled);
}

static bool dol_Gui_Settings_isDebugModeEnabled()
{
  return Settings::Instance().IsDebugModeEnabled();
}

static void dol_Gui_Settings_setRegistersVisible(bool enabled)
{
  Settings::Instance().SetRegistersVisible(enabled);
}

static bool dol_Gui_Settings_isRegistersVisible()
{
  return Settings::Instance().IsRegistersVisible();
}

static void dol_Gui_Settings_setThreadsVisible(bool enabled)
{
  Settings::Instance().SetThreadsVisible(enabled);
}

static bool dol_Gui_Settings_isThreadsVisible()
{
  return Settings::Instance().IsThreadsVisible();
}

static void dol_Gui_Settings_setWatchVisible(bool enabled)
{
  Settings::Instance().SetWatchVisible(enabled);
}

static bool dol_Gui_Settings_isWatchVisible()
{
  return Settings::Instance().IsWatchVisible();
}

static void dol_Gui_Settings_setBreakpointsVisible(bool enabled)
{
  Settings::Instance().SetBreakpointsVisible(enabled);
}

static bool dol_Gui_Settings_isBreakpointsVisible()
{
  return Settings::Instance().IsBreakpointsVisible();
}

static void dol_Gui_Settings_setCodeVisible(bool enabled)
{
  Settings::Instance().SetCodeVisible(enabled);
}

static bool dol_Gui_Settings_isCodeVisible()
{
  return Settings::Instance().IsCodeVisible();
}

static void dol_Gui_Settings_setMemoryVisible(bool enabled)
{
  Settings::Instance().SetMemoryVisible(enabled);
}

static bool dol_Gui_Settings_isMemoryVisible()
{
  return Settings::Instance().IsMemoryVisible();
}

static void dol_Gui_Settings_setNetworkVisible(bool enabled)
{
  Settings::Instance().SetNetworkVisible(enabled);
}

static bool dol_Gui_Settings_isNetworkVisible()
{
  return Settings::Instance().IsNetworkVisible();
}

static void dol_Gui_Settings_setJITVisible(bool enabled)
{
  Settings::Instance().SetJITVisible(enabled);
}

static bool dol_Gui_Settings_isJITVisible()
{
  return Settings::Instance().IsJITVisible();
}

// Auto-Update

static char* dol_Gui_Settings_getAutoUpdateTrack()
{
  return InteropUtil::dupStdString(Settings::Instance().GetAutoUpdateTrack().toStdString());
}

static void dol_Gui_Settings_setAutoUpdateTrack(const char* mode)
{
  Settings::Instance().SetAutoUpdateTrack(QString::fromUtf8(mode));
}

// Fallback Region

static dol_DiscIO_Region dol_Gui_Settings_getFallbackRegion()
{
  return static_cast<dol_DiscIO_Region>(Settings::Instance().GetFallbackRegion());
}

static void dol_Gui_Settings_setFallbackRegion(dol_DiscIO_Region region)
{
  Settings::Instance().SetFallbackRegion(static_cast<DiscIO::Region>(region));
}

// Analytics

static bool dol_Gui_Settings_isAnalyticsEnabled()
{
  return Settings::Instance().IsAnalyticsEnabled();
}

static void dol_Gui_Settings_setAnalyticsEnabled(bool enabled)
{
  Settings::Instance().SetAnalyticsEnabled(enabled);
}

EXPORT dol_Gui_Settings* dol_Gui_Settings_newInterface()
{
  auto iface = static_cast<dol_Gui_Settings*>(interop_calloc(1, sizeof(dol_Gui_Settings)));
  iface->unregisterDevicesChangedCallback = dol_Gui_Settings_unregisterDevicesChangedCallback;
  // UI
  iface->setThemeName = dol_Gui_Settings_setThemeName;
  iface->setCurrentUserStyle = dol_Gui_Settings_setCurrentUserStyle;
  iface->getCurrentUserStyle = dol_Gui_Settings_getCurrentUserStyle;
  iface->setUserStylesEnabled = dol_Gui_Settings_setUserStylesEnabled;
  iface->areUserStylesEnabled = dol_Gui_Settings_areUserStylesEnabled;
  iface->isLogVisible = dol_Gui_Settings_isLogVisible;
  iface->setLogVisible = dol_Gui_Settings_setLogVisible;
  iface->isLogConfigVisible = dol_Gui_Settings_isLogConfigVisible;
  iface->setLogConfigVisible = dol_Gui_Settings_setLogConfigVisible;
  iface->setToolBarVisible = dol_Gui_Settings_setToolBarVisible;
  iface->isToolBarVisible = dol_Gui_Settings_isToolBarVisible;
  iface->setWidgetsLocked = dol_Gui_Settings_setWidgetsLocked;
  iface->areWidgetsLocked = dol_Gui_Settings_areWidgetsLocked;
  iface->refreshWidgetVisibility = dol_Gui_Settings_refreshWidgetVisibility;
  // GameList
  iface->getPaths = dol_Gui_Settings_getPaths;
  iface->addPath = dol_Gui_Settings_addPath;
  iface->removePath = dol_Gui_Settings_removePath;
  iface->getPreferredView = dol_Gui_Settings_getPreferredView;
  iface->setPreferredView = dol_Gui_Settings_setPreferredView;
  iface->getDefaultGame = dol_Gui_Settings_getDefaultGame;
  iface->setDefaultGame = dol_Gui_Settings_setDefaultGame;
  iface->refreshGameList = dol_Gui_Settings_refreshGameList;
  iface->notifyRefreshGameListStarted = dol_Gui_Settings_notifyRefreshGameListStarted;
  iface->notifyRefreshGameListComplete = dol_Gui_Settings_notifyRefreshGameListComplete;
  iface->refreshMetadata = dol_Gui_Settings_refreshMetadata;
  iface->notifyMetadataRefreshComplete = dol_Gui_Settings_notifyMetadataRefreshComplete;
  iface->reloadTitleDB = dol_Gui_Settings_reloadTitleDB;
  iface->isAutoRefreshEnabled = dol_Gui_Settings_isAutoRefreshEnabled;
  iface->setAutoRefreshEnabled = dol_Gui_Settings_setAutoRefreshEnabled;
  // Emulation
  iface->getStateSlot = dol_Gui_Settings_getStateSlot;
  iface->setStateSlot = dol_Gui_Settings_setStateSlot;
  iface->isBatchModeEnabled = dol_Gui_Settings_isBatchModeEnabled;
  iface->setBatchModeEnabled = dol_Gui_Settings_setBatchModeEnabled;
  iface->isSDCardInserted = dol_Gui_Settings_isSDCardInserted;
  iface->setSDCardInserted = dol_Gui_Settings_setSDCardInserted;
  iface->isUSBKeyboardConnected = dol_Gui_Settings_isUSBKeyboardConnected;
  iface->setUSBKeyboardConnected = dol_Gui_Settings_setUSBKeyboardConnected;
  // Graphics
  iface->setCursorVisibility = dol_Gui_Settings_setCursorVisibility;
  iface->getCursorVisibility = dol_Gui_Settings_getCursorVisibility;
  iface->setLockCursor = dol_Gui_Settings_setLockCursor;
  iface->getLockCursor = dol_Gui_Settings_getLockCursor;
  iface->setKeepWindowOnTop = dol_Gui_Settings_setKeepWindowOnTop;
  iface->isKeepWindowOnTopEnabled = dol_Gui_Settings_isKeepWindowOnTopEnabled;
  iface->getGraphicModsEnabled = dol_Gui_Settings_getGraphicModsEnabled;
  iface->setGraphicModsEnabled = dol_Gui_Settings_setGraphicModsEnabled;
  // Audio
  iface->getVolume = dol_Gui_Settings_getVolume;
  iface->setVolume = dol_Gui_Settings_setVolume;
  iface->increaseVolume = dol_Gui_Settings_increaseVolume;
  iface->decreaseVolume = dol_Gui_Settings_decreaseVolume;
  // Cheats
  iface->getCheatsEnabled = dol_Gui_Settings_getCheatsEnabled;
  iface->setCheatsEnabled = dol_Gui_Settings_setCheatsEnabled;
  // Debug
  iface->setDebugModeEnabled = dol_Gui_Settings_setDebugModeEnabled;
  iface->isDebugModeEnabled = dol_Gui_Settings_isDebugModeEnabled;
  iface->setRegistersVisible = dol_Gui_Settings_setRegistersVisible;
  iface->isRegistersVisible = dol_Gui_Settings_isRegistersVisible;
  iface->setThreadsVisible = dol_Gui_Settings_setThreadsVisible;
  iface->isThreadsVisible = dol_Gui_Settings_isThreadsVisible;
  iface->setWatchVisible = dol_Gui_Settings_setWatchVisible;
  iface->isWatchVisible = dol_Gui_Settings_isWatchVisible;
  iface->setBreakpointsVisible = dol_Gui_Settings_setBreakpointsVisible;
  iface->isBreakpointsVisible = dol_Gui_Settings_isBreakpointsVisible;
  iface->setCodeVisible = dol_Gui_Settings_setCodeVisible;
  iface->isCodeVisible = dol_Gui_Settings_isCodeVisible;
  iface->setMemoryVisible = dol_Gui_Settings_setMemoryVisible;
  iface->isMemoryVisible = dol_Gui_Settings_isMemoryVisible;
  iface->setNetworkVisible = dol_Gui_Settings_setNetworkVisible;
  iface->isNetworkVisible = dol_Gui_Settings_isNetworkVisible;
  iface->setJITVisible = dol_Gui_Settings_setJITVisible;
  iface->isJITVisible = dol_Gui_Settings_isJITVisible;
  // Auto-Update
  iface->getAutoUpdateTrack = dol_Gui_Settings_getAutoUpdateTrack;
  iface->setAutoUpdateTrack = dol_Gui_Settings_setAutoUpdateTrack;
  // Fallback Region
  iface->getFallbackRegion = dol_Gui_Settings_getFallbackRegion;
  iface->setFallbackRegion = dol_Gui_Settings_setFallbackRegion;
  // Analytics
  iface->isAnalyticsEnabled = dol_Gui_Settings_isAnalyticsEnabled;
  iface->setAnalyticsEnabled = dol_Gui_Settings_setAnalyticsEnabled;

  return iface;
}
