#include "Export.h"
#include "PluginUtil.h"
using namespace PluginUtil;

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_MainWindow.h"

#include "Core/Core.h"
#include "DolphinQt/MainWindow.h"

#include <QMenu>
#include <QMenuBar>

static MainWindow* _instance;

static void dol_Gui_MainWindow_init()
{
  _instance = new MainWindow({}, {});
}

static void dol_Gui_MainWindow_shutdown()
{
  delete _instance;
}

static void dol_Gui_MainWindow_setIcon(const char* filename)
{
  _instance->setWindowIcon(QIcon(QString::fromUtf8(filename)));
}

static void dol_Gui_MainWindow_show()
{
  _instance->Show();
}

static void dol_Gui_MainWindow_startGame1(const char* path)
{
  _instance->StartGame(BootParameters::GenerateFromFile(path));
}

static void dol_Gui_MainWindow_setResetCallback(void (*callback)(void* userdata), void* userdata)
{
  _instance->SetResetCallback([callback, userdata]() { callback(userdata); });
}

static void dol_Gui_MainWindow_setEmulationStateChangedCallback(
    void (*callback)(dol_Core_State state, void* userdata), void* userdata)
{
  _instance->SetEmulationStateChangedCallback([callback, userdata](Core::State state) {
    callback(static_cast<dol_Core_State>(state), userdata);
  });
}

static void dol_Gui_MainWindow_close()
{
  _instance->close();
}

static void* dol_Gui_MainWindow_asWidget()
{
  return static_cast<QWidget*>(_instance);
}

dol_Gui_Q_MenuBar* dol_Gui_Q_MenuBar_createFromInstance(QMenuBar* menuBar);
dol_Gui_Q_Menu* dol_Gui_Q_Menu_createFromInstance(QMenu* menu);

static dol_Gui_Q_MenuBar* dol_Gui_MainWindow_getMenuBar()
{
  return dol_Gui_Q_MenuBar_createFromInstance(_instance->menuBar());
}

static dol_Gui_Q_Menu* dol_Gui_MainWindow_findMenu(const char* title)
{
  const auto menus = _instance->menuBar()->findChildren<QMenu*>();
  auto title_qs = toQString(title);
  for (const auto menu : menus)
  {
    if (menu->title() == title_qs)
      return dol_Gui_Q_Menu_createFromInstance(menu);
  }
  title_qs = QStringLiteral("%1Menu").arg(title_qs);
  for (const auto menu : menus)
  {
    if (menu->objectName() == title_qs)
      return dol_Gui_Q_Menu_createFromInstance(menu);
  }
  return nullptr;
}

EXPORT dol_Gui_MainWindow* dol_Gui_MainWindow_newInterface()
{
  auto iface = static_cast<dol_Gui_MainWindow*>(interop_calloc(1, sizeof(dol_Gui_MainWindow)));
  iface->init = dol_Gui_MainWindow_init;
  iface->shutdown = dol_Gui_MainWindow_shutdown;
  iface->setIcon = dol_Gui_MainWindow_setIcon;
  iface->show = dol_Gui_MainWindow_show;
  iface->startGame1 = dol_Gui_MainWindow_startGame1;
  iface->setResetCallback = dol_Gui_MainWindow_setResetCallback;
  iface->setEmulationStateChangedCallback = dol_Gui_MainWindow_setEmulationStateChangedCallback;
  iface->close = dol_Gui_MainWindow_close;
  iface->asWidget = dol_Gui_MainWindow_asWidget;
  iface->getMenuBar = dol_Gui_MainWindow_getMenuBar;
  iface->findMenu = dol_Gui_MainWindow_findMenu;

  return iface;
}
