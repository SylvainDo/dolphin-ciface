#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/GuiResources.h"

#include "DolphinQt/Resources.h"

static void dolGuiResources_init()
{
  Resources::Init();
}

EXPORT dolGuiResources* dolGuiResources_newInterface()
{
  auto iface = static_cast<dolGuiResources*>(interop_calloc(1, sizeof(dolGuiResources)));
  iface->init = dolGuiResources_init;

  return iface;
}
