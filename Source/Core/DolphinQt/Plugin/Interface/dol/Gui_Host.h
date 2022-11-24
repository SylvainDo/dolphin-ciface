#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_Host
{
  void (*deleteLater)(void);
  void (*declareAsHostThread)(void);
};

typedef dol_Gui_Host* (*dol_Gui_Host_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
