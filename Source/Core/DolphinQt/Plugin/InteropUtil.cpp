#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;

namespace InteropUtil
{

char* dupStdString(const std::string& src)
{
  auto v = interop_malloc(src.size() + 1);
  memcpy(v, src.c_str(), src.size() + 1);
  return static_cast<char*>(v);
}

}  // namespace InteropUtil
