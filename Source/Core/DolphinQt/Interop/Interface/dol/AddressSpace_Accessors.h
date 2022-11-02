#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_AddressSpace_Accessors
{
  void (*setCurrent)(dol_AddressSpace_Type address_space);
  bool (*isValidAddress)(uint32_t address);
  uint8_t (*readU8)(uint32_t address);
  void (*writeU8)(uint32_t address, uint8_t value);
  uint16_t (*readU16)(uint32_t address);
  void (*writeU16)(uint32_t address, uint16_t value);
  uint32_t (*readU32)(uint32_t address);
  void (*writeU32)(uint32_t address, uint32_t value);
  uint64_t (*readU64)(uint32_t address);
  void (*writeU64)(uint32_t address, uint64_t value);
  float (*readF32)(uint32_t address);
  const uint8_t* (*begin)(void);
  const uint8_t* (*end)(void);
  bool (*search)(uint32_t haystack_offset, const uint8_t* needle_start, size_t needle_size,
                 bool forward, uint32_t* result);
};

typedef dol_AddressSpace_Accessors* (*dol_AddressSpace_Accessors_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
