#pragma once

#include "UICommon_GameFile.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Util
{
  bool (*verifyDisc)(dol_UICommon_GameFile* game, uint8_t* sha1, bool* goodDump);
  bool (*extractDisc)(dol_UICommon_GameFile* game, const char* path);
};

typedef dol_Util* (*dol_Util_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
