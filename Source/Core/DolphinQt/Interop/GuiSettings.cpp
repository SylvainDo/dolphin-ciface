#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/GuiSettings.h"

#include "DolphinQt/Settings.h"

static void dolGuiSettings_unregisterDevicesChangedCallback()
{
  Settings::Instance().UnregisterDevicesChangedCallback();
}

// UI

static void dolGuiSettings_setThemeName(const char* theme_name)
{
  Settings::Instance().SetThemeName(QString::fromUtf8(theme_name));
}

static void dolGuiSettings_setCurrentUserStyle(const char* stylesheet_name)
{
  Settings::Instance().SetCurrentUserStyle(QString::fromUtf8(stylesheet_name));
}

static char* dolGuiSettings_getCurrentUserStyle()
{
  return InteropUtil::dupStdString(Settings::Instance().GetCurrentUserStyle().toStdString());
}

static void dolGuiSettings_setUserStylesEnabled(bool enabled)
{
  Settings::Instance().SetUserStylesEnabled(enabled);
}

static bool dolGuiSettings_areUserStylesEnabled()
{
  return Settings::Instance().AreUserStylesEnabled();
}

static bool dolGuiSettings_isLogVisible()
{
  return Settings::Instance().IsLogVisible();
}

static void dolGuiSettings_setLogVisible(bool visible)
{
  Settings::Instance().SetLogVisible(visible);
}

static bool dolGuiSettings_isLogConfigVisible()
{
  return Settings::Instance().IsLogConfigVisible();
}

static void dolGuiSettings_setLogConfigVisible(bool visible)
{
  Settings::Instance().SetLogConfigVisible(visible);
}

static void dolGuiSettings_setToolBarVisible(bool visible)
{
  Settings::Instance().SetToolBarVisible(visible);
}

static bool dolGuiSettings_isToolBarVisible()
{
  return Settings::Instance().IsToolBarVisible();
}

static void dolGuiSettings_setWidgetsLocked(bool locked)
{
  Settings::Instance().SetWidgetsLocked(locked);
}

static bool dolGuiSettings_areWidgetsLocked()
{
  return Settings::Instance().AreWidgetsLocked();
}

static void dolGuiSettings_refreshWidgetVisibility()
{
  Settings::Instance().RefreshWidgetVisibility();
}

// GameList

static char** dolGuiSettings_getPaths(int* numPaths)
{
  auto paths = Settings::Instance().GetPaths();
  auto v = static_cast<char**>(interop_malloc(sizeof(char*) * paths.size()));
  for (qsizetype i{}; i < paths.size(); ++i)
    v[i] = InteropUtil::dupStdString(paths[i].toStdString());
  *numPaths = static_cast<int>(paths.size());
  return v;
}

static void dolGuiSettings_addPath(const char* path)
{
  Settings::Instance().AddPath(QString::fromUtf8(path));
}

static void dolGuiSettings_removePath(const char* path)
{
  Settings::Instance().RemovePath(QString::fromUtf8(path));
}

static bool dolGuiSettings_getPreferredView()
{
  return Settings::Instance().GetPreferredView();
}

static void dolGuiSettings_setPreferredView(bool list)
{
  Settings::Instance().SetPreferredView(list);
}

static char* dolGuiSettings_getDefaultGame()
{
  return InteropUtil::dupStdString(Settings::Instance().GetDefaultGame().toStdString());
}

static void dolGuiSettings_setDefaultGame(const char* path)
{
  Settings::Instance().SetDefaultGame(QString::fromUtf8(path));
}

static void dolGuiSettings_refreshGameList()
{
  Settings::Instance().RefreshGameList();
}

static void dolGuiSettings_notifyRefreshGameListStarted()
{
  Settings::Instance().NotifyRefreshGameListStarted();
}

static void dolGuiSettings_notifyRefreshGameListComplete()
{
  Settings::Instance().NotifyRefreshGameListComplete();
}

static void dolGuiSettings_refreshMetadata()
{
  Settings::Instance().RefreshMetadata();
}

static void dolGuiSettings_notifyMetadataRefreshComplete()
{
  Settings::Instance().NotifyMetadataRefreshComplete();
}

static void dolGuiSettings_reloadTitleDB()
{
  Settings::Instance().ReloadTitleDB();
}

static bool dolGuiSettings_isAutoRefreshEnabled()
{
  return Settings::Instance().IsAutoRefreshEnabled();
}

