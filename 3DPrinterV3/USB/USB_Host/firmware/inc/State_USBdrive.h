#ifndef STATE_USBDRIVE
#define STATE_USBDRIVE


typedef enum{READY_USBDRIVE = 1, NOT_READY_USBDRIVE = 0} usbstates;

void createState_USBdrive(void);
void setState_USBdrive(usbstates state);
usbstates getState_USBdrive(void);

#endif
