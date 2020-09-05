#include "Buffer_Gcode.h"

#include "stdbool.h"
#include "math.h"


static descreteCommand_Gcode descreteBuffer[3];

static int number(int elementNumber) { return elementNumber - 1; }

void createDescreteCommandBuffer_Gcode(void)
{
    descreteBuffer[number(1)] = defaultDescreteCommand;
    descreteBuffer[number(2)] = defaultDescreteCommand;
    descreteBuffer[number(3)] = defaultDescreteCommand;
}

void addElementToDescreteCommandBuffer_Gcode(descreteCommand_Gcode descreteCommand)
{
    descreteBuffer[number(1)] = descreteBuffer[number(2)];
    descreteBuffer[number(2)] = descreteBuffer[number(3)];
    descreteBuffer[number(3)] = descreteCommand;
}

void clearDescreteBuffer_Gcode(void)
{
    descreteBuffer[number(1)] = defaultDescreteCommand;
    descreteBuffer[number(2)] = defaultDescreteCommand;
    descreteBuffer[number(3)] = defaultDescreteCommand;
}

const descreteCommand_Gcode getDescreteCommandBufferElement_Gcode(int elementNumber)
{
    if (elementNumber < 1) elementNumber = 1;
    if (elementNumber > 3) elementNumber = 3;
    return descreteBuffer[number(elementNumber)];
}


static command_Gcode commandBuffer[COMMAND_BUFFER_LENGTH];

static int firstOccupedElementCommandBuffer;
static int firstFreeElementCommandBuffer;
static _Bool commandBufferIsFull;

