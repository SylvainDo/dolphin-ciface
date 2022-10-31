#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Core.h"

#include "Core/Core.h"

static bool dolCore_getIsThrottlerTempDisabled()
{
  return Core::GetIsThrottlerTempDisabled();
}

static void dolCore_setIsThrottlerTempDisabled(bool disable)
{
  Core::SetIsThrottlerTempDisabled(disable);
}

static double dolCore_getActualEmulationSpeed()
{
  return Core::GetActualEmulationSpeed();
}

static void dolCore_stop()
{
  Core::Stop();
}

static void dolCore_shutdown()
{
  Core::Shutdown();
}

static void dolCore_declareAsCPUThread()
{
  Core::DeclareAsCPUThread();
}

static void dolCore_undeclareAsCPUThread()
{
  Core::UndeclareAsCPUThread();
}

static void dolCore_declareAsGPUThread()
{
  Core::DeclareAsGPUThread();
}

static void dolCore_undeclareAsGPUThread()
{
  Core::UndeclareAsGPUThread();
}

static bool dolCore_isRunning()
{
  return Core::IsRunning();
}

static bool dolCore_isRunningAndStarted()
{
  return Core::IsRunningAndStarted();
}

static bool dolCore_isRunningInCurrentThread()
{
  return Core::IsRunningInCurrentThread();
}

static bool dolCore_isCPUThread()
{
  return Core::IsCPUThread();
}

static bool dolCore_isGPUThread()
{
  return Core::IsGPUThread();
}

static bool dolCore_wantsDeterminism()
{
  return Core::WantsDeterminism();
}

static void dolCore_setState(dolCoreState state)
{
  Core::SetState(static_cast<Core::State>(state));
}

static dolCoreState dolCore_getState()
{
  return static_cast<dolCoreState>(Core::GetState());
}

static void dolCore_saveScreenShot1()
{
  Core::SaveScreenShot();
}

static void dolCore_saveScreenShot2(const char* name)
{
  Core::SaveScreenShot(name);
}

static void dolCore_displayMessage(const char* message, int time_in_ms)
{
  Core::DisplayMessage(message, time_in_ms);
}

static void dolCore_runAsCPUThread(void (*function)(void* userdata), void* userdata)
{
  Core::RunAsCPUThread([function, userdata]() { function(userdata); });
}

static void dolCore_runOnCPUThread(void (*function)(void* userdata), void* userdata,
                                   bool wait_for_completion)
{
  Core::RunOnCPUThread([function, userdata]() { function(userdata); }, wait_for_completion);
}

static int dolCore_addOnStateChangedCallback(void (*callback)(dolCoreState state, void* userdata),
                                             void* userdata)
{
  return Core::AddOnStateChangedCallback([callback, userdata](Core::State state) {
    callback(static_cast<dolCoreState>(state), userdata);
  });
}

static bool dolCore_removeOnStateChangedCallback(int* handle)
{
  return Core::RemoveOnStateChangedCallback(handle);
}

static void dolCore_updateWantDeterminism(bool initial)
{
  Core::UpdateWantDeterminism(initial);
}

static void dolCore_queueHostJob(void (*job)(void* userdata), void* userdata, bool run_during_stop)
{
  Core::QueueHostJob([job, userdata]() { job(userdata); }, run_during_stop);
}

static void dolCore_hostDispatchJobs()
{
  Core::HostDispatchJobs();
}

static void dolCore_doFrameStep()
{
  Core::DoFrameStep();
}

static void dolCore_updateInputGate(bool require_focus, bool require_full_focus)
{
  Core::UpdateInputGate(require_focus, require_full_focus);
}

EXPORT dolCore* dolCore_newInterface()
{
  auto iface = static_cast<dolCore*>(interop_calloc(1, sizeof(dolCore)));
  iface->getIsThrottlerTempDisabled = dolCore_getIsThrottlerTempDisabled;
  iface->setIsThrottlerTempDisabled = dolCore_setIsThrottlerTempDisabled;
  iface->getActualEmulationSpeed = dolCore_getActualEmulationSpeed;
  iface->stop = dolCore_stop;
  iface->shutdown = dolCore_shutdown;
  iface->declareAsCPUThread = dolCore_declareAsCPUThread;
  iface->undeclareAsCPUThread = dolCore_undeclareAsCPUThread;
  iface->declareAsGPUThread = dolCore_declareAsGPUThread;
  iface->undeclareAsGPUThread = dolCore_undeclareAsGPUThread;
  iface->isRunning = dolCore_isRunning;
  iface->isRunningAndStarted = dolCore_isRunningAndStarted;
  iface->isRunningInCurrentThread = dolCore_isRunningInCurrentThread;
  iface->isCPUThread = dolCore_isCPUThread;
  iface->isGPUThread = dolCore_isGPUThread;
  iface->wantsDeterminism = dolCore_wantsDeterminism;
  iface->setState = dolCore_setState;
  iface->getState = dolCore_getState;
  iface->saveScreenShot1 = dolCore_saveScreenShot1;
  iface->saveScreenShot2 = dolCore_saveScreenShot2;
  iface->displayMessage = dolCore_displayMessage;
  iface->runAsCPUThread = dolCore_runAsCPUThread;
  iface->runOnCPUThread = dolCore_runOnCPUThread;
  iface->addOnStateChangedCallback = dolCore_addOnStateChangedCallback;
  iface->removeOnStateChangedCallback = dolCore_removeOnStateChangedCallback;
  iface->updateWantDeterminism = dolCore_updateWantDeterminism;
  iface->queueHostJob = dolCore_queueHostJob;
  iface->hostDispatchJobs = dolCore_hostDispatchJobs;
  iface->doFrameStep = dolCore_doFrameStep;
  iface->updateInputGate = dolCore_updateInputGate;

  return iface;
}
