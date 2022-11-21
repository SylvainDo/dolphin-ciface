#include "Export.h"
#include "PluginUtil.h"

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
  return PluginUtil::dupStdString(ThisGameFile->GetFilePath());
}

static char* dol_UICommon_GameFile_getName(dol_UICommon_GameFile* _this,
                                           dol_UICommon_GameFile_Variant variant)
{
  return PluginUtil::dupStdString(
      ThisGameFile->GetName(static_cast<UICommon::GameFile::Variant>(variant)));
}

static char* dol_UICommon_GameFile_getMaker(dol_UICommon_GameFile* _this,
                                            dol_UICommon_GameFile_Variant variant)
{
  return PluginUtil::dupStdString(
      ThisGameFile->GetMaker(static_cast<UICommon::GameFile::Variant>(variant)));
}

static char* dol_UICommon_GameFile_getDescription(dol_UICommon_GameFile* _this,
                                                  dol_UICommon_GameFile_Variant variant)
{
  return PluginUtil::dupStdString(
      ThisGameFile->GetDescription(static_cast<UICommon::GameFile::Variant>(variant)));
}

static dol_DiscIO_Language* dol_UICommon_GameFile_getLanguages(dol_UICommon_GameFile* _this,
                                                               int* numLanguages)
{
  const auto langs = ThisGameFile->GetLanguages();
  auto v =
      static_cast<dol_DiscIO_Language*>(interop_malloc(sizeof(dol_DiscIO_Language) * langs.size()));
  memcpy(v, langs.data(), sizeof(dol_DiscIO_Language) * langs.size());
  *numLanguages = static_cast<int>(langs.size());
  return v;
}

static char* dol_UICommon_GameFile_getInternalName(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetInternalName());
}

static char* dol_UICommon_GameFile_getGameID(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetGameID());
}

static char* dol_UICommon_GameFile_getGameTDBID(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetGameTDBID());
}

static uint64_t dol_UICommon_GameFile_getTitleID(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetTitleID();
}

static char* dol_UICommon_GameFile_getMakerID(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetMakerID());
}

static uint16_t dol_UICommon_GameFile_getRevision(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetRevision();
}

static uint8_t dol_UICommon_GameFile_getDiscNumber(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetDiscNumber();
}

static void dol_UICommon_GameFile_getSyncHash(dol_UICommon_GameFile* _this, uint8_t* sync_hash)
{
  const auto hash = ThisGameFile->GetSyncHash();
  memcpy(sync_hash, hash.data(), hash.size());
}

static char* dol_UICommon_GameFile_getWiiFSPath(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetWiiFSPath());
}

static dol_DiscIO_Region dol_UICommon_GameFile_getRegion(dol_UICommon_GameFile* _this)
{
  return static_cast<dol_DiscIO_Region>(ThisGameFile->GetRegion());
}

static dol_DiscIO_Country dol_UICommon_GameFile_getCountry(dol_UICommon_GameFile* _this)
{
  return static_cast<dol_DiscIO_Country>(ThisGameFile->GetCountry());
}

static dol_DiscIO_Platform dol_UICommon_GameFile_getPlatform(dol_UICommon_GameFile* _this)
{
  return static_cast<dol_DiscIO_Platform>(ThisGameFile->GetPlatform());
}

static dol_DiscIO_BlobType dol_UICommon_GameFile_getBlobType(dol_UICommon_GameFile* _this)
{
  return static_cast<dol_DiscIO_BlobType>(ThisGameFile->GetBlobType());
}

static uint64_t dol_UICommon_GameFile_getBlockSize(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetBlockSize();
}

static char* dol_UICommon_GameFile_getCompressionMethod(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetCompressionMethod());
}

static char* dol_UICommon_GameFile_getFileFormatName(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetFileFormatName());
}

static char* dol_UICommon_GameFile_getApploaderDate(dol_UICommon_GameFile* _this)
{
  return PluginUtil::dupStdString(ThisGameFile->GetApploaderDate());
}

static uint64_t dol_UICommon_GameFile_getFileSize(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetFileSize();
}

static uint64_t dol_UICommon_GameFile_getVolumeSize(dol_UICommon_GameFile* _this)
{
  return ThisGameFile->GetVolumeSize();
}

static dol_DiscIO_DataSizeType dol_UICommon_GameFile_getVolumeSizeType(dol_UICommon_GameFile* _this)
{
  return static_cast<dol_DiscIO_DataSizeType>(ThisGameFile->GetVolumeSizeType());
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

static dol_UICommon_GameFile* dol_UICommon_GameFile_Factory_create(const char* path)
{
  auto iface =
      static_cast<dol_UICommon_GameFile*>(interop_calloc(1, sizeof(dol_UICommon_GameFile)));
  iface->data = static_cast<void*>(new UICommon::GameFile(path));
  iface->getUnderlyingInstance = dol_UICommon_GameFile_getUnderlyingInstance;
  iface->isValid = dol_UICommon_GameFile_isValid;
  iface->getFilePath = dol_UICommon_GameFile_getFilePath;
  iface->getName = dol_UICommon_GameFile_getName;
  iface->getMaker = dol_UICommon_GameFile_getMaker;
  iface->getDescription = dol_UICommon_GameFile_getDescription;
  iface->getLanguages = dol_UICommon_GameFile_getLanguages;
  iface->getInternalName = dol_UICommon_GameFile_getInternalName;
  iface->getGameID = dol_UICommon_GameFile_getGameID;
  iface->getGameTDBID = dol_UICommon_GameFile_getGameTDBID;
  iface->getTitleID = dol_UICommon_GameFile_getTitleID;
  iface->getMakerID = dol_UICommon_GameFile_getMakerID;
  iface->getRevision = dol_UICommon_GameFile_getRevision;
  iface->getDiscNumber = dol_UICommon_GameFile_getDiscNumber;
  iface->getSyncHash = dol_UICommon_GameFile_getSyncHash;
  iface->getWiiFSPath = dol_UICommon_GameFile_getWiiFSPath;
  iface->getRegion = dol_UICommon_GameFile_getRegion;
  iface->getCountry = dol_UICommon_GameFile_getCountry;
  iface->getPlatform = dol_UICommon_GameFile_getPlatform;
  iface->getBlobType = dol_UICommon_GameFile_getBlobType;
  iface->getBlockSize = dol_UICommon_GameFile_getBlockSize;
  iface->getCompressionMethod = dol_UICommon_GameFile_getCompressionMethod;
  iface->getFileFormatName = dol_UICommon_GameFile_getFileFormatName;
  iface->getApploaderDate = dol_UICommon_GameFile_getApploaderDate;
  iface->getFileSize = dol_UICommon_GameFile_getFileSize;
  iface->getVolumeSize = dol_UICommon_GameFile_getVolumeSize;
  iface->getVolumeSizeType = dol_UICommon_GameFile_getVolumeSizeType;
  iface->isDatelDisc = dol_UICommon_GameFile_isDatelDisc;
  iface->isNKit = dol_UICommon_GameFile_isNKit;
  iface->isModDescriptor = dol_UICommon_GameFile_isModDescriptor;
  iface->getBannerImage = dol_UICommon_GameFile_getBannerImage;

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
