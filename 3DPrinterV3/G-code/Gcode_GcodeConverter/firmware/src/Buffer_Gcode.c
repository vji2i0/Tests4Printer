#include "Buffer_Gcode.h"

#include "stdbool.h"
#include "math.h"
#include <stdlib.h>

const descreteCommand_Gcode defaultDescreteCommand = {EMPTY_COMMAND};
const command_Gcode defaultCommand = {EMPTY_COMMAND};


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
static const float ACCELERATION_Z_STEPS_PER_SS = (float)ACCELERATION_MM_MIN_S_Z*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float MAX_SPEED_XY_STEPS_PER_SECOND = (float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float MAX_SPEED_Z_STEPS_PER_SECOND = (float)MAX_SPEED_MM_MIN_Z*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float MAX_SPEED_E_STEPS_PER_SECOND = (float)MAX_SPEED_MM_MIN_E*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE;

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
    if (XnPrevious == 0 && YnPrevious == 0)
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
    if (XnNext == 0 && YnNext == 0)
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
    float distance_XY = sqrtf(pow(Xn,2)+pow(Yn,2)); float cosX = (float)Xn/distance_XY; float cosY = (float)Yn/distance_XY; float cosE = (float)En/(float)distance_XY;
    float speedTarget = getDescreteCommandBufferElement_Gcode(2).FnXY;  if ( getDescreteCommandBufferElement_Gcode(2).FnXY > MAX_SPEED_XY_STEPS_PER_SECOND ) speedTarget = MAX_SPEED_XY_STEPS_PER_SECOND;
    if (En != 0) if ( fabs(speedTarget*cosE) > MAX_SPEED_E_STEPS_PER_SECOND ) speedTarget = sign(speedTarget)*(float)MAX_SPEED_E_STEPS_PER_SECOND/fabs(cosE);
    float speedStart = 0;                                               if ( conserveSpeedStart(Xn, Yn, 0)  ) speedStart = sqrtf(2*lastCommand().dXn*lastCommand().AnX+2*lastCommand().dYn*lastCommand().AnY+pow(lastCommand().FnX,2)+pow(lastCommand().FnY,2));
    float speedFinish = 0;                                              if ( conserveSpeedFinish(Xn, Yn, 0) ) speedFinish = speedTarget;
    float accelerationStart = ACCELERATION_XY_STEPS_PER_SS*sign(speedTarget-speedStart);
    float accelerationFinish = ACCELERATION_XY_STEPS_PER_SS*sign(speedFinish-speedTarget);
    float LnStart  = 0.5*(pow(speedTarget,2)-pow(speedStart,2))/accelerationStart;
    float LnFinish = 0.5*(pow(speedFinish,2)-pow(speedTarget,2))/accelerationFinish;
    float LnMiddle = distance_XY - LnStart - LnFinish;
    if( LnMiddle < 0 )
    {
        if( conserveSpeedFinish(Xn, Yn, 0) )
        {
            long x1 = Xn;                           long y1 = Yn;                           long e1 = En;
            float vX1 = speedStart*cosX;            float vY1 = speedStart*cosY;            float vE1 = speedStart*cosE;
            float aX1 = accelerationStart*cosX;     float aY1 = accelerationStart*cosY;     float aE1 = accelerationStart*cosE;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0, aE1,   0, 0};  firstInCommandBuffer_Gcode(command1);  if ( !conserveSpeedFinish(Xn, Yn, 0) ) smoothStop_Gcode();  return;
        }
        if( conserveSpeedStart(Xn, Yn, 0) )
        {
            long x1 = Xn;                           long y1 = Yn;                           long e1 = En;
            float vX1 = speedStart*cosX;            float vY1 = speedStart*cosY;            float vE1 = speedStart*cosE;
            float aX1 = accelerationFinish*cosX;    float aY1 = accelerationFinish*cosY;    float aE1 = accelerationFinish*cosE;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0, aE1,   0, 0};  firstInCommandBuffer_Gcode(command1);  if ( !conserveSpeedFinish(Xn, Yn, 0) ) smoothStop_Gcode();  return;
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
        command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0, aE2,   0, 0};  firstInCommandBuffer_Gcode(command2);  if ( !conserveSpeedFinish(Xn, Yn, 0) ) smoothStop_Gcode();  return;
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
    if ( !conserveSpeedFinish(Xn, Yn, 0) ) smoothStop_Gcode();
}

