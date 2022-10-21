#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Core.h"

#include "Core/Core.h"

static double dolCore_getActualEmulationSpeed()
{
  return Core::GetActualEmulationSpeed();
}

static void dolCore_shutdown()
{
  Core::Shutdown();
}

static void dolCore_displayMessage(const char* message, int time_in_ms)
{
  Core::DisplayMessage(message, time_in_ms);
}

static void dolCore_hostDispatchJobs()
{
  Core::HostDispatchJobs();
}

EXPORT dolCore* dolCore_newInterface()
{
  auto iface = static_cast<dolCore*>(interop_calloc(1, sizeof(dolCore)));
  iface->getActualEmulationSpeed = dolCore_getActualEmulationSpeed;
  iface->shutdown = dolCore_shutdown;
  iface->displayMessage = dolCore_displayMessage;
  iface->hostDispatchJobs = dolCore_hostDispatchJobs;

  return iface;
}
