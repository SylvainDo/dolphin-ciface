#pragma once

#include "Core_TitleDatabase.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dol_NetPlay_SyncIdentifier
{
  uint64_t dol_elf_size;
  char* game_id;
  uint16_t revision;
  uint8_t disc_number;
  bool is_datel;
  uint8_t sync_hash[20];
};

enum dol_NetPlay_SyncIdentifierComparison : uint8_t
{
  dol_NetPlay_SyncIdentifierComparison_SameGame,
  dol_NetPlay_SyncIdentifierComparison_DifferentHash,
  dol_NetPlay_SyncIdentifierComparison_DifferentDiscNumber,
  dol_NetPlay_SyncIdentifierComparison_DifferentRevision,
  dol_NetPlay_SyncIdentifierComparison_DifferentRegion,
  dol_NetPlay_SyncIdentifierComparison_DifferentGame,
  dol_NetPlay_SyncIdentifierComparison_Unknown
};

struct dol_UICommon_GameBanner
{
  const uint32_t* buffer;
  size_t size;
  uint32_t width;
  uint32_t height;
};

struct dol_UICommon_GameCover
{
  const uint8_t* buffer;
  size_t size;
};

struct dol_UICommon_GameFile
{
  void* data;
  void* (*getUnderlyingInstance)(dol_UICommon_GameFile* _this);
  bool (*isValid)(dol_UICommon_GameFile* _this);
  char* (*getFilePath)(dol_UICommon_GameFile* _this);
  char* (*getFileName)(dol_UICommon_GameFile* _this);
  char* (*getName1)(dol_UICommon_GameFile* _this, dol_Core_TitleDatabase* title_database);
  char* (*getName2)(dol_UICommon_GameFile* _this, dol_UICommon_GameFile_Variant variant);
  char* (*getMaker)(dol_UICommon_GameFile* _this, dol_UICommon_GameFile_Variant variant);
  char* (*getShortName1)(dol_UICommon_GameFile* _this, dol_DiscIO_Language l);
  char* (*getShortName2)(dol_UICommon_GameFile* _this);
  char* (*getLongName1)(dol_UICommon_GameFile* _this, dol_DiscIO_Language l);
  char* (*getLongName2)(dol_UICommon_GameFile* _this);
  char* (*getShortMaker1)(dol_UICommon_GameFile* _this, dol_DiscIO_Language l);
  char* (*getShortMaker2)(dol_UICommon_GameFile* _this);
  char* (*getLongMaker1)(dol_UICommon_GameFile* _this, dol_DiscIO_Language l);
  char* (*getLongMaker2)(dol_UICommon_GameFile* _this);
  char* (*getDescription1)(dol_UICommon_GameFile* _this, dol_DiscIO_Language l);
  char* (*getDescription2)(dol_UICommon_GameFile* _this, dol_UICommon_GameFile_Variant variant);
  dol_DiscIO_Language* (*getLanguages)(dol_UICommon_GameFile* _this, int* numLanguages);
  char* (*getInternalName)(dol_UICommon_GameFile* _this);
  char* (*getGameID)(dol_UICommon_GameFile* _this);
  char* (*getGameTDBID)(dol_UICommon_GameFile* _this);
  uint64_t (*getTitleID)(dol_UICommon_GameFile* _this);
  char* (*getMakerID)(dol_UICommon_GameFile* _this);
  uint16_t (*getRevision)(dol_UICommon_GameFile* _this);
  uint8_t (*getDiscNumber)(dol_UICommon_GameFile* _this);
  char* (*getNetPlayName)(dol_UICommon_GameFile* _this, dol_Core_TitleDatabase* title_database);
  void (*getSyncHash)(dol_UICommon_GameFile* _this, uint8_t* sync_hash);
  void (*getSyncIdentifier)(dol_UICommon_GameFile* _this,
                            dol_NetPlay_SyncIdentifier* sync_identifier);
  dol_NetPlay_SyncIdentifierComparison (*compareSyncIdentifier)(
      dol_UICommon_GameFile* _this, dol_NetPlay_SyncIdentifier* sync_identifier);
  char* (*getWiiFSPath)(dol_UICommon_GameFile* _this);
  dol_DiscIO_Region (*getRegion)(dol_UICommon_GameFile* _this);
  dol_DiscIO_Country (*getCountry)(dol_UICommon_GameFile* _this);
  dol_DiscIO_Platform (*getPlatform)(dol_UICommon_GameFile* _this);
  dol_DiscIO_BlobType (*getBlobType)(dol_UICommon_GameFile* _this);
  uint64_t (*getBlockSize)(dol_UICommon_GameFile* _this);
  char* (*getCompressionMethod)(dol_UICommon_GameFile* _this);
  bool (*shouldShowFileFormatDetails)(dol_UICommon_GameFile* _this);
  char* (*getFileFormatName)(dol_UICommon_GameFile* _this);
  bool (*shouldAllowConversion)(dol_UICommon_GameFile* _this);
  char* (*getApploaderDate)(dol_UICommon_GameFile* _this);
  uint64_t (*getFileSize)(dol_UICommon_GameFile* _this);
  uint64_t (*getVolumeSize)(dol_UICommon_GameFile* _this);
  dol_DiscIO_DataSizeType (*getVolumeSizeType)(dol_UICommon_GameFile* _this);
  bool (*isDatelDisc)(dol_UICommon_GameFile* _this);
  bool (*isNKit)(dol_UICommon_GameFile* _this);
  bool (*isModDescriptor)(dol_UICommon_GameFile* _this);
  void (*getBannerImage)(dol_UICommon_GameFile* _this, dol_UICommon_GameBanner* banner);
  void (*getCoverImage)(dol_UICommon_GameFile* _this, dol_UICommon_GameCover* cover);
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
