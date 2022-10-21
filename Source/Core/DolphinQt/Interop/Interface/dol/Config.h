#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct dolConfig
{
  void* (*findInfo1)(const char* name);
  void* (*findInfo2)(dolConfigSystem system, const char* section, const char* key);
  int (*getInfo1)(void* prop, bool base);
  char* (*getInfo2)(void* prop, bool base);
  float (*getInfo3)(void* prop, bool base);
  uint16_t (*getInfo4)(void* prop, bool base);
  uint32_t (*getInfo5)(void* prop, bool base);
  void (*setInfo1)(void* prop, int value, bool base);
  void (*setInfo2)(void* prop, const char* value, bool base);
  void (*setInfo3)(void* prop, float value, bool base);
  void (*setInfo4)(void* prop, uint16_t value, bool base);
  void (*setInfo5)(void* prop, uint32_t value, bool base);
  dolDiscIOLanguage (*getDefaultLanguage)(void);
  bool (*getOptionalDefaultCountry)(uint8_t* defaultCountry);
  uint8_t (*getDefaultCountry)(void);
  dolDiscIORegion (*getDefaultRegion)(void);
  void* (*getInfoForMemcardPath)(dolExpansionInterfaceSlot slot);
  void* (*getInfoForAGPCartPath)(dolExpansionInterfaceSlot slot);
  void* (*getInfoForGCIPathOverride)(dolExpansionInterfaceSlot slot);
  void* (*getInfoForEXIDevice)(dolExpansionInterfaceSlot slot);
  void* (*getInfoForSIDevice)(int channel);
  void* (*getInfoForAdapterRumble)(int channel);
  void* (*getInfoForSimulateKonga)(int channel);
  dolConfigGPUDeterminismMode (*getGPUDeterminismMode)(void);
  bool (*shouldUseDPL2Decoder)(void);
  char** (*getIsoPaths)(int* numPaths);
  void (*setIsoPaths)(const char** paths, int numPaths);
  void (*getUSBDeviceWhitelist)(uint16_t** devices_first, uint16_t** devices_second,
                                int* numDevices);
  void (*setUSBDeviceWhitelist)(uint16_t* devices_first, uint16_t* devices_second, int numDevices);
  dolDiscIORegion (*toGameCubeRegion)(dolDiscIORegion region);
  char* (*getDirectoryForRegion)(dolDiscIORegion region);
  char* (*getBootROMPath)(const char* region_directory);
  char* (*getMemcardPath1)(dolExpansionInterfaceSlot slot, dolDiscIORegion* region,
                           uint16_t size_mb);
  char* (*getMemcardPath2)(const char* configured_filename, dolExpansionInterfaceSlot slot,
                           dolDiscIORegion* region, uint16_t size_mb);
  bool (*isDefaultMemcardPathConfigured)(dolExpansionInterfaceSlot slot);
  void* (*getInfoForWiimoteSource)(int index);
};

typedef dolConfig* (*dolConfig_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
