#include "Export.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Pad.h"

#include "Core/HW/GCPad.h"
#include "InputCommon/GCPadStatus.h"

static void dol_Pad_getStatus(int pad_num, dol_GCPadStatus* status)
{
  const auto status2 = Pad::GetStatus(pad_num);
  memcpy(status, &status2, sizeof status2);
}

static void dol_Pad_rumble(int pad_num, dol_ControlState strength)
{
  Pad::Rumble(pad_num, strength);
}

static void dol_Pad_resetRumble(int pad_num)
{
  Pad::ResetRumble(pad_num);
}

EXPORT dol_Pad* dol_Pad_newInterface()
{
  auto iface = static_cast<dol_Pad*>(interop_calloc(1, sizeof(dol_Pad)));
  iface->getStatus = dol_Pad_getStatus;
  iface->rumble = dol_Pad_rumble;
  iface->resetRumble = dol_Pad_resetRumble;

  return iface;
}
