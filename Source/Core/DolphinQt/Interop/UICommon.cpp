#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/UICommon.h"

#include "UICommon/UICommon.h"

static void dolUICommon_init()
{
  UICommon::Init();
}

static void dolUICommon_shutdown()
{
  UICommon::Shutdown();
}

static void dolUICommon_setLocale(const char* locale_name)
{
  UICommon::SetLocale(locale_name);
}

static void dolUICommon_createDirectories()
{
  UICommon::CreateDirectories();
}

static void dolUICommon_setUserDirectory(const char* custom_path)
{
  UICommon::SetUserDirectory(custom_path);
}

static bool dolUICommon_triggerSTMPowerEvent()
{
  return UICommon::TriggerSTMPowerEvent();
}

static char* dolUICommon_formatSize(uint64_t bytes, int decimals)
{
  return InteropUtil::dupStdString(UICommon::FormatSize(bytes, decimals));
}

EXPORT dolUICommon* dolUICommon_newInterface()
{
  auto iface = static_cast<dolUICommon*>(interop_calloc(1, sizeof(dolUICommon)));
  iface->init = dolUICommon_init;
  iface->shutdown = dolUICommon_shutdown;
  iface->setLocale = dolUICommon_setLocale;
  iface->createDirectories = dolUICommon_createDirectories;
  iface->setUserDirectory = dolUICommon_setUserDirectory;
  iface->triggerSTMPowerEvent = dolUICommon_triggerSTMPowerEvent;
  iface->formatSize = dolUICommon_formatSize;

  return iface;
}
