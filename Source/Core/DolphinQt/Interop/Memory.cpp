#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Memory.h"

#include "Core/HW/Memmap.h"

static uint8_t* dolMemory_getPhysicalBase()
{
  return Memory::physical_base;
}

static uint8_t* dolMemory_getLogicalBase()
{
  return Memory::logical_base;
}

static uint8_t* dolMemory_getPhysicalPageMappingsBase()
{
  return Memory::physical_page_mappings_base;
}

static uint8_t* dolMemory_getLogicalPageMappingsBase()
{
  return Memory::logical_page_mappings_base;
}

static uint8_t* dolMemory_getRAMPointer()
{
  return Memory::m_pRAM;
}

static uint8_t* dolMemory_getEXRAMPointer()
{
  return Memory::m_pEXRAM;
}

static uint8_t* dolMemory_getL1CachePointer()
{
  return Memory::m_pL1Cache;
}

static uint8_t* dolMemory_getFakeVMEMPointer()
{
  return Memory::m_pFakeVMEM;
}

static uint32_t dolMemory_getRamSizeReal()
{
  return Memory::GetRamSizeReal();
}

static uint32_t dolMemory_getRamSize()
{
  return Memory::GetRamSize();
}

static uint32_t dolMemory_getRamMask()
{
  return Memory::GetRamMask();
}

static uint32_t dolMemory_getFakeVMemSize()
{
  return Memory::GetFakeVMemSize();
}

static uint32_t dolMemory_getFakeVMemMask()
{
  return Memory::GetFakeVMemMask();
}

static uint32_t dolMemory_getL1CacheSize()
{
  return Memory::GetL1CacheSize();
}

static uint32_t dolMemory_getL1CacheMask()
{
  return Memory::GetL1CacheMask();
}

static uint32_t dolMemory_getExRamSizeReal()
{
  return Memory::GetExRamSizeReal();
}

static uint32_t dolMemory_getExRamSize()
{
  return Memory::GetExRamSize();
}

static uint32_t dolMemory_getExRamMask()
{
  return Memory::GetExRamMask();
}

static bool dolMemory_isInitialized()
{
  return Memory::IsInitialized();
}

static void dolMemory_clear()
{
  return Memory::Clear();
}

static char* dolMemory_getString(uint32_t em_address, size_t size)
{
  return InteropUtil::dupStdString(Memory::GetString(em_address, size));
}

static uint8_t* dolMemory_getPointer(uint32_t address)
{
  return Memory::GetPointer(address);
}

static uint8_t* dolMemory_getPointerForRange(uint32_t address, size_t size)
{
  return Memory::GetPointerForRange(address, size);
}

static void dolMemory_copyFromEmu(void* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmu(data, address, size);
}

static void dolMemory_copyToEmu(uint32_t address, const void* data, size_t size)
{
  Memory::CopyToEmu(address, data, size);
}

static void dolMemory_memset(uint32_t address, uint8_t value, size_t size)
{
  Memory::Memset(address, value, size);
}

static uint8_t dolMemory_readU8(uint32_t address)
{
  return Memory::Read_U8(address);
}

static uint16_t dolMemory_readU16(uint32_t address)
{
  return Memory::Read_U16(address);
}

static uint32_t dolMemory_readU32(uint32_t address)
{
  return Memory::Read_U32(address);
}

static uint64_t dolMemory_readU64(uint32_t address)
{
  return Memory::Read_U64(address);
}

static void dolMemory_writeU8(uint8_t var, uint32_t address)
{
  Memory::Write_U8(var, address);
}

static void dolMemory_writeU16(uint16_t var, uint32_t address)
{
  Memory::Write_U16(var, address);
}

static void dolMemory_writeU32(uint32_t var, uint32_t address)
{
  Memory::Write_U32(var, address);
}

static void dolMemory_writeU64(uint64_t var, uint32_t address)
{
  Memory::Write_U64(var, address);
}

static void dolMemory_writeU32Swap(uint32_t var, uint32_t address)
{
  Memory::Write_U32_Swap(var, address);
}

