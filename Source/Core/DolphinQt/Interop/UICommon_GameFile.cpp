#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/UICommon_GameFile.h"

#include "UICommon/GameFile.h"

#define ThisGameFile static_cast<UICommon::GameFile*>(_this->data)

static void* dol_UICommon_GameFile_getUnderlyingInstance(dol_UICommon_GameFile* _this)
{
  return _this->data;
}

static bool dol_UICommon_GameFile_isValid(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->IsValid();
}

static char* dol_UICommon_GameFile_getFilePath(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetFilePath());
}

static char* dol_UICommon_GameFile_getFileName(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetFileName());
}

static char* dol_UICommon_GameFile_getName1(dol_UICommon_GameFile* _this,
                                            dol_Core_TitleDatabase* title_database)
{
  const auto& title_database_ref =
      *static_cast<Core::TitleDatabase*>(title_database->getUnderlyingInstance(title_database));
  return InteropUtil::dupStdString(ThisGameFile->GetName(title_database_ref));
}

static char* dol_UICommon_GameFile_getName2(dol_UICommon_GameFile* _this,
                                            dol_UICommon_GameFile_Variant variant)
{
  return InteropUtil::dupStdString(
      ThisGameFile->GetName(static_cast<UICommon::GameFile::Variant>(variant)));
}

static char* dol_UICommon_GameFile_getMaker(dol_UICommon_GameFile* _this,
                                            dol_UICommon_GameFile_Variant variant)
{
  return InteropUtil::dupStdString(
      ThisGameFile->GetMaker(static_cast<UICommon::GameFile::Variant>(variant)));
}

static char* dol_UICommon_GameFile_getShortName1(dol_UICommon_GameFile* _this, dolDiscIOLanguage l)
{
  return InteropUtil::dupStdString(ThisGameFile->GetShortName(static_cast<DiscIO::Language>(l)));
}

static char* dol_UICommon_GameFile_getShortName2(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetShortName());
}

static char* dol_UICommon_GameFile_getLongName1(dol_UICommon_GameFile* _this, dolDiscIOLanguage l)
{
  return InteropUtil::dupStdString(ThisGameFile->GetLongName(static_cast<DiscIO::Language>(l)));
}

static char* dol_UICommon_GameFile_getLongName2(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetLongName());
}

static char* dol_UICommon_GameFile_getShortMaker1(dol_UICommon_GameFile* _this, dolDiscIOLanguage l)
{
  return InteropUtil::dupStdString(ThisGameFile->GetShortMaker(static_cast<DiscIO::Language>(l)));
}

static char* dol_UICommon_GameFile_getShortMaker2(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetShortMaker());
}

static char* dol_UICommon_GameFile_getLongMaker1(dol_UICommon_GameFile* _this, dolDiscIOLanguage l)
{
  return InteropUtil::dupStdString(ThisGameFile->GetLongMaker(static_cast<DiscIO::Language>(l)));
}

static char* dol_UICommon_GameFile_getLongMaker2(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetLongMaker());
}

static char* dol_UICommon_GameFile_getDescription1(dol_UICommon_GameFile* _this,
                                                   dolDiscIOLanguage l)
{
  return InteropUtil::dupStdString(ThisGameFile->GetDescription(static_cast<DiscIO::Language>(l)));
}

static char* dol_UICommon_GameFile_getDescription2(dol_UICommon_GameFile* _this,
                                                   dol_UICommon_GameFile_Variant variant)
{
  return InteropUtil::dupStdString(
      ThisGameFile->GetDescription(static_cast<UICommon::GameFile::Variant>(variant)));
}

static dolDiscIOLanguage* dol_UICommon_GameFile_getLanguages(dol_UICommon_GameFile* _this,
                                                             int* numLanguages)
{
  const auto langs = ThisGameFile->GetLanguages();
  auto v =
      static_cast<dolDiscIOLanguage*>(interop_malloc(sizeof(dolDiscIOLanguage) * langs.size()));
  memcpy(v, langs.data(), langs.size());
  *numLanguages = static_cast<int>(langs.size());
  return v;
}

static char* dol_UICommon_GameFile_getInternalName(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetInternalName());
}

static char* dol_UICommon_GameFile_getGameID(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetGameID());
}

static char* dol_UICommon_GameFile_getGameTDBID(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetGameTDBID());
}

static uint64_t dol_UICommon_GameFile_getTitleID(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetTitleID();
}

static char* dol_UICommon_GameFile_getMakerID(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetMakerID());
}

static uint16_t dol_UICommon_GameFile_getRevision(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetRevision();
}

static uint8_t dol_UICommon_GameFile_getDiscNumber(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetDiscNumber();
}