void createCommandBuffer_Gcode(void)
{
    int n;
    for (n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        commandBuffer[number(n)] = defaultCommand;
    firstOccupedElementCommandBuffer = 1;
    firstFreeElementCommandBuffer = 1;
    commandBufferIsFull = false;
}

const command_Gcode getCommandBufferElement_Gcode(int elementNumber)
{
    if (elementNumber < 1) elementNumber = 1;
    if (elementNumber > COMMAND_BUFFER_LENGTH) elementNumber = COMMAND_BUFFER_LENGTH;
    return commandBuffer[number(elementNumber)];
}

void firstInCommandBuffer_Gcode(command_Gcode command)
{
    if (commandBufferIsFull)
        return;

    commandBuffer[number(firstFreeElementCommandBuffer)] = command;

    firstFreeElementCommandBuffer++;
    if (firstFreeElementCommandBuffer > COMMAND_BUFFER_LENGTH)
        firstFreeElementCommandBuffer = firstFreeElementCommandBuffer - COMMAND_BUFFER_LENGTH;
    if (firstFreeElementCommandBuffer == firstOccupedElementCommandBuffer)
        commandBufferIsFull = true;
}

const command_Gcode firstOutCommandBuffer_Gcode(void)
{
    return commandBuffer[number(firstOccupedElementCommandBuffer)];
}

void eraseFirstCommandBuffer_Gcode(void)
{
    if (firstOccupedElementCommandBuffer == firstFreeElementCommandBuffer)
        if (!commandBufferIsFull)
            return;

    commandBuffer[number(firstOccupedElementCommandBuffer)] = defaultCommand;

    if (firstOccupedElementCommandBuffer == COMMAND_BUFFER_LENGTH)
        firstOccupedElementCommandBuffer = firstOccupedElementCommandBuffer - COMMAND_BUFFER_LENGTH;
    firstOccupedElementCommandBuffer++;
    commandBufferIsFull = false;
}

const int checkFreeSpaceCommandBuffer_Gcode(void)
{
    if (firstFreeElementCommandBuffer == firstOccupedElementCommandBuffer)
        if (commandBufferIsFull)
            return 0;

    int occupedSpace = firstFreeElementCommandBuffer - firstOccupedElementCommandBuffer;
    if (occupedSpace < 0)
        occupedSpace = occupedSpace + COMMAND_BUFFER_LENGTH;
    int freeSpace = COMMAND_BUFFER_LENGTH - occupedSpace;
    return freeSpace;
}

_Bool enoghSpaceIsReservedCommandBuffer_Gcode(void)
{
    return checkFreeSpaceCommandBuffer_Gcode() > RESERVE_LENGTH;
}

static const float ACCELERATION_XY_STEPS_PER_SS = (float)ACCELERATION_MM_MIN_S_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float MAX_SPEED_XY_STEPS_PER_SECONDS = (float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float MAX_SPEED_E_STEPS_PER_SECONDS = (float)MAX_SPEED_MM_MIN_E*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE;

static long sign(float x)
{
    if (x<0)
        return -1;
    return 1;
}

static const command_Gcode lastCommand(void)
{
    int number;
    number = firstFreeElementCommandBuffer - 1;
    if (number == 0)
        number = COMMAND_BUFFER_LENGTH;
    return getCommandBufferElement_Gcode(number);
}

static _Bool conserveSpeedStart(long Xn, long Yn, long Zn)
{
    if (firstOccupedElementCommandBuffer == firstFreeElementCommandBuffer)
        return false;
    if (lastCommand().type != MOVE_COMMAND)
        return false;
    long XnPrevious = lastCommand().dXn;
    long YnPrevious = lastCommand().dYn;
    float xy1xy2 = (float)XnPrevious*(float)Xn + (float)YnPrevious*(float)Yn;
    float xy1xy1 = (float)XnPrevious*(float)XnPrevious + (float)YnPrevious*(float)YnPrevious;
    float xy2xy2 = (float)Xn*(float)Xn + (float)Yn*(float)Yn;
    float xy1xy2Critical = sqrtf(xy1xy1)*sqrtf(xy2xy2)*cos(3.14*(float)CRITICAL_ANGLE_XY/180.0);
    if (xy1xy2 < xy1xy2Critical)
        return false;
    return true;
}

static _Bool conserveSpeedFinish(long Xn, long Yn, long Zn)
{
    if (getDescreteCommandBufferElement_Gcode(3).type != MOVE_COMMAND)
        return false;
    long XnNext = getDescreteCommandBufferElement_Gcode(3).Xn - getDescreteCommandBufferElement_Gcode(2).Xn;
    long YnNext = getDescreteCommandBufferElement_Gcode(3).Yn - getDescreteCommandBufferElement_Gcode(2).Yn;
    float xy1xy2 = (float)XnNext*(float)Xn + (float)YnNext*(float)Yn;
    float xy1xy1 = (float)XnNext*(float)XnNext + (float)YnNext*(float)YnNext;
    float xy2xy2 = (float)Xn*(float)Xn + (float)Yn*(float)Yn;
    float xy1xy2Critical = sqrtf(xy1xy1)*sqrtf(xy2xy2)*cos(3.14*(float)CRITICAL_ANGLE_XY/180.0);
    if (xy1xy2 < xy1xy2Critical)
        return false;
    return true;
}

static float distanceStartFastMove(float totalDistance, float speedStart, float speedFinish, float accelerationStart, float accelerationFinish)
{
    float distance_float;
    distance_float = (float)totalDistance*(accelerationFinish/(accelerationFinish-accelerationStart))
                    +(speedFinish*speedFinish-speedStart*speedStart)/(2*(accelerationFinish-accelerationStart));
    return distance_float;
}

static float speedMaxFastMove(float totalDistance, float speedStart, float speedFinish, float accelerationStart, float accelerationFinish)
{
    float speed;
    speed = (float)sign(totalDistance)*sqrt(
                (float)totalDistance*(2*accelerationStart*accelerationFinish/(accelerationFinish-accelerationStart))
                -(speedFinish*speedFinish*accelerationStart-speedStart*speedStart*accelerationFinish)/(accelerationFinish-accelerationStart)
                );
    return speed;
}

static void MoveXY_Analyser(void)
{
    long Xn = getDescreteCommandBufferElement_Gcode(2).Xn - getDescreteCommandBufferElement_Gcode(1).Xn;
    long Yn = getDescreteCommandBufferElement_Gcode(2).Yn - getDescreteCommandBufferElement_Gcode(1).Yn;
    long En = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;
    float distance_XY = sqrtf((float)Xn*(float)Xn+(float)Yn*(float)Yn);
    float cosX = (float)Xn/distance_XY;     float cosY = (float)Yn/distance_XY;     float cosE = (float)En/(float)distance_XY;
    float speedTarget = getDescreteCommandBufferElement_Gcode(2).FnXY;
    if ( getDescreteCommandBufferElement_Gcode(2).FnXY > MAX_SPEED_XY_STEPS_PER_SECONDS ) speedTarget = MAX_SPEED_XY_STEPS_PER_SECONDS;
    if (En != 0) if ( fabs(speedTarget*cosE) > MAX_SPEED_E_STEPS_PER_SECONDS ) speedTarget = sign(speedTarget)*(float)MAX_SPEED_E_STEPS_PER_SECONDS/fabs(cosE);
    float speedStart = 0;   if ( conserveSpeedStart(Xn, Yn, 0) ) speedStart = sqrtf(2*lastCommand().dXn*lastCommand().AnX+2*lastCommand().dYn*lastCommand().AnY+pow(lastCommand().FnX,2)+pow(lastCommand().FnY,2));
    float speedFinish = 0;  if ( conserveSpeedFinish(Xn, Yn, 0) ) speedFinish = speedTarget;
    float accelerationStart = ACCELERATION_XY_STEPS_PER_SS*sign(speedTarget-speedStart);
    float accelerationFinish = ACCELERATION_XY_STEPS_PER_SS*sign(speedFinish-speedTarget);
    float LnStart  = 0.5*(speedTarget*speedTarget-speedStart*speedStart)/accelerationStart;
    float LnFinish = 0.5*(speedFinish*speedFinish-speedTarget*speedTarget)/accelerationFinish;
    float LnMiddle = distance_XY - LnStart - LnFinish;
    if( LnMiddle < 0 )
    {
        if( conserveSpeedFinish(Xn, Yn, 0) )
        {
            long x1 = Xn;                           long y1 = Yn;                           long e1 = En;
            float vX1 = speedStart*cosX;            float vY1 = speedStart*cosY;            float vE1 = speedStart*cosE;
            float aX1 = accelerationStart*cosX;     float aY1 = accelerationStart*cosY;     float aE1 = accelerationStart*cosE;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0, aE1,   0, 0};  firstInCommandBuffer_Gcode(command1);  return;
        }
        if( conserveSpeedStart(Xn, Yn, 0) )
        {
            long x1 = Xn;                           long y1 = Yn;                           long e1 = En;
            float vX1 = speedStart*cosX;            float vY1 = speedStart*cosY;            float vE1 = speedStart*cosE;
            float aX1 = accelerationFinish*cosX;    float aY1 = accelerationFinish*cosY;    float aE1 = accelerationFinish*cosE;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0, aE1,   0, 0};  firstInCommandBuffer_Gcode(command1);  return;
        }
        float distance_XY_buffer = distanceStartFastMove(distance_XY, speedStart, speedFinish, accelerationStart, accelerationFinish);
        float speed_XY_buffer = speedMaxFastMove(distance_XY, speedStart, speedFinish, accelerationStart, accelerationFinish);
        long x1 = lroundf(distance_XY_buffer*cosX); long y1 = lroundf(distance_XY_buffer*cosY);     long e1 = lroundf(distance_XY_buffer*cosE);
        float vX1 = speedStart*cosX;                float vY1 = speedStart*cosY;                    float vE1 = speedStart*cosE;
        float aX1 = accelerationStart*cosX;         float aY1 = accelerationStart*cosY;             float aE1 = accelerationStart*cosE;
        command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0, aE1,   0, 0};  firstInCommandBuffer_Gcode(command1);
        long x2 = Xn - x1;                          long y2 = Yn - y1;                              long e2 = En - e1;
        float vX2 = speed_XY_buffer*cosX;           float vY2 = speed_XY_buffer*cosY;               float vE2 = speed_XY_buffer*cosE;
        float aX2 = accelerationFinish*cosX;        float aY2 = accelerationFinish*cosY;            float aE2 = accelerationFinish*cosE;
        command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0, aE2,   0, 0};  firstInCommandBuffer_Gcode(command2);  return;
    }
    long x1 = lroundf(LnStart*cosX);        long y1 = lroundf(LnStart*cosY);        long e1 = lroundf(LnStart*cosE);
    float vX1 = speedStart*cosX;            float vY1 = speedStart*cosY;            float vE1 = speedStart*cosE;
    float aX1 = accelerationStart*cosX;     float aY1 = accelerationStart*cosY;     float aE1 = accelerationStart*cosE;
    command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0, aE1,   0, 0};  if(x1 != 0 || y1 != 0) firstInCommandBuffer_Gcode(command1);
    long x2 = lroundf(LnMiddle*cosX);       long y2 = lroundf(LnMiddle*cosY);       long e2 = lroundf(LnMiddle*cosE);     if(lroundf(LnFinish) == 0) {x2 = Xn - x1; y2 = Yn - y1; e2 = En - e1;}
    float vX2 = speedTarget*cosX;           float vY2 = speedTarget*cosY;           float vE2 = speedTarget*cosE;
    float aX2 = 0;                          float aY2 = 0;                          float aE2 = 0;
    command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0, aE2,   0, 0};  firstInCommandBuffer_Gcode(command2);
    long x3 = Xn - x1 - x2;                 long y3 = Yn - y2 - y1;                 long e3 = En - e2 - e1;
    float vX3 = speedTarget*cosX;           float vY3 = speedTarget*cosY;           float vE3 = speedTarget*cosE;
    float aX3 = accelerationFinish*cosX;    float aY3 = accelerationFinish*cosY;    float aE3 = accelerationFinish*cosE;
    command_Gcode command3 = {MOVE_COMMAND, x3, y3, 0, e3,    vX3, vY3, 0, vE3,    aX3, aY3, 0, aE3,   0, 0};  if(x3 != 0 || y3 != 0) firstInCommandBuffer_Gcode(command3);
}


