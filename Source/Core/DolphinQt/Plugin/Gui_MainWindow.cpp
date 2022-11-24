#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_MainWindow.h"

#include "Core/Core.h"
#include "DolphinQt/MainWindow.h"

static MainWindow* _instance;

static void dol_Gui_MainWindow_init()
{
  _instance = new MainWindow({}, {});
}

static void dol_Gui_MainWindow_shutdown()
{
  delete _instance;
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

EXPORT dol_Gui_MainWindow* dol_Gui_MainWindow_newInterface()
{
  auto iface = static_cast<dol_Gui_MainWindow*>(interop_calloc(1, sizeof(dol_Gui_MainWindow)));
  iface->init = dol_Gui_MainWindow_init;
  iface->shutdown = dol_Gui_MainWindow_shutdown;
  iface->show = dol_Gui_MainWindow_show;
  iface->startGame1 = dol_Gui_MainWindow_startGame1;
  iface->setResetCallback = dol_Gui_MainWindow_setResetCallback;
  iface->setEmulationStateChangedCallback = dol_Gui_MainWindow_setEmulationStateChangedCallback;

  return iface;
}
