#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef double dol_ControlState;

struct dol_GCPadStatus
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

struct dol_Pad
{
  bool (*isInitialized)(void);
  dol_GCPadStatus (*getStatus)(int pad_num);
  void (*rumble)(int pad_num, dol_ControlState strength);
  void (*resetRumble)(int pad_num);
  bool (*getMicButton)(int pad_num);
};

typedef dol_Pad* (*dol_Pad_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
