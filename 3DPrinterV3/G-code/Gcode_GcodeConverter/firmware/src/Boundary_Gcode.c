#include "Boundary_Gcode.h"

#include <stdint.h>
#include "stdbool.h"

static _Bool boundary_X, boundary_Y, boundary_Z1, boundary_Z2;

void createBoundary_Gcode(void)
{
    setBoundaryXisReached_Gcode();
    setBoundaryYisReached_Gcode();
    setBoundaryZ1isReached_Gcode();
    setBoundaryZ2isReached_Gcode();
}

void setBoundaryXisReached_Gcode(void)          {boundary_X = true;}
void setBoundaryYisReached_Gcode(void)          {boundary_Y = true;}
void setBoundaryZ1isReached_Gcode(void)         {boundary_Z1 = true;}
void setBoundaryZ2isReached_Gcode(void)         {boundary_Z2 = true;}

void setBoundaryXisNotReached_Gcode(void)    {boundary_X = false;}
void setBoundaryYisNotReached_Gcode(void)    {boundary_Y = false;}
void setBoundaryZ1isNotReached_Gcode(void)   {boundary_Z1 = false;}
void setBoundaryZ2isNotReached_Gcode(void)   {boundary_Z2 = false;}

_Bool boundaryXisReached_Gcode(void)            {return boundary_X;}
_Bool boundaryYisReached_Gcode(void)            {return boundary_Y;}
_Bool boundaryZ1isReached_Gcode(void)           {return boundary_Z1;}
_Bool boundaryZ2isReached_Gcode(void)           {return boundary_Z2;}

