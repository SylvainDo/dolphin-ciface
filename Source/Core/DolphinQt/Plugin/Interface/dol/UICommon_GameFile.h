#pragma once

#include "Enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

struct dol_UICommon_GameBanner
{
  const uint32_t* buffer;
  size_t size;
  uint32_t width;
  uint32_t height;
};

struct dol_UICommon_GameFile
{
  void* data;
  void* (*getUnderlyingInstance)(dol_UICommon_GameFile* _this);
  bool (*isValid)(dol_UICommon_GameFile* _this);
  char* (*getFilePath)(dol_UICommon_GameFile* _this);
  char* (*getName)(dol_UICommon_GameFile* _this, dol_UICommon_GameFile_Variant variant);
  char* (*getMaker)(dol_UICommon_GameFile* _this, dol_UICommon_GameFile_Variant variant);
  char* (*getDescription)(dol_UICommon_GameFile* _this, dol_UICommon_GameFile_Variant variant);
  dol_DiscIO_Language* (*getLanguages)(dol_UICommon_GameFile* _this, int* numLanguages);
  char* (*getInternalName)(dol_UICommon_GameFile* _this);
  char* (*getGameID)(dol_UICommon_GameFile* _this);
  char* (*getGameTDBID)(dol_UICommon_GameFile* _this);
  uint64_t (*getTitleID)(dol_UICommon_GameFile* _this);
  char* (*getMakerID)(dol_UICommon_GameFile* _this);
  uint16_t (*getRevision)(dol_UICommon_GameFile* _this);
  uint8_t (*getDiscNumber)(dol_UICommon_GameFile* _this);
  void (*getSyncHash)(dol_UICommon_GameFile* _this, uint8_t* sync_hash);
  char* (*getWiiFSPath)(dol_UICommon_GameFile* _this);
  dol_DiscIO_Region (*getRegion)(dol_UICommon_GameFile* _this);
  dol_DiscIO_Country (*getCountry)(dol_UICommon_GameFile* _this);
  dol_DiscIO_Platform (*getPlatform)(dol_UICommon_GameFile* _this);
  dol_DiscIO_BlobType (*getBlobType)(dol_UICommon_GameFile* _this);
  uint64_t (*getBlockSize)(dol_UICommon_GameFile* _this);
  char* (*getCompressionMethod)(dol_UICommon_GameFile* _this);
  char* (*getFileFormatName)(dol_UICommon_GameFile* _this);
  char* (*getApploaderDate)(dol_UICommon_GameFile* _this);
  uint64_t (*getFileSize)(dol_UICommon_GameFile* _this);
  uint64_t (*getVolumeSize)(dol_UICommon_GameFile* _this);
  dol_DiscIO_DataSizeType (*getVolumeSizeType)(dol_UICommon_GameFile* _this);
  bool (*isDatelDisc)(dol_UICommon_GameFile* _this);
  bool (*isNKit)(dol_UICommon_GameFile* _this);
  bool (*isModDescriptor)(dol_UICommon_GameFile* _this);
  void (*getBannerImage)(dol_UICommon_GameFile* _this, dol_UICommon_GameBanner* banner);
  char* (*getLocalIniPath)(dol_UICommon_GameFile* _this);
};

struct dol_UICommon_GameFile_Factory
{
  dol_UICommon_GameFile* (*create)(const char* path);
  void (*destroy)(dol_UICommon_GameFile* _this);
};

typedef dol_UICommon_GameFile_Factory* (*dol_UICommon_GameFile_Factory_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
