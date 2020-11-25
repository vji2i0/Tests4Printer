#ifndef VIRTUAL_PRINTERS_GCODE
#define VIRTUAL_PRINTERS_GCODE

#include "Config_Gcode.h"
#include "Buffer_Gcode.h"
#include "stdbool.h"

extern const float evaluationPeriod_Gcode;

void virtualPrintersCreate_Gcode(void);

long getCurrentX_Gcode(void);
long getCurrentY_Gcode(void);
long getCurrentZ_Gcode(void);
long getCurrentE_Gcode(void);

void sendCommandToPrinter_Gcode(command_Gcode command);

_Bool evaluatePrinter_Gcode(void);

_Bool moveComleted(void);

#endif
