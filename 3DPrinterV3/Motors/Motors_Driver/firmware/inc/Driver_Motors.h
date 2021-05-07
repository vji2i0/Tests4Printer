#ifndef DRIVER_MOTORS
#define DRIVER_MOTORS


enum {IDLE_MOTORS, FOREWARD_MOTORS, BACKWARD_MOTORS, STEPON_MOTORS, STEPOFF_MOTORS};

void create_Motors(void);

void enable_Motors(void);
void disable_Motors(void);

void doStepX_Motors(long direction);
void doStepY_Motors(long direction);
void doStepZ_Motors(long direction);
void doStepE_Motors(long direction);
void doStepZ1_Motors(long direction);
void doStepZ2_Motors(long direction);

void evaluate_Motors(void);

int getMotorXstate(void);
int getMotorYstate(void);
int getMotorZstate(void);
int getMotorEstate(void);

#endif
