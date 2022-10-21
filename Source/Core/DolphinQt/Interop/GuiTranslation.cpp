#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/GuiTranslation.h"

#include "DolphinQt/Translation.h"

static void dolGuiTranslation_initialize()
{
  Translation::Initialize();
}

EXPORT dolGuiTranslation* dolGuiTranslation_newInterface()
{
  auto iface = static_cast<dolGuiTranslation*>(interop_calloc(1, sizeof(dolGuiTranslation)));
  iface->initialize = dolGuiTranslation_initialize;

  return iface;
}
