#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/GuiHost.h"

#include "DolphinQt/Host.h"

static void dolGuiHost_deleteLater()
{
  Host::GetInstance()->deleteLater();
}

static void dolGuiHost_declareAsHostThread()
{
  Host::GetInstance()->DeclareAsHostThread();
}

static bool dolGuiHost_isHostThread()
{
  return Host::GetInstance()->IsHostThread();
}

EXPORT dolGuiHost* dolGuiHost_newInterface()
{
  auto iface = static_cast<dolGuiHost*>(interop_calloc(1, sizeof(dolGuiHost)));
  iface->deleteLater = dolGuiHost_deleteLater;
  iface->declareAsHostThread = dolGuiHost_declareAsHostThread;
  iface->isHostThread = dolGuiHost_isHostThread;

  return iface;
}
