#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Core.h"

#include "Core/Core.h"

static double dol_Core_getActualEmulationSpeed()
{
  return Core::GetActualEmulationSpeed();
}

static void dol_Core_shutdown()
{
  Core::Shutdown();
}

static bool dol_Core_isRunning()
{
  return Core::IsRunning();
}

static bool dol_Core_isRunningAndStarted()
{
  return Core::IsRunningAndStarted();
}

static void dol_Core_setState(dol_Core_State state)
{
  Core::SetState(static_cast<Core::State>(state));
}

static dol_Core_State dol_Core_getState()
{
  return static_cast<dol_Core_State>(Core::GetState());
}

static void dol_Core_saveScreenShot1()
{
  Core::SaveScreenShot();
}

static void dol_Core_saveScreenShot2(const char* name)
{
  Core::SaveScreenShot(name);
}

static void dol_Core_saveScreenShotAs(const char* filename)
{
  Core::SaveScreenShotAs(filename);
}

static void dol_Core_displayMessage(const char* message, int time_in_ms)
{
  Core::DisplayMessage(message, time_in_ms);
}

static void dol_Core_hostDispatchJobs()
{
  Core::HostDispatchJobs();
}

static void dol_Core_doFrameStep()
{
  Core::DoFrameStep();
}

static void dol_Core_setFrameHandlerEnabled(bool enabled)
{
  Core::SetFrameHandlerEnabled(enabled);
}

static bool dol_Core_getFrameHandlerToken()
{
  return Core::GetFrameHandlerToken();
}

static void dol_Core_setFrameHandlerToken(bool token)
{
  Core::SetFrameHandlerToken(token);
}

EXPORT dol_Core* dol_Core_newInterface()
{
  auto iface = static_cast<dol_Core*>(interop_calloc(1, sizeof(dol_Core)));
  iface->getActualEmulationSpeed = dol_Core_getActualEmulationSpeed;
  iface->shutdown = dol_Core_shutdown;
  iface->isRunning = dol_Core_isRunning;
  iface->isRunningAndStarted = dol_Core_isRunningAndStarted;
  iface->setState = dol_Core_setState;
  iface->getState = dol_Core_getState;
  iface->saveScreenShot1 = dol_Core_saveScreenShot1;
  iface->saveScreenShot2 = dol_Core_saveScreenShot2;
  iface->saveScreenShotAs = dol_Core_saveScreenShotAs;
  iface->displayMessage = dol_Core_displayMessage;
  iface->hostDispatchJobs = dol_Core_hostDispatchJobs;
  iface->doFrameStep = dol_Core_doFrameStep;
  iface->setFrameHandlerEnabled = dol_Core_setFrameHandlerEnabled;
  iface->getFrameHandlerToken = dol_Core_getFrameHandlerToken;
  iface->setFrameHandlerToken = dol_Core_setFrameHandlerToken;

  return iface;
}
