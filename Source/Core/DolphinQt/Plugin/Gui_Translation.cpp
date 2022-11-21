#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Translation.h"

#include "DolphinQt/Translation.h"

static void dol_Gui_Translation_initialize()
{
  Translation::Initialize();
}

EXPORT dol_Gui_Translation* dol_Gui_Translation_newInterface()
{
  auto iface = static_cast<dol_Gui_Translation*>(interop_calloc(1, sizeof(dol_Gui_Translation)));
  iface->initialize = dol_Gui_Translation_initialize;

  return iface;
}
