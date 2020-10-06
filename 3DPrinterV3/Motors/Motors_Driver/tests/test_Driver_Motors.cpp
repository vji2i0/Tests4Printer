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
}

TEST_GROUP(Driver_Motors)
{
    void setup()
    {
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


TEST(Driver_Motors, nothing)
{
    //mock_c()->expectOneCall("RS_low_LCD");
}