static char* dol_UICommon_GameFile_getNetPlayName(dol_UICommon_GameFile* _this,
                                                  dol_Core_TitleDatabase* title_database)
{
  const auto& title_database_ref =
      *static_cast<Core::TitleDatabase*>(title_database->getUnderlyingInstance(title_database));
  return InteropUtil::dupStdString(ThisGameFile->GetNetPlayName(title_database_ref));
}

static void dol_UICommon_GameFile_getSyncHash(dol_UICommon_GameFile* _this, uint8_t* sync_hash)
{
  const auto hash = ThisGameFile->GetSyncHash();
  memcpy(sync_hash, hash.data(), hash.size());
}

static void dol_UICommon_GameFile_getSyncIdentifier(dol_UICommon_GameFile* _this,
                                                    dol_NetPlay_SyncIdentifier* sync_identifier)
{
  const auto id = ThisGameFile->GetSyncIdentifier();
  sync_identifier->dol_elf_size = id.dol_elf_size;
  sync_identifier->game_id = InteropUtil::dupStdString(id.game_id);
  sync_identifier->revision = id.revision;
  sync_identifier->disc_number = id.disc_number;
  sync_identifier->is_datel = id.is_datel;
  memcpy(sync_identifier->sync_hash, id.sync_hash.data(), id.sync_hash.size());
}

static dol_NetPlay_SyncIdentifierComparison
dol_UICommon_GameFile_compareSyncIdentifier(dol_UICommon_GameFile* _this,
                                            dol_NetPlay_SyncIdentifier* sync_identifier)
{
  NetPlay::SyncIdentifier id = {sync_identifier->dol_elf_size, sync_identifier->game_id,
                                sync_identifier->revision, sync_identifier->disc_number,
                                sync_identifier->is_datel};
  memcpy(id.sync_hash.data(), sync_identifier->sync_hash, id.sync_hash.size());
  return static_cast<dol_NetPlay_SyncIdentifierComparison>(ThisGameFile->CompareSyncIdentifier(id));
}

static char* dol_UICommon_GameFile_getWiiFSPath(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetWiiFSPath());
}

static dolDiscIORegion dol_UICommon_GameFile_getRegion(dol_UICommon_GameFile* _this)
{
  return static_cast<dolDiscIORegion>(ThisGameFile->GetRegion());
}

static dolDiscIOCountry dol_UICommon_GameFile_getCountry(dol_UICommon_GameFile* _this)
{
  return static_cast<dolDiscIOCountry>(ThisGameFile->GetCountry());
}

static dolDiscIOPlatform dol_UICommon_GameFile_getPlatform(dol_UICommon_GameFile* _this)
{
  return static_cast<dolDiscIOPlatform>(ThisGameFile->GetPlatform());
}

static dolDiscIOBlobType dol_UICommon_GameFile_getBlobType(dol_UICommon_GameFile* _this)
{
  return static_cast<dolDiscIOBlobType>(ThisGameFile->GetBlobType());
}

static uint64_t dol_UICommon_GameFile_getBlockSize(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetBlockSize();
}

static char* dol_UICommon_GameFile_getCompressionMethod(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetCompressionMethod());
}

static bool dol_UICommon_GameFile_shouldShowFileFormatDetails(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->ShouldShowFileFormatDetails();
}

static char* dol_UICommon_GameFile_getFileFormatName(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetFileFormatName());
}

static bool dol_UICommon_GameFile_shouldAllowConversion(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->ShouldAllowConversion();
}

static char* dol_UICommon_GameFile_getApploaderDate(dol_UICommon_GameFile* _this)
{
  return InteropUtil::dupStdString(ThisGameFile->GetApploaderDate());
}

static uint64_t dol_UICommon_GameFile_getFileSize(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetFileSize();
}

static uint64_t dol_UICommon_GameFile_getVolumeSize(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetVolumeSize();
}

static dolDiscIODataSizeType dol_UICommon_GameFile_getVolumeSizeType(dol_UICommon_GameFile* _this)
{
  return static_cast<dolDiscIODataSizeType>(ThisGameFile->GetVolumeSizeType());
}

static bool dol_UICommon_GameFile_isDatelDisc(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->IsDatelDisc();
}

static bool dol_UICommon_GameFile_isNKit(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->IsNKit();
}

static bool dol_UICommon_GameFile_isModDescriptor(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->IsModDescriptor();
}

static void dol_UICommon_GameFile_getBannerImage(dol_UICommon_GameFile* _this,
                                                 dol_UICommon_GameBanner* banner)
{
  const auto& v = ThisGameFile->GetBannerImage();
  banner->buffer = v.buffer.data();
  banner->size = v.buffer.size();
  banner->width = v.width;
  banner->height = v.height;
}

static void dol_UICommon_GameFile_getCoverImage(dol_UICommon_GameFile* _this,
                                                dol_UICommon_GameCover* cover)
{
  const auto& v = ThisGameFile->GetCoverImage();
  cover->buffer = v.buffer.data();
  cover->size = v.buffer.size();
}