static void MoveE_Analyser(void)
{
    long En = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;
    float speedTarget = sign(En)*getDescreteCommandBufferElement_Gcode(2).FnE;
    if (getDescreteCommandBufferElement_Gcode(2).FnE > MAX_SPEED_E_STEPS_PER_SECOND) speedTarget = sign(En)*MAX_SPEED_E_STEPS_PER_SECOND;
    long e1 = En;
    float vE1 = speedTarget;
    command_Gcode command1 = {MOVE_COMMAND, 0, 0, 0, e1,    0, 0, 0, vE1,    0, 0, 0,   0, 0}; firstInCommandBuffer_Gcode(command1);
}

static void MoveZ_Analyser(void)
{
    long Zn = getDescreteCommandBufferElement_Gcode(2).Zn - getDescreteCommandBufferElement_Gcode(1).Zn;
    float speedTarget = getDescreteCommandBufferElement_Gcode(2).FnZ;
    if ( getDescreteCommandBufferElement_Gcode(2).FnZ > MAX_SPEED_Z_STEPS_PER_SECOND ) speedTarget = MAX_SPEED_Z_STEPS_PER_SECOND;
    float speedStart = 0;
    float speedFinish = 0;
    float accelerationStart = ACCELERATION_Z_STEPS_PER_SS*sign(speedTarget-speedStart);
    float accelerationFinish = ACCELERATION_Z_STEPS_PER_SS*sign(speedFinish-speedTarget);
    float LnStart  = 0.5*(pow(speedTarget,2)-pow(speedStart,2))/accelerationStart;
    float LnFinish = 0.5*(pow(speedFinish,2)-pow(speedTarget,2))/accelerationFinish;
    float LnMiddle = (float)abs(Zn) - LnStart - LnFinish;
    if( LnMiddle < 0 )
    {
        float distance_Z_buffer = distanceStartFastMove( (float)abs(Zn), speedStart, speedFinish, accelerationStart, accelerationFinish );
        float speed_Z_buffer = speedMaxFastMove( (float)abs(Zn), speedStart, speedFinish, accelerationStart, accelerationFinish );
        long z1 = lroundf(distance_Z_buffer*sign(Zn));
        float vZ1 = speedStart;
        float aZ1 = accelerationStart*sign(Zn);
        command_Gcode command1 = {MOVE_COMMAND, 0, 0, z1, 0,    0, 0, vZ1, 0,    0, 0, aZ1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);
        long z2 = Zn - z1;
        float vZ2 = speed_Z_buffer*sign(Zn);
        float aZ2 = accelerationFinish*sign(Zn);
        command_Gcode command2 = {MOVE_COMMAND, 0, 0, z2, 0,    0, 0, vZ2, 0,    0, 0, aZ2, 0,   0, 0};  firstInCommandBuffer_Gcode(command2);  return;
    }
    long z1 = lroundf(LnStart*sign(Zn));
    float vZ1 = speedStart*sign(Zn);
    float aZ1 = accelerationStart*sign(Zn);
    command_Gcode command1 = {MOVE_COMMAND, 0, 0, z1, 0,    0, 0, vZ1, 0,    0, 0, aZ1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);
    long z2 = lroundf(LnMiddle*sign(Zn));
    float vZ2 = speedTarget*sign(Zn);
    float aZ2 = 0;
    command_Gcode command2 = {MOVE_COMMAND, 0, 0, z2, 0,    0, 0, vZ2, 0,    0, 0, aZ2, 0,   0, 0};  firstInCommandBuffer_Gcode(command2);
    long z3 = Zn - z1 - z2;
    float vZ3 = speedTarget*sign(Zn);
    float aZ3 = accelerationFinish*sign(Zn);
    command_Gcode command3 = {MOVE_COMMAND, 0, 0, z3, 0,    0, 0, vZ3, 0,    0, 0, aZ3, 0,   0, 0};  firstInCommandBuffer_Gcode(command3);
}

