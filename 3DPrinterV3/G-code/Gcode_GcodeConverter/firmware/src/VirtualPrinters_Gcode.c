#include "VirtualPrinters_Gcode.h"

static struct
{
    long X;
    long Y;
    long Z;
    long E;
} discretePrinter;

void virtualPrintersCreate_Gcode(void)
{
    discretePrinter.X = 0;
    discretePrinter.Y = 0;
    discretePrinter.Z = 0;
    discretePrinter.E = 0;
}

long getCurrentX_Gcode(void) {return discretePrinter.X;}
long getCurrentY_Gcode(void) {return discretePrinter.Y;}
long getCurrentZ_Gcode(void) {return discretePrinter.Z;}
long getCurrentE_Gcode(void) {return discretePrinter.E;}
