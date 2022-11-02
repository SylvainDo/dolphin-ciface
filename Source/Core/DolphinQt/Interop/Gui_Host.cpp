#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Host.h"

#include "DolphinQt/Host.h"

static void dol_Gui_Host_deleteLater()
{
  Host::GetInstance()->deleteLater();
}

static void dol_Gui_Host_declareAsHostThread()
{
  Host::GetInstance()->DeclareAsHostThread();
}

static bool dol_Gui_Host_isHostThread()
{
  return Host::GetInstance()->IsHostThread();
}

EXPORT dol_Gui_Host* dol_Gui_Host_newInterface()
{
  auto iface = static_cast<dol_Gui_Host*>(interop_calloc(1, sizeof(dol_Gui_Host)));
  iface->deleteLater = dol_Gui_Host_deleteLater;
  iface->declareAsHostThread = dol_Gui_Host_declareAsHostThread;
  iface->isHostThread = dol_Gui_Host_isHostThread;

  return iface;
}
