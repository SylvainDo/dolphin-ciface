#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef void* (*dol_malloc_t)(size_t);
typedef void* (*dol_calloc_t)(size_t, size_t);
typedef void (*dol_free_t)(void*);

typedef void (*dol_setMalloc_t)(dol_malloc_t f);
typedef void (*dol_setCalloc_t)(dol_calloc_t f);
typedef void (*dol_setFree_t)(dol_free_t f);

#ifdef __cplusplus
}
#endif
