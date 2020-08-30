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

static long distanceStartFastMove(long totalDistance, float speedStart, float speedFinish, float accelerationStart, float accelerationFinish)
{
    float distance_float;
    distance_float = (float)totalDistance*(accelerationFinish/(accelerationFinish-accelerationStart))
                    +(speedFinish*speedFinish-speedStart*speedStart)/(2*(accelerationFinish-accelerationStart));
    return lroundf(distance_float);
}

static long distanceFinishFastMove(long totalDistance, float speedStart, float speedFinish, float accelerationStart, float accelerationFinish)
{
    float distance_float;
    distance_float = (float)totalDistance*(accelerationStart/(accelerationStart-accelerationFinish))
                    -(speedFinish*speedFinish-speedStart*speedStart)/(2*(accelerationStart-accelerationFinish));
    return lroundf(distance_float);
}

static float speedMaxFastMove(long totalDistance, float speedStart, float speedFinish, float accelerationStart, float accelerationFinish)
{
    float speed;
    speed = (float)sign(totalDistance)*sqrt(
                (float)totalDistance*(2*accelerationStart*accelerationFinish/(accelerationFinish-accelerationStart))
                -(speedFinish*speedFinish*accelerationStart-speedStart*speedStart*accelerationFinish)/(accelerationFinish-accelerationStart)
                );
    return speed;
}

static void MoveX_Analyser(void)
{
    long Xn = getDescreteCommandBufferElement_Gcode(2).Xn - getDescreteCommandBufferElement_Gcode(1).Xn;
    long Yn = getDescreteCommandBufferElement_Gcode(2).Yn - getDescreteCommandBufferElement_Gcode(1).Yn;
    long En = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;
    float distance_XY = sqrtf((float)Xn*(float)Xn+(float)Yn*(float)Yn);
    float cosX = (float)Xn/distance_XY;     float cosY = (float)Yn/distance_XY;     float tgEX = (float)En/(float)Xn;
    float speedTarget = getDescreteCommandBufferElement_Gcode(2).FnXY*cosX;
    if ( getDescreteCommandBufferElement_Gcode(2).FnXY > MAX_SPEED_XY_STEPS_PER_SECONDS ) speedTarget = MAX_SPEED_XY_STEPS_PER_SECONDS*cosX;
    if (En != 0) if ( fabs(speedTarget*tgEX) > MAX_SPEED_E_STEPS_PER_SECONDS ) speedTarget = sign(speedTarget)*(float)MAX_SPEED_E_STEPS_PER_SECONDS/fabs(tgEX);
    float speedStart = 0;
    if ( conserveSpeedStart(Xn, Yn, 0) ) speedStart = sign(Xn)*sqrt(2*lastCommand().dXn*lastCommand().AnX+pow(lastCommand().FnX,2));
    float speedFinish = 0;
    if ( conserveSpeedFinish(Xn, Yn, 0) ) speedFinish = speedTarget;
    float accelerationStart = ACCELERATION_XY_STEPS_PER_SS*sign(speedTarget-speedStart)*fabs(cosX);
    float accelerationFinish = ACCELERATION_XY_STEPS_PER_SS*sign(speedFinish-speedTarget)*fabs(cosX);
    long XnStart = lroundf(0.5*(speedTarget*speedTarget-speedStart*speedStart)/accelerationStart);
    long XnFinish = lroundf(0.5*(speedFinish*speedFinish-speedTarget*speedTarget)/accelerationFinish);
    long XnMiddle = Xn - XnStart - XnFinish;
    if( sign(XnMiddle) != sign(Xn) )
    {
        if( conserveSpeedFinish(Xn, Yn, 0) )
        {
            long x1 = Xn;                   long y1 = Yn;                   long e1 = En;
            float vX1 = speedStart;         float vY1 = vX1*cosY/cosX;      float vE1 = vX1*tgEX;
            float aX1 = accelerationStart;  float aY1 = aX1*cosY/cosX;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);  return;
        }
        if( conserveSpeedStart(Xn, Yn, 0) )
        {
            long x1 = Xn;                   long y1 = Yn;                   long e1 = En;
            float vX1 = speedStart;         float vY1 = vX1*cosY/cosX;      float vE1 = vX1*tgEX;
            float aX1 = accelerationFinish; float aY1 = aX1*cosY/cosX;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);  return;
        }
        long x1 = distanceStartFastMove(Xn, speedStart, speedFinish, accelerationStart, accelerationFinish);    long y1 = lroundf(x1*cosY/cosX);    long e1 = lroundf(x1*tgEX);
        float vX1 = speedStart;                                                                                 float vY1 = vX1*cosY/cosX;          float vE1 = vX1*tgEX;
        float aX1 = accelerationStart;                                                                          float aY1 = aX1*cosY/cosX;
        command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);
        long x2 = distanceFinishFastMove(Xn, speedStart, speedFinish, accelerationStart, accelerationFinish);   long y2 = Yn - y1;                  long e2 = En - e1;
        float vX2 = speedMaxFastMove(Xn, speedStart, speedFinish, accelerationStart, accelerationFinish);       float vY2 = vX2*cosY/cosX;          float vE2 = vX2*tgEX;
        float aX2 = accelerationFinish;                                                                         float aY2 = aX2*cosY/cosX;
        command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0,   0, 0};  firstInCommandBuffer_Gcode(command2);  return;
    }
    long x1 = XnStart;              long y1 = lroundf(x1*cosY/cosX);    long e1 = lroundf(x1*tgEX);
    float vX1 = speedStart;         float vY1 = vX1*cosY/cosX;          float vE1 = vX1*tgEX;
    float aX1 = accelerationStart;  float aY1 = aX1*cosY/cosX;
    command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  if(x1 != 0) firstInCommandBuffer_Gcode(command1);
    long x2 = XnMiddle;             long y2 = lroundf(x2*cosY/cosX);    long e2 = lroundf(x2*tgEX);     if(XnFinish == 0) {y2 = Yn - y1; e2 = En - e1;}
    float vX2 = speedTarget;        float vY2 = vX2*cosY/cosX;          float vE2 = vX2*tgEX;
    float aX2 = 0;                  float aY2 = aX2*cosY/cosX;
    command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0,   0, 0};  firstInCommandBuffer_Gcode(command2);
    long x3 = XnFinish;             long y3 = Yn - y2 - y1;             long e3 = lroundf(x3*tgEX);
    float vX3 = speedTarget;        float vY3 = vX3*cosY/cosX;          float vE3 = vX3*tgEX;
    float aX3 = accelerationFinish; float aY3 = aX3*cosY/cosX;
    command_Gcode command3 = {MOVE_COMMAND, x3, y3, 0, e3,    vX3, vY3, 0, vE3,    aX3, aY3, 0,   0, 0};  if(x3 != 0) firstInCommandBuffer_Gcode(command3);
}

