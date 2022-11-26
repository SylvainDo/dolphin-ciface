#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/State.h"

#include "Core/State.h"

#include <cstring>

static void dol_State_enableCompression(bool compression)
{
  State::EnableCompression(compression);
}

static void dol_State_save(int slot, bool wait)
{
  State::Save(slot, wait);
}

static void dol_State_load(int slot)
{
  State::Load(slot);
}

static void dol_State_saveAs(const char* filename, bool wait)
{
  State::SaveAs(filename, wait);
}

static void dol_State_loadAs(const char* filename)
{
  State::LoadAs(filename);
}

static void dol_State_saveToBuffer(uint8_t** buffer, size_t* size)
{
  std::vector<u8> buf;
  State::SaveToBuffer(buf);
  *buffer = static_cast<uint8_t*>(interop_malloc(buf.size()));
  memcpy(*buffer, buf.data(), buf.size());
  *size = buf.size();
}

static void dol_State_loadFromBuffer(uint8_t* buffer, size_t size)
{
  std::vector<u8> buf(size);
  memcpy(buf.data(), buffer, size);
  State::LoadFromBuffer(buf);
}

EXPORT dol_State* dol_State_newInterface()
{
  auto iface = static_cast<dol_State*>(interop_calloc(1, sizeof(dol_State)));
  iface->enableCompression = dol_State_enableCompression;
  iface->save = dol_State_save;
  iface->load = dol_State_load;
  iface->saveAs = dol_State_saveAs;
  iface->loadAs = dol_State_loadAs;
  iface->saveToBuffer = dol_State_saveToBuffer;
  iface->loadFromBuffer = dol_State_loadFromBuffer;

  return iface;
}