static const float HOME_COARSE_SPEED_XY_STEPS_PER_SECOND = (float)HOME_COARSE_SPEED*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float HOME_COARSE_SPEED_Z_STEPS_PER_SECOND = (float)HOME_COARSE_SPEED*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float HOME_FINE_SPEED_XY_STEPS_PER_SECOND = (float)HOME_FINE_SPEED*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float HOME_FINE_SPEED_Z_STEPS_PER_SECOND = (float)HOME_FINE_SPEED*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const long  HOME_FINE_STEPS_XY = HOME_FINE_DISTANCE*STEPS_PER_MM_XY;
static const long  HOME_FINE_STEPS_Z = HOME_FINE_DISTANCE*STEPS_PER_MM_Z;


static void HomeX_Analyser(void)
{
    long dXn = getDescreteCommandBufferElement_Gcode(2).Xn;
    long x; float v; float a;

    long  L_HOME_XY = lroundf(pow(HOME_COARSE_SPEED_XY_STEPS_PER_SECOND,2)/(2*ACCELERATION_XY_STEPS_PER_SS));

    x = 0;                          v = -HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;         a = 0;
    command_Gcode command1 = {GO_HOME_X_COMMAND, x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command1);
    x = HOME_FINE_STEPS_XY;         v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;          a = 0;
    command_Gcode command2 = {MOVE_COMMAND,      x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command2);
    x = 0;                          v = -HOME_FINE_SPEED_XY_STEPS_PER_SECOND;           a = 0;
    command_Gcode command3 = {GO_HOME_X_COMMAND, x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command3);
    if (dXn <= 0)
        return;

    if (dXn < 2*L_HOME_XY)
    {
        long  xStar = lroundf(0.25+(float)dXn/2);
        float vStar = sqrtf(2*ACCELERATION_XY_STEPS_PER_SS*xStar);
        x = xStar;                  v = 0;                                              a = ACCELERATION_XY_STEPS_PER_SS;
        command_Gcode command4 = {MOVE_COMMAND,      x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
        x = dXn-xStar;              v = vStar;                                          a = -ACCELERATION_XY_STEPS_PER_SS;
        command_Gcode command5 = {MOVE_COMMAND,      x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
        return;
    }

    x = L_HOME_XY;              v = 0;                                              a = ACCELERATION_XY_STEPS_PER_SS;
    command_Gcode command4 = {MOVE_COMMAND,      x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
    x = dXn-2*L_HOME_XY;        v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;          a = 0;
    command_Gcode command5 = {MOVE_COMMAND,      x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
    x = L_HOME_XY;              v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;          a = -ACCELERATION_XY_STEPS_PER_SS;
    command_Gcode command6 = {MOVE_COMMAND,      x, 0, 0, 0,    v, 0, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command6);
}

static void HomeY_Analyser(void)
{
    long dYn = getDescreteCommandBufferElement_Gcode(2).Yn;
    long y; float v; float a;

    long  L_HOME_XY = lroundf(pow(HOME_COARSE_SPEED_XY_STEPS_PER_SECOND,2)/(2*ACCELERATION_XY_STEPS_PER_SS));

    y = 0;                          v = -HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;         a = 0;
    command_Gcode command1 = {GO_HOME_Y_COMMAND, 0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command1);
    y = HOME_FINE_STEPS_XY;         v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;          a = 0;
    command_Gcode command2 = {MOVE_COMMAND,      0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command2);
    y = 0;                          v = -HOME_FINE_SPEED_XY_STEPS_PER_SECOND;           a = 0;
    command_Gcode command3 = {GO_HOME_Y_COMMAND, 0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command3);
    if (dYn <= 0)
        return;

    if (dYn < 2*L_HOME_XY)
    {
        long  yStar = lroundf(0.25+(float)dYn/2);
        float vStar = sqrtf(2*ACCELERATION_XY_STEPS_PER_SS*yStar);
        y = yStar;                  v = 0;                                              a = ACCELERATION_XY_STEPS_PER_SS;
        command_Gcode command4 = {MOVE_COMMAND,      0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
        y = dYn-yStar;              v = vStar;                                          a = -ACCELERATION_XY_STEPS_PER_SS;
        command_Gcode command5 = {MOVE_COMMAND,      0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
        return;
    }

    y = L_HOME_XY;              v = 0;                                              a = ACCELERATION_XY_STEPS_PER_SS;
    command_Gcode command4 = {MOVE_COMMAND,      0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
    y = dYn-2*L_HOME_XY;        v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;          a = 0;
    command_Gcode command5 = {MOVE_COMMAND,      0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
    y = L_HOME_XY;              v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;          a = -ACCELERATION_XY_STEPS_PER_SS;
    command_Gcode command6 = {MOVE_COMMAND,      0, y, 0, 0,    0, v, 0, 0,    0, a, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command6);
}

static void HomeZ_Analyser(void)
{
    long dZn = getDescreteCommandBufferElement_Gcode(2).Zn;
    long z; float v; float a;

    long  L_HOME_Z = lroundf(pow(HOME_COARSE_SPEED_Z_STEPS_PER_SECOND,2)/(2*ACCELERATION_Z_STEPS_PER_SS));

    z = 0;                          v = HOME_COARSE_SPEED_Z_STEPS_PER_SECOND;           a = 0;
    command_Gcode command1 = {GO_HOME_Z_COMMAND, 0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command1);
    z = -HOME_FINE_STEPS_Z;         v = -HOME_COARSE_SPEED_Z_STEPS_PER_SECOND;          a = 0;
    command_Gcode command2 = {MOVE_COMMAND,      0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command2);
    z = 0;                          v = HOME_FINE_SPEED_Z_STEPS_PER_SECOND;             a = 0;
    command_Gcode command3 = {GO_HOME_Z_COMMAND, 0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command3);
    if (dZn >= 0)
        return;

    if (abs(dZn) < 2*L_HOME_Z)
    {
        long  zStar = abs(lroundf(-0.25+(float)dZn/2));
        float vStar = sqrtf(2*ACCELERATION_Z_STEPS_PER_SS*zStar);
        z = -zStar;                 v = 0;                                              a = -ACCELERATION_Z_STEPS_PER_SS;
        command_Gcode command4 = {MOVE_COMMAND,      0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
        z = dZn+zStar;              v = -vStar;                                         a = ACCELERATION_Z_STEPS_PER_SS;
        command_Gcode command5 = {MOVE_COMMAND,      0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
        return;
    }

    z = -L_HOME_Z;              v = 0;                                              a = -ACCELERATION_Z_STEPS_PER_SS;
    command_Gcode command4 = {MOVE_COMMAND,      0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
    z = dZn+2*L_HOME_Z;         v = -HOME_COARSE_SPEED_Z_STEPS_PER_SECOND;          a = 0;
    command_Gcode command5 = {MOVE_COMMAND,      0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
    z = -L_HOME_Z;              v = -HOME_COARSE_SPEED_Z_STEPS_PER_SECOND;          a = ACCELERATION_Z_STEPS_PER_SS;
    command_Gcode command6 = {MOVE_COMMAND,      0, 0, z, 0,    0, 0, v, 0,    0, 0, a, 0,   0, 0};     firstInCommandBuffer_Gcode(command6);
}

static void HomeXY_Analyser(void)
{
    long dXn = getDescreteCommandBufferElement_Gcode(2).Xn;
    long dYn = getDescreteCommandBufferElement_Gcode(2).Yn;

    long x; long y; float v; float a;   float vX; float vY; float aX; float aY;

    x = 0;                      y = 0;                          v = -HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;        a = 0;
    command_Gcode command1 = {GO_HOME_XY_COMMAND, x, y, 0, 0,   v, v, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command1);
    x = HOME_FINE_STEPS_XY;     y = HOME_FINE_STEPS_XY;         v = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND;         a = 0;
    command_Gcode command2 = {MOVE_COMMAND,       x, y, 0, 0,   v, v, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command2);
    x = 0;                      y = 0;                          v = -HOME_FINE_SPEED_XY_STEPS_PER_SECOND;          a = 0;
    command_Gcode command3 = {GO_HOME_XY_COMMAND, x, y, 0, 0,   v, v, 0, 0,    a, 0, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command3);

    if (dXn == 0 && dYn == 0) return;
    if (dXn <  0 || dYn <  0) return;

    float distance_XY = sqrtf(pow(dXn,2)+pow(dYn,2));
    float cosX = (float)dXn/distance_XY;    float targetSpeedX = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND*cosX;  float accelerationX = ACCELERATION_XY_STEPS_PER_SS*cosX;
    float cosY = (float)dYn/distance_XY;    float targetSpeedY = HOME_COARSE_SPEED_XY_STEPS_PER_SECOND*cosY;  float accelerationY = ACCELERATION_XY_STEPS_PER_SS*cosY;
    float startDistance_XY = pow(HOME_COARSE_SPEED_XY_STEPS_PER_SECOND,2)/(2*ACCELERATION_XY_STEPS_PER_SS);
    long l_HOME_X = lroundf(startDistance_XY*cosX);     long l_HOME_Y = lroundf(startDistance_XY*cosY);

    if (distance_XY < 2*startDistance_XY)
    {
        long xStar = lroundf(0.25+(float)dXn/2);   float vStarX = cosX*sqrtf(2*ACCELERATION_XY_STEPS_PER_SS*distance_XY);
        long yStar = lroundf(0.25+(float)dYn/2);   float vStarY = cosY*sqrtf(2*ACCELERATION_XY_STEPS_PER_SS*distance_XY);
        x = xStar;              y = yStar;              vX = 0;                vY = 0;              aX = accelerationX;     aY = accelerationY;
        command_Gcode command4 = {MOVE_COMMAND,      x, y, 0, 0,    vX, vY, 0, 0,    aX, aY, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
        x = dXn-xStar;          y = dYn-yStar;          vX = vStarX;           vY = vStarY;         aX = -accelerationX;    aY = -accelerationY;
        command_Gcode command5 = {MOVE_COMMAND,      x, y, 0, 0,    vX, vY, 0, 0,    aX, aY, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
        return;
    }

    x = l_HOME_X;           y = l_HOME_Y;           vX = 0;                vY = 0;                aX = accelerationX;     aY = accelerationY;
    command_Gcode command4 = {MOVE_COMMAND,      x, y, 0, 0,    vX, vY, 0, 0,    aX, aY, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command4);
    x = dXn-2*l_HOME_X;     y = dYn-2*l_HOME_Y;     vX = targetSpeedX;     vY = targetSpeedY;     aX = 0;                 aY = 0;
    command_Gcode command5 = {MOVE_COMMAND,      x, y, 0, 0,    vX, vY, 0, 0,    aX, aY, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command5);
    x = l_HOME_X;           y = l_HOME_Y;           vX = targetSpeedX;     vY = targetSpeedY;     aX = -accelerationX;    aY = -accelerationY;
    command_Gcode command6 = {MOVE_COMMAND,      x, y, 0, 0,    vX, vY, 0, 0,    aX, aY, 0, 0,   0, 0};     firstInCommandBuffer_Gcode(command6);
}

static void SetExtrTemp_Analyser(void)
{
    float t  = getDescreteCommandBufferElement_Gcode(2).extrT;
    command_Gcode command = {HEAT_EXTRUDER_COMMAND, 0, 0, 0, 0,   0, 0, 0, 0,    0, 0, 0, 0,   t, 0};     firstInCommandBuffer_Gcode(command);
}

static void SetBedTemp_Analyser(void)
{
    float t  = getDescreteCommandBufferElement_Gcode(2).bedT;
    command_Gcode command = {HEAT_BED_COMMAND, 0, 0, 0, 0,   0, 0, 0, 0,    0, 0, 0, 0,   0, t};     firstInCommandBuffer_Gcode(command);
}

static void WaitExtrTemp_Analyser(void)
{
    float t  = getDescreteCommandBufferElement_Gcode(2).extrT;
    command_Gcode command = {WAIT_HEAT_EXTRUDER_COMMAND, 0, 0, 0, 0,   0, 0, 0, 0,    0, 0, 0, 0,   t, 0};     firstInCommandBuffer_Gcode(command);
}

static void WaitBedTemp_Analyser(void)
{
    float t  = getDescreteCommandBufferElement_Gcode(2).bedT;
    command_Gcode command = {WAIT_HEAT_BED_COMMAND, 0, 0, 0, 0,   0, 0, 0, 0,    0, 0, 0, 0,   0, t};     firstInCommandBuffer_Gcode(command);
}

void descreteCommandAnalyser_Gcode(void)
{
    commandType_Gcode typeOfCommand = getDescreteCommandBufferElement_Gcode(2).type;
    long dXn = getDescreteCommandBufferElement_Gcode(2).Xn - getDescreteCommandBufferElement_Gcode(1).Xn;
    long dYn = getDescreteCommandBufferElement_Gcode(2).Yn - getDescreteCommandBufferElement_Gcode(1).Yn;
    long dZn = getDescreteCommandBufferElement_Gcode(2).Zn - getDescreteCommandBufferElement_Gcode(1).Zn;
    long dEn = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;

    if (typeOfCommand == MOVE_COMMAND)
    {
        if (dZn != 0)
            MoveZ_Analyser();
        if (dXn != 0 || dYn != 0)
        {
            MoveXY_Analyser();
            return;
        }
        if (dEn != 0)
            MoveE_Analyser();
        return;
    }

    if (typeOfCommand == GO_HOME_X_COMMAND)   {HomeX_Analyser();  return;}
    if (typeOfCommand == GO_HOME_Y_COMMAND)   {HomeY_Analyser();  return;}
    if (typeOfCommand == GO_HOME_Z_COMMAND)   {HomeZ_Analyser();  return;}
    if (typeOfCommand == GO_HOME_XY_COMMAND)  {HomeXY_Analyser(); return;}
    if (typeOfCommand == GO_HOME_XZ_COMMAND)  {HomeZ_Analyser();  HomeX_Analyser();  return;}
    if (typeOfCommand == GO_HOME_YZ_COMMAND)  {HomeZ_Analyser();  HomeY_Analyser();  return;}
    if (typeOfCommand == GO_HOME_XYZ_COMMAND) {HomeZ_Analyser();  HomeXY_Analyser(); return;}

    if (typeOfCommand == HEAT_EXTRUDER_COMMAND)   {SetExtrTemp_Analyser();  return;}
    if (typeOfCommand == HEAT_BED_COMMAND)        {SetBedTemp_Analyser();   return;}

    if (typeOfCommand == WAIT_HEAT_EXTRUDER_COMMAND)   {WaitExtrTemp_Analyser();  return;}
    if (typeOfCommand == WAIT_HEAT_BED_COMMAND)        {WaitBedTemp_Analyser();   return;}
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

static _Bool smoothable(commandType_Gcode commandType)
{
    if( commandType == MOVE_COMMAND) return true;
    return false;
}

void smoothStop_Gcode(void)
{
    int currentCommandNumber = lastCommandNumber();
    command_Gcode command = commandBuffer[number(currentCommandNumber)];

    if (!smoothable(command.type)) return;

    float speedAtTheEnd = 0;
    float speedAtTheStart = sqrtf(pow(command.FnX,2)+pow(command.FnY,2));
    float acceleration = ACCELERATION_XY_STEPS_PER_SS;
    float allowedDistance = sqrtf( pow(command.dXn,2) + pow(command.dYn,2) );
    float cosX = (float)command.dXn/allowedDistance;
    float cosY = (float)command.dYn/allowedDistance;
    float cosE = (float)command.dEn/allowedDistance;

    //if    (allowedDistance + 0.5 > distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration)) return;
    //while (allowedDistance + 0.5 < distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration))
    if    (allowedDistance + 1 >= distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration)) return;
    while (allowedDistance + 1 <  distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration))
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


_Bool descreteCommandIsRepeated(descreteCommand_Gcode descreteCommand)
{
    if( descreteBuffer[number(3)].type == descreteCommand.type &&
        descreteBuffer[number(3)].Xn == descreteCommand.Xn &&
        descreteBuffer[number(3)].Yn == descreteCommand.Yn &&
        descreteBuffer[number(3)].Zn == descreteCommand.Zn &&
        fabs(descreteBuffer[number(3)].FnXY - descreteCommand.FnXY) < 0.1 &&
        fabs(descreteBuffer[number(3)].FnZ - descreteCommand.FnZ) < 0.1 &&
        fabs(descreteBuffer[number(3)].FnE - descreteCommand.FnE) < 0.1 &&
        fabs(descreteBuffer[number(3)].extrT - descreteCommand.extrT) < 0.1 &&
        fabs(descreteBuffer[number(3)].bedT - descreteCommand.bedT) < 0.1
        ) return true;
    return false;
}
