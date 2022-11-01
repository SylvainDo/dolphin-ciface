#include "Export.h"
#include "InteropUtil.h"

#include "Interface/dol/Alloc.h"
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Pad.h"

#include "Core/HW/GCPad.h"
#include "InputCommon/GCPadStatus.h"

static bool dolPad_isInitialized()
{
  return Pad::IsInitialized();
}

static dolGCPadStatus dolPad_getStatus(int pad_num)
{
  auto status = Pad::GetStatus(pad_num);
  dolGCPadStatus status2;
  memcpy(&status2, &status, sizeof status);
  return status2;
}

static void dolPad_rumble(int pad_num, dolControlState strength)
{
  Pad::Rumble(pad_num, strength);
}

static void dolPad_resetRumble(int pad_num)
{
  Pad::ResetRumble(pad_num);
}

static bool dolPad_getMicButton(int pad_num)
{
  return Pad::GetMicButton(pad_num);
}

EXPORT dolPad* dolPad_newInterface()
{
  auto iface = static_cast<dolPad*>(interop_calloc(1, sizeof(dolPad)));
  iface->isInitialized = dolPad_isInitialized;
  iface->getStatus = dolPad_getStatus;
  iface->rumble = dolPad_rumble;
  iface->resetRumble = dolPad_resetRumble;
  iface->getMicButton = dolPad_getMicButton;

  return iface;
}
