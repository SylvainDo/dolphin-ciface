#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef double dolControlState;

struct dolGCPadStatus
{
  uint16_t button;
  uint8_t stickX;
  uint8_t stickY;
  uint8_t substickX;
  uint8_t substickY;
  uint8_t triggerLeft;
  uint8_t triggerRight;
  uint8_t analogA;
  uint8_t analogB;
  bool isConnected;
};

struct dolPad
{
  bool (*isInitialized)(void);
  dolGCPadStatus (*getStatus)(int pad_num);
  void (*rumble)(int pad_num, dolControlState strength);
  void (*resetRumble)(int pad_num);
  bool (*getMicButton)(int pad_num);
};

typedef dolPad* (*dolPad_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
