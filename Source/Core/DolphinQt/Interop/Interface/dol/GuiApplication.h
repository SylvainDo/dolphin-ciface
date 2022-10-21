#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dolGuiApplication
{
  void (*setOrganizationDomain)(const char* orgDomain);
  void (*setOrganizationName)(const char* orgName);
  void (*setApplicationName)(const char* application);
  void (*setApplicationVersion)(const char* version);
  void (*setApplicationDisplayName)(const char* name);
  void (*init)(void);
  void (*shutdown)(void);
  bool (*hasExited)(void);
  int (*exec)(void);
  void (*processEvents1)(void);
  void (*processEvents2)(int maxtime);
  bool (*processEvents3)(void);
};

typedef dolGuiApplication* (*dolGuiApplication_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
