#include "Driver_Motors.h"

#include "GPIO_Motors.h"

static int motorXstate, motorYstate, motorZstate, motorEstate, motorZ1state, motorZ2state;
static int motorXstateBuffer, motorYstateBuffer, motorZstateBuffer, motorEstateBuffer, motorZ1stateBuffer, motorZ2stateBuffer;


void create_Motors(void)
{
    motorXstate = IDLE_MOTORS;
    motorYstate = IDLE_MOTORS;
    motorZstate = IDLE_MOTORS;
    motorEstate = IDLE_MOTORS;

    motorXstateBuffer = IDLE_MOTORS;
    motorYstateBuffer = IDLE_MOTORS;
    motorZstateBuffer = IDLE_MOTORS;
    motorEstateBuffer = IDLE_MOTORS;
}

void enable_Motors(void)
{
    EnableX_Motors();
    EnableY_Motors();
    EnableZ_Motors();
    EnableE_Motors();
}

void disable_Motors(void)
{
    DisableX_Motors();
    DisableY_Motors();
    DisableZ_Motors();
    DisableE_Motors();
}

void doStepX_Motors(long direction)
{
    if (motorXstate == IDLE_MOTORS)
    {
        if (direction == 1)  { motorXstate = FOREWARD_MOTORS; return; }
        if (direction == -1) { motorXstate = BACKWARD_MOTORS; return; }
    }
    if (direction == 1)  { motorXstateBuffer = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorXstateBuffer = BACKWARD_MOTORS; return; }
}

void doStepY_Motors(long direction)
{
    if (motorYstate == IDLE_MOTORS)
    {
        if (direction == 1)  { motorYstate = FOREWARD_MOTORS; return; }
        if (direction == -1) { motorYstate = BACKWARD_MOTORS; return; }
    }
    if (direction == 1)  { motorYstateBuffer = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorYstateBuffer = BACKWARD_MOTORS; return; }
}

void doStepZ_Motors(long direction)
{
    if (motorZstate == IDLE_MOTORS)
    {
        if (direction == 1)  { motorZstate = FOREWARD_MOTORS; return; }
        if (direction == -1) { motorZstate = BACKWARD_MOTORS; return; }
    }
    if (direction == 1)  { motorZstateBuffer = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorZstateBuffer = BACKWARD_MOTORS; return; }
}

void doStepE_Motors(long direction)
{
    if (motorEstate == IDLE_MOTORS)
    {
        if (direction == 1)  { motorEstate = FOREWARD_MOTORS; return; }
        if (direction == -1) { motorEstate = BACKWARD_MOTORS; return; }
    }
    if (direction == 1)  { motorEstateBuffer = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorEstateBuffer = BACKWARD_MOTORS; return; }
/*
    if (motorEstate != IDLE_MOTORS)   return;
    if (direction == 1)  { motorEstate = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorEstate = BACKWARD_MOTORS; return; }
*/
}

void doStepZ1_Motors(long direction)
{
    if (motorZ1state == IDLE_MOTORS)
    {
        if (direction == 1)  { motorZ1state = FOREWARD_MOTORS; return; }
        if (direction == -1) { motorZ1state = BACKWARD_MOTORS; return; }
    }
    if (direction == 1)  { motorZ1stateBuffer = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorZ1stateBuffer = BACKWARD_MOTORS; return; }
}
void doStepZ2_Motors(long direction)
{
    if (motorZ2state == IDLE_MOTORS)
    {
        if (direction == 1)  { motorZ2state = FOREWARD_MOTORS; return; }
        if (direction == -1) { motorZ2state = BACKWARD_MOTORS; return; }
    }
    if (direction == 1)  { motorZ2stateBuffer = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorZ2stateBuffer = BACKWARD_MOTORS; return; }
}

void evaluate_Motors(void)
{
    switch(motorXstate)
    {
        case FOREWARD_MOTORS:   ForwardX_Motors();  motorXstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardX_Motors(); motorXstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnX_Motors();   motorXstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffX_Motors();  motorXstate = motorXstateBuffer; motorXstateBuffer = IDLE_MOTORS; break;
        default:                                    motorXstate = IDLE_MOTORS;      break;
    }
    switch(motorYstate)
    {
        case FOREWARD_MOTORS:   ForwardY_Motors();  motorYstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardY_Motors(); motorYstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnY_Motors();   motorYstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffY_Motors();  motorYstate = motorYstateBuffer; motorYstateBuffer = IDLE_MOTORS; break;
        default:                                    motorYstate = IDLE_MOTORS;      break;
    }
    switch(motorZstate)
    {
        case FOREWARD_MOTORS:   ForwardZ_Motors();  motorZstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardZ_Motors(); motorZstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnZ_Motors();   motorZstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffZ_Motors();  motorZstate = motorZstateBuffer; motorZstateBuffer = IDLE_MOTORS; break;
        default:                                    motorZstate = IDLE_MOTORS;      break;
    }
    switch(motorEstate)
    {
        case FOREWARD_MOTORS:   ForwardE_Motors();  motorEstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardE_Motors(); motorEstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnE_Motors();   motorEstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffE_Motors();  motorEstate = motorEstateBuffer; motorEstateBuffer = IDLE_MOTORS; break;
        default:                                    motorEstate = IDLE_MOTORS;      break;
    }
    switch(motorZ1state)
    {
        case FOREWARD_MOTORS:   ForwardZ1_Motors(); motorZ1state = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardZ1_Motors();motorZ1state = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnZ1_Motors();  motorZ1state = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffZ1_Motors(); motorZ1state = motorZ1stateBuffer; motorZ1stateBuffer = IDLE_MOTORS; break;
        default:                                    motorZ1state = IDLE_MOTORS;      break;
    }
    switch(motorZ2state)
    {
        case FOREWARD_MOTORS:   ForwardZ2_Motors(); motorZ2state = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardZ2_Motors();motorZ2state = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnZ2_Motors();  motorZ2state = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffZ2_Motors(); motorZ2state = motorZ2stateBuffer; motorZ2stateBuffer = IDLE_MOTORS; break;
        default:                                    motorZ2state = IDLE_MOTORS;      break;
    }
}


int getMotorXstate() {return motorXstate;}
int getMotorYstate() {return motorYstate;}
int getMotorZstate() {return motorZstate;}
int getMotorEstate() {return motorEstate;}
