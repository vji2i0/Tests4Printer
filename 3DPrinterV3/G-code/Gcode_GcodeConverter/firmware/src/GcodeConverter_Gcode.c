#include "GcodeConverter_Gcode.h"

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>


static convertedCommand_Gcode command;

static void setCommand (float x, float y, float z, float e, float f, float bt, float et,
                    _Bool change_x, _Bool change_y, _Bool change_z, _Bool change_e, _Bool change_f, _Bool change_bt, _Bool change_et)
{
    if (change_x) command.X = x;
    if (change_y) command.Y = y;
    if (change_z) command.Z = z;
    if (change_e) command.E = e;
    if (change_f) command.F = f;
    if (change_bt) command.bedT = bt;
    if (change_et) command.extrT = et;
}

void createGcodeConverter_Gcode(void)
{
    command.type = EMPTY_COMMAND;
    setCommand(0, 0, 0, 0, F_DEFAULT, 0, 0, true, true, true, true, true, true, true);
}


const convertedCommand_Gcode getConvertedCommand_Gcode(void) { return command; }


void convertCommand_Gcode(const char* commandString)
{
    uint8_t G=0, M=0;
    float X=0, Y=0, Z=0, E=0, F=0, T=0;
    _Bool XisChanged = false, YisChanged = false, ZisChanged = false, EisChanged = false, FisChanged = false, TisChanged = false;

    char *stringOffset;
    if ((stringOffset = strchr(commandString, 'G')) != NULL)  G = atoi(stringOffset + sizeof(uint8_t));
    if ((stringOffset = strchr(commandString, 'M')) != NULL)  M = atoi(stringOffset + sizeof(uint8_t));
    if ((stringOffset = strchr(commandString, 'X')) != NULL) {X = atof(stringOffset + sizeof(uint8_t)); XisChanged = true;}
    if ((stringOffset = strchr(commandString, 'Y')) != NULL) {Y = atof(stringOffset + sizeof(uint8_t)); YisChanged = true;}
    if ((stringOffset = strchr(commandString, 'Z')) != NULL) {Z = atof(stringOffset + sizeof(uint8_t)); ZisChanged = true;}
    if ((stringOffset = strchr(commandString, 'E')) != NULL) {E = atof(stringOffset + sizeof(uint8_t)); EisChanged = true;}
    if ((stringOffset = strchr(commandString, 'F')) != NULL) {F = atof(stringOffset + sizeof(uint8_t)); FisChanged = true;}
    if ((stringOffset = strchr(commandString, 'T')) != NULL) {T = atof(stringOffset + sizeof(uint8_t)); TisChanged = true;}

    if(G==1)   { command.type = MOVE_COMMAND;               setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, EisChanged, FisChanged, false,      false);      return; }
    if(G==92)  { command.type = SET_COORDINATES_COMMAND;    setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, EisChanged, false,      false,      false);      return; }
    if(M==140) { command.type = HEAT_BED_COMMAND;           setCommand(X, Y, Z, E, F, T, T, false,      false,      false,      false,      false,      TisChanged, false);      return; }
    if(M==104) { command.type = HEAT_EXTRUDER_COMMAND;      setCommand(X, Y, Z, E, F, T, T, false,      false,      false,      false,      false,      false,      TisChanged); return; }
    if(M==190) { command.type = WAIT_HEAT_BED_COMMAND;      setCommand(X, Y, Z, E, F, T, T, false,      false,      false,      false,      false,      TisChanged, false);      return; }
    if(M==109) { command.type = WAIT_HEAT_EXTRUDER_COMMAND; setCommand(X, Y, Z, E, F, T, T, false,      false,      false,      false,      false,      false,      TisChanged); return; }

    if(G==28 && XisChanged  && YisChanged  && ZisChanged )   { command.type = GO_HOME_XYZ_COMMAND; setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }
    if(G==28 && XisChanged  && !YisChanged && !ZisChanged)   { command.type = GO_HOME_X_COMMAND;   setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }
    if(G==28 && !XisChanged && YisChanged  && !ZisChanged)   { command.type = GO_HOME_Y_COMMAND;   setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }
    if(G==28 && !XisChanged && !YisChanged && ZisChanged )   { command.type = GO_HOME_Z_COMMAND;   setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }
    if(G==28 && XisChanged  && YisChanged  && !ZisChanged)   { command.type = GO_HOME_XY_COMMAND;  setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }
    if(G==28 && XisChanged  && !YisChanged && ZisChanged )   { command.type = GO_HOME_XZ_COMMAND;  setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }
    if(G==28 && !XisChanged && YisChanged  && ZisChanged )   { command.type = GO_HOME_YZ_COMMAND;  setCommand(X, Y, Z, E, F, T, T, XisChanged, YisChanged, ZisChanged, false,      FisChanged, false,      false);      return; }

}
