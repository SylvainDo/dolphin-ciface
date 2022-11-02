#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Core_TitleDatabase.h"

#include "Core/TitleDatabase.h"

#define ThisTitleDatabase static_cast<Core::TitleDatabase*>(_this->data)

static void* dol_Core_TitleDatabase_getUnderlyingInstance(dol_Core_TitleDatabase* _this)
{
  return _this->data;
}

static char* dol_Core_TitleDatabase_getTitleName(dol_Core_TitleDatabase* _this,
                                                 const char* gametdb_id, dol_DiscIO_Language language)
{
  return InteropUtil::dupStdString(
      ThisTitleDatabase->GetTitleName(gametdb_id, static_cast<DiscIO::Language>(language)));
}

static char* dol_Core_TitleDatabase_getChannelName(dol_Core_TitleDatabase* _this, uint64_t title_id,
                                                   dol_DiscIO_Language language)
{
  return InteropUtil::dupStdString(
      ThisTitleDatabase->GetChannelName(title_id, static_cast<DiscIO::Language>(language)));
}

static char* dol_Core_TitleDatabase_describe(dol_Core_TitleDatabase* _this, const char* gametdb_id,
                                             dol_DiscIO_Language language)
{
  return InteropUtil::dupStdString(
      ThisTitleDatabase->Describe(gametdb_id, static_cast<DiscIO::Language>(language)));
}

static dol_Core_TitleDatabase* dol_Core_TitleDatabase_Factory_create()
{
  auto iface =
      static_cast<dol_Core_TitleDatabase*>(interop_calloc(1, sizeof(dol_Core_TitleDatabase)));
  iface->data = static_cast<void*>(new Core::TitleDatabase);
  iface->getUnderlyingInstance = dol_Core_TitleDatabase_getUnderlyingInstance;
  iface->getTitleName = dol_Core_TitleDatabase_getTitleName;
  iface->getChannelName = dol_Core_TitleDatabase_getChannelName;
  iface->describe = dol_Core_TitleDatabase_describe;

  return iface;
}

static void dol_Core_TitleDatabase_Factory_destroy(dol_Core_TitleDatabase* _this)
{
  delete ThisTitleDatabase;
}

EXPORT dol_Core_TitleDatabase_Factory* dol_Core_TitleDatabase_Factory_newInterface()
{
  auto iface = static_cast<dol_Core_TitleDatabase_Factory*>(
      interop_calloc(1, sizeof(dol_Core_TitleDatabase_Factory)));
  iface->create = dol_Core_TitleDatabase_Factory_create;
  iface->destroy = dol_Core_TitleDatabase_Factory_destroy;

  return iface;
}
