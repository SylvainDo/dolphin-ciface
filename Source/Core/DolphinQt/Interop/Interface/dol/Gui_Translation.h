#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_Translation
{
  void (*initialize)(void);
};

typedef dol_Gui_Translation* (*dol_Gui_Translation_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
