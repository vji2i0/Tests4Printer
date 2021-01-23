#ifndef BUFFER_GCODE
#define BUFFER_GCODE

#include "Config_Gcode.h"
#include "Descritization_Gcode.h"
#include "stdbool.h"

extern const descreteCommand_Gcode defaultDescreteCommand;

void createDescreteCommandBuffer_Gcode(void);
void addElementToDescreteCommandBuffer_Gcode(descreteCommand_Gcode descreteCommand);
void clearDescreteBuffer_Gcode(void);

const descreteCommand_Gcode getDescreteCommandBufferElement_Gcode(int elementNumber);


typedef struct
{
    commandType_Gcode type;
    long dXn, dYn, dZn, dEn;
    float FnX, FnY, FnZ, FnE;
    float AnX, AnY, AnZ, AnE;
    float extrT, bedT;
} command_Gcode;

extern const command_Gcode defaultCommand;

void createCommandBuffer_Gcode(void);

const command_Gcode getCommandBufferElement_Gcode(int elementNumber);

void firstInCommandBuffer_Gcode(command_Gcode command);
const command_Gcode firstOutCommandBuffer_Gcode(void);
void eraseFirstCommandBuffer_Gcode(void);

const int checkFreeSpaceCommandBuffer_Gcode(void);
_Bool enoghSpaceIsReservedCommandBuffer_Gcode(void);


void descreteCommandAnalyser_Gcode(void);

void smoothStop_Gcode(void);

_Bool descreteCommandIsRepeated(descreteCommand_Gcode descreteCommand);
#endif
