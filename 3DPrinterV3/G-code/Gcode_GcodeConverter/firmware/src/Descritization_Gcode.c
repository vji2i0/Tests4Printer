#include "Descritization_Gcode.h"
#include <math.h>

static descreteCommand_Gcode descreteCommand;

static void setCommand (long xn, long yn, long zn, long en, float fnxy, float fnz, float fne, float bt, float et)
{
    descreteCommand.Xn = xn;
    descreteCommand.Yn = yn;
    descreteCommand.Zn = zn;
    descreteCommand.En = en;
    descreteCommand.FnXY = fnxy;
    descreteCommand.FnZ = fnz;
    descreteCommand.FnE = fne;
    descreteCommand.bedT = bt;
    descreteCommand.extrT = et;
}

static float descreteSpeedXY(float f) { return f*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE; }
static float descreteSpeedZ (float f) { return f*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;  }
static float descreteSpeedE (float f) { return f*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE;  }
static long descreteXY(float xy) { return lroundf(xy*STEPS_PER_MM_XY); }
static long descreteZ (float z)  { return lroundf(z*STEPS_PER_MM_Z);   }
static long descreteE (float e)  { return lroundf(e*STEPS_PER_MM_E);   }


void createDescretization_Gcode(void)
{
    descreteCommand.type = EMPTY_COMMAND;
    setCommand(0, 0, 0, 0,
                descreteSpeedXY(F_DEFAULT), descreteSpeedZ(F_DEFAULT), descreteSpeedE(F_DEFAULT),
                    0, 0);
}

const descreteCommand_Gcode getDescreteCommand_Gcode() {return descreteCommand;}

void setDescreteCommand_Gcode(convertedCommand_Gcode convertedCommand)
{
    descreteCommand.type = convertedCommand.type;

    setCommand(descreteXY(convertedCommand.X), descreteXY(convertedCommand.Y), descreteZ(convertedCommand.Z), descreteE(convertedCommand.E),
                descreteSpeedXY(convertedCommand.F), descreteSpeedZ(convertedCommand.F), descreteSpeedE(convertedCommand.F),
                    convertedCommand.bedT, convertedCommand.extrT);
}