static void MoveY_Analyser(void)
{
    long Xn = getDescreteCommandBufferElement_Gcode(2).Xn - getDescreteCommandBufferElement_Gcode(1).Xn;
    long Yn = getDescreteCommandBufferElement_Gcode(2).Yn - getDescreteCommandBufferElement_Gcode(1).Yn;
    long En = getDescreteCommandBufferElement_Gcode(2).En - getDescreteCommandBufferElement_Gcode(1).En;
    float distance_XY = sqrtf((float)Xn*(float)Xn+(float)Yn*(float)Yn);
    float cosY = (float)Yn/distance_XY;     float cosX = (float)Xn/distance_XY;     float tgEY = (float)En/(float)Yn;
    float speedTarget = getDescreteCommandBufferElement_Gcode(2).FnXY*cosY;
    if ( getDescreteCommandBufferElement_Gcode(2).FnXY > MAX_SPEED_XY_STEPS_PER_SECONDS ) speedTarget = MAX_SPEED_XY_STEPS_PER_SECONDS*cosY;
    if (En != 0) if ( fabs(speedTarget*tgEY) > MAX_SPEED_E_STEPS_PER_SECONDS ) speedTarget = sign(speedTarget)*(float)MAX_SPEED_E_STEPS_PER_SECONDS/fabs(tgEY);
    float speedStart = 0;
    if ( conserveSpeedStart(Xn, Yn, 0) ) speedStart = sign(Yn)*sqrt(2*lastCommand().dYn*lastCommand().AnY+lastCommand().FnY*lastCommand().FnY);
    float speedFinish = 0;
    if ( conserveSpeedFinish(Xn, Yn, 0) ) speedFinish = speedTarget;
    float accelerationStart = ACCELERATION_XY_STEPS_PER_SS*sign(speedTarget-speedStart)*fabs(cosY);
    float accelerationFinish = ACCELERATION_XY_STEPS_PER_SS*sign(speedFinish-speedTarget)*fabs(cosY);
    long YnStart = lroundf(0.5*(speedTarget*speedTarget-speedStart*speedStart)/accelerationStart);
    long YnFinish = lroundf(0.5*(speedFinish*speedFinish-speedTarget*speedTarget)/accelerationFinish);
    long YnMiddle = Yn - YnStart - YnFinish;
    if( sign(YnMiddle) != sign(Yn) )
    {
        if( conserveSpeedFinish(Xn, Yn, 0) )
        {
            long y1 = Yn;                       long x1 = Xn;                   long e1 = En;
            float vY1 = speedStart;             float vX1 = vY1*cosX/cosY;      float vE1 = vY1*tgEY;
            float aY1 = accelerationStart;      float aX1 = aY1*cosX/cosY;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);  return;
        }
        if( conserveSpeedStart(Xn, Yn, 0) )
        {
            long y1 = Yn;                       long x1 = Xn;                   long e1 = En;
            float vY1 = speedStart;             float vX1 = vY1*cosX/cosY;      float vE1 = vY1*tgEY;
            float aY1 = accelerationFinish;     float aX1 = aY1*cosX/cosY;
            command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);  return;
        }
        long y1 = distanceStartFastMove(Yn, speedStart, speedFinish, accelerationStart, accelerationFinish);    long x1 = lroundf(y1*cosX/cosY);    long e1 = lroundf(y1*tgEY);
        float vY1 = speedStart;                                                                                 float vX1 = vY1*cosX/cosY;          float vE1 = vY1*tgEY;
        float aY1 = accelerationStart;                                                                          float aX1 = aY1*cosX/cosY;
        command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  firstInCommandBuffer_Gcode(command1);
        long y2 = distanceFinishFastMove(Yn, speedStart, speedFinish, accelerationStart, accelerationFinish);   long x2 = Xn - x1;                  long e2 = En - e1;
        float vY2 = speedMaxFastMove(Yn, speedStart, speedFinish, accelerationStart, accelerationFinish);       float vX2 = vY2*cosX/cosY;          float vE2 = vY2*tgEY;
        float aY2 = accelerationFinish;                                                                         float aX2 = aY2*cosX/cosY;
        command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0,   0, 0};  firstInCommandBuffer_Gcode(command2);  return;
    }
    long y1 = YnStart;                  long x1 = lroundf(y1*cosX/cosY);    long e1 = lroundf(y1*tgEY);
    float vY1 = speedStart;             float vX1 = vY1*cosX/cosY;          float vE1 = vY1*tgEY;
    float aY1 = accelerationStart;      float aX1 = aY1*cosX/cosY;
    command_Gcode command1 = {MOVE_COMMAND, x1, y1, 0, e1,    vX1, vY1, 0, vE1,    aX1, aY1, 0,   0, 0};  if(y1 != 0) firstInCommandBuffer_Gcode(command1);
    long y2 = YnMiddle;                 long x2 = lroundf(y2*cosX/cosY);    long e2 = lroundf(y2*tgEY);     if(YnFinish == 0) {x2 = Xn - x1; e2 = En - e1;}
    float vY2 = speedTarget;            float vX2 = vY2*cosX/cosY;          float vE2 = vY2*tgEY;
    float aY2 = 0;                      float aX2 = aY2*cosX/cosY;
    command_Gcode command2 = {MOVE_COMMAND, x2, y2, 0, e2,    vX2, vY2, 0, vE2,    aX2, aY2, 0,   0, 0};  firstInCommandBuffer_Gcode(command2);
    long y3 = YnFinish;                 long x3 = Xn - x2 - x1;             long e3 = lroundf(y3*tgEY);
    float vY3 = speedTarget;            float vX3 = vY3*cosX/cosY;          float vE3 = vY3*tgEY;
    float aY3 = accelerationFinish;     float aX3 = aY3*cosX/cosY;
    command_Gcode command3 = {MOVE_COMMAND, x3, y3, 0, e3,    vX3, vY3, 0, vE3,    aX3, aY3, 0,   0, 0};  if(y3 != 0) firstInCommandBuffer_Gcode(command3);
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
            if (abs(dXn) > abs(dYn)) { MoveX_Analyser(); return;}
            MoveY_Analyser(); return;
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

