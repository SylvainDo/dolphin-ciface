#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dolUICommon
{
  void (*init)(void);
  void (*shutdown)(void);
  void (*setLocale)(const char* locale_name);
  void (*createDirectories)(void);
  void (*setUserDirectory)(const char* custom_path);
  bool (*triggerSTMPowerEvent)(void);
  char* (*formatSize)(uint64_t bytes, int decimals);
};

typedef dolUICommon* (*dolUICommon_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