static void MoveE_Analyser(void)
{
    long En = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;
    float speedTarget = sign(En)*getDescreteCommandBufferElement_Gcode(2).FnE;
    if (getDescreteCommandBufferElement_Gcode(2).FnE > MAX_SPEED_E_STEPS_PER_SECONDS) speedTarget = sign(En)*MAX_SPEED_E_STEPS_PER_SECONDS;
    long e1 = En;
    float vE1 = speedTarget;
    command_Gcode command1 = {MOVE_COMMAND, 0, 0, 0, e1,    0, 0, 0, vE1,    0, 0, 0,   0, 0}; firstInCommandBuffer_Gcode(command1);
}

void descreteCommandAnalyser_Gcode(void)
{
    commandType_Gcode typeOfCommand = getDescreteCommandBufferElement_Gcode(2).type;

    if (typeOfCommand == MOVE_COMMAND)
    {
        long dXn = getDescreteCommandBufferElement_Gcode(2).Xn - getDescreteCommandBufferElement_Gcode(1).Xn;
        long dYn = getDescreteCommandBufferElement_Gcode(2).Yn - getDescreteCommandBufferElement_Gcode(1).Yn;
        long dEn = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;
        if (dXn != 0 || dYn != 0)
        {
            MoveXY_Analyser();
            return;
        }
        if (dEn != 0)
            MoveE_Analyser();
        return;
    }
}

