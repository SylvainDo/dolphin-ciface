#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_Q_Color
{
  int r;
  int g;
  int b;
  int a;
};

struct dol_Gui_Q_CommonDialogs
{
  void (*about)(void* parent, const char* title, const char* text);
  int (*critical)(void* parent, const char* title, const char* text, int buttons,
                  int defaultButton);
  int (*information)(void* parent, const char* title, const char* text, int buttons,
                     int defaultButton);
  int (*question)(void* parent, const char* title, const char* text, int buttons,
                  int defaultButton);
  int (*warning)(void* parent, const char* title, const char* text, int buttons, int defaultButton);
  dol_Gui_Q_Color (*getColor)(dol_Gui_Q_Color initial, void* parent, const char* title,
                              int options);
  double (*getDouble)(void* parent, const char* title, const char* label, double value,
                      double minValue, double maxValue, int decimals, bool* ok, double step);
  int (*getInt)(void* parent, const char* title, const char* label, int value, int minValue,
                int maxValue, int step, bool* ok);
  char* (*getItem)(void* parent, const char* title, const char* label, const char** items,
                   int numItems, int current, bool editable, bool* ok);
  char* (*getMultiLineText)(void* parent, const char* title, const char* label, const char* text,
                            bool* ok);
  char* (*getText)(void* parent, const char* title, const char* label, int echo, const char* text,
                   bool* ok);
  char* (*getExistingDirectory)(void* parent, const char* caption, const char* dir, int options);
  char* (*getOpenFileName)(void* parent, const char* caption, const char* dir, const char* filter,
                           char** selectedFilter, int options);
  char** (*getOpenFileNames)(void* parent, const char* caption, const char* dir, const char* filter,
                             char** selectedFilter, int options, int* numPaths);
  char* (*getSaveFileName)(void* parent, const char* caption, const char* dir, const char* filter,
                           char** selectedFilter, int options);
};

typedef dol_Gui_Q_CommonDialogs* (*dol_Gui_Q_CommonDialogs_newInterface_t)(void);

#ifdef __cplusplus
}
#endif