static void dolMemory_writeU64Swap(uint64_t var, uint32_t address)
{
  Memory::Write_U64_Swap(var, address);
}

static void dolMemory_copyFromEmuU16Swap(uint16_t* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmuSwapped(data, address, size);
}

static void dolMemory_copyToEmuU16Swap(uint32_t address, const uint16_t* data, size_t size)
{
  Memory::CopyToEmuSwapped(address, data, size);
}

static void dolMemory_copyFromEmuU32Swap(uint32_t* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmuSwapped(data, address, size);
}

static void dolMemory_copyToEmuU32Swap(uint32_t address, const uint32_t* data, size_t size)
{
  Memory::CopyToEmuSwapped(address, data, size);
}

static void dolMemory_copyFromEmuU64Swap(uint64_t* data, uint32_t address, size_t size)
{
  Memory::CopyFromEmuSwapped(data, address, size);
}

static void dolMemory_copyToEmuU64Swap(uint32_t address, const uint64_t* data, size_t size)
{
  Memory::CopyToEmuSwapped(address, data, size);
}

EXPORT dolMemory* dolMemory_newInterface()
{
  auto iface = static_cast<dolMemory*>(interop_calloc(1, sizeof(dolMemory)));
  iface->getPhysicalBase = dolMemory_getPhysicalBase;
  iface->getLogicalBase = dolMemory_getLogicalBase;
  iface->getPhysicalPageMappingsBase = dolMemory_getPhysicalPageMappingsBase;
  iface->getLogicalPageMappingsBase = dolMemory_getLogicalPageMappingsBase;
  iface->getRAMPointer = dolMemory_getRAMPointer;
  iface->getEXRAMPointer = dolMemory_getEXRAMPointer;
  iface->getL1CachePointer = dolMemory_getL1CachePointer;
  iface->getFakeVMEMPointer = dolMemory_getFakeVMEMPointer;
  iface->getRamSizeReal = dolMemory_getRamSizeReal;
  iface->getRamSize = dolMemory_getRamSize;
  iface->getRamMask = dolMemory_getRamMask;
  iface->getFakeVMemSize = dolMemory_getFakeVMemSize;
  iface->getFakeVMemMask = dolMemory_getFakeVMemMask;
  iface->getL1CacheSize = dolMemory_getL1CacheSize;
  iface->getL1CacheMask = dolMemory_getL1CacheMask;
  iface->getExRamSizeReal = dolMemory_getExRamSizeReal;
  iface->getExRamSize = dolMemory_getExRamSize;
  iface->getExRamMask = dolMemory_getExRamMask;
  iface->isInitialized = dolMemory_isInitialized;
  iface->clear = dolMemory_clear;
  iface->getString = dolMemory_getString;
  iface->getPointer = dolMemory_getPointer;
  iface->getPointerForRange = dolMemory_getPointerForRange;
  iface->copyFromEmu = dolMemory_copyFromEmu;
  iface->copyToEmu = dolMemory_copyToEmu;
  iface->memset = dolMemory_memset;
  iface->readU8 = dolMemory_readU8;
  iface->readU16 = dolMemory_readU16;
  iface->readU32 = dolMemory_readU32;
  iface->readU64 = dolMemory_readU64;
  iface->writeU8 = dolMemory_writeU8;
  iface->writeU16 = dolMemory_writeU16;
  iface->writeU32 = dolMemory_writeU32;
  iface->writeU64 = dolMemory_writeU64;
  iface->writeU32Swap = dolMemory_writeU32Swap;
  iface->writeU64Swap = dolMemory_writeU64Swap;
  iface->copyFromEmuU16Swap = dolMemory_copyFromEmuU16Swap;
  iface->copyToEmuU16Swap = dolMemory_copyToEmuU16Swap;
  iface->copyFromEmuU32Swap = dolMemory_copyFromEmuU32Swap;
  iface->copyToEmuU32Swap = dolMemory_copyToEmuU32Swap;
  iface->copyFromEmuU64Swap = dolMemory_copyFromEmuU64Swap;
  iface->copyToEmuU64Swap = dolMemory_copyToEmuU64Swap;

  return iface;
}
