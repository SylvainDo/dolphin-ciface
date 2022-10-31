#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/AddressSpaceAccessors.h"

#include "Core/HW/AddressSpace.h"

static AddressSpace::Accessors* _instance;

static void dolAddressSpaceAccessors_setCurrent(dolAddressSpaceType address_space)
{
  _instance = AddressSpace::GetAccessors(static_cast<AddressSpace::Type>(address_space));
}

static bool dolAddressSpaceAccessors_isValidAddress(uint32_t address)
{
  return _instance->IsValidAddress(address);
}

static uint8_t dolAddressSpaceAccessors_readU8(uint32_t address)
{
  return _instance->ReadU8(address);
}

static void dolAddressSpaceAccessors_writeU8(uint32_t address, uint8_t value)
{
  _instance->WriteU8(address, value);
}

static uint16_t dolAddressSpaceAccessors_readU16(uint32_t address)
{
  return _instance->ReadU16(address);
}

static void dolAddressSpaceAccessors_writeU16(uint32_t address, uint16_t value)
{
  _instance->WriteU16(address, value);
}

static uint32_t dolAddressSpaceAccessors_readU32(uint32_t address)
{
  return _instance->ReadU32(address);
}

static void dolAddressSpaceAccessors_writeU32(uint32_t address, uint32_t value)
{
  _instance->WriteU32(address, value);
}

static uint64_t dolAddressSpaceAccessors_readU64(uint32_t address)
{
  return _instance->ReadU64(address);
}

static void dolAddressSpaceAccessors_writeU64(uint32_t address, uint64_t value)
{
  _instance->WriteU64(address, value);
}

static float dolAddressSpaceAccessors_readF32(uint32_t address)
{
  return _instance->ReadF32(address);
}

static const uint8_t* dolAddressSpaceAccessors_begin()
{
  return _instance->begin();
}

static const uint8_t* dolAddressSpaceAccessors_end()
{
  return _instance->end();
}

static bool dolAddressSpaceAccessors_search(uint32_t haystack_offset, const uint8_t* needle_start,
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

EXPORT dolAddressSpaceAccessors* dolAddressSpaceAccessors_newInterface()
{
  auto iface =
      static_cast<dolAddressSpaceAccessors*>(interop_calloc(1, sizeof(dolAddressSpaceAccessors)));
  iface->setCurrent = dolAddressSpaceAccessors_setCurrent;
  iface->isValidAddress = dolAddressSpaceAccessors_isValidAddress;
  iface->readU8 = dolAddressSpaceAccessors_readU8;
  iface->writeU8 = dolAddressSpaceAccessors_writeU8;
  iface->readU16 = dolAddressSpaceAccessors_readU16;
  iface->writeU16 = dolAddressSpaceAccessors_writeU16;
  iface->readU32 = dolAddressSpaceAccessors_readU32;
  iface->writeU32 = dolAddressSpaceAccessors_writeU32;
  iface->readU64 = dolAddressSpaceAccessors_readU64;
  iface->writeU64 = dolAddressSpaceAccessors_writeU64;
  iface->readF32 = dolAddressSpaceAccessors_readF32;
  iface->begin = dolAddressSpaceAccessors_begin;
  iface->end = dolAddressSpaceAccessors_end;
  iface->search = dolAddressSpaceAccessors_search;

  return iface;
}
