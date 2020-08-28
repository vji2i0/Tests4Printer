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
#include "GcodeConverter_Gcode.h"

#include <math.h>
}

TEST_GROUP(GcodeConverter_Gcode)
{
    float floatError = 0.001;
    void setup()
    {
        createGcodeConverter_Gcode();
    }
    void teardown()
    {
    }
};

TEST(GcodeConverter_Gcode, commands_type_check)
{
    CHECK(EMPTY_COMMAND != MOVE_COMMAND);
}

TEST(GcodeConverter_Gcode, create_converted_command)
{
    CHECK_EQUAL(EMPTY_COMMAND, getConvertedCommand_Gcode().type);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().X);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().Y);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().Z);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().E);
    CHECK_EQUAL(F_DEFAULT, getConvertedCommand_Gcode().F);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().bedT);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().extrT);
}

TEST(GcodeConverter_Gcode, convert_G1_after_random_command)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 F999.99");
    convertCommand_Gcode("G1 X10.11 Y20.22 Z30.33 E40.44 F1200.44");

    CHECK_EQUAL(MOVE_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(10.11 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(20.22 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(30.33 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(40.44 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G1_preserve_speed)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G1 X10.11 Y20.22 Z30.33 E40.44");

    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F ) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G1_default_speed)
{
    convertCommand_Gcode("G1 X10.11 Y20.22 Z30.33");

    CHECK( fabs(F_DEFAULT - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G1_save_position_of_unspecified_axes)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G1 X10.11 Y20.22");

    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G92_set_coordinates)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G92 X10.11 Y20.22 Z30.33 E40.44");

    CHECK_EQUAL(SET_COORDINATES_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(10.11 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(20.22 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(30.33 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(40.44 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_xyz)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 X10.11 Y20.22 Z30.33 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_XYZ_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(10.11 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(20.22 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(30.33 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_x)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 X10.11 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_X_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(10.11 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_y)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 Y20.22 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_Y_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(20.22 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_z)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 Z30.33 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_Z_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(30.33 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_xy)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 X10.11 Y20.22 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_XY_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(10.11 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(20.22 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_xz)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 X10.11 Z30.33 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_XZ_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(10.11 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(30.33 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_G28_home_yz)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 Y20.22 Z30.33 E40.44 F1200.44");

    CHECK_EQUAL(GO_HOME_YZ_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(20.22 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(30.33 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(1200.44 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, ignore_G28_home_without_parameters)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("G28 F1200.44");

    CHECK_EQUAL(MOVE_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_M104_set_extruder_temperature)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("M104 T100.04");

    CHECK_EQUAL(HEAT_EXTRUDER_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(100.04 - getConvertedCommand_Gcode().extrT) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_M140_set_bed_temperature)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("M140 T100.04");

    CHECK_EQUAL(HEAT_BED_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(100.04 - getConvertedCommand_Gcode().bedT) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_M109_wait_for_extruder_temperature)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("M109 T100.04");

    CHECK_EQUAL(WAIT_HEAT_EXTRUDER_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(100.04 - getConvertedCommand_Gcode().extrT) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F) < floatError );
}

TEST(GcodeConverter_Gcode, convert_M190_wait_for_bed_temperature)
{
    convertCommand_Gcode("G1 X999.99 Y999.99 Z999.99 E999.99 F9999.99");
    convertCommand_Gcode("M190 T100.04");

    CHECK_EQUAL(WAIT_HEAT_BED_COMMAND, getConvertedCommand_Gcode().type);
    CHECK( fabs(100.04 - getConvertedCommand_Gcode().bedT) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().X) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Y) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().Z) < floatError );
    CHECK( fabs(999.99 - getConvertedCommand_Gcode().E) < floatError );
    CHECK( fabs(9999.99 - getConvertedCommand_Gcode().F) < floatError );
}


TEST(GcodeConverter_Gcode, set_bed_set_extruder_wait_bed)
{
    convertCommand_Gcode("M140 T100.01");
    convertCommand_Gcode("M104 T200.02");

    CHECK( fabs(100.01 - getConvertedCommand_Gcode().bedT) < floatError );
    CHECK( fabs(200.02 - getConvertedCommand_Gcode().extrT) < floatError );

    convertCommand_Gcode("M190");

    CHECK( fabs(100.01 - getConvertedCommand_Gcode().bedT) < floatError );
}

TEST(GcodeConverter_Gcode, unknown_command_is_ignored)
{
    convertCommand_Gcode("G125 X100.01");

    CHECK_EQUAL(EMPTY_COMMAND, getConvertedCommand_Gcode().type);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().X);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().Y);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().Z);
    CHECK_EQUAL(F_DEFAULT, getConvertedCommand_Gcode().F);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().bedT);
    CHECK_EQUAL(0, getConvertedCommand_Gcode().extrT);
}
