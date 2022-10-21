#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolGuiResources
{
  void (*init)(void);
};

typedef dolGuiResources* (*dolGuiResources_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