static void dolGuiSettings_setAutoRefreshEnabled(bool enabled)
{
  Settings::Instance().SetAutoRefreshEnabled(enabled);
}

// Emulation

static int dolGuiSettings_getStateSlot()
{
  return Settings::Instance().GetStateSlot();
}

static void dolGuiSettings_setStateSlot(int slot)
{
  Settings::Instance().SetStateSlot(slot);
}

static bool dolGuiSettings_isBatchModeEnabled()
{
  return Settings::Instance().IsBatchModeEnabled();
}

static void dolGuiSettings_setBatchModeEnabled(bool batch)
{
  Settings::Instance().SetBatchModeEnabled(batch);
}

static bool dolGuiSettings_isSDCardInserted()
{
  return Settings::Instance().IsSDCardInserted();
}

static void dolGuiSettings_setSDCardInserted(bool inserted)
{
  Settings::Instance().SetSDCardInserted(inserted);
}

static bool dolGuiSettings_isUSBKeyboardConnected()
{
  return Settings::Instance().IsUSBKeyboardConnected();
}

static void dolGuiSettings_setUSBKeyboardConnected(bool connected)
{
  Settings::Instance().SetUSBKeyboardConnected(connected);
}

// Graphics

static void dolGuiSettings_setCursorVisibility(dolConfigShowCursor hideCursor)
{
  Settings::Instance().SetCursorVisibility(static_cast<Config::ShowCursor>(hideCursor));
}

static dolConfigShowCursor dolGuiSettings_getCursorVisibility()
{
  return static_cast<dolConfigShowCursor>(Settings::Instance().GetCursorVisibility());
}

static void dolGuiSettings_setLockCursor(bool lock_cursor)
{
  Settings::Instance().SetLockCursor(lock_cursor);
}

static bool dolGuiSettings_getLockCursor()
{
  return Settings::Instance().GetLockCursor();
}

static void dolGuiSettings_setKeepWindowOnTop(bool top)
{
  Settings::Instance().SetKeepWindowOnTop(top);
}

static bool dolGuiSettings_isKeepWindowOnTopEnabled()
{
  return Settings::Instance().IsKeepWindowOnTopEnabled();
}

static bool dolGuiSettings_getGraphicModsEnabled()
{
  return Settings::Instance().GetGraphicModsEnabled();
}

static void dolGuiSettings_setGraphicModsEnabled(bool enabled)
{
  Settings::Instance().SetGraphicModsEnabled(enabled);
}

// Audio

static int dolGuiSettings_getVolume()
{
  return Settings::Instance().GetVolume();
}

static void dolGuiSettings_setVolume(int volume)
{
  Settings::Instance().SetVolume(volume);
}

static void dolGuiSettings_increaseVolume(int volume)
{
  Settings::Instance().IncreaseVolume(volume);
}

static void dolGuiSettings_decreaseVolume(int volume)
{
  Settings::Instance().DecreaseVolume(volume);
}

// Cheats

static bool dolGuiSettings_getCheatsEnabled()
{
  return Settings::Instance().GetCheatsEnabled();
}

static void dolGuiSettings_setCheatsEnabled(bool enabled)
{
  Settings::Instance().SetCheatsEnabled(enabled);
}

// Debug

static void dolGuiSettings_setDebugModeEnabled(bool enabled)
{
  Settings::Instance().SetDebugModeEnabled(enabled);
}

static bool dolGuiSettings_isDebugModeEnabled()
{
  return Settings::Instance().IsDebugModeEnabled();
}

static void dolGuiSettings_setRegistersVisible(bool enabled)
{
  Settings::Instance().SetRegistersVisible(enabled);
}

static bool dolGuiSettings_isRegistersVisible()
{
  return Settings::Instance().IsRegistersVisible();
}

static void dolGuiSettings_setThreadsVisible(bool enabled)
{
  Settings::Instance().SetThreadsVisible(enabled);
}

static bool dolGuiSettings_isThreadsVisible()
{
  return Settings::Instance().IsThreadsVisible();
}

static void dolGuiSettings_setWatchVisible(bool enabled)
{
  Settings::Instance().SetWatchVisible(enabled);
}

static bool dolGuiSettings_isWatchVisible()
{
  return Settings::Instance().IsWatchVisible();
}

static void dolGuiSettings_setBreakpointsVisible(bool enabled)
{
  Settings::Instance().SetBreakpointsVisible(enabled);
}

