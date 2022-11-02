#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_Resources
{
  void (*init)(void);
};

typedef dol_Gui_Resources* (*dol_Gui_Resources_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
