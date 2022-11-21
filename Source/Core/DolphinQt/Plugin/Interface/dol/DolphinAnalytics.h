#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_DolphinAnalytics
{
  void (*reloadConfig)(void);
  void (*generateNewIdentity)(void);
};

typedef dol_DolphinAnalytics* (*dol_DolphinAnalytics_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
