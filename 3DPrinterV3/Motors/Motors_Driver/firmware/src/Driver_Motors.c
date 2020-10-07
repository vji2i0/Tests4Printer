#include "Driver_Motors.h"

#include "GPIO_Motors.h"

static int motorXstate, motorYstate, motorZstate, motorEstate;


void create_Motors(void)
{
    motorXstate = IDLE_MOTORS;
    motorYstate = IDLE_MOTORS;
    motorZstate = IDLE_MOTORS;
    motorEstate = IDLE_MOTORS;
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
    if (motorXstate != IDLE_MOTORS)   return;
    if (direction == 1)  { motorXstate = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorXstate = BACKWARD_MOTORS; return; }
}

void doStepY_Motors(long direction)
{
    if (motorYstate != IDLE_MOTORS)   return;
    if (direction == 1)  { motorYstate = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorYstate = BACKWARD_MOTORS; return; }
}

void doStepZ_Motors(long direction)
{
    if (motorZstate != IDLE_MOTORS)   return;
    if (direction == 1)  { motorZstate = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorZstate = BACKWARD_MOTORS; return; }
}

void doStepE_Motors(long direction)
{
    if (motorEstate != IDLE_MOTORS)   return;
    if (direction == 1)  { motorEstate = FOREWARD_MOTORS; return; }
    if (direction == -1) { motorEstate = BACKWARD_MOTORS; return; }
}

void evaluate_Motors(void)
{
    switch(motorXstate)
    {
        case FOREWARD_MOTORS:   ForwardX_Motors();  motorXstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardX_Motors(); motorXstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnX_Motors();   motorXstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffX_Motors();  motorXstate = IDLE_MOTORS;      break;
        default:                                    motorXstate = IDLE_MOTORS;      break;
    }

    switch(motorYstate)
    {
        case FOREWARD_MOTORS:   ForwardY_Motors();  motorYstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardY_Motors(); motorYstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnY_Motors();   motorYstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffY_Motors();  motorYstate = IDLE_MOTORS;      break;
        default:                                    motorYstate = IDLE_MOTORS;      break;
    }

    switch(motorZstate)
    {
        case FOREWARD_MOTORS:   ForwardZ_Motors();  motorZstate = STEPON_MOTORS;    break;
        case BACKWARD_MOTORS:   BackwardZ_Motors(); motorZstate = STEPON_MOTORS;    break;
        case STEPON_MOTORS:     StepOnZ_Motors();   motorZstate = STEPOFF_MOTORS;   break;
        case STEPOFF_MOTORS:    StepOffZ_Motors();  motorZstate = IDLE_MOTORS;      break;
        default:                                    motorZstate = IDLE_MOTORS;      break;
    }

}
