#include "PluginUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;

#include <cstring>

namespace PluginUtil
{

char* dupStdString(const std::string& src)
{
  auto v = interop_malloc(src.size() + 1);
  memcpy(v, src.c_str(), src.size() + 1);
  return static_cast<char*>(v);
}

char* dupQString(const QString& str)
{
  return PluginUtil::dupStdString(str.toStdString());
}

QString toQString(const char* str)
{
  return QString::fromUtf8(str);
}

}  // namespace PluginUtil
