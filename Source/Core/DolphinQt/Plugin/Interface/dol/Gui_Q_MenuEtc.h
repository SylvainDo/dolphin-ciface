#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct dol_Gui_Q_Menu;
struct dol_Gui_Q_Action;

struct dol_Gui_Q_MenuBar
{
  void* data;
  dol_Gui_Q_Menu* (*addMenu)(dol_Gui_Q_MenuBar* _this, const char* title);
};

struct dol_Gui_Q_Menu
{
  void* data;
  dol_Gui_Q_Action* (*addSeparator)(dol_Gui_Q_Menu* _this);
  dol_Gui_Q_Menu* (*addMenu1)(dol_Gui_Q_Menu* _this, const char* title);
  dol_Gui_Q_Menu* (*addMenu2)(dol_Gui_Q_Menu* _this, const char* iconFileName, const char* title);
  dol_Gui_Q_Action* (*addAction1)(dol_Gui_Q_Menu* _this, const char* text);
  dol_Gui_Q_Action* (*addAction2)(dol_Gui_Q_Menu* _this, const char* iconFileName,
                                  const char* text);
  bool (*isEnabled)(dol_Gui_Q_Menu* _this);
  void (*setEnabled)(dol_Gui_Q_Menu* _this, bool enabled);
  bool (*isVisible)(dol_Gui_Q_Menu* _this);
  void (*setVisible)(dol_Gui_Q_Menu* _this, bool visible);
  void (*setIcon)(dol_Gui_Q_Menu* _this, const char* iconFileName);
  void (*setTitle)(dol_Gui_Q_Menu* _this, const char* title);
};

struct dol_Gui_Q_Action
{
  void* data;
  void (*destroy)(dol_Gui_Q_Action* _this);
  void (*setToggledCallback)(dol_Gui_Q_Action* _this,
                             void (*callback)(bool checked, void* userdata), void* userdata);
  void (*setTriggeredCallback)(dol_Gui_Q_Action* _this,
                               void (*callback)(bool checked, void* userdata), void* userdata);
  bool (*isEnabled)(dol_Gui_Q_Action* _this);
  void (*setEnabled)(dol_Gui_Q_Action* _this, bool enabled);
  bool (*isVisible)(dol_Gui_Q_Action* _this);
  void (*setVisible)(dol_Gui_Q_Action* _this, bool visible);
  bool (*isCheckable)(dol_Gui_Q_Action* _this);
  void (*setCheckable)(dol_Gui_Q_Action* _this, bool checkable);
  bool (*isChecked)(dol_Gui_Q_Action* _this);
  void (*setChecked)(dol_Gui_Q_Action* _this, bool checked);
  void (*setIcon)(dol_Gui_Q_Action* _this, const char* iconFileName);
  void (*setText)(dol_Gui_Q_Action* _this, const char* text);
  void (*setShortcut)(dol_Gui_Q_Action* _this, const char* shortcut);
};

#ifdef __cplusplus
}
#endif
