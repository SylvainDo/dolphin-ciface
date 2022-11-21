#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Resources.h"

#include "DolphinQt/Resources.h"

static void dol_Gui_Resources_init()
{
  Resources::Init();
}

EXPORT dol_Gui_Resources* dol_Gui_Resources_newInterface()
{
  auto iface = static_cast<dol_Gui_Resources*>(interop_calloc(1, sizeof(dol_Gui_Resources)));
  iface->init = dol_Gui_Resources_init;

  return iface;
}
