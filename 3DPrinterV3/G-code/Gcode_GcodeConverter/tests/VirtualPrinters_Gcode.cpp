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
#include "temperature.h"
#include "Boundary_Gcode.h"

#include "math.h"

#include "CppUTestExt/MockSupport_c.h"
}

const command_Gcode emptyCommand =  {EMPTY_COMMAND, 0, 0, 0, 0,    10, 0, 0, 0,    0, 0, 0, 0,   0, 0};

const command_Gcode moveXwithoutAccelerationPositive =  {MOVE_COMMAND, 100, 0, 0, 0,    10, 0, 0, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveXwithoutAccelerationNegative =  {MOVE_COMMAND, -100, 0, 0, 0,    -10, 0, 0, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveYwithoutAccelerationPositive =  {MOVE_COMMAND, 0, 100, 0, 0,    0, 10, 0, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveYwithoutAccelerationNegative =  {MOVE_COMMAND, 0, -100, 0, 0,   0, -10, 0, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveZwithoutAccelerationPositive =  {MOVE_COMMAND, 0, 0, 100, 0,    0, 0, 10, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveZwithoutAccelerationNegative =  {MOVE_COMMAND, 0, 0, -100, 0,   0, 0, -10, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveEwithoutAccelerationPositive =  {MOVE_COMMAND, 0, 0, 0, 100,    0, 0, 0, 10,    0, 0, 0, 0,   0, 0};
const command_Gcode moveEwithoutAccelerationNegative =  {MOVE_COMMAND, 0, 0, 0, -100,   0, 0, 0, -10,    0, 0, 0, 0,   0, 0};
const command_Gcode moveXYwithoutAccelerationPositive = {MOVE_COMMAND, 200, 100, 0, 0,    20, 10, 0, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveXYwithoutAccelerationNegative = {MOVE_COMMAND, -200, 100, 0, 0,    -20, 10, 0, 0,    0, 0, 0, 0,   0, 0};
const command_Gcode moveXwithAccelerationPositive =     {MOVE_COMMAND, 100, 0, 0, 0,     0, 0, 0, 0,    10, 0, 0, 0,   0, 0};
const command_Gcode moveXwithAccelerationNegative =     {MOVE_COMMAND, -800, 0, 0, 0,    -600, 0, 0, 0,    100, 0, 0, 0,   0, 0};
const command_Gcode moveXwithAccelerationNegative2 =    {MOVE_COMMAND, -1300, 0, 0, 0,   -677, 0, 0, 0,    101, 0, 0, 0,   0, 0};
const command_Gcode moveXZeroDistanseToTravel =         {MOVE_COMMAND,  0, 0, 0, 0,     800, 0, 0, 0,    0, 0, 0, 0,   0, 0};


const command_Gcode moveX_bagged_1 = {MOVE_COMMAND,  17, 0, 0, 0,     0, 0, 0, 0,       13333.3, 0, 0, 0,   0, 0};
const command_Gcode moveX_bagged_2 = {MOVE_COMMAND,  7, 0, 0, 0,     673.3, 0, 0, 0,    13333.3, 0, 0, 0,   0, 0};
const command_Gcode moveX_bagged_3 = {MOVE_COMMAND,  0, 0, 0, 0,     800, 0, 0, 0,      0, 0, 0, 0,   0, 0};
const command_Gcode moveX_bagged_4 = {MOVE_COMMAND,  3, 0, 0, 0,     800, 0, 0, 0,      -13333.3, 0, 0, 0,   0, 0};
const command_Gcode moveX_bagged_5 = {MOVE_COMMAND,  21, 0, 0, 0,    748.331, 0, 0, 0,  -13333.3, 0, 0, 0,   0, 0};

const command_Gcode SetExtruder1Temperature = {HEAT_EXTRUDER_COMMAND,  0, 0, 0, 0,     0, 0, 0, 0,    0, 0, 0, 0,   200, 0};
const command_Gcode SetBedTemperature =       {HEAT_BED_COMMAND,  0, 0, 0, 0,     0, 0, 0, 0,    0, 0, 0, 0,   0, 100};

const command_Gcode WaitForExtruder1Temperature = {WAIT_HEAT_EXTRUDER_COMMAND,  0, 0, 0, 0,     0, 0, 0, 0,    0, 0, 0, 0,   200, 0};
const command_Gcode WaitForBedTemperature =       {WAIT_HEAT_BED_COMMAND,  0, 0, 0, 0,     0, 0, 0, 0,    0, 0, 0, 0,   0, 100};

const command_Gcode homeZ = {GO_HOME_Z_COMMAND, 0, 0, 0, 0,    0, 0, -667, 0,    0, 0, 0, 0,   0, 0};



TEST_GROUP(VirtualPrinters_Gcode)
{
    void setup()
    {
        virtualPrintersCreate_Gcode();
        createBoundary_Gcode();
    }
    void teardown()
    {
        mock_c()->checkExpectations();
        mock_c()->clear();
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

TEST(VirtualPrinters_Gcode, move_x_with_acceleration_positive)
{
    sendCommandToPrinter_Gcode(moveXwithAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithAccelerationPositive.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_with_acceleration_negative)
{
    sendCommandToPrinter_Gcode(moveXwithAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithAccelerationNegative.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_with_acceleration_sequential_commands)
{
    sendCommandToPrinter_Gcode(moveXwithAccelerationNegative);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithAccelerationNegative.dXn, getCurrentX_Gcode());

    sendCommandToPrinter_Gcode(moveXwithAccelerationNegative2);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithAccelerationNegative2.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_zero_distanse_to_travel)
{
    sendCommandToPrinter_Gcode(moveXwithAccelerationPositive);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveXwithAccelerationPositive.dXn, getCurrentX_Gcode());

    sendCommandToPrinter_Gcode(moveXZeroDistanseToTravel);
    //while (!evaluatePrinter_Gcode()) {}
    CHECK(evaluatePrinter_Gcode());
    CHECK_EQUAL(moveXZeroDistanseToTravel.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, move_x_strange_bug)
{
    sendCommandToPrinter_Gcode(moveX_bagged_1);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveX_bagged_1.dXn, getCurrentX_Gcode());

    sendCommandToPrinter_Gcode(moveX_bagged_2);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveX_bagged_2.dXn, getCurrentX_Gcode());

    sendCommandToPrinter_Gcode(moveX_bagged_3);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveX_bagged_3.dXn, getCurrentX_Gcode());

    sendCommandToPrinter_Gcode(moveX_bagged_4);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveX_bagged_4.dXn, getCurrentX_Gcode());

    sendCommandToPrinter_Gcode(moveX_bagged_5);
    while (!evaluatePrinter_Gcode()) {}
    CHECK_EQUAL(moveX_bagged_5.dXn, getCurrentX_Gcode());
}

TEST(VirtualPrinters_Gcode, empty_command)
{
    sendCommandToPrinter_Gcode(emptyCommand);
    CHECK(evaluatePrinter_Gcode())
}

TEST(VirtualPrinters_Gcode, set_extruder1_temperature)
{
    sendCommandToPrinter_Gcode(SetExtruder1Temperature);
    CHECK(evaluatePrinter_Gcode())
    CHECK_EQUAL(SetExtruder1Temperature.extrT, roundf(getTargetExtruder1_Temperature()));
}

TEST(VirtualPrinters_Gcode, set_bed_temperature)
{
    sendCommandToPrinter_Gcode(SetBedTemperature);
    CHECK(evaluatePrinter_Gcode())
    CHECK_EQUAL(SetBedTemperature.bedT, roundf(getTargetBed_Temperature()));
}

TEST(VirtualPrinters_Gcode, wait_for_extruder1_temperature)
{
    sendCommandToPrinter_Gcode(WaitForExtruder1Temperature);
    CHECK(!evaluatePrinter_Gcode())
    CHECK_EQUAL(WaitForExtruder1Temperature.extrT, roundf(getTargetExtruder1_Temperature()));
    regNewTemperature_Extruder1_Temperature(WaitForExtruder1Temperature.extrT - 20);
    CHECK(!moveCompleted());
    CHECK(!evaluatePrinter_Gcode());
    regNewTemperature_Extruder1_Temperature(WaitForExtruder1Temperature.extrT - 10);
    CHECK(!moveCompleted());
    CHECK(!evaluatePrinter_Gcode());
    regNewTemperature_Extruder1_Temperature(WaitForExtruder1Temperature.extrT + 1);
    CHECK(evaluatePrinter_Gcode());
    CHECK(moveCompleted());
}

TEST(VirtualPrinters_Gcode, wait_for_bed_temperature)
{
    sendCommandToPrinter_Gcode(WaitForBedTemperature);
    CHECK(!evaluatePrinter_Gcode())
    CHECK_EQUAL(WaitForBedTemperature.bedT, roundf(getTargetBed_Temperature()));
    regNewTemperature_Bed_Temperature(WaitForBedTemperature.bedT - 20);
    CHECK(!moveCompleted());
    CHECK(!evaluatePrinter_Gcode());
    regNewTemperature_Bed_Temperature(WaitForBedTemperature.bedT - 10);
    CHECK(!moveCompleted());
    CHECK(!evaluatePrinter_Gcode());
    regNewTemperature_Bed_Temperature(WaitForBedTemperature.bedT + 1);
    CHECK(evaluatePrinter_Gcode());
    CHECK(moveCompleted());
}


TEST(VirtualPrinters_Gcode, home_Z1_and_Z2_boundary_is_not_reached)
{
    sendCommandToPrinter_Gcode(homeZ);

    setBoundaryZ1isNotReached_Gcode();
    setBoundaryZ2isNotReached_Gcode();
    CHECK(!boundaryZ1isReached_Gcode());
    CHECK(!boundaryZ2isReached_Gcode());
    CHECK(!evaluatePrinter_Gcode());

    int n;
    for (n=0;n<20;n++) evaluatePrinter_Gcode();

    CHECK(getCurrentZ_Gcode()>0);
}

TEST(VirtualPrinters_Gcode, home_Z1_boundary_is_not_reached)
{
    sendCommandToPrinter_Gcode(homeZ);

    setBoundaryZ1isNotReached_Gcode();
    setBoundaryZ2isReached_Gcode();
    CHECK(!boundaryZ1isReached_Gcode());
    CHECK(boundaryZ2isReached_Gcode());
    CHECK(!evaluatePrinter_Gcode());

    int n;
    for (n=0;n<20;n++) evaluatePrinter_Gcode();

    CHECK(getCurrentZ_Gcode()>0);
}

TEST(VirtualPrinters_Gcode, home_Z2_boundary_is_not_reached)
{
    sendCommandToPrinter_Gcode(homeZ);

    setBoundaryZ1isReached_Gcode();
    setBoundaryZ2isNotReached_Gcode();
    CHECK(boundaryZ1isReached_Gcode());
    CHECK(!boundaryZ2isReached_Gcode());
    CHECK(!evaluatePrinter_Gcode());

    int n;
    for (n=0;n<20;n++) evaluatePrinter_Gcode();

    CHECK(getCurrentZ_Gcode()>0);
}

TEST(VirtualPrinters_Gcode, home_Z_boundary_is_reached)
{
    sendCommandToPrinter_Gcode(homeZ);

    setBoundaryZ1isReached_Gcode();
    setBoundaryZ2isReached_Gcode();
    CHECK(boundaryZ1isReached_Gcode());
    CHECK(boundaryZ2isReached_Gcode());
    CHECK(evaluatePrinter_Gcode());
}
