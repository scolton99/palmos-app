#include <PalmOS.h>

#ifdef __GNUC__
#include "Callback.h"
#endif

#include "Events.h"
#include "ResourceIDs.h"

static Boolean HelloWorldFormHandleEvent(EventPtr event) {
  Boolean handled = false;

  #ifdef __GNUC__
    CALLBACK_PROLOGUE
  #endif

  MemHandleNew(1000);

  switch (event->eType) {
  case ctlSelectEvent: // A control button was pressed and released
    FrmAlert(HelloWorldAlert);
    handled = true;
    break;

  case frmOpenEvent:
    FrmDrawForm(FrmGetActiveForm());
    handled = true;
    break;

  case menuEvent:
    if (event->data.menu.itemID == FirstBeep)
      SndPlaySystemSound(sndInfo);
    handled = true;
    break;

  default:
    break;
  }

  #ifdef __GNUC__
    CALLBACK_EPILOGUE
  #endif

  return handled;
}

Boolean ApplicationHandleEvent(EventPtr event) {
  FormPtr frm;
  UInt16 formId;
  Boolean handled = false;

  if (event->eType == frmLoadEvent) {
    // Load the form resource specified in the event then activate it
    formId = event->data.frmLoad.formID;
    frm = FrmInitForm(formId);
    FrmSetActiveForm(frm);

    // Set the event handler for the form. The handler of the currently
    // active form is called by FrmDispatchEvent each time it is called
    switch (formId) {
    case HelloWorldForm:
      FrmSetEventHandler(frm, HelloWorldFormHandleEvent);
      break;
    }

    handled = true;
  }

  return handled;
}