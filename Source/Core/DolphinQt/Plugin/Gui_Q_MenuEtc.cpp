#include "Export.h"
#include "PluginUtil.h"
using namespace PluginUtil;

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Q_MenuEtc.h"

#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>

struct Q_Action_Data
{
  QAction* action;
  QMetaObject::Connection toggledConnection;
  std::function<void(bool)> toggled;
  QMetaObject::Connection triggeredConnection;
  std::function<void(bool)> triggered;
};

dol_Gui_Q_Menu* dol_Gui_Q_Menu_createFromInstance(QMenu* menu);
dol_Gui_Q_Action* dol_Gui_Q_Action_createFromInstance(QAction* action);

namespace MenuBar
{

#define ThisMenuBar static_cast<QMenuBar*>(_this->data)

dol_Gui_Q_Menu* addMenu(dol_Gui_Q_MenuBar* _this, const char* title)
{
  return dol_Gui_Q_Menu_createFromInstance(ThisMenuBar->addMenu(toQString(title)));
}

#undef ThisMenuBar

}  // namespace MenuBar

dol_Gui_Q_MenuBar* dol_Gui_Q_MenuBar_createFromInstance(QMenuBar* menuBar)
{
  auto iface = static_cast<dol_Gui_Q_MenuBar*>(interop_calloc(1, sizeof(dol_Gui_Q_MenuBar)));
  iface->data = menuBar;
  iface->addMenu = MenuBar::addMenu;

  return iface;
}

namespace Menu
{

#define ThisMenu static_cast<QMenu*>(_this->data)

dol_Gui_Q_Action* addSeparator(dol_Gui_Q_Menu* _this)
{
  return dol_Gui_Q_Action_createFromInstance(ThisMenu->addSeparator());
}

dol_Gui_Q_Menu* addMenu1(dol_Gui_Q_Menu* _this, const char* title)
{
  return dol_Gui_Q_Menu_createFromInstance(ThisMenu->addMenu(toQString(title)));
}

dol_Gui_Q_Menu* addMenu2(dol_Gui_Q_Menu* _this, const char* iconFileName, const char* title)
{
  return dol_Gui_Q_Menu_createFromInstance(
      ThisMenu->addMenu(QIcon(toQString(iconFileName)), toQString(title)));
}

dol_Gui_Q_Action* addAction1(dol_Gui_Q_Menu* _this, const char* text)
{
  return dol_Gui_Q_Action_createFromInstance(ThisMenu->addAction(toQString(text)));
}

dol_Gui_Q_Action* addAction2(dol_Gui_Q_Menu* _this, const char* iconFileName, const char* text)
{
  return dol_Gui_Q_Action_createFromInstance(
      ThisMenu->addAction(QIcon(toQString(iconFileName)), toQString(text)));
}

bool isEnabled(dol_Gui_Q_Menu* _this)
{
  return ThisMenu->isEnabled();
}

void setEnabled(dol_Gui_Q_Menu* _this, bool enabled)
{
  ThisMenu->setEnabled(enabled);
}

bool isVisible(dol_Gui_Q_Menu* _this)
{
  return ThisMenu->isVisible();
}

void setVisible(dol_Gui_Q_Menu* _this, bool visible)
{
  ThisMenu->setVisible(visible);
}

void setIcon(dol_Gui_Q_Menu* _this, const char* iconFileName)
{
  ThisMenu->setIcon(QIcon(toQString(iconFileName)));
}

void setTitle(dol_Gui_Q_Menu* _this, const char* title)
{
  ThisMenu->setTitle(toQString(title));
}

#undef ThisMenu

}  // namespace Menu

dol_Gui_Q_Menu* dol_Gui_Q_Menu_createFromInstance(QMenu* menu)
{
  auto iface = static_cast<dol_Gui_Q_Menu*>(interop_calloc(1, sizeof(dol_Gui_Q_Menu)));
  iface->data = menu;
  iface->addSeparator = Menu::addSeparator;
  iface->addMenu1 = Menu::addMenu1;
  iface->addMenu2 = Menu::addMenu2;
  iface->addAction1 = Menu::addAction1;
  iface->addAction2 = Menu::addAction2;
  iface->isEnabled = Menu::isEnabled;
  iface->setEnabled = Menu::setEnabled;
  iface->isVisible = Menu::isVisible;
  iface->setVisible = Menu::setVisible;
  iface->setIcon = Menu::setIcon;
  iface->setTitle = Menu::setTitle;

  return iface;
}

