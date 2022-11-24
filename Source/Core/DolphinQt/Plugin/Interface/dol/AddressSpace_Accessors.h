#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_AddressSpace_Accessors
{
  bool (*isValidAddress)(dol_AddressSpace_Type address_space, uint32_t address);
  const uint8_t* (*begin)(dol_AddressSpace_Type address_space);
  const uint8_t* (*end)(dol_AddressSpace_Type address_space);
  bool (*search)(dol_AddressSpace_Type address_space, uint32_t haystack_offset,
                 const uint8_t* needle_start, size_t needle_size, bool forward, uint32_t* result);
};

typedef dol_AddressSpace_Accessors* (*dol_AddressSpace_Accessors_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
