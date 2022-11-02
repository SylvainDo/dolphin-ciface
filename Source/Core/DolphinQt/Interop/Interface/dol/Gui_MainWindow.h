#pragma once

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
};

typedef dol_Gui_MainWindow* (*dol_Gui_MainWindow_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
