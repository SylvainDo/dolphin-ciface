#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/DolphinAnalytics.h"

#include "Core/DolphinAnalytics.h"

static void dol_DolphinAnalytics_reloadConfig()
{
  DolphinAnalytics::Instance().ReloadConfig();
}

EXPORT dol_DolphinAnalytics* dol_DolphinAnalytics_newInterface()
{
  auto iface = static_cast<dol_DolphinAnalytics*>(interop_calloc(1, sizeof(dol_DolphinAnalytics)));
  iface->reloadConfig = dol_DolphinAnalytics_reloadConfig;

  return iface;
}
