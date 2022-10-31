#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dolMemory
{
  uint8_t* (*getPhysicalBase)(void);
  uint8_t* (*getLogicalBase)(void);
  uint8_t* (*getPhysicalPageMappingsBase)(void);
  uint8_t* (*getLogicalPageMappingsBase)(void);
  uint8_t* (*getRAMPointer)(void);
  uint8_t* (*getEXRAMPointer)(void);
  uint8_t* (*getL1CachePointer)(void);
  uint8_t* (*getFakeVMEMPointer)(void);
  uint32_t (*getRamSizeReal)(void);
  uint32_t (*getRamSize)(void);
  uint32_t (*getRamMask)(void);
  uint32_t (*getFakeVMemSize)(void);
  uint32_t (*getFakeVMemMask)(void);
  uint32_t (*getL1CacheSize)(void);
  uint32_t (*getL1CacheMask)(void);
  uint32_t (*getExRamSizeReal)(void);
  uint32_t (*getExRamSize)(void);
  uint32_t (*getExRamMask)(void);
  bool (*isInitialized)(void);
  void (*clear)(void);
  char* (*getString)(uint32_t em_address, size_t size);
  uint8_t* (*getPointer)(uint32_t address);
  uint8_t* (*getPointerForRange)(uint32_t address, size_t size);
  void (*copyFromEmu)(void* data, uint32_t address, size_t size);
  void (*copyToEmu)(uint32_t address, const void* data, size_t size);
  void (*memset)(uint32_t address, uint8_t value, size_t size);
  uint8_t (*readU8)(uint32_t address);
  uint16_t (*readU16)(uint32_t address);
  uint32_t (*readU32)(uint32_t address);
  uint64_t (*readU64)(uint32_t address);
  void (*writeU8)(uint8_t var, uint32_t address);
  void (*writeU16)(uint16_t var, uint32_t address);
  void (*writeU32)(uint32_t var, uint32_t address);
  void (*writeU64)(uint64_t var, uint32_t address);
  void (*writeU32Swap)(uint32_t var, uint32_t address);
  void (*writeU64Swap)(uint64_t var, uint32_t address);
  void (*copyFromEmuU16Swap)(uint16_t* data, uint32_t address, size_t size);
  void (*copyToEmuU16Swap)(uint32_t address, const uint16_t* data, size_t size);
  void (*copyFromEmuU32Swap)(uint32_t* data, uint32_t address, size_t size);
  void (*copyToEmuU32Swap)(uint32_t address, const uint32_t* data, size_t size);
  void (*copyFromEmuU64Swap)(uint64_t* data, uint32_t address, size_t size);
  void (*copyToEmuU64Swap)(uint32_t address, const uint64_t* data, size_t size);
};

typedef dolMemory* (*dolMemory_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
