#include <PalmOS.h>

#include "ResourceIDs.h"
#include "Events.h"

static Err StartApplication(void) {
  FrmGotoForm(HelloWorldForm);
  return 0;
}

static void StopApplication(void) {

}

static void EventLoop(void) {
  EventType event;
  UInt16 error;

  do {
    EvtGetEvent(&event, evtWaitForever);
    if (!SysHandleEvent(&event))
      if (!MenuHandleEvent(0, &event, &error))
        if (!ApplicationHandleEvent(&event))
          FrmDispatchEvent(&event);
  } while (event.eType != appStopEvent);
}

UInt32 PilotMain(UInt16 launchCode, void *cmdPBP, UInt16 launchFlags) {
  Err err;

  if (launchCode == sysAppLaunchCmdNormalLaunch) {
    if ((err = StartApplication()) == 0) {
      EventLoop();
      StopApplication();
    }
  }

  return err;

}

