#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_MainWindow
{
  void (*init)(void);
  void (*shutdown)(void);
  void (*show)(void);
  bool (*requestStop)(void);
  void (*startGame1)(const char* path);
  void (*setResetCallback)(void (*callback)(void* userdata), void* userdata);
  void (*setEmulationStateChangedCallback)(void (*callback)(dol_Core_State state, void* userdata),
                                           void* userdata);
};

typedef dol_Gui_MainWindow* (*dol_Gui_MainWindow_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
