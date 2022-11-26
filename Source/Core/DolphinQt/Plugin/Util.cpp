#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Util.h"

#include "Common/FileUtil.h"
#include "Common/IniFile.h"
#include "Core/ActionReplay.h"
#include "Core/ConfigManager.h"
#include "Core/GeckoCode.h"
#include "Core/GeckoCodeConfig.h"
#include "Core/PatchEngine.h"
#include "DiscIO/DiscExtractor.h"
#include "DiscIO/DiscUtils.h"
#include "DiscIO/Filesystem.h"
#include "DiscIO/VolumeVerifier.h"
#include "UICommon/GameFile.h"

#include <filesystem>

#include <QString>

static bool dol_Util_enablePatch(dol_UICommon_GameFile* game, const char* name)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  if (!_game->IsValid())
    return false;

  const std::string ini_path = File::GetUserPath(D_GAMESETTINGS_IDX) + _game->GetGameID() + ".ini";
  std::vector<PatchEngine::Patch> patches;

  IniFile game_ini_local;
  game_ini_local.Load(ini_path);

  IniFile game_ini_default =
      SConfig::GetInstance().LoadDefaultGameIni(_game->GetGameID(), _game->GetRevision());
  PatchEngine::LoadPatchSection("OnFrame", &patches, game_ini_default, game_ini_local);

  auto it = std::find_if(patches.begin(), patches.end(),
                         [name](PatchEngine::Patch& i) { return i.name == name; });
  if (it == patches.end())
    return false;
  it->enabled = true;

  PatchEngine::SavePatchSection(&game_ini_local, patches);
  game_ini_local.Save(ini_path);

  return true;
}

static bool dol_Util_enableARCode(dol_UICommon_GameFile* game, const char* name)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  if (!_game->IsValid())
    return false;

  const std::string ini_path = File::GetUserPath(D_GAMESETTINGS_IDX) + _game->GetGameID() + ".ini";
  std::vector<ActionReplay::ARCode> ar_codes;

  IniFile game_ini_local;
  game_ini_local.Load(ini_path);

  const IniFile game_ini_default =
      SConfig::LoadDefaultGameIni(_game->GetGameID(), _game->GetRevision());
  ar_codes = ActionReplay::LoadCodes(game_ini_default, game_ini_local);

  auto it = std::find_if(ar_codes.begin(), ar_codes.end(),
                         [name](ActionReplay::ARCode& i) { return i.name == name; });
  if (it == ar_codes.end())
    return false;
  it->enabled = true;

  ActionReplay::ApplyCodes(ar_codes);

  ActionReplay::SaveCodes(&game_ini_local, ar_codes);
  game_ini_local.Save(ini_path);

  return true;
}

static bool dol_Util_enableGeckoCode(dol_UICommon_GameFile* game, const char* name)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  if (!_game->IsValid())
    return false;

  const std::string ini_path = File::GetUserPath(D_GAMESETTINGS_IDX) + _game->GetGameID() + ".ini";
  std::vector<Gecko::GeckoCode> gecko_codes;

  IniFile game_ini_local;
  game_ini_local.Load(ini_path);

  const IniFile game_ini_default =
      SConfig::LoadDefaultGameIni(_game->GetGameID(), _game->GetRevision());
  gecko_codes = Gecko::LoadCodes(game_ini_default, game_ini_local);

  auto it = std::find_if(gecko_codes.begin(), gecko_codes.end(),
                         [name](Gecko::GeckoCode& i) { return i.name == name; });
  if (it == gecko_codes.end())
    return false;
  it->enabled = true;

  Gecko::SetActiveCodes(gecko_codes);

  Gecko::SaveCodes(game_ini_local, gecko_codes);
  game_ini_local.Save(ini_path);

  return true;
}

