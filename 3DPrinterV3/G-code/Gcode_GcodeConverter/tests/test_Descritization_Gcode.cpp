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
#include "Descritization_Gcode.h"


#include <math.h>
}

TEST_GROUP(Descritization_Gcode)
{
    float X1=999.99, Y1=999.99, Z1=999.99, E1=999.99, F1=9999.99, bedT1 = 99.99, extrT1 = 99.99;
    //float X2=100.11, Y2=200.22, Z2=300.33, E2=400.44, F2=5000.55, bedT2 = 70.77, extrT2 = 80.88;
    convertedCommand_Gcode convertedMoveCommand_1 = {MOVE_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    convertedCommand_Gcode convertedSetCoordinatesCommand_1 = {SET_COORDINATES_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    convertedCommand_Gcode convertedHomeCommand_1 = {GO_HOME_XYZ_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    convertedCommand_Gcode convertedSetExtruderTemperatureCommand_1 = {HEAT_EXTRUDER_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    convertedCommand_Gcode convertedSetBedTemperatureCommand_1 = {HEAT_BED_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    convertedCommand_Gcode convertedWaitExtruderTemperatureCommand_1 = {WAIT_HEAT_EXTRUDER_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    convertedCommand_Gcode convertedWaitBedTemperatureCommand_1 = {WAIT_HEAT_BED_COMMAND, X1, Y1, Z1, E1, F1, bedT1, extrT1};
    float floatError=0.001, oneStep = 1;
    void setup()
    {
        createDescretization_Gcode();
    }
    void teardown()
    {
    }
};

TEST(Descritization_Gcode, round_float_to_int)
{
    CHECK_EQUAL(1, lroundf(0.9));
    CHECK_EQUAL(1, lroundf(1.1));
    CHECK_EQUAL(1, lroundf(0.5));
    CHECK_EQUAL(2, lroundf(1.5));
    CHECK_EQUAL(0, lroundf(0.49));
}

TEST(Descritization_Gcode, create_descrete_command)
{
    CHECK_EQUAL(EMPTY_COMMAND, getDescreteCommand_Gcode().type);
    CHECK_EQUAL(0, getDescreteCommand_Gcode().Xn);
    CHECK_EQUAL(0, getDescreteCommand_Gcode().Yn);
    CHECK_EQUAL(0, getDescreteCommand_Gcode().Zn);
    CHECK_EQUAL(0, getDescreteCommand_Gcode().En);
    CHECK( fabs(F_DEFAULT*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F_DEFAULT*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnZ) < floatError );
    CHECK( fabs(F_DEFAULT*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnE) < floatError );
    CHECK_EQUAL(0, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(0, getDescreteCommand_Gcode().bedT);
}


TEST(Descritization_Gcode, move_command)
{
    setDescreteCommand_Gcode(convertedMoveCommand_1);

    CHECK_EQUAL(MOVE_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}


TEST(Descritization_Gcode, set_coordinates_command)
{
    setDescreteCommand_Gcode(convertedSetCoordinatesCommand_1);

    CHECK_EQUAL(SET_COORDINATES_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}

TEST(Descritization_Gcode, home_command)
{
    setDescreteCommand_Gcode(convertedHomeCommand_1);

    CHECK_EQUAL(GO_HOME_XYZ_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}

TEST(Descritization_Gcode, set_extruder_temperature)
{
    setDescreteCommand_Gcode(convertedSetExtruderTemperatureCommand_1);

    CHECK_EQUAL(HEAT_EXTRUDER_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}

TEST(Descritization_Gcode, set_bed_temperature)
{
    setDescreteCommand_Gcode(convertedSetBedTemperatureCommand_1);

    CHECK_EQUAL(HEAT_BED_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}

TEST(Descritization_Gcode, wait_extruder_temperature)
{
    setDescreteCommand_Gcode(convertedWaitExtruderTemperatureCommand_1);

    CHECK_EQUAL(WAIT_HEAT_EXTRUDER_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}

TEST(Descritization_Gcode, wait_bed_temperature)
{
    setDescreteCommand_Gcode(convertedWaitBedTemperatureCommand_1);

    CHECK_EQUAL(WAIT_HEAT_BED_COMMAND, getDescreteCommand_Gcode().type);
    CHECK( fabs(X1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Xn) < oneStep );
    CHECK( fabs(Y1*STEPS_PER_MM_XY - getDescreteCommand_Gcode().Yn) < oneStep );
    CHECK( fabs(Z1*STEPS_PER_MM_Z  - getDescreteCommand_Gcode().Zn) < oneStep );
    CHECK( fabs(E1*STEPS_PER_MM_E  - getDescreteCommand_Gcode().En) < oneStep );
    CHECK( fabs(F1*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE - getDescreteCommand_Gcode().FnXY) < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnZ)  < floatError );
    CHECK( fabs(F1*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE  - getDescreteCommand_Gcode().FnE)  < floatError );
    CHECK_EQUAL(bedT1, getDescreteCommand_Gcode().extrT);
    CHECK_EQUAL(extrT1, getDescreteCommand_Gcode().bedT);
}





