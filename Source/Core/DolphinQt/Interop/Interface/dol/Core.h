#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dolCore
{
  bool (*getIsThrottlerTempDisabled)(void);
  void (*setIsThrottlerTempDisabled)(bool disable);
  double (*getActualEmulationSpeed)(void);
  void (*stop)(void);
  void (*shutdown)(void);
  void (*declareAsCPUThread)(void);
  void (*undeclareAsCPUThread)(void);
  void (*declareAsGPUThread)(void);
  void (*undeclareAsGPUThread)(void);
  bool (*isRunning)(void);
  bool (*isRunningAndStarted)(void);
  bool (*isRunningInCurrentThread)(void);
  bool (*isCPUThread)(void);
  bool (*isGPUThread)(void);
  bool (*wantsDeterminism)(void);
  void (*setState)(dolCoreState state);
  dolCoreState (*getState)(void);
  void (*saveScreenShot1)(void);
  void (*saveScreenShot2)(const char* name);
  void (*displayMessage)(const char* message, int time_in_ms);
  void (*runAsCPUThread)(void (*function)(void* userdata), void* userdata);
  void (*runOnCPUThread)(void (*function)(void* userdata), void* userdata,
                         bool wait_for_completion);
  int (*addOnStateChangedCallback)(void (*callback)(dolCoreState state, void* userdata),
                                   void* userdata);
  bool (*removeOnStateChangedCallback)(int* handle);
  void (*updateWantDeterminism)(bool initial);
  void (*queueHostJob)(void (*job)(void* userdata), void* userdata, bool run_during_stop);
  void (*hostDispatchJobs)(void);
  void (*doFrameStep)(void);
  void (*updateInputGate)(bool require_focus, bool require_full_focus);
};

typedef dolCore* (*dolCore_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
