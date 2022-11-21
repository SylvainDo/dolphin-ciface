#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_UICommon
{
  void (*init)(void);
  void (*shutdown)(void);
  void (*createDirectories)(void);
  void (*setUserDirectory)(const char* custom_path);
  char* (*formatSize)(uint64_t bytes, int decimals);
};

typedef dol_UICommon* (*dol_UICommon_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
