#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/GuiMainWindow.h"

#include "DolphinQt/MainWindow.h"

static MainWindow* _instance;

static void dolGuiMainWindow_init()
{
  _instance = new MainWindow({}, {});
}

static void dolGuiMainWindow_shutdown()
{
  delete _instance;
}

static void dolGuiMainWindow_show()
{
  _instance->Show();
}

static bool dolGuiMainWindow_requestStop()
{
  return _instance->RequestStop();
}

static void dolGuiMainWindow_startGame1(const char* path)
{
  _instance->StartGame(BootParameters::GenerateFromFile(path));
}

EXPORT dolGuiMainWindow* dolGuiMainWindow_newInterface()
{
  auto iface = static_cast<dolGuiMainWindow*>(interop_calloc(1, sizeof(dolGuiMainWindow)));
  iface->init = dolGuiMainWindow_init;
  iface->shutdown = dolGuiMainWindow_shutdown;
  iface->show = dolGuiMainWindow_show;
  iface->requestStop = dolGuiMainWindow_requestStop;
  iface->startGame1 = dolGuiMainWindow_startGame1;

  return iface;
}