namespace Action
{

#define ThisAction static_cast<QAction*>(static_cast<Q_Action_Data*>(_this->data)->action)

void destroy(dol_Gui_Q_Action* _this)
{
  auto data = static_cast<Q_Action_Data*>(_this->data);
  if (data->toggled)
  {
    QObject::disconnect(data->toggledConnection);
    data->toggled = {};
  }
  if (data->triggered)
  {
    QObject::disconnect(data->triggeredConnection);
    data->triggered = {};
  }
}

void setToggledCallback(dol_Gui_Q_Action* _this, void (*callback)(bool checked, void* userdata),
                        void* userdata)
{
  auto data = static_cast<Q_Action_Data*>(_this->data);
  data->toggled = [callback, userdata](bool checked) { callback(checked, userdata); };
  data->toggledConnection = QObject::connect(data->action, &QAction::toggled, [data](bool checked) {
    if (data->toggled)
      data->toggled(checked);
  });
}

void setTriggeredCallback(dol_Gui_Q_Action* _this, void (*callback)(bool checked, void* userdata),
                          void* userdata)
{
  auto data = static_cast<Q_Action_Data*>(_this->data);
  data->triggered = [callback, userdata](bool checked) { callback(checked, userdata); };
  data->triggeredConnection =
      QObject::connect(data->action, &QAction::triggered, [data](bool checked) {
        if (data->triggered)
          data->triggered(checked);
      });
}

bool isEnabled(dol_Gui_Q_Action* _this)
{
  return ThisAction->isEnabled();
}

void setEnabled(dol_Gui_Q_Action* _this, bool enabled)
{
  ThisAction->setEnabled(enabled);
}

bool isVisible(dol_Gui_Q_Action* _this)
{
  return ThisAction->isVisible();
}

void setVisible(dol_Gui_Q_Action* _this, bool visible)
{
  ThisAction->setVisible(visible);
}

bool isCheckable(dol_Gui_Q_Action* _this)
{
  return ThisAction->isCheckable();
}

void setCheckable(dol_Gui_Q_Action* _this, bool checkable)
{
  ThisAction->setCheckable(checkable);
}

bool isChecked(dol_Gui_Q_Action* _this)
{
  return ThisAction->isChecked();
}

void setChecked(dol_Gui_Q_Action* _this, bool checked)
{
  ThisAction->setChecked(checked);
}

void setIcon(dol_Gui_Q_Action* _this, const char* iconFileName)
{
  ThisAction->setIcon(QIcon(toQString(iconFileName)));
}

void setText(dol_Gui_Q_Action* _this, const char* text)
{
  ThisAction->setText(toQString(text));
}

void setShortcut(dol_Gui_Q_Action* _this, const char* shortcut)
{
  ThisAction->setShortcut(QKeySequence(toQString(shortcut)));
}

#undef ThisAction

}  // namespace Action

dol_Gui_Q_Action* dol_Gui_Q_Action_createFromInstance(QAction* action)
{
  auto iface = static_cast<dol_Gui_Q_Action*>(interop_calloc(1, sizeof(dol_Gui_Q_Action)));
  iface->data = new Q_Action_Data{.action = action};
  iface->destroy = Action::destroy;
  iface->setToggledCallback = Action::setToggledCallback;
  iface->setTriggeredCallback = Action::setTriggeredCallback;
  iface->isEnabled = Action::isEnabled;
  iface->setEnabled = Action::setEnabled;
  iface->isVisible = Action::isVisible;
  iface->setVisible = Action::setVisible;
  iface->isCheckable = Action::isCheckable;
  iface->setCheckable = Action::setCheckable;
  iface->isChecked = Action::isChecked;
  iface->setChecked = Action::setChecked;
  iface->setIcon = Action::setIcon;
  iface->setText = Action::setText;
  iface->setShortcut = Action::setShortcut;

  return iface;
}
