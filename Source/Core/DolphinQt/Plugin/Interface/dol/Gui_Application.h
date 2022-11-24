#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_Application
{
  void (*setOrganizationDomain)(const char* orgDomain);
  void (*setOrganizationName)(const char* orgName);
  void (*setApplicationName)(const char* application);
  void (*setApplicationVersion)(const char* version);
  void (*setApplicationDisplayName)(const char* name);
  void (*addLibraryPath)(const char* path);
  void (*setExeDirectory)(const char* path);
  void (*init)(void);
  void (*shutdown)(void);
  bool (*hasExited)(void);
  bool (*processEvents3)(void);
};

typedef dol_Gui_Application* (*dol_Gui_Application_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
