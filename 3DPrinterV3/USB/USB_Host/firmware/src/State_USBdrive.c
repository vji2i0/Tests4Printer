#include "State_USBdrive.h"

static usbstates state_USBdrive = NOT_READY_USBDRIVE;

void createState_USBdrive(void) {state_USBdrive = NOT_READY_USBDRIVE;}
void setState_USBdrive(usbstates state) {state_USBdrive = state;}
usbstates getState_USBdrive(void){return state_USBdrive;}

