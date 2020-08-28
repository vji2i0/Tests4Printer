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
#include "State_USBdrive.h"
}

TEST_GROUP(State_USBdrive)
{
    void setup()
    {
        createState_USBdrive();
    }
    void teardown()
    {
    }
};

TEST(State_USBdrive, get_state_after_initialization)
{
    CHECK_EQUAL(NOT_READY_USBDRIVE, getState_USBdrive());
}

TEST(State_USBdrive, set_state_ready_get_state_ready)
{
    setState_USBdrive(READY_USBDRIVE);
    CHECK_EQUAL(READY_USBDRIVE, getState_USBdrive());
}

TEST(State_USBdrive, set_state_notready_get_state_notready)
{
    setState_USBdrive(NOT_READY_USBDRIVE);
    CHECK_EQUAL(NOT_READY_USBDRIVE, getState_USBdrive());
}
