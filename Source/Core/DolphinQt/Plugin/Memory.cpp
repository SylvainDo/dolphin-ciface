#include "Export.h"
#include "PluginUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Memory.h"

#include "Core/HW/Memmap.h"

static uint8_t* dol_Memory_getPhysicalBase()
{
  return Memory::physical_base;
}

static uint8_t* dol_Memory_getLogicalBase()
{
  return Memory::logical_base;
}

static uint8_t* dol_Memory_getPhysicalPageMappingsBase()
{
  return Memory::physical_page_mappings_base;
}

static uint8_t* dol_Memory_getLogicalPageMappingsBase()
{
  return Memory::logical_page_mappings_base;
}

static uint8_t* dol_Memory_getRAMPointer()
{
  return Memory::m_pRAM;
}

static uint8_t* dol_Memory_getEXRAMPointer()
{
  return Memory::m_pEXRAM;
}

static uint8_t* dol_Memory_getL1CachePointer()
{
  return Memory::m_pL1Cache;
}

static uint8_t* dol_Memory_getFakeVMEMPointer()
{
  return Memory::m_pFakeVMEM;
}

static uint32_t dol_Memory_getRamSizeReal()
{
  return Memory::GetRamSizeReal();
}

static uint32_t dol_Memory_getRamSize()
{
  return Memory::GetRamSize();
}

static uint32_t dol_Memory_getRamMask()
{
  return Memory::GetRamMask();
}

static uint32_t dol_Memory_getFakeVMemSize()
{
  return Memory::GetFakeVMemSize();
}

static uint32_t dol_Memory_getFakeVMemMask()
{
  return Memory::GetFakeVMemMask();
}

static uint32_t dol_Memory_getL1CacheSize()
{
  return Memory::GetL1CacheSize();
}

static uint32_t dol_Memory_getL1CacheMask()
{
  return Memory::GetL1CacheMask();
}

static uint32_t dol_Memory_getExRamSizeReal()
{
  return Memory::GetExRamSizeReal();
}

static uint32_t dol_Memory_getExRamSize()
{
  return Memory::GetExRamSize();
}

static uint32_t dol_Memory_getExRamMask()
{
  return Memory::GetExRamMask();
}

static bool dol_Memory_isInitialized()
{
  return Memory::IsInitialized();
}

static void dol_Memory_clear()
{
  return Memory::Clear();
}

static char* dol_Memory_getString(uint32_t em_address, size_t size)
{
  return PluginUtil::dupStdString(Memory::GetString(em_address, size));
}

static uint8_t* dol_Memory_getPointer(uint32_t address)
{
  return Memory::GetPointer(address);
}

static uint8_t* dol_Memory_getPointerForRange(uint32_t address, size_t size)
{
  return Memory::GetPointerForRange(address, size);
}

static void dol_Memory_copyFromEmu(void* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmu(data, address, size);
}

static void dol_Memory_copyToEmu(uint32_t address, const void* data, size_t size)
{
  Memory::CopyToEmu(address, data, size);
}

static void dol_Memory_memset(uint32_t address, uint8_t value, size_t size)
{
  Memory::Memset(address, value, size);
}

static uint8_t dol_Memory_readU8(uint32_t address)
{
  return Memory::Read_U8(address);
}

static uint16_t dol_Memory_readU16(uint32_t address)
{
  return Memory::Read_U16(address);
}

static uint32_t dol_Memory_readU32(uint32_t address)
{
  return Memory::Read_U32(address);
}

static uint64_t dol_Memory_readU64(uint32_t address)
{
  return Memory::Read_U64(address);
}

static void dol_Memory_writeU8(uint8_t var, uint32_t address)
{
  Memory::Write_U8(var, address);
}

static void dol_Memory_writeU16(uint16_t var, uint32_t address)
{
  Memory::Write_U16(var, address);
}

static void dol_Memory_writeU32(uint32_t var, uint32_t address)
{
  Memory::Write_U32(var, address);
}

static void dol_Memory_writeU64(uint64_t var, uint32_t address)
{
  Memory::Write_U64(var, address);
}

static void dol_Memory_writeU32Swap(uint32_t var, uint32_t address)
{
  Memory::Write_U32_Swap(var, address);
}

