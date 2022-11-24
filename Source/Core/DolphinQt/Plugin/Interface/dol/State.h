#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_State
{
  void (*enableCompression)(bool compression);
  void (*save)(int slot, bool wait);
  void (*load)(int slot);
  void (*saveAs)(const char* filename, bool wait);
  void (*loadAs)(const char* filename);
  void (*saveToBuffer)(uint8_t** buffer, size_t* size);
  void (*loadFromBuffer)(uint8_t* buffer, size_t size);
};

typedef dol_State* (*dol_State_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
