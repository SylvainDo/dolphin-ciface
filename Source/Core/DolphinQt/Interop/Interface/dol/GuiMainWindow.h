#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolGuiMainWindow
{
  void (*init)(void);
  void (*shutdown)(void);
  void (*show)(void);
  bool (*requestStop)(void);
  void (*startGame1)(const char* path);
};

typedef dolGuiMainWindow* (*dolGuiMainWindow_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