static bool dolGuiSettings_isBreakpointsVisible()
{
  return Settings::Instance().IsBreakpointsVisible();
}

static void dolGuiSettings_setCodeVisible(bool enabled)
{
  Settings::Instance().SetCodeVisible(enabled);
}

static bool dolGuiSettings_isCodeVisible()
{
  return Settings::Instance().IsCodeVisible();
}

static void dolGuiSettings_setMemoryVisible(bool enabled)
{
  Settings::Instance().SetMemoryVisible(enabled);
}

static bool dolGuiSettings_isMemoryVisible()
{
  return Settings::Instance().IsMemoryVisible();
}

static void dolGuiSettings_setNetworkVisible(bool enabled)
{
  Settings::Instance().SetNetworkVisible(enabled);
}

static bool dolGuiSettings_isNetworkVisible()
{
  return Settings::Instance().IsNetworkVisible();
}

static void dolGuiSettings_setJITVisible(bool enabled)
{
  Settings::Instance().SetJITVisible(enabled);
}

static bool dolGuiSettings_isJITVisible()
{
  return Settings::Instance().IsJITVisible();
}

// Auto-Update

static char* dolGuiSettings_getAutoUpdateTrack()
{
  return InteropUtil::dupStdString(Settings::Instance().GetAutoUpdateTrack().toStdString());
}

static void dolGuiSettings_setAutoUpdateTrack(const char* mode)
{
  Settings::Instance().SetAutoUpdateTrack(QString::fromUtf8(mode));
}

// Fallback Region

static dolDiscIORegion dolGuiSettings_getFallbackRegion()
{
  return static_cast<dolDiscIORegion>(Settings::Instance().GetFallbackRegion());
}

static void dolGuiSettings_setFallbackRegion(dolDiscIORegion region)
{
  Settings::Instance().SetFallbackRegion(static_cast<DiscIO::Region>(region));
}

// Analytics

static bool dolGuiSettings_isAnalyticsEnabled()
{
  return Settings::Instance().IsAnalyticsEnabled();
}

static void dolGuiSettings_setAnalyticsEnabled(bool enabled)
{
  Settings::Instance().SetAnalyticsEnabled(enabled);
}