static int lastCommandNumber(void)
{
    if (firstFreeElementCommandBuffer == 1)
        return COMMAND_BUFFER_LENGTH;
    return firstFreeElementCommandBuffer - 1;
}

static int prevoiusCommandNumber(int commandNumber)
{
    if (commandNumber == 1)
        return COMMAND_BUFFER_LENGTH;
    return commandNumber - 1;
}

static int nextCommandNumber(int commandNumber)
{
    if (commandNumber == COMMAND_BUFFER_LENGTH)
        return 1;
    return commandNumber + 1;
}

static long distanceRequired(float speedStart, float speedFinish, float acceleration)
{
    return lroundf(fabs(pow(speedFinish,2)-pow(speedStart,2))/fabs(2*acceleration));
}

static void shiftRightAllTheCommandsTillThis(int commandNumber)
{
    int currentCommandNumber = lastCommandNumber();
    firstInCommandBuffer_Gcode(lastCommand());
    while ((currentCommandNumber != commandNumber))
    {
        commandBuffer[number(currentCommandNumber)] = commandBuffer[number(prevoiusCommandNumber(currentCommandNumber))];
        currentCommandNumber = prevoiusCommandNumber(currentCommandNumber);
    }
}

void smoothStop_Gcode(void)
{

    int currentCommandNumber = lastCommandNumber();
    command_Gcode command = commandBuffer[number(currentCommandNumber)];

    float speedAtTheEnd = 0;
    float speedAtTheStart = sqrtf(pow(command.FnX,2)+pow(command.FnY,2));
    float acceleration = ACCELERATION_XY_STEPS_PER_SS;
    float allowedDistance = sqrtf( pow(command.dXn,2) + pow(command.dYn,2) );
    float cosX = (float)command.dXn/allowedDistance;
    float cosY = (float)command.dYn/allowedDistance;
    float cosE = (float)command.dEn/allowedDistance;

    if    (allowedDistance + 0.5 > distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration)) return;
    while (allowedDistance + 0.5 < distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration))
    {
        commandBuffer[number(currentCommandNumber)].FnX = cosX*sqrtf(pow(speedAtTheEnd,2)+2*acceleration*allowedDistance);
        commandBuffer[number(currentCommandNumber)].FnY = cosY*sqrtf(pow(speedAtTheEnd,2)+2*acceleration*allowedDistance);
        commandBuffer[number(currentCommandNumber)].FnE = cosE*sqrtf(pow(speedAtTheEnd,2)+2*acceleration*allowedDistance);
        commandBuffer[number(currentCommandNumber)].AnX = -cosX*acceleration;
        commandBuffer[number(currentCommandNumber)].AnY = -cosY*acceleration;
        commandBuffer[number(currentCommandNumber)].AnE = -cosE*acceleration;

        currentCommandNumber = prevoiusCommandNumber(currentCommandNumber);
        command = commandBuffer[number(currentCommandNumber)];

        speedAtTheEnd = sqrtf( pow(commandBuffer[number(nextCommandNumber(currentCommandNumber))].FnX,2)+pow(commandBuffer[number(nextCommandNumber(currentCommandNumber))].FnY,2) );
        speedAtTheStart = sqrtf(pow(command.FnX,2)+pow(command.FnY,2));
        acceleration = ACCELERATION_XY_STEPS_PER_SS;
        allowedDistance = sqrtf( pow(command.dXn,2) + pow(command.dYn,2) );
        cosX = (float)command.dXn/allowedDistance;
        cosY = (float)command.dYn/allowedDistance;
        cosE = (float)command.dEn/allowedDistance;
    }

    shiftRightAllTheCommandsTillThis(currentCommandNumber);

    float aStar = sqrtf(pow(command.AnX,2)+pow(command.AnY,2));
    float lStar = acceleration*allowedDistance/(acceleration+aStar) + ( pow(speedAtTheEnd,2) - pow(speedAtTheStart,2) )/2/(acceleration+aStar);
    float vStar = sqrtf( pow(speedAtTheStart,2) + 2*aStar*lStar );

    commandBuffer[number(currentCommandNumber)].dXn = lroundf(lStar*cosX);              commandBuffer[number(currentCommandNumber)].dYn = lroundf(lStar*cosY);              commandBuffer[number(currentCommandNumber)].dEn = lroundf(lStar*cosE);

    currentCommandNumber = nextCommandNumber(currentCommandNumber);
    commandBuffer[number(currentCommandNumber)].dXn = command.dXn-lroundf(lStar*cosX);  commandBuffer[number(currentCommandNumber)].dYn = command.dYn-lroundf(lStar*cosY);  commandBuffer[number(currentCommandNumber)].dEn = command.dEn-lroundf(lStar*cosE);
    commandBuffer[number(currentCommandNumber)].FnX = vStar*cosX;                       commandBuffer[number(currentCommandNumber)].FnY = vStar*cosY;                       commandBuffer[number(currentCommandNumber)].FnE = vStar*cosE;
    commandBuffer[number(currentCommandNumber)].AnX = -acceleration*cosX;               commandBuffer[number(currentCommandNumber)].AnY = -acceleration*cosY;               commandBuffer[number(currentCommandNumber)].AnE = -acceleration*cosE;
}