namespace VerifyDiscDetails
{

bool Verify(UICommon::GameFile& game, uint8_t* sha1, bool* goodDump)
{
  if (!game.IsValid() || game.GetPlatform() == DiscIO::Platform::ELFOrDOL)
    return false;

  auto volume = DiscIO::CreateVolume(game.GetFilePath());
  DiscIO::VolumeVerifier verifier(*volume, true, {false, false, true});

  auto future = std::async(std::launch::async,
                           [&verifier]() -> std::optional<DiscIO::VolumeVerifier::Result> {
                             verifier.Start();
                             while (verifier.GetBytesProcessed() != verifier.GetTotalBytes())
                               verifier.Process();
                             verifier.Finish();

                             const DiscIO::VolumeVerifier::Result result = verifier.GetResult();
                             return result;
                           });

  std::optional<DiscIO::VolumeVerifier::Result> result = future.get();
  if (!result)
    return false;

  memcpy(sha1, result->hashes.sha1.data(), result->hashes.sha1.size());
  *goodDump = result->redump.status == DiscIO::RedumpVerifier::Status::GoodDump;
  return result->problems.empty();
}

}  // namespace VerifyDiscDetails

static bool dol_Util_verifyDisc(dol_UICommon_GameFile* game, uint8_t* sha1, bool* goodDump)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  return VerifyDiscDetails::Verify(*_game, sha1, goodDump);
}

namespace ExtractDiscDetails
{

void ExtractDirectory(std::unique_ptr<DiscIO::Volume>& volume, const DiscIO::Partition& partition,
                      const QString& path, const QString& out)
{
  const DiscIO::FileSystem* filesystem = volume->GetFileSystem(partition);
  if (!filesystem)
    return;

  std::unique_ptr<DiscIO::FileInfo> info = filesystem->FindFileInfo(path.toStdString());
  DiscIO::ExportDirectory(*volume, partition, *info, true, path.toStdString(), out.toStdString(),
                          [](const std::string& current) { return false; });
}

bool ExtractSystemData(std::unique_ptr<DiscIO::Volume>& volume, const DiscIO::Partition& partition,
                       const QString& out)
{
  return DiscIO::ExportSystemData(*volume, partition, out.toStdString());
}

void ExtractPartition(std::unique_ptr<DiscIO::Volume>& volume, const DiscIO::Partition& partition,
                      const QString& out)
{
  ExtractDirectory(volume, partition, QString{}, out + QStringLiteral("/files"));
  ExtractSystemData(volume, partition, out);
}

bool Extract(UICommon::GameFile& game, const char* path)
{
  if (!game.IsValid() || game.GetPlatform() == DiscIO::Platform::ELFOrDOL)
    return false;

  std::filesystem::create_directories(path);

  auto folder = QString::fromUtf8(path);
  auto volume = DiscIO::CreateVolume(game.GetFilePath());

  if (volume->GetPartitions().empty())
  {
    ExtractPartition(volume, DiscIO::PARTITION_NONE, folder);
  }
  else
  {
    for (DiscIO::Partition& p : volume->GetPartitions())
    {
      if (const std::optional<u32> partition_type = volume->GetPartitionType(p))
      {
        const std::string partition_name = DiscIO::NameForPartitionType(*partition_type, true);
        ExtractPartition(volume, p, folder + QChar(u'/') + QString::fromStdString(partition_name));
      }
    }
  }

  return true;
}

}  // namespace ExtractDiscDetails

static bool dol_Util_extractDisc(dol_UICommon_GameFile* game, const char* path)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  return ExtractDiscDetails::Extract(*_game, path);
}

EXPORT dol_Util* dol_Util_newInterface()
{
  auto iface = static_cast<dol_Util*>(interop_calloc(1, sizeof(dol_Util)));
  iface->enablePatch = dol_Util_enablePatch;
  iface->enableARCode = dol_Util_enableARCode;
  iface->enableGeckoCode = dol_Util_enableGeckoCode;
  iface->verifyDisc = dol_Util_verifyDisc;
  iface->extractDisc = dol_Util_extractDisc;

  return iface;
}
