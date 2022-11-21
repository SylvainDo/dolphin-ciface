#include "Export.h"

#include "Interface/dol/Alloc.h"
dol_malloc_t interop_malloc;
dol_calloc_t interop_calloc;
dol_free_t interop_free;

EXPORT void dol_setMalloc(dol_malloc_t f)
{
  interop_malloc = f;
}

EXPORT void dol_setCalloc(dol_calloc_t f)
{
  interop_calloc = f;
}

EXPORT void dol_setFree(dol_free_t f)
{
  interop_free = f;
}
