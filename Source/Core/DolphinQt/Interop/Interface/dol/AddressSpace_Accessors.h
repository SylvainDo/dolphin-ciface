#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_AddressSpace_Accessors
{
  bool (*isValidAddress)(dol_AddressSpace_Type address_space, uint32_t address);
  uint8_t (*readU8)(dol_AddressSpace_Type address_space, uint32_t address);
  void (*writeU8)(dol_AddressSpace_Type address_space, uint32_t address, uint8_t value);
  uint16_t (*readU16)(dol_AddressSpace_Type address_space, uint32_t address);
  void (*writeU16)(dol_AddressSpace_Type address_space, uint32_t address, uint16_t value);
  uint32_t (*readU32)(dol_AddressSpace_Type address_space, uint32_t address);
  void (*writeU32)(dol_AddressSpace_Type address_space, uint32_t address, uint32_t value);
  uint64_t (*readU64)(dol_AddressSpace_Type address_space, uint32_t address);
  void (*writeU64)(dol_AddressSpace_Type address_space, uint32_t address, uint64_t value);
  float (*readF32)(dol_AddressSpace_Type address_space, uint32_t address);
  const uint8_t* (*begin)(dol_AddressSpace_Type address_space);
  const uint8_t* (*end)(dol_AddressSpace_Type address_space);
  bool (*search)(dol_AddressSpace_Type address_space, uint32_t haystack_offset,
                 const uint8_t* needle_start, size_t needle_size, bool forward, uint32_t* result);
};

typedef dol_AddressSpace_Accessors* (*dol_AddressSpace_Accessors_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