static _Bool smoothX(command_Gcode command)
{
    if( abs(command.dXn) > abs(command.dYn) )
        return true;
    return false;
}

void smoothStop_Gcode(void)
{
    int currentCommandNumber = lastCommandNumber();         command_Gcode command = commandBuffer[number(currentCommandNumber)];
    float distance_XY = sqrtf( pow((float)command.dXn,2) + pow((float)command.dYn,2) ),   cosX = (float)command.dXn/distance_XY,   cosY = (float)command.dYn/distance_XY;
    float speedAtTheEnd, speedAtTheStart, acceleration;     long allowedDistance;
    if (smoothX(command))
    {
        speedAtTheEnd = 0;                                      speedAtTheStart = command.FnX;
        acceleration = -ACCELERATION_XY_STEPS_PER_SS*cosX;      allowedDistance = abs(command.dXn);
    }else{
        speedAtTheEnd = 0;    speedAtTheStart = command.FnY;
        acceleration = -ACCELERATION_XY_STEPS_PER_SS*cosY;
        allowedDistance = abs(command.dYn);
    }
    if    (allowedDistance > distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration)) return;
    while (allowedDistance < distanceRequired(speedAtTheStart, speedAtTheEnd, acceleration))
    {
        if(smoothX(command))
        {
            commandBuffer[number(currentCommandNumber)].FnX = sign(command.dXn)*sqrtf(pow(speedAtTheEnd,2)-2*acceleration*command.dXn);     commandBuffer[number(currentCommandNumber)].FnY = commandBuffer[number(currentCommandNumber)].FnX*cosY/cosX;
            commandBuffer[number(currentCommandNumber)].AnX = acceleration;                                                                 commandBuffer[number(currentCommandNumber)].AnY = commandBuffer[number(currentCommandNumber)].AnX*cosY/cosX;
        }else{
            commandBuffer[number(currentCommandNumber)].FnY = sign(command.dYn)*sqrtf(pow(speedAtTheEnd,2)-2*acceleration*command.dYn);     commandBuffer[number(currentCommandNumber)].FnX = commandBuffer[number(currentCommandNumber)].FnY*cosX/cosY;
            commandBuffer[number(currentCommandNumber)].AnY = acceleration;                                                                 commandBuffer[number(currentCommandNumber)].AnX = commandBuffer[number(currentCommandNumber)].AnY*cosX/cosY;
        }
        currentCommandNumber = prevoiusCommandNumber(currentCommandNumber);     command = commandBuffer[number(currentCommandNumber)];
        if(smoothX(command))
        {
            speedAtTheEnd = commandBuffer[number(nextCommandNumber(currentCommandNumber))].FnX;     speedAtTheStart = command.FnX;
            acceleration = -ACCELERATION_XY_STEPS_PER_SS*cosX;                                      allowedDistance = abs(command.dXn);
        }else{
            speedAtTheEnd = commandBuffer[number(nextCommandNumber(currentCommandNumber))].FnY;     speedAtTheStart = command.FnY;
            acceleration = -ACCELERATION_XY_STEPS_PER_SS*cosY;                                      allowedDistance = abs(command.dYn);
        }
    }
    shiftRightAllTheCommandsTillThis(currentCommandNumber);
    long xStar, yStar; float vxStar, vyStar, axStar, ayStar;
    if (smoothX(command))
    {
        xStar = lroundf( acceleration*(float)command.dXn/(acceleration-command.AnX) + ( pow(speedAtTheStart,2) - pow(speedAtTheEnd,2) )/2/(acceleration-command.AnX) );  yStar  = lroundf((float)xStar*cosY/cosX);
        vxStar = sign(command.dXn)*sqrtf( pow(speedAtTheEnd,2)-2*acceleration*(float)(command.dXn-xStar) );                                                              vyStar = vxStar*cosY/cosX;
        axStar = acceleration;                                                                                                                                           ayStar = acceleration*cosY/cosX;
    }else{
        yStar = lroundf( acceleration*(float)command.dYn/(acceleration-command.AnY) + ( pow(speedAtTheStart,2) - pow(speedAtTheEnd,2) )/2/(acceleration-command.AnY) );  xStar  = lroundf((float)yStar*cosX/cosY);
        vyStar = sign(command.dYn)*sqrtf( pow(speedAtTheEnd,2)-2*acceleration*(float)(command.dYn-yStar) );                                                              vxStar = vyStar*cosX/cosY;
        ayStar = acceleration;                                                                                                                                           axStar = acceleration*cosX/cosY;
    }
        commandBuffer[number(currentCommandNumber)].dXn = xStar;                commandBuffer[number(currentCommandNumber)].dYn = yStar;
        currentCommandNumber = nextCommandNumber(currentCommandNumber);
        commandBuffer[number(currentCommandNumber)].dXn = command.dXn-xStar;    commandBuffer[number(currentCommandNumber)].dYn = command.dYn-yStar;
        commandBuffer[number(currentCommandNumber)].FnX = vxStar;               commandBuffer[number(currentCommandNumber)].FnY = vyStar;
        commandBuffer[number(currentCommandNumber)].AnX = axStar;               commandBuffer[number(currentCommandNumber)].AnY = ayStar;
}


