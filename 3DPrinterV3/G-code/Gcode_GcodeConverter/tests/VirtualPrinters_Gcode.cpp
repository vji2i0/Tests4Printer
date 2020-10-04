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
#include "VirtualPrinters_Gcode.h"

#include "Buffer_Gcode.h"
}

const command_Gcode moveXwithoutAccelerationPositive =  {MOVE_COMMAND, 100, 0, 0, 0,    10, 0, 0, 0,    0, 0, 0,   0, 0};
const command_Gcode moveXwithoutAccelerationNegative =  {MOVE_COMMAND, -100, 0, 0, 0,    -10, 0, 0, 0,    0, 0, 0,   0, 0};
const command_Gcode moveYwithoutAccelerationPositive =  {MOVE_COMMAND, 0, 100, 0, 0,    0, 10, 0, 0,    0, 0, 0,   0, 0};
const command_Gcode moveYwithoutAccelerationNegative =  {MOVE_COMMAND, 0, -100, 0, 0,   0, -10, 0, 0,    0, 0, 0,   0, 0};
const command_Gcode moveZwithoutAccelerationPositive =  {MOVE_COMMAND, 0, 0, 100, 0,    0, 0, 10, 0,    0, 0, 0,   0, 0};
const command_Gcode moveZwithoutAccelerationNegative =  {MOVE_COMMAND, 0, 0, -100, 0,   0, 0, -10, 0,    0, 0, 0,   0, 0};
const command_Gcode moveEwithoutAccelerationPositive =  {MOVE_COMMAND, 0, 0, 0, 100,    0, 0, 0, 10,    0, 0, 0,   0, 0};
const command_Gcode moveEwithoutAccelerationNegative =  {MOVE_COMMAND, 0, 0, 0, -100,   0, 0, 0, -10,    0, 0, 0,   0, 0};
const command_Gcode moveXYwithoutAccelerationPositive = {MOVE_COMMAND, 200, 100, 0, 0,    20, 10, 0, 0,    0, 0, 0,   0, 0};
const command_Gcode moveXYwithoutAccelerationNegative = {MOVE_COMMAND, -200, 100, 0, 0,    -20, 10, 0, 0,    0, 0, 0,   0, 0};


TEST_GROUP(VirtualPrinters_Gcode)
{
    void setup()
    {
        virtualPrintersCreate_Gcode();
    }
    void teardown()
    {
    }
};

TEST(VirtualPrinters_Gcode, create_virtual_printers)
{
    CHECK_EQUAL(0, getCurrentX_Gcode());
    CHECK_EQUAL(0, getCurrentY_Gcode());
    CHECK_EQUAL(0, getCurrentZ_Gcode());
    CHECK_EQUAL(0, getCurrentE_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_without_acceleration_positive)
{
    sendCommandToPrinter_Gcode(moveXwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithoutAccelerationPositive.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_without_acceleration_negative)
{
    sendCommandToPrinter_Gcode(moveXwithoutAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithoutAccelerationNegative.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, move_y_without_acceleration_positive)
{
    sendCommandToPrinter_Gcode(moveYwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveYwithoutAccelerationPositive.dYn, getCurrentY_Gcode());
}

TEST(VirtualPrinters_Gcode, move_y_without_acceleration_negative)
{
    sendCommandToPrinter_Gcode(moveYwithoutAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveYwithoutAccelerationNegative.dYn, getCurrentY_Gcode());
}

TEST(VirtualPrinters_Gcode, move_z_without_acceleration_positive)
{
    sendCommandToPrinter_Gcode(moveZwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveZwithoutAccelerationPositive.dZn, getCurrentZ_Gcode());
}

TEST(VirtualPrinters_Gcode, move_z_without_acceleration_negative)
{
    sendCommandToPrinter_Gcode(moveZwithoutAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveZwithoutAccelerationNegative.dZn, getCurrentZ_Gcode());
}

TEST(VirtualPrinters_Gcode, move_e_without_acceleration_positive)
{
    sendCommandToPrinter_Gcode(moveEwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveEwithoutAccelerationPositive.dEn, getCurrentE_Gcode());
}

TEST(VirtualPrinters_Gcode, move_e_without_acceleration_negative)
{
    sendCommandToPrinter_Gcode(moveEwithoutAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveEwithoutAccelerationNegative.dEn, getCurrentE_Gcode());
}

TEST(VirtualPrinters_Gcode, move_xy_without_acceleration_positive)
{
    sendCommandToPrinter_Gcode(moveXYwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXYwithoutAccelerationPositive.dXn, getCurrentX_Gcode());
    CHECK_EQUAL(moveXYwithoutAccelerationPositive.dYn, getCurrentY_Gcode());
}

TEST(VirtualPrinters_Gcode, move_xy_without_acceleration_negative)
{
    sendCommandToPrinter_Gcode(moveXYwithoutAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXYwithoutAccelerationNegative.dXn, getCurrentX_Gcode());
    CHECK_EQUAL(moveXYwithoutAccelerationNegative.dYn, getCurrentY_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_y_without_acceleration_sequential)
{
    sendCommandToPrinter_Gcode(moveXwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithoutAccelerationPositive.dXn, getCurrentX_Gcode());
    CHECK_EQUAL(moveXwithoutAccelerationPositive.dYn, getCurrentY_Gcode());

    sendCommandToPrinter_Gcode(moveYwithoutAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveYwithoutAccelerationPositive.dXn, getCurrentX_Gcode());
    CHECK_EQUAL(moveYwithoutAccelerationPositive.dYn, getCurrentY_Gcode());
}
