#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Util.h"

#include "DiscIO/DiscExtractor.h"
#include "DiscIO/DiscUtils.h"
#include "DiscIO/Filesystem.h"
#include "DiscIO/VolumeVerifier.h"
#include "UICommon/GameFile.h"

#include <filesystem>
#include <iostream>

#include <QString>

namespace VerifyDiscDetails
{

bool Verify(UICommon::GameFile& game, uint8_t* sha1, bool* goodDump)
{
  if (game.GetPlatform() == DiscIO::Platform::ELFOrDOL)
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

bool VerifySafe(UICommon::GameFile& game, uint8_t* sha1, bool* goodDump)
{
  try
  {
    return Verify(game, sha1, goodDump);
  }
  catch (std::exception& e)
  {
    std::cerr << "verify disc: exception occurred: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "verify disc: unknown exception occurred" << std::endl;
  }
  return false;
}

}  // namespace VerifyDiscDetails

static bool dol_Util_verifyDisc(dol_UICommon_GameFile* game, uint8_t* sha1, bool* goodDump)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  return VerifyDiscDetails::VerifySafe(*_game, sha1, goodDump);
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
  if (game.GetPlatform() == DiscIO::Platform::ELFOrDOL)
    return false;

  if (!std::filesystem::create_directories(path))
    return false;

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

bool ExtractSafe(UICommon::GameFile& game, const char* path)
{
  try
  {
    return Extract(game, path);
  }
  catch (std::exception& e)
  {
    std::cerr << "extract disc: exception occurred: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "extract disc: unknown exception occurred" << std::endl;
  }
  return false;
}

}  // namespace ExtractDiscDetails

static bool dol_Util_extractDisc(dol_UICommon_GameFile* game, const char* path)
{
  auto _game = static_cast<UICommon::GameFile*>(game->getUnderlyingInstance(game));
  return ExtractDiscDetails::ExtractSafe(*_game, path);
}

EXPORT dol_Util* dol_Util_newInterface()
{
  auto iface = static_cast<dol_Util*>(interop_calloc(1, sizeof(dol_Util)));
  iface->verifyDisc = dol_Util_verifyDisc;
  iface->extractDisc = dol_Util_extractDisc;

  return iface;
}
