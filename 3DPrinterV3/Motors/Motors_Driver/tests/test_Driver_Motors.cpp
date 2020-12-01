//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved
//-    For use by owners of Test-Driven Development for Embedded C,
//-    and attendees of Renaissance Software Consulting, Co. training
//-    classes.
//-
//-    Available at http://pragprog.com/titles/jgade/
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3
//-
//-    Authorized users may use this source code in your own
//-    projects, however the source code may not be used to
//-    create training material, courses, books, articles, and
//-    the like. We make no guarantees that this source code is
//-    fit for any purpose.
//-
//-    www.renaissancesoftware.net james@renaissancesoftware.net
//- ------------------------------------------------------------------


#include "CppUTest/TestHarness.h"


extern "C"
{
#include "CppUTestExt/MockSupport_c.h"
#include "Driver_Motors.h"
#include "GPIO_Motors.h"
}

TEST_GROUP(Driver_Motors)
{
    void setup()
    {
        create_Motors();
    }
    void teardown()
    {
        mock_c()->checkExpectations();
        mock_c()->clear();
    }
};


void EnableX_Motors(void)      { mock_c()->actualCall("EnableX");}
void DisableX_Motors(void)     { mock_c()->actualCall("DisableX");}
void ForwardX_Motors(void)     { mock_c()->actualCall("ForwardX");}
void BackwardX_Motors(void)    { mock_c()->actualCall("BackwardX");}
void StepOnX_Motors(void)      { mock_c()->actualCall("StepOnX");}
void StepOffX_Motors(void)     { mock_c()->actualCall("StepOffX");}
void EnableY_Motors(void)      { mock_c()->actualCall("EnableY");}
void DisableY_Motors(void)     { mock_c()->actualCall("DisableY");}
void ForwardY_Motors(void)     { mock_c()->actualCall("ForwardY");}
void BackwardY_Motors(void)    { mock_c()->actualCall("BackwardY");}
void StepOnY_Motors(void)      { mock_c()->actualCall("StepOnY");}
void StepOffY_Motors(void)     { mock_c()->actualCall("StepOffY");}
void EnableZ_Motors(void)      { mock_c()->actualCall("EnableZ");}
void DisableZ_Motors(void)     { mock_c()->actualCall("DisableZ");}
void ForwardZ_Motors(void)     { mock_c()->actualCall("ForwardZ");}
void BackwardZ_Motors(void)    { mock_c()->actualCall("BackwardZ");}
void StepOnZ_Motors(void)      { mock_c()->actualCall("StepOnZ");}
void StepOffZ_Motors(void)     { mock_c()->actualCall("StepOffZ");}
void EnableE_Motors(void)      { mock_c()->actualCall("EnableE");}
void DisableE_Motors(void)     { mock_c()->actualCall("DisableE");}
void ForwardE_Motors(void)     { mock_c()->actualCall("ForwardE");}
void BackwardE_Motors(void)    { mock_c()->actualCall("BackwardE");}
void StepOnE_Motors(void)      { mock_c()->actualCall("StepOnE");}
void StepOffE_Motors(void)     { mock_c()->actualCall("StepOffE");}


TEST(Driver_Motors, create_and_do_noting)
{
    evaluate_Motors();
}

TEST(Driver_Motors, enable_motors)
{
    mock_c()->expectOneCall("EnableX");
    mock_c()->expectOneCall("EnableY");
    mock_c()->expectOneCall("EnableZ");
    mock_c()->expectOneCall("EnableE");

    enable_Motors();
}

TEST(Driver_Motors, disable_motors)
{
    mock_c()->expectOneCall("DisableX");
    mock_c()->expectOneCall("DisableY");
    mock_c()->expectOneCall("DisableZ");
    mock_c()->expectOneCall("DisableE");

    disable_Motors();
}

TEST(Driver_Motors, step_foreward_along_x)
{
    mock_c()->expectOneCall("ForwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("StepOffX");

    doStepX_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, step_backward_along_x)
{
    mock_c()->expectOneCall("BackwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("StepOffX");

    doStepX_Motors(-1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, step_foreward_along_y)
{
    mock_c()->expectOneCall("ForwardY");
    mock_c()->expectOneCall("StepOnY");
    mock_c()->expectOneCall("StepOffY");

    doStepY_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, step_backward_along_y)
{
    mock_c()->expectOneCall("BackwardY");
    mock_c()->expectOneCall("StepOnY");
    mock_c()->expectOneCall("StepOffY");

    doStepY_Motors(-1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, step_foreward_along_z)
{
    mock_c()->expectOneCall("ForwardZ");
    mock_c()->expectOneCall("StepOnZ");
    mock_c()->expectOneCall("StepOffZ");

    doStepZ_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, step_backward_along_z)
{
    mock_c()->expectOneCall("BackwardZ");
    mock_c()->expectOneCall("StepOnZ");
    mock_c()->expectOneCall("StepOffZ");

    doStepZ_Motors(-1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, step_foreward_along_x_and_y)
{
    mock_c()->expectOneCall("ForwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("ForwardY");
    mock_c()->expectOneCall("StepOffX");
    mock_c()->expectOneCall("StepOnY");
    mock_c()->expectOneCall("StepOffY");

    doStepX_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    doStepY_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, two_sequential_steps_along_x)
{
    mock_c()->expectOneCall("ForwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("StepOffX");
    mock_c()->expectOneCall("ForwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("StepOffX");

    doStepX_Motors(1);
    evaluate_Motors();
    doStepX_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, two_sequential_steps_along_x_backward)
{
    mock_c()->expectOneCall("ForwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("StepOffX");
    mock_c()->expectOneCall("BackwardX");
    mock_c()->expectOneCall("StepOnX");
    mock_c()->expectOneCall("StepOffX");

    doStepX_Motors(1);
    evaluate_Motors();
    doStepX_Motors(-1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, two_sequential_steps_along_y)
{
    mock_c()->expectOneCall("ForwardY");
    mock_c()->expectOneCall("StepOnY");
    mock_c()->expectOneCall("StepOffY");
    mock_c()->expectOneCall("ForwardY");
    mock_c()->expectOneCall("StepOnY");
    mock_c()->expectOneCall("StepOffY");

    doStepY_Motors(1);
    evaluate_Motors();
    doStepY_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, two_sequential_steps_along_z)
{
    mock_c()->expectOneCall("ForwardZ");
    mock_c()->expectOneCall("StepOnZ");
    mock_c()->expectOneCall("StepOffZ");
    mock_c()->expectOneCall("ForwardZ");
    mock_c()->expectOneCall("StepOnZ");
    mock_c()->expectOneCall("StepOffZ");

    doStepZ_Motors(1);
    evaluate_Motors();
    doStepZ_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}

TEST(Driver_Motors, two_sequential_steps_along_e)
{
    mock_c()->expectOneCall("ForwardE");
    mock_c()->expectOneCall("StepOnE");
    mock_c()->expectOneCall("StepOffE");
    mock_c()->expectOneCall("ForwardE");
    mock_c()->expectOneCall("StepOnE");
    mock_c()->expectOneCall("StepOffE");

    doStepE_Motors(1);
    evaluate_Motors();
    doStepE_Motors(1);
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
    evaluate_Motors();
}
