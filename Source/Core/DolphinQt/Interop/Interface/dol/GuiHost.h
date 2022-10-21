#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolGuiHost
{
  void (*deleteLater)(void);
  void (*declareAsHostThread)(void);
  bool (*isHostThread)(void);
};

typedef dolGuiHost* (*dolGuiHost_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
