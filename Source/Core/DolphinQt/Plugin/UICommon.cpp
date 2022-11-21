#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/UICommon.h"

#include "UICommon/UICommon.h"

static void dol_UICommon_init()
{
  UICommon::Init();
}

static void dol_UICommon_shutdown()
{
  UICommon::Shutdown();
}

static void dol_UICommon_createDirectories()
{
  UICommon::CreateDirectories();
}

static void dol_UICommon_setUserDirectory(const char* custom_path)
{
  UICommon::SetUserDirectory(custom_path);
}

static char* dol_UICommon_formatSize(uint64_t bytes, int decimals)
{
  return InteropUtil::dupStdString(UICommon::FormatSize(bytes, decimals));
}

EXPORT dol_UICommon* dol_UICommon_newInterface()
{
  auto iface = static_cast<dol_UICommon*>(interop_calloc(1, sizeof(dol_UICommon)));
  iface->init = dol_UICommon_init;
  iface->shutdown = dol_UICommon_shutdown;
  iface->createDirectories = dol_UICommon_createDirectories;
  iface->setUserDirectory = dol_UICommon_setUserDirectory;
  iface->formatSize = dol_UICommon_formatSize;

  return iface;
}
