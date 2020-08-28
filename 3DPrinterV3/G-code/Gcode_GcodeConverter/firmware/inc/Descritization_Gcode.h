#ifndef DESCRITIZATION_GCODE
#define DESCRITIZATION_GCODE

#include "Config_Gcode.h"
#include "GcodeConverter_Gcode.h"


typedef struct
{
    commandType_Gcode type;
    long Xn;
    long Yn;
    long Zn;
    long En;
    float FnXY;
    float FnZ;
    float FnE;
    float extrT;
    float bedT;
} descreteCommand_Gcode;

void createDescretization_Gcode(void);

descreteCommand_Gcode getDescreteCommand_Gcode(void);

void setDescreteCommand_Gcode(convertedCommand_Gcode convertedCommand);


#endif
