#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/JitInterface.h"

#include "Core/PowerPC/JitInterface.h"

static void dol_JitInterface_clearCache()
{
  JitInterface::ClearCache();
}

static void dol_JitInterface_invalidateICache(uint32_t address, uint32_t size, bool forced)
{
  JitInterface::InvalidateICache(address, size, forced);
}

static void dol_JitInterface_invalidateICacheLines(uint32_t address, uint32_t count)
{
  JitInterface::InvalidateICacheLines(address, count);
}

EXPORT dol_JitInterface* dol_JitInterface_newInterface()
{
  auto iface = static_cast<dol_JitInterface*>(interop_calloc(1, sizeof(dol_JitInterface)));
  iface->clearCache = dol_JitInterface_clearCache;
  iface->invalidateICache = dol_JitInterface_invalidateICache;
  iface->invalidateICacheLines = dol_JitInterface_invalidateICacheLines;

  return iface;
}
