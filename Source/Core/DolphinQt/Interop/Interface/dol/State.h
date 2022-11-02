#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dol_State_StateHeader
{
  char gameID[6];
  uint16_t reserved1;
  uint32_t size;
  uint32_t reserved2;
  double time;
};

struct dol_State
{
  void (*enableCompression)(bool compression);
  bool (*readHeader)(const char* filename, dol_State_StateHeader* header);
  char* (*getInfoStringOfSlot)(int slot, bool translate);
  uint64_t (*getUnixTimeOfSlot)(int slot);
  void (*save)(int slot, bool wait);
  void (*load)(int slot);
  void (*saveAs)(const char* filename, bool wait);
  void (*loadAs)(const char* filename);
  void (*saveToBuffer)(uint8_t** buffer, size_t* size);
  void (*loadFromBuffer)(uint8_t* buffer, size_t size);
  void (*loadLastSaved)(int i);
  void (*saveFirstSaved)(void);
  void (*undoSaveState)(void);
  void (*undoLoadState)(void);
};

typedef dol_State* (*dol_State_newInterface_t)(void);

#ifdef __cplusplus
}

#include <cstddef>

constexpr size_t DOL_STATE_HEADER_SIZE = sizeof(dol_State_StateHeader);
static_assert(DOL_STATE_HEADER_SIZE == 24);
static_assert(offsetof(dol_State_StateHeader, size) == 8);
static_assert(offsetof(dol_State_StateHeader, time) == 16);

#endif
