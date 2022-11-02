#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_Core_TitleDatabase
{
  void* data;
  void* (*getUnderlyingInstance)(dol_Core_TitleDatabase* _this);
  char* (*getTitleName)(dol_Core_TitleDatabase* _this, const char* gametdb_id,
                        dol_DiscIO_Language language);
  char* (*getChannelName)(dol_Core_TitleDatabase* _this, uint64_t title_id,
                          dol_DiscIO_Language language);
  char* (*describe)(dol_Core_TitleDatabase* _this, const char* gametdb_id,
                    dol_DiscIO_Language language);
};

struct dol_Core_TitleDatabase_Factory
{
  dol_Core_TitleDatabase* (*create)(void);
  void (*destroy)(dol_Core_TitleDatabase* _this);
};

typedef dol_Core_TitleDatabase_Factory* (*dol_Core_TitleDatabase_Factory_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
