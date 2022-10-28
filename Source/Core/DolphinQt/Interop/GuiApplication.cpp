#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/GuiApplication.h"

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

static void dolGuiApplication_setOrganizationDomain(const char* orgDomain)
{
  QApplication::setOrganizationDomain(QString::fromUtf8(orgDomain));
}

static void dolGuiApplication_setOrganizationName(const char* orgName)
{
  QApplication::setOrganizationName(QString::fromUtf8(orgName));
}

static void dolGuiApplication_setApplicationName(const char* application)
{
  QApplication::setApplicationName(QString::fromUtf8(application));
}

static void dolGuiApplication_setApplicationVersion(const char* version)
{
  QApplication::setApplicationVersion(QString::fromUtf8(version));
}

static void dolGuiApplication_setApplicationDisplayName(const char* name)
{
  QApplication::setApplicationDisplayName(QString::fromUtf8(name));
}

static void dolGuiApplication_addLibraryPath(const char* path)
{
  QApplication::addLibraryPath(QString::fromUtf8(path));
}

static void dolGuiApplication_setExeDirectory(const char* path)
{
  File::SetExeDirectory(path);
}

static void dolGuiApplication_init()
{
  QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);

  _instance.app = new QApplication(__argc, __argv);
  _instance.app->installEventFilter(new QuitEventFilter);

  Common::RegisterMsgAlertHandler(QtMsgAlertHandler);
  QObject::connect(QAbstractEventDispatcher::instance(), &QAbstractEventDispatcher::aboutToBlock,
                   _instance.app, &Core::HostDispatchJobs);
}

static void dolGuiApplication_shutdown()
{
  delete _instance.app;
}

static bool dolGuiApplication_hasExited()
{
  return _instance.hasExited;
}

static int dolGuiApplication_exec()
{
  return QApplication::exec();
}

static void dolGuiApplication_processEvents1()
{
  QApplication::processEvents(QEventLoop::AllEvents);
}

static void dolGuiApplication_processEvents2(int maxtime)
{
  QApplication::processEvents(QEventLoop::AllEvents, maxtime);
}

static bool dolGuiApplication_processEvents3()
{
  return QApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents);
}

EXPORT dolGuiApplication* dolGuiApplication_newInterface()
{
  auto iface = static_cast<dolGuiApplication*>(interop_calloc(1, sizeof(dolGuiApplication)));
  iface->setOrganizationDomain = dolGuiApplication_setOrganizationDomain;
  iface->setOrganizationName = dolGuiApplication_setOrganizationName;
  iface->setApplicationName = dolGuiApplication_setApplicationName;
  iface->setApplicationVersion = dolGuiApplication_setApplicationVersion;
  iface->setApplicationDisplayName = dolGuiApplication_setApplicationDisplayName;
  iface->addLibraryPath = dolGuiApplication_addLibraryPath;
  iface->setExeDirectory = dolGuiApplication_setExeDirectory;
  iface->init = dolGuiApplication_init;
  iface->shutdown = dolGuiApplication_shutdown;
  iface->hasExited = dolGuiApplication_hasExited;
  iface->exec = dolGuiApplication_exec;
  iface->processEvents1 = dolGuiApplication_processEvents1;
  iface->processEvents2 = dolGuiApplication_processEvents2;
  iface->processEvents3 = dolGuiApplication_processEvents3;

  return iface;
}
