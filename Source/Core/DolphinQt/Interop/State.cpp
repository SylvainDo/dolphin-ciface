#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/State.h"

#include "Core/State.h"

static void dolState_enableCompression(bool compression)
{
  State::EnableCompression(compression);
}

static bool dolState_readHeader(const char* filename, dolState_StateHeader* header)
{
  return State::ReadHeader(filename, *reinterpret_cast<State::StateHeader*>(header));
}

static char* dolState_getInfoStringOfSlot(int slot, bool translate)
{
  return InteropUtil::dupStdString(State::GetInfoStringOfSlot(slot, translate));
}

static uint64_t dolState_getUnixTimeOfSlot(int slot)
{
  return State::GetUnixTimeOfSlot(slot);
}

static void dolState_save(int slot, bool wait)
{
  State::Save(slot, wait);
}

static void dolState_load(int slot)
{
  State::Load(slot);
}

static void dolState_saveAs(const char* filename, bool wait)
{
  State::SaveAs(filename, wait);
}

static void dolState_loadAs(const char* filename)
{
  State::LoadAs(filename);
}

static void dolState_saveToBuffer(uint8_t** buffer, size_t* size)
{
  std::vector<u8> buf;
  State::SaveToBuffer(buf);
  *buffer = static_cast<uint8_t*>(interop_malloc(buf.size()));
  memcpy(*buffer, buf.data(), buf.size());
  *size = buf.size();
}

static void dolState_loadFromBuffer(uint8_t* buffer, size_t size)
{
  std::vector<u8> buf(size);
  memcpy(buf.data(), buffer, size);
  State::LoadFromBuffer(buf);
}

static void dolState_loadLastSaved(int i)
{
  State::LoadLastSaved(i);
}

static void dolState_saveFirstSaved()
{
  State::SaveFirstSaved();
}

static void dolState_undoSaveState()
{
  State::UndoSaveState();
}

static void dolState_undoLoadState()
{
  State::UndoLoadState();
}

EXPORT dolState* dolState_newInterface()
{
  auto iface = static_cast<dolState*>(interop_calloc(1, sizeof(dolState)));
  iface->enableCompression = dolState_enableCompression;
  iface->readHeader = dolState_readHeader;
  iface->getInfoStringOfSlot = dolState_getInfoStringOfSlot;
  iface->getUnixTimeOfSlot = dolState_getUnixTimeOfSlot;
  iface->save = dolState_save;
  iface->load = dolState_load;
  iface->saveAs = dolState_saveAs;
  iface->loadAs = dolState_loadAs;
  iface->saveToBuffer = dolState_saveToBuffer;
  iface->loadFromBuffer = dolState_loadFromBuffer;
  iface->loadLastSaved = dolState_loadLastSaved;
  iface->saveFirstSaved = dolState_saveFirstSaved;
  iface->undoSaveState = dolState_undoSaveState;
  iface->undoLoadState = dolState_undoLoadState;

  return iface;
}
