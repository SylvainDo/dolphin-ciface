#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dolJitInterface
{
  void (*clearCache)(void);
  void (*clearSafe)(void);
  void (*invalidateICache)(uint32_t address, uint32_t size, bool forced);
  void (*invalidateICacheLine)(uint32_t address);
  void (*invalidateICacheLines)(uint32_t address, uint32_t count);
};

typedef dolJitInterface* (*dolJitInterface_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
