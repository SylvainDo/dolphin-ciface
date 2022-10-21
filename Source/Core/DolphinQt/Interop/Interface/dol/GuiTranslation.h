#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolGuiTranslation
{
  void (*initialize)(void);
};

typedef dolGuiTranslation* (*dolGuiTranslation_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
