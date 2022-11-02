#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/AddressSpace_Accessors.h"

#include "Core/HW/AddressSpace.h"

static AddressSpace::Accessors* _instance;

static void dol_AddressSpace_Accessors_setCurrent(dol_AddressSpace_Type address_space)
{
  _instance = AddressSpace::GetAccessors(static_cast<AddressSpace::Type>(address_space));
}

static bool dol_AddressSpace_Accessors_isValidAddress(uint32_t address)
{
  return _instance->IsValidAddress(address);
}

static uint8_t dol_AddressSpace_Accessors_readU8(uint32_t address)
{
  return _instance->ReadU8(address);
}

static void dol_AddressSpace_Accessors_writeU8(uint32_t address, uint8_t value)
{
  _instance->WriteU8(address, value);
}

static uint16_t dol_AddressSpace_Accessors_readU16(uint32_t address)
{
  return _instance->ReadU16(address);
}

static void dol_AddressSpace_Accessors_writeU16(uint32_t address, uint16_t value)
{
  _instance->WriteU16(address, value);
}

static uint32_t dol_AddressSpace_Accessors_readU32(uint32_t address)
{
  return _instance->ReadU32(address);
}

static void dol_AddressSpace_Accessors_writeU32(uint32_t address, uint32_t value)
{
  _instance->WriteU32(address, value);
}

static uint64_t dol_AddressSpace_Accessors_readU64(uint32_t address)
{
  return _instance->ReadU64(address);
}

static void dol_AddressSpace_Accessors_writeU64(uint32_t address, uint64_t value)
{
  _instance->WriteU64(address, value);
}

static float dol_AddressSpace_Accessors_readF32(uint32_t address)
{
  return _instance->ReadF32(address);
}

static const uint8_t* dol_AddressSpace_Accessors_begin()
{
  return _instance->begin();
}

static const uint8_t* dol_AddressSpace_Accessors_end()
{
  return _instance->end();
}

static bool dol_AddressSpace_Accessors_search(uint32_t haystack_offset, const uint8_t* needle_start,
                                              size_t needle_size, bool forward, uint32_t* result)
{
  auto opt = _instance->Search(haystack_offset, needle_start, needle_size, forward);
  if (opt.has_value())
  {
    *result = opt.value();
    return true;
  }
  return false;
}

EXPORT dol_AddressSpace_Accessors* dol_AddressSpace_Accessors_newInterface()
{
  auto iface = static_cast<dol_AddressSpace_Accessors*>(
      interop_calloc(1, sizeof(dol_AddressSpace_Accessors)));
  iface->setCurrent = dol_AddressSpace_Accessors_setCurrent;
  iface->isValidAddress = dol_AddressSpace_Accessors_isValidAddress;
  iface->readU8 = dol_AddressSpace_Accessors_readU8;
  iface->writeU8 = dol_AddressSpace_Accessors_writeU8;
  iface->readU16 = dol_AddressSpace_Accessors_readU16;
  iface->writeU16 = dol_AddressSpace_Accessors_writeU16;
  iface->readU32 = dol_AddressSpace_Accessors_readU32;
  iface->writeU32 = dol_AddressSpace_Accessors_writeU32;
  iface->readU64 = dol_AddressSpace_Accessors_readU64;
  iface->writeU64 = dol_AddressSpace_Accessors_writeU64;
  iface->readF32 = dol_AddressSpace_Accessors_readF32;
  iface->begin = dol_AddressSpace_Accessors_begin;
  iface->end = dol_AddressSpace_Accessors_end;
  iface->search = dol_AddressSpace_Accessors_search;

  return iface;
}