EXPORT dolGuiSettings* dolGuiSettings_newInterface()
{
  auto iface = static_cast<dolGuiSettings*>(interop_calloc(1, sizeof(dolGuiSettings)));
  iface->unregisterDevicesChangedCallback = dolGuiSettings_unregisterDevicesChangedCallback;
  // UI
  iface->setThemeName = dolGuiSettings_setThemeName;
  iface->setCurrentUserStyle = dolGuiSettings_setCurrentUserStyle;
  iface->getCurrentUserStyle = dolGuiSettings_getCurrentUserStyle;
  iface->setUserStylesEnabled = dolGuiSettings_setUserStylesEnabled;
  iface->areUserStylesEnabled = dolGuiSettings_areUserStylesEnabled;
  iface->isLogVisible = dolGuiSettings_isLogVisible;
  iface->setLogVisible = dolGuiSettings_setLogVisible;
  iface->isLogConfigVisible = dolGuiSettings_isLogConfigVisible;
  iface->setLogConfigVisible = dolGuiSettings_setLogConfigVisible;
  iface->setToolBarVisible = dolGuiSettings_setToolBarVisible;
  iface->isToolBarVisible = dolGuiSettings_isToolBarVisible;
  iface->setWidgetsLocked = dolGuiSettings_setWidgetsLocked;
  iface->areWidgetsLocked = dolGuiSettings_areWidgetsLocked;
  iface->refreshWidgetVisibility = dolGuiSettings_refreshWidgetVisibility;
  // GameList
  iface->getPaths = dolGuiSettings_getPaths;
  iface->addPath = dolGuiSettings_addPath;
  iface->removePath = dolGuiSettings_removePath;
  iface->getPreferredView = dolGuiSettings_getPreferredView;
  iface->setPreferredView = dolGuiSettings_setPreferredView;
  iface->getDefaultGame = dolGuiSettings_getDefaultGame;
  iface->setDefaultGame = dolGuiSettings_setDefaultGame;
  iface->refreshGameList = dolGuiSettings_refreshGameList;
  iface->notifyRefreshGameListStarted = dolGuiSettings_notifyRefreshGameListStarted;
  iface->notifyRefreshGameListComplete = dolGuiSettings_notifyRefreshGameListComplete;
  iface->refreshMetadata = dolGuiSettings_refreshMetadata;
  iface->notifyMetadataRefreshComplete = dolGuiSettings_notifyMetadataRefreshComplete;
  iface->reloadTitleDB = dolGuiSettings_reloadTitleDB;
  iface->isAutoRefreshEnabled = dolGuiSettings_isAutoRefreshEnabled;
  iface->setAutoRefreshEnabled = dolGuiSettings_setAutoRefreshEnabled;
  // Emulation
  iface->getStateSlot = dolGuiSettings_getStateSlot;
  iface->setStateSlot = dolGuiSettings_setStateSlot;
  iface->isBatchModeEnabled = dolGuiSettings_isBatchModeEnabled;
  iface->setBatchModeEnabled = dolGuiSettings_setBatchModeEnabled;
  iface->isSDCardInserted = dolGuiSettings_isSDCardInserted;
  iface->setSDCardInserted = dolGuiSettings_setSDCardInserted;
  iface->isUSBKeyboardConnected = dolGuiSettings_isUSBKeyboardConnected;
  iface->setUSBKeyboardConnected = dolGuiSettings_setUSBKeyboardConnected;
  // Graphics
  iface->setCursorVisibility = dolGuiSettings_setCursorVisibility;
  iface->getCursorVisibility = dolGuiSettings_getCursorVisibility;
  iface->setLockCursor = dolGuiSettings_setLockCursor;
  iface->getLockCursor = dolGuiSettings_getLockCursor;
  iface->setKeepWindowOnTop = dolGuiSettings_setKeepWindowOnTop;
  iface->isKeepWindowOnTopEnabled = dolGuiSettings_isKeepWindowOnTopEnabled;
  iface->getGraphicModsEnabled = dolGuiSettings_getGraphicModsEnabled;
  iface->setGraphicModsEnabled = dolGuiSettings_setGraphicModsEnabled;
  // Audio
  iface->getVolume = dolGuiSettings_getVolume;
  iface->setVolume = dolGuiSettings_setVolume;
  iface->increaseVolume = dolGuiSettings_increaseVolume;
  iface->decreaseVolume = dolGuiSettings_decreaseVolume;
  // Cheats
  iface->getCheatsEnabled = dolGuiSettings_getCheatsEnabled;
  iface->setCheatsEnabled = dolGuiSettings_setCheatsEnabled;
  // Debug
  iface->setDebugModeEnabled = dolGuiSettings_setDebugModeEnabled;
  iface->isDebugModeEnabled = dolGuiSettings_isDebugModeEnabled;
  iface->setRegistersVisible = dolGuiSettings_setRegistersVisible;
  iface->isRegistersVisible = dolGuiSettings_isRegistersVisible;
  iface->setThreadsVisible = dolGuiSettings_setThreadsVisible;
  iface->isThreadsVisible = dolGuiSettings_isThreadsVisible;
  iface->setWatchVisible = dolGuiSettings_setWatchVisible;
  iface->isWatchVisible = dolGuiSettings_isWatchVisible;
  iface->setBreakpointsVisible = dolGuiSettings_setBreakpointsVisible;
  iface->isBreakpointsVisible = dolGuiSettings_isBreakpointsVisible;
  iface->setCodeVisible = dolGuiSettings_setCodeVisible;
  iface->isCodeVisible = dolGuiSettings_isCodeVisible;
  iface->setMemoryVisible = dolGuiSettings_setMemoryVisible;
  iface->isMemoryVisible = dolGuiSettings_isMemoryVisible;
  iface->setNetworkVisible = dolGuiSettings_setNetworkVisible;
  iface->isNetworkVisible = dolGuiSettings_isNetworkVisible;
  iface->setJITVisible = dolGuiSettings_setJITVisible;
  iface->isJITVisible = dolGuiSettings_isJITVisible;
  // Auto-Update
  iface->getAutoUpdateTrack = dolGuiSettings_getAutoUpdateTrack;
  iface->setAutoUpdateTrack = dolGuiSettings_setAutoUpdateTrack;
  // Fallback Region
  iface->getFallbackRegion = dolGuiSettings_getFallbackRegion;
  iface->setFallbackRegion = dolGuiSettings_setFallbackRegion;
  // Analytics
  iface->isAnalyticsEnabled = dolGuiSettings_isAnalyticsEnabled;
  iface->setAnalyticsEnabled = dolGuiSettings_setAnalyticsEnabled;

  return iface;
}
