#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Core.h"

#include "Core/Core.h"

static bool dol_Core_getIsThrottlerTempDisabled()
{
  return Core::GetIsThrottlerTempDisabled();
}

static void dol_Core_setIsThrottlerTempDisabled(bool disable)
{
  Core::SetIsThrottlerTempDisabled(disable);
}

static double dol_Core_getActualEmulationSpeed()
{
  return Core::GetActualEmulationSpeed();
}

static void dol_Core_stop()
{
  Core::Stop();
}

static void dol_Core_shutdown()
{
  Core::Shutdown();
}

static void dol_Core_declareAsCPUThread()
{
  Core::DeclareAsCPUThread();
}

static void dol_Core_undeclareAsCPUThread()
{
  Core::UndeclareAsCPUThread();
}

static void dol_Core_declareAsGPUThread()
{
  Core::DeclareAsGPUThread();
}

static void dol_Core_undeclareAsGPUThread()
{
  Core::UndeclareAsGPUThread();
}

static bool dol_Core_isRunning()
{
  return Core::IsRunning();
}

static bool dol_Core_isRunningAndStarted()
{
  return Core::IsRunningAndStarted();
}

static bool dol_Core_isRunningInCurrentThread()
{
  return Core::IsRunningInCurrentThread();
}

static bool dol_Core_isCPUThread()
{
  return Core::IsCPUThread();
}

static bool dol_Core_isGPUThread()
{
  return Core::IsGPUThread();
}

static bool dol_Core_wantsDeterminism()
{
  return Core::WantsDeterminism();
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

static void dol_Core_displayMessage(const char* message, int time_in_ms)
{
  Core::DisplayMessage(message, time_in_ms);
}

static void dol_Core_runAsCPUThread(void (*function)(void* userdata), void* userdata)
{
  Core::RunAsCPUThread([function, userdata]() { function(userdata); });
}

static void dol_Core_runOnCPUThread(void (*function)(void* userdata), void* userdata,
                                    bool wait_for_completion)
{
  Core::RunOnCPUThread([function, userdata]() { function(userdata); }, wait_for_completion);
}

static int dol_Core_addOnStateChangedCallback(void (*callback)(dol_Core_State state,
                                                               void* userdata),
                                              void* userdata)
{
  return Core::AddOnStateChangedCallback([callback, userdata](Core::State state) {
    callback(static_cast<dol_Core_State>(state), userdata);
  });
}

static bool dol_Core_removeOnStateChangedCallback(int* handle)
{
  return Core::RemoveOnStateChangedCallback(handle);
}

static void dol_Core_updateWantDeterminism(bool initial)
{
  Core::UpdateWantDeterminism(initial);
}

static void dol_Core_queueHostJob(void (*job)(void* userdata), void* userdata, bool run_during_stop)
{
  Core::QueueHostJob([job, userdata]() { job(userdata); }, run_during_stop);
}

static void dol_Core_hostDispatchJobs()
{
  Core::HostDispatchJobs();
}

static void dol_Core_doFrameStep()
{
  Core::DoFrameStep();
}

static void dol_Core_updateInputGate(bool require_focus, bool require_full_focus)
{
  Core::UpdateInputGate(require_focus, require_full_focus);
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
  iface->getIsThrottlerTempDisabled = dol_Core_getIsThrottlerTempDisabled;
  iface->setIsThrottlerTempDisabled = dol_Core_setIsThrottlerTempDisabled;
  iface->getActualEmulationSpeed = dol_Core_getActualEmulationSpeed;
  iface->stop = dol_Core_stop;
  iface->shutdown = dol_Core_shutdown;
  iface->declareAsCPUThread = dol_Core_declareAsCPUThread;
  iface->undeclareAsCPUThread = dol_Core_undeclareAsCPUThread;
  iface->declareAsGPUThread = dol_Core_declareAsGPUThread;
  iface->undeclareAsGPUThread = dol_Core_undeclareAsGPUThread;
  iface->isRunning = dol_Core_isRunning;
  iface->isRunningAndStarted = dol_Core_isRunningAndStarted;
  iface->isRunningInCurrentThread = dol_Core_isRunningInCurrentThread;
  iface->isCPUThread = dol_Core_isCPUThread;
  iface->isGPUThread = dol_Core_isGPUThread;
  iface->wantsDeterminism = dol_Core_wantsDeterminism;
  iface->setState = dol_Core_setState;
  iface->getState = dol_Core_getState;
  iface->saveScreenShot1 = dol_Core_saveScreenShot1;
  iface->saveScreenShot2 = dol_Core_saveScreenShot2;
  iface->displayMessage = dol_Core_displayMessage;
  iface->runAsCPUThread = dol_Core_runAsCPUThread;
  iface->runOnCPUThread = dol_Core_runOnCPUThread;
  iface->addOnStateChangedCallback = dol_Core_addOnStateChangedCallback;
  iface->removeOnStateChangedCallback = dol_Core_removeOnStateChangedCallback;
  iface->updateWantDeterminism = dol_Core_updateWantDeterminism;
  iface->queueHostJob = dol_Core_queueHostJob;
  iface->hostDispatchJobs = dol_Core_hostDispatchJobs;
  iface->doFrameStep = dol_Core_doFrameStep;
  iface->updateInputGate = dol_Core_updateInputGate;
  iface->setFrameHandlerEnabled = dol_Core_setFrameHandlerEnabled;
  iface->getFrameHandlerToken = dol_Core_getFrameHandlerToken;
  iface->setFrameHandlerToken = dol_Core_setFrameHandlerToken;

  return iface;
}
