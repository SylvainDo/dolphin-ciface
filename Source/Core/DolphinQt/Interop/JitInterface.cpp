#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/JitInterface.h"

#include "Core/PowerPC/JitInterface.h"

static void dolJitInterface_clearCache()
{
  JitInterface::ClearCache();
}

static void dolJitInterface_clearSafe()
{
  JitInterface::ClearSafe();
}

static void dolJitInterface_invalidateICache(uint32_t address, uint32_t size, bool forced)
{
  JitInterface::InvalidateICache(address, size, forced);
}

static void dolJitInterface_invalidateICacheLine(uint32_t address)
{
  JitInterface::InvalidateICacheLine(address);
}

static void dolJitInterface_invalidateICacheLines(uint32_t address, uint32_t count)
{
  JitInterface::InvalidateICacheLines(address, count);
}

EXPORT dolJitInterface* dolJitInterface_newInterface()
{
  auto iface = static_cast<dolJitInterface*>(interop_calloc(1, sizeof(dolJitInterface)));
  iface->clearCache = dolJitInterface_clearCache;
  iface->clearSafe = dolJitInterface_clearSafe;
  iface->invalidateICache = dolJitInterface_invalidateICache;
  iface->invalidateICacheLine = dolJitInterface_invalidateICacheLine;
  iface->invalidateICacheLines = dolJitInterface_invalidateICacheLines;

  return iface;
}
