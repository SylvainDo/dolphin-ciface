#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/AddressSpace_Accessors.h"

#include "Core/HW/AddressSpace.h"

inline AddressSpace::Accessors* Get(dol_AddressSpace_Type address_space)
{
  return AddressSpace::GetAccessors(static_cast<AddressSpace::Type>(address_space));
}

static bool dol_AddressSpace_Accessors_isValidAddress(dol_AddressSpace_Type address_space,
                                                      uint32_t address)
{
  return Get(address_space)->IsValidAddress(address);
}

static const uint8_t* dol_AddressSpace_Accessors_begin(dol_AddressSpace_Type address_space)
{
  return Get(address_space)->begin();
}

static const uint8_t* dol_AddressSpace_Accessors_end(dol_AddressSpace_Type address_space)
{
  return Get(address_space)->end();
}

static bool dol_AddressSpace_Accessors_search(dol_AddressSpace_Type address_space,
                                              uint32_t haystack_offset, const uint8_t* needle_start,
                                              size_t needle_size, bool forward, uint32_t* result)
{
  auto opt = Get(address_space)->Search(haystack_offset, needle_start, needle_size, forward);
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
  iface->isValidAddress = dol_AddressSpace_Accessors_isValidAddress;
  iface->begin = dol_AddressSpace_Accessors_begin;
  iface->end = dol_AddressSpace_Accessors_end;
  iface->search = dol_AddressSpace_Accessors_search;

  return iface;
}
