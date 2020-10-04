#include "VirtualPrinters_Gcode.h"

#include "math.h"

const float evaluationPeriod_Gcode = 0.001;


static struct
{
    command_Gcode command;
    _Bool xDone;    long xDirection;
    _Bool yDone;    long yDirection;
    _Bool zDone;    long zDirection;
    _Bool eDone;    long eDirection;
} currentCommand;

static struct
{
    long X;
    long Y;
    long Z;
    long E;
} discretePrinter;

static struct
{
    float X;    float vX;
    float Y;    float vY;
    float Z;    float vZ;
    float E;    float vE;
} continiuosPrinter;

void virtualPrintersCreate_Gcode(void)
{
    discretePrinter.X = 0;          discretePrinter.Y = 0;          discretePrinter.Z = 0;          discretePrinter.E = 0;
    continiuosPrinter.X = 0;        continiuosPrinter.Y = 0;        continiuosPrinter.Z = 0;        continiuosPrinter.E = 0;
    continiuosPrinter.vX = 0;       continiuosPrinter.vY = 0;       continiuosPrinter.vZ = 0;       continiuosPrinter.vE = 0;
    currentCommand.xDone = true;    currentCommand.yDone = true;    currentCommand.zDone = true;    currentCommand.eDone = true;
}

long getCurrentX_Gcode(void) {return discretePrinter.X;}
long getCurrentY_Gcode(void) {return discretePrinter.Y;}
long getCurrentZ_Gcode(void) {return discretePrinter.Z;}
long getCurrentE_Gcode(void) {return discretePrinter.E;}

static long sign(long dLn)
{
    if (dLn > 0) return 1;
    if (dLn < 0) return -1;
    return 0;
}

void sendCommandToPrinter_Gcode(command_Gcode command)
{
    virtualPrintersCreate_Gcode();
    currentCommand.command = command;
    continiuosPrinter.vX = command.FnX; currentCommand.xDirection = sign(command.dXn);  if (command.dXn != 0) currentCommand.xDone = false;
    continiuosPrinter.vY = command.FnY; currentCommand.yDirection = sign(command.dYn);  if (command.dYn != 0) currentCommand.yDone = false;
    continiuosPrinter.vZ = command.FnZ; currentCommand.zDirection = sign(command.dZn);  if (command.dZn != 0) currentCommand.zDone = false;
    continiuosPrinter.vE = command.FnE; currentCommand.eDirection = sign(command.dEn);  if (command.dEn != 0) currentCommand.eDone = false;
}

static _Bool moveComleted(void)
{
    return currentCommand.xDone && currentCommand.yDone && currentCommand.zDone && currentCommand.eDone;
}

_Bool evaluatePrinter_Gcode(void)
{
    if (moveComleted())
        return true;
    if (!currentCommand.xDone)
    {
        continiuosPrinter.vX += currentCommand.command.AnX*evaluationPeriod_Gcode;
        continiuosPrinter.X  += continiuosPrinter.vX*evaluationPeriod_Gcode;
        if (lroundf(continiuosPrinter.X - (float)discretePrinter.X) != 0) discretePrinter.X += currentCommand.xDirection;
        if (discretePrinter.X == currentCommand.command.dXn) currentCommand.xDone = true;
    }
    if (!currentCommand.yDone)
    {
        continiuosPrinter.vY += currentCommand.command.AnY*evaluationPeriod_Gcode;
        continiuosPrinter.Y  += continiuosPrinter.vY*evaluationPeriod_Gcode;
        if (lroundf(continiuosPrinter.Y - (float)discretePrinter.Y) != 0) discretePrinter.Y += currentCommand.yDirection;
        if (discretePrinter.Y == currentCommand.command.dYn) currentCommand.yDone = true;
    }
    if (!currentCommand.zDone)
    {
        continiuosPrinter.vZ += currentCommand.command.AnZ*evaluationPeriod_Gcode;
        continiuosPrinter.Z  += continiuosPrinter.vZ*evaluationPeriod_Gcode;
        if (lroundf(continiuosPrinter.Z - (float)discretePrinter.Z) != 0) discretePrinter.Z += currentCommand.zDirection;
        if (discretePrinter.Z == currentCommand.command.dZn) currentCommand.zDone = true;
    }
    if (!currentCommand.eDone)
    {
        continiuosPrinter.vE += currentCommand.command.AnE*evaluationPeriod_Gcode;
        continiuosPrinter.E  += continiuosPrinter.vE*evaluationPeriod_Gcode;
        if (lroundf(continiuosPrinter.E - (float)discretePrinter.E) != 0) discretePrinter.E += currentCommand.eDirection;
        if (discretePrinter.E == currentCommand.command.dEn) currentCommand.eDone = true;
    }
    return false;
}
