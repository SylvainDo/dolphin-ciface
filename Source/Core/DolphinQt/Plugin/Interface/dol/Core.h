#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Core
{
  double (*getActualEmulationSpeed)(void);
  void (*shutdown)(void);
  bool (*isRunning)(void);
  bool (*isRunningAndStarted)(void);
  void (*setState)(dol_Core_State state);
  dol_Core_State (*getState)(void);
  void (*saveScreenShot1)(void);
  void (*saveScreenShot2)(const char* name);
  void (*saveScreenShotAs)(const char* filename);
  void (*displayMessage)(const char* message, int time_in_ms);
  void (*hostDispatchJobs)(void);
  void (*doFrameStep)(void);
  void (*setFrameHandlerEnabled)(bool enabled);
  bool (*getFrameHandlerToken)(void);
  void (*setFrameHandlerToken)(bool token);
};

typedef dol_Core* (*dol_Core_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
