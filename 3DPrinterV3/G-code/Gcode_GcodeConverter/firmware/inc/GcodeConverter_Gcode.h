#ifndef GCODECONVERTER_GCODE
#define GCODECONVERTER_GCODE

#include "Config_Gcode.h"

typedef enum {EMPTY_COMMAND,
    MOVE_COMMAND, SET_COORDINATES_COMMAND,
    GO_HOME_X_COMMAND, GO_HOME_Y_COMMAND, GO_HOME_Z_COMMAND, GO_HOME_XY_COMMAND, GO_HOME_XZ_COMMAND, GO_HOME_YZ_COMMAND, GO_HOME_XYZ_COMMAND,
    HEAT_EXTRUDER_COMMAND, HEAT_BED_COMMAND,
    WAIT_HEAT_EXTRUDER_COMMAND, WAIT_HEAT_BED_COMMAND} commandType_Gcode;


typedef struct
{
    commandType_Gcode type;
    float X;
    float Y;
    float Z;
    float E;
    float F;
    float extrT;
    float bedT;
} convertedCommand_Gcode;

void createGcodeConverter_Gcode(void);

const convertedCommand_Gcode getConvertedCommand_Gcode(void);

void convertCommand_Gcode(const char* commandString);

#endif