static dol_UICommon_GameFile* dol_UICommon_GameFile_Factory_create(const char* path)
{
  auto iface =
      static_cast<dol_UICommon_GameFile*>(interop_calloc(1, sizeof(dol_UICommon_GameFile)));
  iface->data = static_cast<void*>(new UICommon::GameFile(path));
  iface->getUnderlyingInstance = dol_UICommon_GameFile_getUnderlyingInstance;
  iface->isValid = dol_UICommon_GameFile_isValid;
  iface->getFilePath = dol_UICommon_GameFile_getFilePath;
  iface->getFileName = dol_UICommon_GameFile_getFileName;
  iface->getName1 = dol_UICommon_GameFile_getName1;
  iface->getName2 = dol_UICommon_GameFile_getName2;
  iface->getMaker = dol_UICommon_GameFile_getMaker;
  iface->getShortName1 = dol_UICommon_GameFile_getShortName1;
  iface->getShortName2 = dol_UICommon_GameFile_getShortName2;
  iface->getLongName1 = dol_UICommon_GameFile_getLongName1;
  iface->getLongName2 = dol_UICommon_GameFile_getLongName2;
  iface->getShortMaker1 = dol_UICommon_GameFile_getShortMaker1;
  iface->getShortMaker2 = dol_UICommon_GameFile_getShortMaker2;
  iface->getLongMaker1 = dol_UICommon_GameFile_getLongMaker1;
  iface->getLongMaker2 = dol_UICommon_GameFile_getLongMaker2;
  iface->getDescription1 = dol_UICommon_GameFile_getDescription1;
  iface->getDescription2 = dol_UICommon_GameFile_getDescription2;
  iface->getLanguages = dol_UICommon_GameFile_getLanguages;
  iface->getInternalName = dol_UICommon_GameFile_getInternalName;
  iface->getGameID = dol_UICommon_GameFile_getGameID;
  iface->getGameTDBID = dol_UICommon_GameFile_getGameTDBID;
  iface->getTitleID = dol_UICommon_GameFile_getTitleID;
  iface->getMakerID = dol_UICommon_GameFile_getMakerID;
  iface->getRevision = dol_UICommon_GameFile_getRevision;
  iface->getDiscNumber = dol_UICommon_GameFile_getDiscNumber;
  iface->getNetPlayName = dol_UICommon_GameFile_getNetPlayName;
  iface->getSyncHash = dol_UICommon_GameFile_getSyncHash;
  iface->getSyncIdentifier = dol_UICommon_GameFile_getSyncIdentifier;
  iface->compareSyncIdentifier = dol_UICommon_GameFile_compareSyncIdentifier;
  iface->getWiiFSPath = dol_UICommon_GameFile_getWiiFSPath;
  iface->getRegion = dol_UICommon_GameFile_getRegion;
  iface->getCountry = dol_UICommon_GameFile_getCountry;
  iface->getPlatform = dol_UICommon_GameFile_getPlatform;
  iface->getBlobType = dol_UICommon_GameFile_getBlobType;
  iface->getBlockSize = dol_UICommon_GameFile_getBlockSize;
  iface->getCompressionMethod = dol_UICommon_GameFile_getCompressionMethod;
  iface->shouldShowFileFormatDetails = dol_UICommon_GameFile_shouldShowFileFormatDetails;
  iface->getFileFormatName = dol_UICommon_GameFile_getFileFormatName;
  iface->shouldAllowConversion = dol_UICommon_GameFile_shouldAllowConversion;
  iface->getApploaderDate = dol_UICommon_GameFile_getApploaderDate;
  iface->getFileSize = dol_UICommon_GameFile_getFileSize;
  iface->getVolumeSize = dol_UICommon_GameFile_getVolumeSize;
  iface->getVolumeSizeType = dol_UICommon_GameFile_getVolumeSizeType;
  iface->isDatelDisc = dol_UICommon_GameFile_isDatelDisc;
  iface->isNKit = dol_UICommon_GameFile_isNKit;
  iface->isModDescriptor = dol_UICommon_GameFile_isModDescriptor;
  iface->getBannerImage = dol_UICommon_GameFile_getBannerImage;
  iface->getCoverImage = dol_UICommon_GameFile_getCoverImage;

  return iface;
}

static void dol_UICommon_GameFile_Factory_destroy(dol_UICommon_GameFile* _this)
{
  delete ThisGameFile;
}

EXPORT dol_UICommon_GameFile_Factory* dol_UICommon_GameFile_Factory_newInterface()
{
  auto iface = static_cast<dol_UICommon_GameFile_Factory*>(
      interop_calloc(1, sizeof(dol_UICommon_GameFile_Factory)));
  iface->create = dol_UICommon_GameFile_Factory_create;
  iface->destroy = dol_UICommon_GameFile_Factory_destroy;

  return iface;
}
