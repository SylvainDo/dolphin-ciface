#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/DolphinAnalytics.h"

#include "Core/DolphinAnalytics.h"

static void dolDolphinAnalytics_reloadConfig()
{
  DolphinAnalytics::Instance().ReloadConfig();
}

static void dolDolphinAnalytics_generateNewIdentity()
{
  DolphinAnalytics::Instance().GenerateNewIdentity();
}

EXPORT dolDolphinAnalytics* dolDolphinAnalytics_newInterface()
{
  auto iface = static_cast<dolDolphinAnalytics*>(interop_calloc(1, sizeof(dolDolphinAnalytics)));
  iface->reloadConfig = dolDolphinAnalytics_reloadConfig;
  iface->generateNewIdentity = dolDolphinAnalytics_generateNewIdentity;

  return iface;
}
