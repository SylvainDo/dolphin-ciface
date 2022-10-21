#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolDolphinAnalytics
{
  void (*reloadConfig)(void);
  void (*generateNewIdentity)(void);
};

typedef dolDolphinAnalytics* (*dolDolphinAnalytics_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
