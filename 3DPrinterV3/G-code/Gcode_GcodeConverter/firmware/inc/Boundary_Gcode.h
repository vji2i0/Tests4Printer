#ifndef __BOUNDARY_GCODE
#define __BOUNDARY_GCODE

#include <stdint.h>
#include "stdbool.h"


void createBoundary_Gcode(void);

void setBoundaryXisReached_Gcode(void);
void setBoundaryYisReached_Gcode(void);
void setBoundaryZ1isReached_Gcode(void);
void setBoundaryZ2isReached_Gcode(void);

void setBoundaryXisNotReached_Gcode(void);
void setBoundaryYisNotReached_Gcode(void);
void setBoundaryZ1isNotReached_Gcode(void);
void setBoundaryZ2isNotReached_Gcode(void);

_Bool boundaryXisReached_Gcode(void);
_Bool boundaryYisReached_Gcode(void);
_Bool boundaryZ1isReached_Gcode(void);
_Bool boundaryZ2isReached_Gcode(void);

#endif
