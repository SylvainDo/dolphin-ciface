#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolCore
{
  double (*getActualEmulationSpeed)(void);
  void (*shutdown)(void);
  void (*displayMessage)(const char* message, int time_in_ms);
  void (*hostDispatchJobs)(void);
};

typedef dolCore* (*dolCore_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