static void dol_Memory_writeU64Swap(uint64_t var, uint32_t address)
{
  Memory::Write_U64_Swap(var, address);
}

static void dol_Memory_copyFromEmuU16Swap(uint16_t* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmuSwapped(data, address, size);
}

static void dol_Memory_copyToEmuU16Swap(uint32_t address, const uint16_t* data, size_t size)
{
  Memory::CopyToEmuSwapped(address, data, size);
}

static void dol_Memory_copyFromEmuU32Swap(uint32_t* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmuSwapped(data, address, size);
}

static void dol_Memory_copyToEmuU32Swap(uint32_t address, const uint32_t* data, size_t size)
{
  Memory::CopyToEmuSwapped(address, data, size);
}

static void dol_Memory_copyFromEmuU64Swap(uint64_t* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmuSwapped(data, address, size);
}

static void dol_Memory_copyToEmuU64Swap(uint32_t address, const uint64_t* data, size_t size)
{
  Memory::CopyToEmuSwapped(address, data, size);
}

EXPORT dol_Memory* dol_Memory_newInterface()
{
  auto iface = static_cast<dol_Memory*>(interop_calloc(1, sizeof(dol_Memory)));
  iface->getPhysicalBase = dol_Memory_getPhysicalBase;
  iface->getLogicalBase = dol_Memory_getLogicalBase;
  iface->getPhysicalPageMappingsBase = dol_Memory_getPhysicalPageMappingsBase;
  iface->getLogicalPageMappingsBase = dol_Memory_getLogicalPageMappingsBase;
  iface->getRAMPointer = dol_Memory_getRAMPointer;
  iface->getEXRAMPointer = dol_Memory_getEXRAMPointer;
  iface->getL1CachePointer = dol_Memory_getL1CachePointer;
  iface->getFakeVMEMPointer = dol_Memory_getFakeVMEMPointer;
  iface->getRamSizeReal = dol_Memory_getRamSizeReal;
  iface->getRamSize = dol_Memory_getRamSize;
  iface->getRamMask = dol_Memory_getRamMask;
  iface->getFakeVMemSize = dol_Memory_getFakeVMemSize;
  iface->getFakeVMemMask = dol_Memory_getFakeVMemMask;
  iface->getL1CacheSize = dol_Memory_getL1CacheSize;
  iface->getL1CacheMask = dol_Memory_getL1CacheMask;
  iface->getExRamSizeReal = dol_Memory_getExRamSizeReal;
  iface->getExRamSize = dol_Memory_getExRamSize;
  iface->getExRamMask = dol_Memory_getExRamMask;
  iface->isInitialized = dol_Memory_isInitialized;
  iface->clear = dol_Memory_clear;
  iface->getString = dol_Memory_getString;
  iface->getPointer = dol_Memory_getPointer;
  iface->getPointerForRange = dol_Memory_getPointerForRange;
  iface->copyFromEmu = dol_Memory_copyFromEmu;
  iface->copyToEmu = dol_Memory_copyToEmu;
  iface->memset = dol_Memory_memset;
  iface->readU8 = dol_Memory_readU8;
  iface->readU16 = dol_Memory_readU16;
  iface->readU32 = dol_Memory_readU32;
  iface->readU64 = dol_Memory_readU64;
  iface->writeU8 = dol_Memory_writeU8;
  iface->writeU16 = dol_Memory_writeU16;
  iface->writeU32 = dol_Memory_writeU32;
  iface->writeU64 = dol_Memory_writeU64;
  iface->writeU32Swap = dol_Memory_writeU32Swap;
  iface->writeU64Swap = dol_Memory_writeU64Swap;
  iface->copyFromEmuU16Swap = dol_Memory_copyFromEmuU16Swap;
  iface->copyToEmuU16Swap = dol_Memory_copyToEmuU16Swap;
  iface->copyFromEmuU32Swap = dol_Memory_copyFromEmuU32Swap;
  iface->copyToEmuU32Swap = dol_Memory_copyToEmuU32Swap;
  iface->copyFromEmuU64Swap = dol_Memory_copyFromEmuU64Swap;
  iface->copyToEmuU64Swap = dol_Memory_copyToEmuU64Swap;

  return iface;
}
