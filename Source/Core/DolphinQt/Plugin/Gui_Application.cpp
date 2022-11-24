#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Application.h"

#include <QAbstractEventDispatcher>
#include <QApplication>

#include "Common/FileUtil.h"
#include "Common/MsgHandler.h"
#include "Core/Core.h"

bool QtMsgAlertHandler(const char* caption, const char* text, bool yes_no, Common::MsgType style);

struct App
{
  QApplication* app;
  bool hasExited;
};
static App _instance;

struct QuitEventFilter : QObject
{
  bool eventFilter(QObject* watched, QEvent* event) override
  {
    if (event->type() == QEvent::Quit)
    {
      _instance.hasExited = true;
      return true;
    }
    return false;
  }
};

static void dol_Gui_Application_setOrganizationDomain(const char* orgDomain)
{
  QApplication::setOrganizationDomain(QString::fromUtf8(orgDomain));
}

static void dol_Gui_Application_setOrganizationName(const char* orgName)
{
  QApplication::setOrganizationName(QString::fromUtf8(orgName));
}

static void dol_Gui_Application_setApplicationName(const char* application)
{
  QApplication::setApplicationName(QString::fromUtf8(application));
}

static void dol_Gui_Application_setApplicationVersion(const char* version)
{
  QApplication::setApplicationVersion(QString::fromUtf8(version));
}

static void dol_Gui_Application_setApplicationDisplayName(const char* name)
{
  QApplication::setApplicationDisplayName(QString::fromUtf8(name));
}

static void dol_Gui_Application_addLibraryPath(const char* path)
{
  QApplication::addLibraryPath(QString::fromUtf8(path));
}

static void dol_Gui_Application_setExeDirectory(const char* path)
{
  File::SetExeDirectory(path);
}

static void dol_Gui_Application_init()
{
  QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);

  _instance.app = new QApplication(__argc, __argv);
  _instance.app->installEventFilter(new QuitEventFilter);

  Common::RegisterMsgAlertHandler(QtMsgAlertHandler);
  QObject::connect(QAbstractEventDispatcher::instance(), &QAbstractEventDispatcher::aboutToBlock,
                   _instance.app, &Core::HostDispatchJobs);
}

static void dol_Gui_Application_shutdown()
{
  delete _instance.app;
}

static bool dol_Gui_Application_hasExited()
{
  return _instance.hasExited;
}

static bool dol_Gui_Application_processEvents3()
{
  return QApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents);
}

EXPORT dol_Gui_Application* dol_Gui_Application_newInterface()
{
  auto iface = static_cast<dol_Gui_Application*>(interop_calloc(1, sizeof(dol_Gui_Application)));
  iface->setOrganizationDomain = dol_Gui_Application_setOrganizationDomain;
  iface->setOrganizationName = dol_Gui_Application_setOrganizationName;
  iface->setApplicationName = dol_Gui_Application_setApplicationName;
  iface->setApplicationVersion = dol_Gui_Application_setApplicationVersion;
  iface->setApplicationDisplayName = dol_Gui_Application_setApplicationDisplayName;
  iface->addLibraryPath = dol_Gui_Application_addLibraryPath;
  iface->setExeDirectory = dol_Gui_Application_setExeDirectory;
  iface->init = dol_Gui_Application_init;
  iface->shutdown = dol_Gui_Application_shutdown;
  iface->hasExited = dol_Gui_Application_hasExited;
  iface->processEvents3 = dol_Gui_Application_processEvents3;

  return iface;
}
