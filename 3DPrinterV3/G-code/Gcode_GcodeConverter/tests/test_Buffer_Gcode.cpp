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
#include "Buffer_Gcode.h"

#include <math.h>
#include "stdbool.h"
}

static const float floatError = 0.001;

static void DCMNDCMP_EQUAL(const descreteCommand_Gcode expectedDescreteCommand, const descreteCommand_Gcode actualDescreteCommand)
{
    CHECK_EQUAL(expectedDescreteCommand.type, actualDescreteCommand.type);
    CHECK_EQUAL(expectedDescreteCommand.Xn, actualDescreteCommand.Xn);
    CHECK_EQUAL(expectedDescreteCommand.Yn, actualDescreteCommand.Yn);
    CHECK_EQUAL(expectedDescreteCommand.Zn, actualDescreteCommand.Zn);
    CHECK_EQUAL(expectedDescreteCommand.En, actualDescreteCommand.En);
    CHECK( fabs(expectedDescreteCommand.FnXY - actualDescreteCommand.FnXY) < floatError );
    CHECK( fabs(expectedDescreteCommand.FnZ - actualDescreteCommand.FnZ) < floatError );
    CHECK( fabs(expectedDescreteCommand.FnE - actualDescreteCommand.FnE) < floatError );
    CHECK( fabs(expectedDescreteCommand.extrT - actualDescreteCommand.extrT) < floatError );
    CHECK( fabs(expectedDescreteCommand.bedT - actualDescreteCommand.bedT) < floatError );
}

static void CMNDCMP_EQUAL(const command_Gcode expectedCommand, const command_Gcode actualCommand)
{
    CHECK_EQUAL(expectedCommand.type, actualCommand.type);
    CHECK_EQUAL(expectedCommand.dXn, actualCommand.dXn);
    CHECK_EQUAL(expectedCommand.dYn, actualCommand.dYn);
    CHECK_EQUAL(expectedCommand.dZn, actualCommand.dZn);
    CHECK_EQUAL(expectedCommand.dEn, actualCommand.dEn);
    CHECK( fabs(expectedCommand.FnX - actualCommand.FnX) < floatError );
    CHECK( fabs(expectedCommand.FnY - actualCommand.FnY) < floatError );
    CHECK( fabs(expectedCommand.FnZ - actualCommand.FnZ) < floatError );
    CHECK( fabs(expectedCommand.FnE - actualCommand.FnE) < floatError );
    CHECK( fabs(expectedCommand.extrT - actualCommand.extrT) < floatError );
    CHECK( fabs(expectedCommand.bedT - actualCommand.bedT) < floatError );
}


TEST_GROUP(Buffer_Gcode)
{
    const descreteCommand_Gcode descreteCommand1 = {MOVE_COMMAND, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    const descreteCommand_Gcode descreteCommand2 = {MOVE_COMMAND, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    const descreteCommand_Gcode descreteCommand3 = {MOVE_COMMAND, 3, 3, 3, 3, 3, 3, 3, 3, 3};

    const command_Gcode command1 = {MOVE_COMMAND, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    const command_Gcode command2 = {MOVE_COMMAND, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};


    void setup()
    {
        createDescreteCommandBuffer_Gcode();
        createCommandBuffer_Gcode();
    }
    void teardown()
    {
    }
};

TEST(Buffer_Gcode, create_descrete_buffer)
{
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(1));
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(2));
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(3));
}

TEST(Buffer_Gcode, add_commands_to_descrete_buffer)
{
    addElementToDescreteCommandBuffer_Gcode(descreteCommand1);

    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(1));
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(2));
    DCMNDCMP_EQUAL(descreteCommand1, getDescreteCommandBufferElement_Gcode(3));

    addElementToDescreteCommandBuffer_Gcode(descreteCommand2);

    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(1));
    DCMNDCMP_EQUAL(descreteCommand1, getDescreteCommandBufferElement_Gcode(2));
    DCMNDCMP_EQUAL(descreteCommand2, getDescreteCommandBufferElement_Gcode(3));

    addElementToDescreteCommandBuffer_Gcode(descreteCommand3);

    DCMNDCMP_EQUAL(descreteCommand1, getDescreteCommandBufferElement_Gcode(1));
    DCMNDCMP_EQUAL(descreteCommand2, getDescreteCommandBufferElement_Gcode(2));
    DCMNDCMP_EQUAL(descreteCommand3, getDescreteCommandBufferElement_Gcode(3));

    addElementToDescreteCommandBuffer_Gcode(descreteCommand3);

    DCMNDCMP_EQUAL(descreteCommand2, getDescreteCommandBufferElement_Gcode(1));
    DCMNDCMP_EQUAL(descreteCommand3, getDescreteCommandBufferElement_Gcode(2));
    DCMNDCMP_EQUAL(descreteCommand3, getDescreteCommandBufferElement_Gcode(3));
}

TEST(Buffer_Gcode, clear_descrete_buffer)
{
    addElementToDescreteCommandBuffer_Gcode(descreteCommand1);
    addElementToDescreteCommandBuffer_Gcode(descreteCommand2);
    addElementToDescreteCommandBuffer_Gcode(descreteCommand3);

    clearDescreteBuffer_Gcode();
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(1));
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(2));
    DCMNDCMP_EQUAL(defaultDescreteCommand, getDescreteCommandBufferElement_Gcode(3));
}

TEST(Buffer_Gcode, create_command_buffer)
{
    int n;
    for (n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        CMNDCMP_EQUAL(defaultCommand, getCommandBufferElement_Gcode(n));
}

TEST(Buffer_Gcode, add_and_free_one_command_in_buffer)
{
    CMNDCMP_EQUAL(defaultCommand, firstOutCommandBuffer_Gcode());

    firstInCommandBuffer_Gcode(command1);
    CMNDCMP_EQUAL(command1, firstOutCommandBuffer_Gcode());

    eraseFirstCommandBuffer_Gcode();
    CMNDCMP_EQUAL(defaultCommand, firstOutCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, add_and_free_multiple_commands_in_buffer)
{
    CMNDCMP_EQUAL(defaultCommand, firstOutCommandBuffer_Gcode());

    firstInCommandBuffer_Gcode(command1);
    firstInCommandBuffer_Gcode(command2);

    CMNDCMP_EQUAL(command1, firstOutCommandBuffer_Gcode());
    eraseFirstCommandBuffer_Gcode();
    CMNDCMP_EQUAL(command2, firstOutCommandBuffer_Gcode());
    eraseFirstCommandBuffer_Gcode();
    CMNDCMP_EQUAL(defaultCommand, firstOutCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, do_not_free_empty_element_of_command_buffer)
{
    eraseFirstCommandBuffer_Gcode();
    firstInCommandBuffer_Gcode(command1);

    CMNDCMP_EQUAL(command1, firstOutCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, circle_the_command_buffer)
{
    int n;
    for(n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        firstInCommandBuffer_Gcode(command1);
    for(n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        eraseFirstCommandBuffer_Gcode();

    firstInCommandBuffer_Gcode(command2);
    CMNDCMP_EQUAL(command2, getCommandBufferElement_Gcode(1));
    CMNDCMP_EQUAL(command2, firstOutCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, do_not_add_element_to_a_full_command_buffer)
{
    int n;
    for(n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        firstInCommandBuffer_Gcode(command1);
    CMNDCMP_EQUAL(command1, firstOutCommandBuffer_Gcode());


    firstInCommandBuffer_Gcode(command2);
    CMNDCMP_EQUAL(command1, firstOutCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, free_space_check_of_empty_command_buffer)
{
    CHECK_EQUAL(COMMAND_BUFFER_LENGTH, checkFreeSpaceCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, free_space_check_command_buffer_one_command_is_added)
{
    firstInCommandBuffer_Gcode(command1);
    CHECK_EQUAL(COMMAND_BUFFER_LENGTH-1, checkFreeSpaceCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, free_space_check_of_full_command_buffer)
{
    int n;
    for(n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        firstInCommandBuffer_Gcode(command1);
    CHECK_EQUAL(0, checkFreeSpaceCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, free_space_check_command_buffer_over_circle)
{
    int n;
    for(n=1; n<=COMMAND_BUFFER_LENGTH; n++)
        firstInCommandBuffer_Gcode(command1);
    for(n=1; n<=COMMAND_BUFFER_LENGTH-1; n++)
        eraseFirstCommandBuffer_Gcode();
    CHECK_EQUAL(COMMAND_BUFFER_LENGTH-1, checkFreeSpaceCommandBuffer_Gcode());
}

TEST(Buffer_Gcode, enogh_space_is_reserved_in_command_buffer)
{
    CHECK(enoghSpaceIsReservedCommandBuffer_Gcode());

    int n;
    for(n=1; n<=COMMAND_BUFFER_LENGTH-RESERVE_LENGTH-1; n++)
        firstInCommandBuffer_Gcode(command1);
    CHECK(enoghSpaceIsReservedCommandBuffer_Gcode());

    firstInCommandBuffer_Gcode(command1);
    CHECK(!enoghSpaceIsReservedCommandBuffer_Gcode());
}






TEST_GROUP(Descrete_command_analyser_Gcode)
{


    void setup()
    {
        createDescreteCommandBuffer_Gcode();
        createCommandBuffer_Gcode();
    }
    void teardown()
    {
    }
};

static const float aDefault = (float)ACCELERATION_MM_MIN_S_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float aDefaultZ = (float)ACCELERATION_MM_MIN_S_Z*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float maxSpeedXY = (float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float maxSpeedZ = (float)MAX_SPEED_MM_MIN_Z*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float maxSpeedE = (float)MAX_SPEED_MM_MIN_E*(float)STEPS_PER_MM_E/(float)SECONDS_IN_MINUTE;

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_X)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(descreteMoveXSlow.FnXY - v2) < floatError );    CHECK( fabs(descreteMoveXSlow.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_X_backwards)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, -10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                              CHECK(x2 < 0);                              CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(-descreteMoveXSlow.FnXY - v2) < floatError );   CHECK( fabs(-descreteMoveXSlow.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_X_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 100000, 0, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(maxSpeedXY-v2) < floatError );  CHECK( fabs(maxSpeedXY-v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(-aDefault - a3) < floatError);
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_X)
{
    const descreteCommand_Gcode descreteMoveXFast = {MOVE_COMMAND, 100, 0, 0, 0,     3000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXFast.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1>0);                                CHECK(x2>0);
    CHECK_EQUAL(descreteMoveXFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(maxSpeedXY) > fabs(v2) );
    CHECK( v2 > 0 );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(-aDefault - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_X_backwards)
{
    const descreteCommand_Gcode descreteMoveXFast = {MOVE_COMMAND, -100, 0, 0, 0,     3000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXFast.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1<0);                                CHECK(x2<0);
    CHECK_EQUAL(descreteMoveXFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(maxSpeedXY) > fabs(v2) );
    CHECK( v2 < 0 );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );  CHECK( fabs(aDefault - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_X_do_not_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND,     0, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(descreteMoveXSlow1.FnXY - v2) < floatError );   CHECK( fabs(descreteMoveXSlow1.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(4).dXn;  x2 = getCommandBufferElement_Gcode(5).dXn;                  x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK(x1 < 0);                              CHECK(x2 < 0);                                              CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn-descreteMoveXSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;  y2 = getCommandBufferElement_Gcode(5).dYn;                  y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(4).FnX;  v2 = getCommandBufferElement_Gcode(5).FnX;                  v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(-descreteMoveXSlow2.FnXY - v2) < floatError );  CHECK( fabs(-descreteMoveXSlow2.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;  v2 = getCommandBufferElement_Gcode(5).FnY;                  v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;  a2 = getCommandBufferElement_Gcode(5).AnX;                  a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;  a2 = getCommandBufferElement_Gcode(5).AnY;                  a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_X_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 20000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                              CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                                         CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(descreteMoveXSlow1.FnXY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;                  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;                  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault - a1) < floatError );                  CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;                  x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                              CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn-descreteMoveXSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;                  y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);                                         CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;                  v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(descreteMoveXSlow2.FnXY - v1) < floatError );   CHECK( fabs(descreteMoveXSlow2.FnXY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;                  v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;                  a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(-aDefault - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;                  a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_X_backwards_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, -10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, -20000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                              CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                                         CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(-descreteMoveXSlow1.FnXY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;                  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;                  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );                  CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;                  x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                              CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn-descreteMoveXSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;                  y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);                                         CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;                  v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(-descreteMoveXSlow2.FnXY - v1) < floatError );  CHECK( fabs(-descreteMoveXSlow2.FnXY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;                  v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;                  a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(aDefault - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;                  a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_X_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND,   10, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 2000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    float speedFinal1 = sqrt(2*(float)descreteMoveXSlow1.Xn*aDefault);

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(0 - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;                 x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                             CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn-descreteMoveXSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;                 y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                        CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;                 v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedFinal1 - v1) < floatError );       CHECK( fabs(descreteMoveXSlow2.FnXY - v2) < floatError );  CHECK( fabs(descreteMoveXSlow2.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;                 v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                        CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;                 a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;                 a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_X_backwards_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND,   -10, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, -2000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    float speedFinal1 = -sqrt(2*fabs(descreteMoveXSlow1.Xn)*aDefault);

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(0 - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;                 x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                             CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn-descreteMoveXSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;                 y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                        CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;                 v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedFinal1 - v1) < floatError );       CHECK( fabs(-descreteMoveXSlow2.FnXY - v2) < floatError ); CHECK( fabs(-descreteMoveXSlow2.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;                 v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                        CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;                 a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;                 a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_X_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 10015, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    float vTarget1 = descreteMoveXSlow1.FnXY;


    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vTarget1 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;  x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                              CHECK(x3 > 0);                              CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn, x1+x2+x3+x4);
    CHECK(labs(lroundf(pow(vTarget1, 2)/2/aDefault) - (x3+x4) ) <= 1);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;  y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);                         CHECK_EQUAL(0, y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;  v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(vTarget1 - v2) < floatError );  CHECK( fabs(vTarget1 - v3) < floatError );  CHECK( fabs(v4) < fabs(vTarget1) );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;  v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );         CHECK( fabs(0 - v4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;  a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(-aDefault - a3) <floatError );  CHECK( fabs(-aDefault - a4) <floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;  a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );         CHECK( fabs(0 - a4) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_X_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, 20, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 30, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    float vTarget1 = descreteMoveXSlow1.FnXY;


    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(0 - a1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn, x1+x2+x3);
    CHECK(fabs(x1 - x2 - x3) < floatError );
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(v2) < fabs(vTarget1) );         CHECK( fabs(v3) < fabs(vTarget1) );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(-aDefault - a2) < floatError ); CHECK( fabs(-aDefault - a3) <floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_X_move_Z_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, 20, 0,   0, 0,     1000,    0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 30, 0,   0, 0,     1000,    0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);
    const descreteCommand_Gcode descreteMoveZSlow3 = {MOVE_COMMAND, 30, 0,  10, 0,        0, 1000, 0,     0, 0};

    float vTarget1 = descreteMoveXSlow1.FnXY;


    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(0 - a1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(descreteMoveZSlow3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn, x1+x2+x3);
    CHECK(fabs(x1 - x2 - x3) < floatError );
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(v2) < fabs(vTarget1) );         CHECK( fabs(v3) < fabs(vTarget1) );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(-aDefault - a2) < floatError ); CHECK( fabs(-aDefault - a3) <floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_X_backwards_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, -1000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, -1010, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    float vTarget1 = -descreteMoveXSlow1.FnXY;


    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vTarget1 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;  x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                              CHECK(x2 < 0);                              CHECK(x3 < 0);                              CHECK(x4 < 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn, x1+x2+x3+x4);
    CHECK(labs(-lroundf(pow(vTarget1, 2)/2/aDefault) - (x3+x4) ) <= 1);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;  y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);                         CHECK_EQUAL(0, y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;  v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(vTarget1 - v2) < floatError );  CHECK( fabs(vTarget1 - v3) < floatError );  CHECK( fabs(v4) < fabs(vTarget1) );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;  v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );         CHECK( fabs(0 - v4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;  a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(-aDefault - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(aDefault - a3) <floatError );   CHECK( fabs(aDefault - a4) <floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;  a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );         CHECK( fabs(0 - a4) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_X_backwards_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, -20, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, -30, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    float vTarget1 = -descreteMoveXSlow1.FnXY;


    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(0 - a1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                              CHECK(x2 < 0);                              CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn, x1+x2+x3);
    CHECK(fabs(x1 - x2 - x3) < floatError );
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(v2) < fabs(vTarget1) );         CHECK( fabs(v3) < fabs(vTarget1) );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );  CHECK( fabs(aDefault - a2) < floatError ); CHECK( fabs(aDefault - a3) <floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
}


TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Y)
{
    const descreteCommand_Gcode descreteMoveYSlow = {MOVE_COMMAND, 0, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);                                             CHECK(x3 == 0);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                              CHECK(y2 > 0);                                              CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(descreteMoveYSlow.FnXY - v2) < floatError );    CHECK( fabs(descreteMoveYSlow.FnXY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefault - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Y_backwards)
{
    const descreteCommand_Gcode descreteMoveYSlow = {MOVE_COMMAND, 0, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);                                             CHECK(x3 == 0);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                              CHECK(y2 < 0);                                              CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(-descreteMoveYSlow.FnXY - v2) < floatError );   CHECK( fabs(-descreteMoveYSlow.FnXY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(aDefault - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Y_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveYSlow = {MOVE_COMMAND, 0, 100000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveYSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);                             CHECK(x3 == 0);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                              CHECK(y2 > 0);                              CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(maxSpeedXY-v2) < floatError );  CHECK( fabs(maxSpeedXY-v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(-aDefault - a3) < floatError);
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_Y)
{
    const descreteCommand_Gcode descreteMoveYFast = {MOVE_COMMAND, 0, 100, 0, 0,     3000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYFast.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                              CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(maxSpeedXY) > fabs(v2) );
    CHECK( v2 > 0 );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(-aDefault - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_Y_backwards)
{
    const descreteCommand_Gcode descreteMoveYFast = {MOVE_COMMAND, 0, -100, 0, 0,     3000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYFast.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                              CHECK(y2 < 0);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(maxSpeedXY) > fabs(v2) );
    CHECK( v2 < 0 );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );  CHECK( fabs(aDefault - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_Y_do_not_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND,     0, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND,     0,     0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);                                             CHECK(x3 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                              CHECK(y2 > 0);                                              CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(descreteMoveYSlow1.FnXY - v2) < floatError );   CHECK( fabs(descreteMoveYSlow1.FnXY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefault - a3) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(4).dXn;  x2 = getCommandBufferElement_Gcode(5).dXn;                  x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK(x1 == 0);                             CHECK(x2 == 0);                                             CHECK(x3 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn-descreteMoveYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;  y2 = getCommandBufferElement_Gcode(5).dYn;                  y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK(y1 < 0);                              CHECK(y2 < 0);                                              CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn-descreteMoveYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(4).FnX;  v2 = getCommandBufferElement_Gcode(5).FnX;                  v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;  v2 = getCommandBufferElement_Gcode(5).FnY;                  v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(-descreteMoveYSlow2.FnXY - v2) < floatError );  CHECK( fabs(-descreteMoveYSlow2.FnXY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;  a2 = getCommandBufferElement_Gcode(5).AnX;                  a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;  a2 = getCommandBufferElement_Gcode(5).AnY;                  a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(-aDefault - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(aDefault - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_Y_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, 20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 == 0);                                             CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                              CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;                  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(descreteMoveYSlow1.FnXY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;                  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault - a1) < floatError );                  CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;                  x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 == 0);                                             CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn-descreteMoveYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;                  y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                              CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn-descreteMoveYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;                  v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;                  v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(descreteMoveYSlow2.FnXY - v1) < floatError );   CHECK( fabs(descreteMoveYSlow2.FnXY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;                  a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;                  a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(-aDefault - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_Y_backwards_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, -20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                  x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 == 0);                                             CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                  y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                              CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                  v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;                  v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(-descreteMoveYSlow1.FnXY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;                  a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                  a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );                  CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;                  x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 == 0);                                             CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn-descreteMoveYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;                  y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                              CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn-descreteMoveYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;                  v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;                  v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(-descreteMoveYSlow2.FnXY - v1) < floatError );  CHECK( fabs(-descreteMoveYSlow2.FnXY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;                  a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;                  a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                         CHECK( fabs(aDefault - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_Y_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0,   10, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, 2000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    float speedFinal1 = sqrt(2*(float)descreteMoveYSlow1.Yn*aDefault);

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;                 x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 == 0);                                     CHECK(x2 == 0);                                            CHECK(x3 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn-descreteMoveYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;                 y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                             CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn-descreteMoveYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;                 v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                        CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;                 v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedFinal1 - v1) < floatError );       CHECK( fabs(descreteMoveYSlow2.FnXY - v2) < floatError );  CHECK( fabs(descreteMoveYSlow2.FnXY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;                 a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;                 a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(-aDefault - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_Y_backwards_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0,   -10, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, -2000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    float speedFinal1 = -sqrt(2*fabs(descreteMoveYSlow1.Yn)*aDefault);

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;                 x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 == 0);                                     CHECK(x2 == 0);                                            CHECK(x3 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn-descreteMoveYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;                 y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                             CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn-descreteMoveYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;                 v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                        CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;                 v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedFinal1 - v1) < floatError );       CHECK( fabs(-descreteMoveYSlow2.FnXY - v2) < floatError ); CHECK( fabs(-descreteMoveYSlow2.FnXY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;                 a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;                 a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                        CHECK( fabs(aDefault - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_Y_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND, 0, 1000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND, 0, 1010, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);

    float vTarget1 = descreteMoveSlow1.FnXY;


    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vTarget1 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;  x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK_EQUAL(0, x1);                         CHECK_EQUAL(0, x2);                         CHECK_EQUAL(0, x3);                         CHECK_EQUAL(0, x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;  y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                              CHECK(y2 > 0);                              CHECK(y3 > 0);                              CHECK(y4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK( labs(lroundf(pow(vTarget1, 2)/2/aDefault) - (y3+y4) ) <= 1);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;  v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );         CHECK( fabs(0 - v4) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;  v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(vTarget1 - v2) < floatError );  CHECK( fabs(vTarget1 - v3) < floatError );  CHECK( fabs(v4) < fabs(vTarget1) );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;  a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );         CHECK( fabs(0 - a4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;  a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(-aDefault - a3) <floatError );  CHECK( fabs(-aDefault - a4) <floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_Y_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND, 0, 20, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND, 0, 30, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);

    float vTarget1 = descreteMoveSlow1.FnXY;


    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK_EQUAL(0, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault - a1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                         CHECK_EQUAL(0, x2);                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                              CHECK(y2 > 0);                              CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3);
    CHECK(fabs(y1 - y2 - y3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(v2) < fabs(vTarget1) );         CHECK( fabs(v3) < fabs(vTarget1) );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault - a1) < floatError );  CHECK( fabs(-aDefault - a2) < floatError ); CHECK( fabs(-aDefault - a3) <floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_Y_backwards_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND, 0, -1000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND, 0, -1010, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);

    float vTarget1 = -descreteMoveSlow1.FnXY;


    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vTarget1 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;  x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK_EQUAL(0, x1);                         CHECK_EQUAL(0, x2);                         CHECK_EQUAL(0, x3);                         CHECK_EQUAL(0, x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;  y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                              CHECK(y2 < 0);                              CHECK(y3 < 0);                              CHECK(y4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK( labs(-lroundf(pow(vTarget1, 2)/2/aDefault) - (y3+y4) ) <= 1);
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;  v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );         CHECK( fabs(0 - v4) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;  v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(vTarget1 - v2) < floatError );  CHECK( fabs(vTarget1 - v3) < floatError );  CHECK( fabs(v4) < fabs(vTarget1) );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;  a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );         CHECK( fabs(0 - a4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;  a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(-aDefault - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(aDefault - a3) <floatError );   CHECK( fabs(aDefault - a4) <floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_Y_backwards_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND, 0, -20, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND, 0, -30, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);

    float vTarget1 = -descreteMoveSlow1.FnXY;


    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK_EQUAL(0, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                         CHECK_EQUAL(0, x2);                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                              CHECK(y2 < 0);                              CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3);
    CHECK(fabs(y1 - y2 - y3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnX;  v2 = getCommandBufferElement_Gcode(2).FnX;  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(0 - v2) < floatError );         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;  v2 = getCommandBufferElement_Gcode(2).FnY;  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );         CHECK( fabs(v2) < fabs(vTarget1) );         CHECK( fabs(v3) < fabs(vTarget1) );
    a1 = getCommandBufferElement_Gcode(1).AnX;  a2 = getCommandBufferElement_Gcode(2).AnX;  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;  a2 = getCommandBufferElement_Gcode(2).AnY;  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );  CHECK( fabs(aDefault - a2) < floatError ); CHECK( fabs(aDefault - a3) <floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_1)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 10000, 5000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_2)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 5000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_3)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 10000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_4)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 10000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                  CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_1_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, -10000, -5000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;        x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                                    CHECK(x2 < 0);                                    CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;        y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                    CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;        v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );               CHECK( fabs(speedTargetX - v2) < floatError );   CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;        v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );               CHECK( fabs(speedTargetY - v2) < floatError );   CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;        a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;        a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );  CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_2_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, -5000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                                  CHECK(x2 < 0);                                    CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                  CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_3_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, -10000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = (float)descreteMoveXYSlow.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYSlow.FnXY*cosY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                                  CHECK(x2 < 0);                                    CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                  CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_1_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 20000, 10000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = cosX*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
    float speedTargetY = cosY*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_2_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 10000, 20000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = cosX*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
    float speedTargetY = cosY*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_3_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, 20000, 20000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = cosX*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
    float speedTargetY = cosY*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_1_cross_speed_limit_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, -20000, -10000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = cosX*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
    float speedTargetY = cosY*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                                  CHECK(x2 < 0);                                    CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                  CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_2_cross_speed_limit_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, -10000, -20000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = cosX*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
    float speedTargetY = cosY*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                                  CHECK(x2 < 0);                                    CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                  CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XY_3_cross_speed_limit_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow = {MOVE_COMMAND, -20000, -20000, 0, 0,     10000, 0, 0,     0, 0};
    CHECK(maxSpeedXY < descreteMoveXYSlow.FnXY);
    float distance = sqrt((float)descreteMoveXYSlow.Xn*(float)descreteMoveXYSlow.Xn+(float)descreteMoveXYSlow.Yn*(float)descreteMoveXYSlow.Yn);
    float cosX = (float)descreteMoveXYSlow.Xn/distance;
    float cosY = (float)descreteMoveXYSlow.Yn/distance;
    float speedTargetX = cosX*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
    float speedTargetY = cosY*(float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);                                  CHECK(x2 < 0);                                    CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);                                  CHECK(y2 < 0);                                    CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XY_1_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, 20, 10, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYFast.FnXY);
    float distance = sqrt((float)descreteMoveXYFast.Xn*(float)descreteMoveXYFast.Xn+(float)descreteMoveXYFast.Yn*(float)descreteMoveXYFast.Yn);
    float cosX = (float)descreteMoveXYFast.Xn/distance;
    float cosY = (float)descreteMoveXYFast.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYFast.FnXY;
    float speedTargetY = cosY*descreteMoveXYFast.FnXY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;                     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                 CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                     y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                                 CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                     v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                     a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XY_2_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, 10, 20, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYFast.FnXY);
    float distance = sqrt((float)descreteMoveXYFast.Xn*(float)descreteMoveXYFast.Xn+(float)descreteMoveXYFast.Yn*(float)descreteMoveXYFast.Yn);
    float cosX = (float)descreteMoveXYFast.Xn/distance;
    float cosY = (float)descreteMoveXYFast.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYFast.FnXY;
    float speedTargetY = cosY*descreteMoveXYFast.FnXY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;                     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                 CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                     y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                                 CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                     v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                     a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XY_3_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, 20, 20, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYFast.FnXY);
    float distance = sqrt((float)descreteMoveXYFast.Xn*(float)descreteMoveXYFast.Xn+(float)descreteMoveXYFast.Yn*(float)descreteMoveXYFast.Yn);
    float cosX = (float)descreteMoveXYFast.Xn/distance;
    float cosY = (float)descreteMoveXYFast.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYFast.FnXY;
    float speedTargetY = cosY*descreteMoveXYFast.FnXY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;                     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                 CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                     y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                                 CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                     v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                     a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XY_1_cross_speed_limit_backwards)
{
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, -20, -10, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYFast.FnXY);
    float distance = sqrt((float)descreteMoveXYFast.Xn*(float)descreteMoveXYFast.Xn+(float)descreteMoveXYFast.Yn*(float)descreteMoveXYFast.Yn);
    float cosX = (float)descreteMoveXYFast.Xn/distance;
    float cosY = (float)descreteMoveXYFast.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYFast.FnXY;
    float speedTargetY = cosY*descreteMoveXYFast.FnXY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;                     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                                 CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                     y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                                 CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                     v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                     a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XY_2_cross_speed_limit_backwards)
{
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, -10, -20, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYFast.FnXY);
    float distance = sqrt((float)descreteMoveXYFast.Xn*(float)descreteMoveXYFast.Xn+(float)descreteMoveXYFast.Yn*(float)descreteMoveXYFast.Yn);
    float cosX = (float)descreteMoveXYFast.Xn/distance;
    float cosY = (float)descreteMoveXYFast.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYFast.FnXY;
    float speedTargetY = cosY*descreteMoveXYFast.FnXY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;                     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                                 CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                     y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                                 CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                     v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                     a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XY_3_cross_speed_limit_backwards)
{
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, -20, -20, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYFast.FnXY);
    float distance = sqrt((float)descreteMoveXYFast.Xn*(float)descreteMoveXYFast.Xn+(float)descreteMoveXYFast.Yn*(float)descreteMoveXYFast.Yn);
    float cosX = (float)descreteMoveXYFast.Xn/distance;
    float cosY = (float)descreteMoveXYFast.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYFast.FnXY;
    float speedTargetY = cosY*descreteMoveXYFast.FnXY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYFast);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;                     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                                 CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYFast.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                     y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                                 CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYFast.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;                     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                     v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                            CHECK( fabs(v2) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                     a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_do_not_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     10000, 5000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,         0,    0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                      CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                      CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_do_not_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     5000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,         0,    0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                      CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                      CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_do_not_conserve_speed_3)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     10000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,         0,    0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                      CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                      CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     10000,  5000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     20000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;          x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;          y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;          v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );      CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;          v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );      CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;          a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;          a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,      5000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     10000, 20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;          x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;          y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;          v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );      CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;          v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );      CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;          a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;          a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_conserve_speed_3)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     10000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     20000, 20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;          x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;          y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;          v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );      CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;          v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );      CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;          a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;          a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_conserve_speed_1_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     -10000,  -5000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -20000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;          x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;          y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;          v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );      CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;          v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );      CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;          a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;          a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_conserve_speed_2_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,      -5000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -10000, -20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;          x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;          y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;          v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );      CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;          v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );      CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;          a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;          a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_XY_conserve_speed_3_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     -10000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -20000, -20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;          x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;          y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(3).FnX;          v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );      CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;          v2 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );      CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;          a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;          a2 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XY_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,       10,      5, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     2000,   1000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XY_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,        5,   10, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     1000, 2000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XY_conserve_speed_3)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,         5,     5, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     10000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XY_conserve_speed_1_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,        -10,     -5, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -20000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                      CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                      CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XY_conserve_speed_2_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,         -5,    -10, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -10000, -20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                      CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                      CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XY_conserve_speed_3_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,         -5,     -5, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -10000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveXYSlow1.Xn, 2.0)+pow((float)descreteMoveXYSlow1.Yn,2));
    float cosX = (float)descreteMoveXYSlow1.Xn/distance;
    float cosY = (float)descreteMoveXYSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveXYSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveXYSlow1.FnXY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);                                      CHECK(x3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);                                      CHECK(y3 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1+y2+y3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_1_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     20000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     20010, 10005, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2));
    float cosX = (float)descreteMoveSlow1.Xn/distance;
    float cosY = (float)descreteMoveSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveSlow1.FnXY;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    /*CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());*/

    distance = sqrt(pow((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn, 2)+pow((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn,2));
    cosX = ((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn)/distance;
    cosY = ((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveSlow2.FnXY;
    speedTargetY = cosY*descreteMoveSlow2.FnXY;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;           x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                      x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                       CHECK(x2 > 0);                                                 CHECK(x3 > 0);                                                  CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;           y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                      y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                       CHECK(y2 > 0);                                                 CHECK(y3 > 0);                                                  CHECK(y4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;           v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                      v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );    CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;           v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                      v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );    CHECK( fabs(v4) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;           a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                      a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;           a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                      a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_2_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     10000, 20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     10005, 20010, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2));
    float cosX = (float)descreteMoveSlow1.Xn/distance;
    float cosY = (float)descreteMoveSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveSlow1.FnXY;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn, 2)+pow((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn,2));
    cosX = ((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn)/distance;
    cosY = ((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveSlow2.FnXY;
    speedTargetY = cosY*descreteMoveSlow2.FnXY;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;                      x3 = getCommandBufferElement_Gcode(3).dXn;                      x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);                                                  CHECK(x3 > 0);                                                  CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;                      y2 = getCommandBufferElement_Gcode(2).dYn;                      y3 = getCommandBufferElement_Gcode(3).dYn;                      y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                                  CHECK(y2 > 0);                                                  CHECK(y3 > 0);                                                  CHECK(y4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK_EQUAL(lroundf(pow(speedTargetY, 2)/2/aDefault/cosY), y3+y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;                      v2 = getCommandBufferElement_Gcode(2).FnX;                      v3 = getCommandBufferElement_Gcode(3).FnX;                      v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                             CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );    CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );    CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                      v2 = getCommandBufferElement_Gcode(2).FnY;                      v3 = getCommandBufferElement_Gcode(3).FnY;                      v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                             CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );    CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );    CHECK( fabs(v4) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                      a2 = getCommandBufferElement_Gcode(2).AnX;                      a3 = getCommandBufferElement_Gcode(3).AnX;                      a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < 0.01*fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                             CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                      a2 = getCommandBufferElement_Gcode(2).AnY;                      a3 = getCommandBufferElement_Gcode(3).AnY;                      a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < 0.01*fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                             CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_3_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     10000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     10010, 10010, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2));
    float cosX = (float)descreteMoveSlow1.Xn/distance;
    float cosY = (float)descreteMoveSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveSlow1.FnXY;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn, 2)+pow((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn,2));
    cosX = ((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn)/distance;
    cosY = ((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveSlow2.FnXY;
    speedTargetY = cosY*descreteMoveSlow2.FnXY;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;           x2 = getCommandBufferElement_Gcode(2).dXn;           x3 = getCommandBufferElement_Gcode(3).dXn;          x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                       CHECK(x2 > 0);                                       CHECK(x3 > 0);                                      CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;           y2 = getCommandBufferElement_Gcode(2).dYn;           y3 = getCommandBufferElement_Gcode(3).dYn;          y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                       CHECK(y2 > 0);                                       CHECK(y3 > 0);                                      CHECK(y4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK_EQUAL(lroundf(pow(speedTargetY, 2)/2/aDefault/cosY), y3+y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;           v2 = getCommandBufferElement_Gcode(2).FnX;           v3 = getCommandBufferElement_Gcode(3).FnX;          v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetX - v2) < floatError );       CHECK( fabs(speedTargetX - v3) < floatError );      CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;           v2 = getCommandBufferElement_Gcode(2).FnY;           v3 = getCommandBufferElement_Gcode(3).FnY;          v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetY - v2) < floatError );       CHECK( fabs(speedTargetY - v3) < floatError );      CHECK( fabs(v4) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;           a2 = getCommandBufferElement_Gcode(2).AnX;           a3 = getCommandBufferElement_Gcode(3).AnX;          a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                  CHECK( fabs(-aDefault*cosX - a3) < floatError );    CHECK( fabs(-aDefault*cosX - a4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;           a2 = getCommandBufferElement_Gcode(2).AnY;           a3 = getCommandBufferElement_Gcode(3).AnY;          a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                  CHECK( fabs(-aDefault*cosY - a3) < floatError );    CHECK( fabs(-aDefault*cosY - a4) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_1_backwards_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     -20000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     -20010, -10005, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2));
    float cosX = (float)descreteMoveSlow1.Xn/distance;
    float cosY = (float)descreteMoveSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveSlow1.FnXY;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn, 2)+pow((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn,2));
    cosX = ((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn)/distance;
    cosY = ((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveSlow2.FnXY;
    speedTargetY = cosY*descreteMoveSlow2.FnXY;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;           x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                      x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                       CHECK(x2 < 0);                                                 CHECK(x3 < 0);                                                  CHECK(x4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;           y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                      y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                       CHECK(y2 < 0);                                                 CHECK(y3 < 0);                                                  CHECK(y4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;           v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                      v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );    CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;           v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                      v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );    CHECK( fabs(v4) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;           a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                      a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;           a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                      a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_2_backwards_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     -10000, -20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     -10005, -20010, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2));
    float cosX = (float)descreteMoveSlow1.Xn/distance;
    float cosY = (float)descreteMoveSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveSlow1.FnXY;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn, 2)+pow((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn,2));
    cosX = ((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn)/distance;
    cosY = ((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveSlow2.FnXY;
    speedTargetY = cosY*descreteMoveSlow2.FnXY;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;           x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                      x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                       CHECK(x2 < 0);                                                 CHECK(x3 < 0);                                                  CHECK(x4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;           y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                      y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                       CHECK(y2 < 0);                                                 CHECK(y3 < 0);                                                  CHECK(y4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK_EQUAL(lroundf(pow(speedTargetY, 2)/2/aDefault/cosY), y3+y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;           v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                      v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );    CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;           v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                      v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );    CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;           a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                      a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX - a4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;           a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                      a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosY - a4) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_3_backwards_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     -10000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     -10010, -10010, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2));
    float cosX = (float)descreteMoveSlow1.Xn/distance;
    float cosY = (float)descreteMoveSlow1.Yn/distance;
    float speedTargetX = cosX*descreteMoveSlow1.FnXY;
    float speedTargetY = cosY*descreteMoveSlow1.FnXY;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                      CHECK(x2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn, 2)+pow((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn,2));
    cosX = ((float)descreteMoveSlow2.Xn-(float)descreteMoveSlow1.Xn)/distance;
    cosY = ((float)descreteMoveSlow2.Yn-(float)descreteMoveSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveSlow2.FnXY;
    speedTargetY = cosY*descreteMoveSlow2.FnXY;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;           x2 = getCommandBufferElement_Gcode(2).dXn;           x3 = getCommandBufferElement_Gcode(3).dXn;          x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                       CHECK(x2 < 0);                                       CHECK(x3 < 0);                                      CHECK(x4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;           y2 = getCommandBufferElement_Gcode(2).dYn;           y3 = getCommandBufferElement_Gcode(3).dYn;          y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                       CHECK(y2 < 0);                                       CHECK(y3 < 0);                                      CHECK(y4 < 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK_EQUAL(lroundf(pow(speedTargetY, 2)/2/aDefault/cosY), y3+y4);
    v1 = getCommandBufferElement_Gcode(1).FnX;           v2 = getCommandBufferElement_Gcode(2).FnX;           v3 = getCommandBufferElement_Gcode(3).FnX;          v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetX - v2) < floatError );       CHECK( fabs(speedTargetX - v3) < floatError );      CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;           v2 = getCommandBufferElement_Gcode(2).FnY;           v3 = getCommandBufferElement_Gcode(3).FnY;          v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                  CHECK( fabs(speedTargetY - v2) < floatError );       CHECK( fabs(speedTargetY - v3) < floatError );      CHECK( fabs(v4) < fabs(speedTargetY) );
    a1 = getCommandBufferElement_Gcode(1).AnX;           a2 = getCommandBufferElement_Gcode(2).AnX;           a3 = getCommandBufferElement_Gcode(3).AnX;          a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                  CHECK( fabs(-aDefault*cosX - a3) < floatError );    CHECK( fabs(-aDefault*cosX - a4) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;           a2 = getCommandBufferElement_Gcode(2).AnY;           a3 = getCommandBufferElement_Gcode(3).AnY;          a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                  CHECK( fabs(-aDefault*cosY - a3) < floatError );    CHECK( fabs(-aDefault*cosY - a4) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_E)
{
    const descreteCommand_Gcode descreteMoveE = {MOVE_COMMAND, 0, 0, 0, 10000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE.FnE);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    long  e1;
    float v1;

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(descreteMoveE.FnE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_E_backwards)
{
    const descreteCommand_Gcode descreteMoveE = {MOVE_COMMAND, 0, 0, 0, -10000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE.FnE);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    long  e1;
    float v1;

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(-descreteMoveE.FnE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_E_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveE = {MOVE_COMMAND, 0, 0, 0, 10000,     0, 0, 20000,     0, 0};
    CHECK(maxSpeedE < descreteMoveE.FnE);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    long  e1;
    float v1;

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(maxSpeedE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_E_backwards_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveE = {MOVE_COMMAND, 0, 0, 0, -10000,     0, 0, 20000,     0, 0};
    CHECK(maxSpeedE < descreteMoveE.FnE);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    long  e1;
    float v1;

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(-maxSpeedE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_E_in_line_motion)
{
    const descreteCommand_Gcode descreteMoveE1 = {MOVE_COMMAND, 0, 0, 0, 10000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE1.FnE);
    const descreteCommand_Gcode descreteMoveE2 = {MOVE_COMMAND, 0, 0, 0, 20000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE2.FnE);

    long  e1;
    float v1;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(descreteMoveE1.FnE - v1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    e1 = getCommandBufferElement_Gcode(2).dEn;
    CHECK_EQUAL(descreteMoveE2.En-descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(descreteMoveE2.FnE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_E_opposite_motion)
{
    const descreteCommand_Gcode descreteMoveE1 = {MOVE_COMMAND, 0, 0, 0,  10000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE1.FnE);
    const descreteCommand_Gcode descreteMoveE2 = {MOVE_COMMAND, 0, 0, 0, -15000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE2.FnE);

    long  e1;
    float v1;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(descreteMoveE1.FnE - v1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    e1 = getCommandBufferElement_Gcode(2).dEn;
    CHECK_EQUAL(descreteMoveE2.En-descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(-descreteMoveE2.FnE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XYE_1)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 10000, 5000, 0, 10000,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEX = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Xn;
    float speedTargetX = (float)descreteMoveXYE.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE.FnXY*cosX*tgEX;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;        a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX*tgEX - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XYE_2)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 5000, 10000, 0, 10000,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEY = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Yn;
    float speedTargetX = (float)descreteMoveXYE.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE.FnXY*cosY*tgEY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;        a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(aDefault*cosY*tgEY - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY*tgEY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XYE_1_backwards)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 10000, 5000, 0, -10000,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEX = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Xn;
    float speedTargetX = (float)descreteMoveXYE.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE.FnXY*cosX*tgEX;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);                                    CHECK(e3 < 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;        a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX*tgEX - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XYE_2_backwards)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 5000, 10000, 0, -10000,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEY = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Yn;
    float speedTargetX = (float)descreteMoveXYE.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE.FnXY*cosY*tgEY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);                                    CHECK(e3 < 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;        a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(aDefault*cosY*tgEY - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY*tgEY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XYE_1_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 10000, 5000, 0, 200000,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEX = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Xn;
    CHECK((float)descreteMoveXYE.FnXY*(float)descreteMoveXYE.En/distance > maxSpeedE );
    float speedTargetX = maxSpeedE/tgEX;
    float speedTargetY = maxSpeedE/tgEX*cosY/cosX;
    float speedTargetE = maxSpeedE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;                          x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                                      CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;                          y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                                      CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;                          e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                                      CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;                          v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                                 CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;                          v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                                 CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;                          v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                                 CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;                          a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                     CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                          a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                     CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;                          a2 = getCommandBufferElement_Gcode(2).AnE;        a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < 0.01*fabs(a1)+floatError );  CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XYE_2_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 5000, 10000, 0, 200000,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEY = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Yn;
    CHECK((float)descreteMoveXYE.FnXY*(float)descreteMoveXYE.En/distance > maxSpeedE );
    float speedTargetX = (float)maxSpeedE/tgEY*cosX/cosY;
    float speedTargetY = (float)maxSpeedE/tgEY;
    float speedTargetE = (float)maxSpeedE;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;                          x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                                      CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;                          y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                                      CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;                          e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                                      CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;                          v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                                 CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;                          v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                                 CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;                          v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                                 CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;                          a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );                     CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                          a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );                     CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;                          a2 = getCommandBufferElement_Gcode(2).AnE;        a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(aDefault*cosY*tgEY - a1) < 0.01*fabs(a1)+floatError );  CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY*tgEY - a3) < 0.01*fabs(a3)+floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XYE_1)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 10, 5, 0, 10,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEX = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Xn;
    float speedTargetX = (float)descreteMoveXYE.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE.FnXY*cosX*tgEX;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    long  e1, e2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(v2) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(v2) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(-aDefault*cosY - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK_EQUAL(aDefault*cosX*tgEX, a1);
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(-aDefault*cosX*tgEX - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XYE_2)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 5, 10, 0, 10,     1000, 0, 2000,     0, 0};
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE.FnXY)-fabs(descreteMoveXYE.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE.FnXY);
    float distance = sqrt((float)descreteMoveXYE.Xn*(float)descreteMoveXYE.Xn+(float)descreteMoveXYE.Yn*(float)descreteMoveXYE.Yn);
    float cosX = (float)descreteMoveXYE.Xn/distance;
    float cosY = (float)descreteMoveXYE.Yn/distance;
    float tgEY = (float)descreteMoveXYE.En/(float)descreteMoveXYE.Yn;
    float speedTargetX = (float)descreteMoveXYE.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE.FnXY*cosY*tgEY;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    long  e1, e2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(v2) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(v2) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(-aDefault*cosY - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY*tgEY - a1) < floatError );    CHECK( fabs(-aDefault*cosY*tgEY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XYE_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYE1 = {MOVE_COMMAND,        10,     5, 0,     10,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE1.FnXY)-fabs(descreteMoveXYE1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    const descreteCommand_Gcode descreteMoveXYE2 = {MOVE_COMMAND,     20000, 10000, 0,  20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYE2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE2.FnXY)-fabs(descreteMoveXYE2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE2.FnXY);

    float distance = sqrt(pow((float)descreteMoveXYE1.Xn,2)+pow((float)descreteMoveXYE1.Yn,2));
    float cosX = (float)descreteMoveXYE1.Xn/distance;
    float cosY = (float)descreteMoveXYE1.Yn/distance;
    float tgEX = (float)descreteMoveXYE1.En/(float)descreteMoveXYE1.Xn;
    float speedTargetX = (float)descreteMoveXYE1.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE1.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE1.FnXY*cosX*tgEX;

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Yn, y1);
    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK(e1 > 0);
    CHECK_EQUAL(descreteMoveXYE1.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn,2)+pow((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn,2));
    cosX = ((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn)/distance;
    cosY = ((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn)/distance;
    tgEX = ((float)descreteMoveXYE2.En-(float)descreteMoveXYE1.En)/((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn);
    speedTargetX = (float)descreteMoveXYE2.FnXY*cosX;
    speedTargetY = (float)descreteMoveXYE2.FnXY*cosY;
    speedTargetE = (float)descreteMoveXYE2.FnXY*cosX*tgEX;

    x1 = getCommandBufferElement_Gcode(2).dXn;              x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Xn-descreteMoveXYE1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;              y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Yn-descreteMoveXYE1.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(2).dEn;              e2 = getCommandBufferElement_Gcode(3).dEn;          e3 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                      CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.En-descreteMoveXYE1.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(2).FnX;              v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;              v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnE;              v2 = getCommandBufferElement_Gcode(3).FnE;          v3 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(v1) < fabs(speedTargetE) );                 CHECK( fabs(speedTargetE - v2) < floatError );      CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;              a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;              a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnE;              a2 = getCommandBufferElement_Gcode(3).AnE;          a3 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX*tgEX - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XYE_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYE1 = {MOVE_COMMAND,         5,    10, 0,     10,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE1.FnXY)-fabs(descreteMoveXYE1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    const descreteCommand_Gcode descreteMoveXYE2 = {MOVE_COMMAND,     10000, 20000, 0,  20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYE2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE2.FnXY)-fabs(descreteMoveXYE2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE2.FnXY);

    float distance = sqrt(pow((float)descreteMoveXYE1.Xn,2)+pow((float)descreteMoveXYE1.Yn,2));
    float cosX = (float)descreteMoveXYE1.Xn/distance;
    float cosY = (float)descreteMoveXYE1.Yn/distance;
    float tgEY = (float)descreteMoveXYE1.En/(float)descreteMoveXYE1.Yn;
    float speedTargetX = (float)descreteMoveXYE1.FnXY*cosX;
    float speedTargetY = (float)descreteMoveXYE1.FnXY*cosY;
    float speedTargetE = (float)descreteMoveXYE1.FnXY*cosY*tgEY;

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Yn, y1);
    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK(e1 > 0);
    CHECK_EQUAL(descreteMoveXYE1.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;
    CHECK( fabs(aDefault*cosY*tgEY - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn,2)+pow((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn,2));
    cosX = ((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn)/distance;
    cosY = ((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn)/distance;
    tgEY = ((float)descreteMoveXYE2.En-(float)descreteMoveXYE1.En)/((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn);
    speedTargetX = (float)descreteMoveXYE2.FnXY*cosX;
    speedTargetY = (float)descreteMoveXYE2.FnXY*cosY;
    speedTargetE = (float)descreteMoveXYE2.FnXY*cosY*tgEY;

    x1 = getCommandBufferElement_Gcode(2).dXn;              x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Xn-descreteMoveXYE1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;              y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Yn-descreteMoveXYE1.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(2).dEn;              e2 = getCommandBufferElement_Gcode(3).dEn;          e3 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                      CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.En-descreteMoveXYE1.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(2).FnX;              v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );                 CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;              v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );                 CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnE;              v2 = getCommandBufferElement_Gcode(3).FnE;          v3 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(v1) < fabs(speedTargetE) );                 CHECK( fabs(speedTargetE - v2) < floatError );      CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;              a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;              a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnE;              a2 = getCommandBufferElement_Gcode(3).AnE;          a3 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosY*tgEY - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY*tgEY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_1_smoothly)
{
    const descreteCommand_Gcode descreteMove1 = {MOVE_COMMAND,     20000, 10000, 0, 20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove1.FnXY)-fabs(descreteMove1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    const descreteCommand_Gcode descreteMove2 = {MOVE_COMMAND,     20010, 10005, 0, 20010,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove2.FnXY)-fabs(descreteMove2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove2.FnXY);

    float distance = sqrt(pow((float)descreteMove1.Xn,2)+pow((float)descreteMove1.Yn,2));
    float cosX = (float)descreteMove1.Xn/distance;
    float cosY = (float)descreteMove1.Yn/distance;
    float tgEX = (float)descreteMove1.En/(float)descreteMove1.Xn;
    float speedTargetX = (float)descreteMove1.FnXY*cosX;
    float speedTargetY = (float)descreteMove1.FnXY*cosY;
    float speedTargetE = (float)descreteMove1.FnXY*cosX*tgEX;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMove1);
    addElementToDescreteCommandBuffer_Gcode(descreteMove2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);
    CHECK_EQUAL(descreteMove1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);
    CHECK_EQUAL(descreteMove1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);
    CHECK_EQUAL(descreteMove1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMove2.Xn-(float)descreteMove1.Xn,2)+pow((float)descreteMove2.Yn-(float)descreteMove1.Yn,2));
    cosX = ((float)descreteMove2.Xn-(float)descreteMove1.Xn)/distance;
    cosY = ((float)descreteMove2.Yn-(float)descreteMove1.Yn)/distance;
    tgEX = ((float)descreteMove2.En-(float)descreteMove1.En)/((float)descreteMove2.Xn-(float)descreteMove1.Xn);
    speedTargetX = (float)descreteMove2.FnXY*cosX;
    speedTargetY = (float)descreteMove2.FnXY*cosY;
    speedTargetE = (float)descreteMove2.FnXY*cosX*tgEX;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                           x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                                 CHECK(x3 > 0);                                                       CHECK(x4 > 0);
    CHECK_EQUAL(descreteMove2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                           y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                                 CHECK(y3 > 0);                                                       CHECK(y4 > 0);
    CHECK_EQUAL(descreteMove2.Yn, y1+y2+y3+y4);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;                     e3 = getCommandBufferElement_Gcode(3).dEn;                           e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                                 CHECK(e3 > 0);                                                       CHECK(e4 > 0);
    CHECK_EQUAL(descreteMove2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                           v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                           v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;                     v3 = getCommandBufferElement_Gcode(3).FnE;                           v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetE - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                           a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                           a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;                     a3 = getCommandBufferElement_Gcode(3).AnE;                           a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX*tgEX - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_2_smoothly)
{
    const descreteCommand_Gcode descreteMove1 = {MOVE_COMMAND,     10000, 20000, 0, 20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove1.FnXY)-fabs(descreteMove1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    const descreteCommand_Gcode descreteMove2 = {MOVE_COMMAND,     10005, 20010, 0, 20010,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove2.FnXY)-fabs(descreteMove2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove2.FnXY);

    float distance = sqrt(pow((float)descreteMove1.Xn,2)+pow((float)descreteMove1.Yn,2));
    float cosX = (float)descreteMove1.Xn/distance;
    float cosY = (float)descreteMove1.Yn/distance;
    float tgEX = (float)descreteMove1.En/(float)descreteMove1.Xn;
    float speedTargetX = (float)descreteMove1.FnXY*cosX;
    float speedTargetY = (float)descreteMove1.FnXY*cosY;
    float speedTargetE = (float)descreteMove1.FnXY*cosX*tgEX;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMove1);
    addElementToDescreteCommandBuffer_Gcode(descreteMove2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);
    CHECK_EQUAL(descreteMove1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);
    CHECK_EQUAL(descreteMove1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);
    CHECK_EQUAL(descreteMove1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMove2.Xn-(float)descreteMove1.Xn,2)+pow((float)descreteMove2.Yn-(float)descreteMove1.Yn,2));
    cosX = ((float)descreteMove2.Xn-(float)descreteMove1.Xn)/distance;
    cosY = ((float)descreteMove2.Yn-(float)descreteMove1.Yn)/distance;
    tgEX = ((float)descreteMove2.En-(float)descreteMove1.En)/((float)descreteMove2.Xn-(float)descreteMove1.Xn);
    speedTargetX = (float)descreteMove2.FnXY*cosX;
    speedTargetY = (float)descreteMove2.FnXY*cosY;
    speedTargetE = (float)descreteMove2.FnXY*cosX*tgEX;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                           x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                                 CHECK(x3 > 0);                                                       CHECK(x4 > 0);
    CHECK_EQUAL(descreteMove2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                           y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                                 CHECK(y3 > 0);                                                       CHECK(y4 > 0);
    CHECK_EQUAL(descreteMove2.Yn, y1+y2+y3+y4);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;                     e3 = getCommandBufferElement_Gcode(3).dEn;                           e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                                 CHECK(e3 > 0);                                                       CHECK(e4 > 0);
    CHECK_EQUAL(descreteMove2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                           v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                           v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;                     v3 = getCommandBufferElement_Gcode(3).FnE;                           v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetE - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                           a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                           a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;                     a3 = getCommandBufferElement_Gcode(3).AnE;                           a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX*tgEX - a4) < 0.01*fabs(a4)+floatError );
}


TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_3_smoothly)
{
    const descreteCommand_Gcode descreteMove1 = {MOVE_COMMAND,     10000, 10000, 0, 20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove1.FnXY)-fabs(descreteMove1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    const descreteCommand_Gcode descreteMove2 = {MOVE_COMMAND,     10005, 10005, 0, 20010,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove2.FnXY)-fabs(descreteMove2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove2.FnXY);

    float distance = sqrt(pow((float)descreteMove1.Xn,2)+pow((float)descreteMove1.Yn,2));
    float cosX = (float)descreteMove1.Xn/distance;
    float cosY = (float)descreteMove1.Yn/distance;
    float tgEX = (float)descreteMove1.En/(float)descreteMove1.Xn;
    float speedTargetX = (float)descreteMove1.FnXY*cosX;
    float speedTargetY = (float)descreteMove1.FnXY*cosY;
    float speedTargetE = (float)descreteMove1.FnXY*cosX*tgEX;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMove1);
    addElementToDescreteCommandBuffer_Gcode(descreteMove2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);
    CHECK_EQUAL(descreteMove1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);
    CHECK_EQUAL(descreteMove1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);
    CHECK_EQUAL(descreteMove1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMove2.Xn-(float)descreteMove1.Xn,2)+pow((float)descreteMove2.Yn-(float)descreteMove1.Yn,2));
    cosX = ((float)descreteMove2.Xn-(float)descreteMove1.Xn)/distance;
    cosY = ((float)descreteMove2.Yn-(float)descreteMove1.Yn)/distance;
    tgEX = ((float)descreteMove2.En-(float)descreteMove1.En)/((float)descreteMove2.Xn-(float)descreteMove1.Xn);
    speedTargetX = (float)descreteMove2.FnXY*cosX;
    speedTargetY = (float)descreteMove2.FnXY*cosY;
    speedTargetE = (float)descreteMove2.FnXY*cosX*tgEX;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                           x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                          CHECK(x2 > 0);                                                 CHECK(x3 > 0);                                                       CHECK(x4 > 0);
    CHECK_EQUAL(descreteMove2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                           y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                          CHECK(y2 > 0);                                                 CHECK(y3 > 0);                                                       CHECK(y4 > 0);
    CHECK_EQUAL(descreteMove2.Yn, y1+y2+y3+y4);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;                     e3 = getCommandBufferElement_Gcode(3).dEn;                           e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                          CHECK(e2 > 0);                                                 CHECK(e3 > 0);                                                       CHECK(e4 > 0);
    CHECK_EQUAL(descreteMove2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                           v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                           v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;                     v3 = getCommandBufferElement_Gcode(3).FnE;                           v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(speedTargetE - v3) < 0.1/*floatError*/ );
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetE - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                           a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                           a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;                     a3 = getCommandBufferElement_Gcode(3).AnE;                           a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX*tgEX - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_1_backwards_smoothly)
{
    const descreteCommand_Gcode descreteMove1 = {MOVE_COMMAND,     -20000, -10000, 0, -20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove1.FnXY)-fabs(descreteMove1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    const descreteCommand_Gcode descreteMove2 = {MOVE_COMMAND,     -20010, -10005, 0, -20010,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove2.FnXY)-fabs(descreteMove2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove2.FnXY);

    float distance = sqrt(pow((float)descreteMove1.Xn,2)+pow((float)descreteMove1.Yn,2));
    float cosX = (float)descreteMove1.Xn/distance;
    float cosY = (float)descreteMove1.Yn/distance;
    float tgEX = (float)descreteMove1.En/(float)descreteMove1.Xn;
    float speedTargetX = (float)descreteMove1.FnXY*cosX;
    float speedTargetY = (float)descreteMove1.FnXY*cosY;
    float speedTargetE = (float)descreteMove1.FnXY*cosX*tgEX;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMove1);
    addElementToDescreteCommandBuffer_Gcode(descreteMove2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                          CHECK(x2 < 0);
    CHECK_EQUAL(descreteMove1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                          CHECK(y2 < 0);
    CHECK_EQUAL(descreteMove1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);
    CHECK_EQUAL(descreteMove1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMove2.Xn-(float)descreteMove1.Xn,2)+pow((float)descreteMove2.Yn-(float)descreteMove1.Yn,2));
    cosX = ((float)descreteMove2.Xn-(float)descreteMove1.Xn)/distance;
    cosY = ((float)descreteMove2.Yn-(float)descreteMove1.Yn)/distance;
    tgEX = ((float)descreteMove2.En-(float)descreteMove1.En)/((float)descreteMove2.Xn-(float)descreteMove1.Xn);
    speedTargetX = (float)descreteMove2.FnXY*cosX;
    speedTargetY = (float)descreteMove2.FnXY*cosY;
    speedTargetE = (float)descreteMove2.FnXY*cosX*tgEX;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                           x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                          CHECK(x2 < 0);                                                 CHECK(x3 < 0);                                                       CHECK(x4 < 0);
    CHECK_EQUAL(descreteMove2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                           y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                          CHECK(y2 < 0);                                                 CHECK(y3 < 0);                                                       CHECK(y4 < 0);
    CHECK_EQUAL(descreteMove2.Yn, y1+y2+y3+y4);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;                     e3 = getCommandBufferElement_Gcode(3).dEn;                           e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);                                                 CHECK(e3 < 0);                                                       CHECK(e4 < 0);
    CHECK_EQUAL(descreteMove2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                           v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                           v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;                     v3 = getCommandBufferElement_Gcode(3).FnE;                           v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetE - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                           a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                           a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;                     a3 = getCommandBufferElement_Gcode(3).AnE;                           a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX*tgEX - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_2_backwards_smoothly)
{
    const descreteCommand_Gcode descreteMove1 = {MOVE_COMMAND,     -10000, -20000, 0, -20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove1.FnXY)-fabs(descreteMove1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    const descreteCommand_Gcode descreteMove2 = {MOVE_COMMAND,     -10005, -20010, 0, -20010,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove2.FnXY)-fabs(descreteMove2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove2.FnXY);

    float distance = sqrt(pow((float)descreteMove1.Xn,2)+pow((float)descreteMove1.Yn,2));
    float cosX = (float)descreteMove1.Xn/distance;
    float cosY = (float)descreteMove1.Yn/distance;
    float tgEX = (float)descreteMove1.En/(float)descreteMove1.Xn;
    float speedTargetX = (float)descreteMove1.FnXY*cosX;
    float speedTargetY = (float)descreteMove1.FnXY*cosY;
    float speedTargetE = (float)descreteMove1.FnXY*cosX*tgEX;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMove1);
    addElementToDescreteCommandBuffer_Gcode(descreteMove2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                          CHECK(x2 < 0);
    CHECK_EQUAL(descreteMove1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                          CHECK(y2 < 0);
    CHECK_EQUAL(descreteMove1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);
    CHECK_EQUAL(descreteMove1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMove2.Xn-(float)descreteMove1.Xn,2)+pow((float)descreteMove2.Yn-(float)descreteMove1.Yn,2));
    cosX = ((float)descreteMove2.Xn-(float)descreteMove1.Xn)/distance;
    cosY = ((float)descreteMove2.Yn-(float)descreteMove1.Yn)/distance;
    tgEX = ((float)descreteMove2.En-(float)descreteMove1.En)/((float)descreteMove2.Xn-(float)descreteMove1.Xn);
    speedTargetX = (float)descreteMove2.FnXY*cosX;
    speedTargetY = (float)descreteMove2.FnXY*cosY;
    speedTargetE = (float)descreteMove2.FnXY*cosX*tgEX;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                           x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                          CHECK(x2 < 0);                                                 CHECK(x3 < 0);                                                       CHECK(x4 < 0);
    CHECK_EQUAL(descreteMove2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                           y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                          CHECK(y2 < 0);                                                 CHECK(y3 < 0);                                                       CHECK(y4 < 0);
    CHECK_EQUAL(descreteMove2.Yn, y1+y2+y3+y4);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;                     e3 = getCommandBufferElement_Gcode(3).dEn;                           e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);                                                 CHECK(e3 < 0);                                                       CHECK(e4 < 0);
    CHECK_EQUAL(descreteMove2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                           v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                           v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;                     v3 = getCommandBufferElement_Gcode(3).FnE;                           v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetE - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                           a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                           a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;                     a3 = getCommandBufferElement_Gcode(3).AnE;                           a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX*tgEX - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_3_backwards_smoothly)
{
    const descreteCommand_Gcode descreteMove1 = {MOVE_COMMAND,     -10000, -10000, 0, -20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove1.FnXY)-fabs(descreteMove1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove1.FnXY);
    const descreteCommand_Gcode descreteMove2 = {MOVE_COMMAND,     -10005, -10005, 0, -20010,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMove2.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMove2.FnXY)-fabs(descreteMove2.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMove2.FnXY);

    float distance = sqrt(pow((float)descreteMove1.Xn,2)+pow((float)descreteMove1.Yn,2));
    float cosX = (float)descreteMove1.Xn/distance;
    float cosY = (float)descreteMove1.Yn/distance;
    float tgEX = (float)descreteMove1.En/(float)descreteMove1.Xn;
    float speedTargetX = (float)descreteMove1.FnXY*cosX;
    float speedTargetY = (float)descreteMove1.FnXY*cosY;
    float speedTargetE = (float)descreteMove1.FnXY*cosX*tgEX;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMove1);
    addElementToDescreteCommandBuffer_Gcode(descreteMove2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 < 0);                                          CHECK(x2 < 0);
    CHECK_EQUAL(descreteMove1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                          CHECK(y2 < 0);
    CHECK_EQUAL(descreteMove1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);
    CHECK_EQUAL(descreteMove1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    distance = sqrt(pow((float)descreteMove2.Xn-(float)descreteMove1.Xn,2)+pow((float)descreteMove2.Yn-(float)descreteMove1.Yn,2));
    cosX = ((float)descreteMove2.Xn-(float)descreteMove1.Xn)/distance;
    cosY = ((float)descreteMove2.Yn-(float)descreteMove1.Yn)/distance;
    tgEX = ((float)descreteMove2.En-(float)descreteMove1.En)/((float)descreteMove2.Xn-(float)descreteMove1.Xn);
    speedTargetX = (float)descreteMove2.FnXY*cosX;
    speedTargetY = (float)descreteMove2.FnXY*cosY;
    speedTargetE = (float)descreteMove2.FnXY*cosX*tgEX;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;              x2 = getCommandBufferElement_Gcode(2).dXn;                     x3 = getCommandBufferElement_Gcode(3).dXn;                           x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 < 0);                                          CHECK(x2 < 0);                                                 CHECK(x3 < 0);                                                       CHECK(x4 < 0);
    CHECK_EQUAL(descreteMove2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(speedTargetX, 2)/2/aDefault/cosX), x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;              y2 = getCommandBufferElement_Gcode(2).dYn;                     y3 = getCommandBufferElement_Gcode(3).dYn;                           y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 < 0);                                          CHECK(y2 < 0);                                                 CHECK(y3 < 0);                                                       CHECK(y4 < 0);
    CHECK_EQUAL(descreteMove2.Yn, y1+y2+y3+y4);
    e1 = getCommandBufferElement_Gcode(1).dEn;              e2 = getCommandBufferElement_Gcode(2).dEn;                     e3 = getCommandBufferElement_Gcode(3).dEn;                           e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 < 0);                                          CHECK(e2 < 0);                                                 CHECK(e3 < 0);                                                       CHECK(e4 < 0);
    CHECK_EQUAL(descreteMove2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;              v2 = getCommandBufferElement_Gcode(2).FnX;                     v3 = getCommandBufferElement_Gcode(3).FnX;                           v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetX - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetX - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;              v2 = getCommandBufferElement_Gcode(2).FnY;                     v3 = getCommandBufferElement_Gcode(3).FnY;                           v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetY - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetY - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;              v2 = getCommandBufferElement_Gcode(2).FnE;                     v3 = getCommandBufferElement_Gcode(3).FnE;                           v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(0 - v1) < floatError );                     CHECK( fabs(speedTargetE - v2) < 0.01*fabs(v2)+floatError );   CHECK( fabs(speedTargetE - v3) < 0.01*fabs(v3)+floatError );         CHECK( fabs(v4) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;              a2 = getCommandBufferElement_Gcode(2).AnX;                     a3 = getCommandBufferElement_Gcode(3).AnX;                           a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosX - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;              a2 = getCommandBufferElement_Gcode(2).AnY;                     a3 = getCommandBufferElement_Gcode(3).AnY;                           a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosY - a3) < 0.01*fabs(a3)+floatError );       CHECK( fabs(-aDefault*cosY - a4) < 0.01*fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;              a2 = getCommandBufferElement_Gcode(2).AnE;                     a3 = getCommandBufferElement_Gcode(3).AnE;                           a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosX*tgEX - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                            CHECK( fabs(-aDefault*cosX*tgEX - a3) < 0.01*fabs(a3)+floatError );  CHECK( fabs(-aDefault*cosX*tgEX - a4) < 0.01*fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_E_do_not_smooth)
{
    const descreteCommand_Gcode descreteMoveE = {MOVE_COMMAND, 0, 0, 0, 10000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE.FnE);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    long  e1;
    float v1;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());
    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(descreteMoveE.FnE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Z_do_not_smooth)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, 10000, 0,     0, 1000, 0,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);                                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;                  z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK(z1 > 0);                                  CHECK(z2 > 0);                                              CHECK(z3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2+z3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;                  v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(descreteMoveXSlow.FnZ - v2) < floatError );     CHECK( fabs(descreteMoveXSlow.FnZ - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;                  a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(aDefaultZ - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefaultZ - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_E_in_line_motion_do_not_smooth)
{
    const descreteCommand_Gcode descreteMoveE1 = {MOVE_COMMAND, 0, 0, 0, 10000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE1.FnE);
    const descreteCommand_Gcode descreteMoveE2 = {MOVE_COMMAND, 0, 0, 0, 20000,     0, 0, 1000,     0, 0};
    CHECK(maxSpeedE > descreteMoveE2.FnE);

    long  e1;
    float v1;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(descreteMoveE1.FnE - v1) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());
    e1 = getCommandBufferElement_Gcode(1).dEn;
    CHECK_EQUAL(descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(1).FnE;
    CHECK( fabs(descreteMoveE1.FnE - v1) < floatError );

    e1 = getCommandBufferElement_Gcode(2).dEn;
    CHECK_EQUAL(descreteMoveE2.En-descreteMoveE1.En, e1);
    v1 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(descreteMoveE2.FnE - v1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_X_do_not_smooth)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    float v1, v2, v3;
    float a1, a2, a3;

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(descreteMoveXSlow.FnXY - v2) < floatError );    CHECK( fabs(descreteMoveXSlow.FnXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XY_conserve_speed_different_directions_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     20000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    float distance1 = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2.0));
    float cosX1 = (float)descreteMoveSlow1.Xn/distance1;
    float cosY1 = (float)descreteMoveSlow1.Yn/distance1;
    float speedTargetX1 = cosX1*descreteMoveSlow1.FnXY;
    float speedTargetY1 = cosY1*descreteMoveSlow1.FnXY;

    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     20009, 10005, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance2 = sqrt(pow((float)(descreteMoveSlow2.Xn-descreteMoveSlow1.Xn),2)+pow((float)(descreteMoveSlow2.Yn-descreteMoveSlow1.Yn),2));
    float cosX2 = (float)(descreteMoveSlow2.Xn-descreteMoveSlow1.Xn)/distance2;
    float cosY2 = (float)(descreteMoveSlow2.Yn-descreteMoveSlow1.Yn)/distance2;

    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX1 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY1 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX1 - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY1 - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                  x2 = getCommandBufferElement_Gcode(2).dXn;                         x3 = getCommandBufferElement_Gcode(3).dXn;                      x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                              CHECK(x2 > 0);                                                     CHECK(x3 > 0);                                                  CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;                  y2 = getCommandBufferElement_Gcode(2).dYn;                         y3 = getCommandBufferElement_Gcode(3).dYn;                      y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                              CHECK(y2 > 0);                                                     CHECK(y3 > 0);                                                  CHECK(y4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK( labs(lroundf(pow(descreteMoveSlow1.FnXY, 2)/2/aDefault) - ( lroundf( sqrtf(pow(x3,2)+pow(y3,2)) + sqrtf(pow(x4,2)+pow(y4,2)) ) )) <= 1);
    v1 = getCommandBufferElement_Gcode(1).FnX;                  v2 = getCommandBufferElement_Gcode(2).FnX;                         v3 = getCommandBufferElement_Gcode(3).FnX;                      v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(speedTargetX1 - v2) < 0.01*fabs(v2)+floatError );      CHECK( fabs(speedTargetX1 - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(descreteMoveSlow1.FnXY*cosX2) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                  v2 = getCommandBufferElement_Gcode(2).FnY;                         v3 = getCommandBufferElement_Gcode(3).FnY;                      v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(speedTargetY1 - v2) < 0.01*fabs(v2)+floatError );      CHECK( fabs(speedTargetY1 - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(descreteMoveSlow1.FnXY*cosY2) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                  a2 = getCommandBufferElement_Gcode(2).AnX;                         a3 = getCommandBufferElement_Gcode(3).AnX;                      a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX1 - a1) < fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                                CHECK( fabs(-aDefault*cosX1 - a3) < fabs(a3)+floatError );      CHECK( fabs(-aDefault*cosX2 - a4) < fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                  a2 = getCommandBufferElement_Gcode(2).AnY;                         a3 = getCommandBufferElement_Gcode(3).AnY;                      a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY1 - a1) < fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                                CHECK( fabs(-aDefault*cosY1 - a3) < fabs(a3)+floatError );      CHECK( fabs(-aDefault*cosY2 - a4) < fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_slow_stop_XYE_conserve_speed_different_directions_smoothly)
{
    const descreteCommand_Gcode descreteMoveSlow1 = {MOVE_COMMAND,     20000, 10000, 0, 20000,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow1.FnXY);
    float distance1 = sqrt(pow((float)descreteMoveSlow1.Xn, 2.0)+pow((float)descreteMoveSlow1.Yn,2.0));
    float cosX1 = (float)descreteMoveSlow1.Xn/distance1;
    float cosY1 = (float)descreteMoveSlow1.Yn/distance1;
    float cosE1 = (float)descreteMoveSlow1.En/distance1;
    float speedTargetX1 = cosX1*descreteMoveSlow1.FnXY;
    float speedTargetY1 = cosY1*descreteMoveSlow1.FnXY;
    float speedTargetE1 = cosE1*descreteMoveSlow1.FnXY;

    const descreteCommand_Gcode descreteMoveSlow2 = {MOVE_COMMAND,     20009, 10005, 0, 20010,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveSlow2.FnXY);
    float distance2 = sqrt(pow((float)(descreteMoveSlow2.Xn-descreteMoveSlow1.Xn),2)+pow((float)(descreteMoveSlow2.Yn-descreteMoveSlow1.Yn),2));
    float cosX2 = (float)(descreteMoveSlow2.Xn-descreteMoveSlow1.Xn)/distance2;
    float cosY2 = (float)(descreteMoveSlow2.Yn-descreteMoveSlow1.Yn)/distance2;
    float cosE2 = (float)(descreteMoveSlow2.En-descreteMoveSlow1.En)/distance2;


    long  x1, x2, x3, x4;
    long  y1, y2, y3, y4;
    long  e1, e2, e3, e4;
    float v1, v2, v3, v4;
    float a1, a2, a3, a4;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                      CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveSlow1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetX1 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetY1 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(speedTargetE1 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX1 - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY1 - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;
    CHECK( fabs(aDefault*cosE1 - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                  x2 = getCommandBufferElement_Gcode(2).dXn;                         x3 = getCommandBufferElement_Gcode(3).dXn;                      x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                              CHECK(x2 > 0);                                                     CHECK(x3 > 0);                                                  CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Xn, x1+x2+x3+x4);
    y1 = getCommandBufferElement_Gcode(1).dYn;                  y2 = getCommandBufferElement_Gcode(2).dYn;                         y3 = getCommandBufferElement_Gcode(3).dYn;                      y4 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                              CHECK(y2 > 0);                                                     CHECK(y3 > 0);                                                  CHECK(y4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.Yn, y1+y2+y3+y4);
    CHECK( labs(lroundf(pow(descreteMoveSlow1.FnXY, 2)/2/aDefault) - ( lroundf( sqrtf(pow(x3,2)+pow(y3,2)) + sqrtf(pow(x4,2)+pow(y4,2)) ) )) <= 1);
    e1 = getCommandBufferElement_Gcode(1).dEn;                  e2 = getCommandBufferElement_Gcode(2).dEn;                         e3 = getCommandBufferElement_Gcode(3).dEn;                      e4 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                              CHECK(e2 > 0);                                                     CHECK(e3 > 0);                                                  CHECK(e4 > 0);
    CHECK_EQUAL(descreteMoveSlow2.En, e1+e2+e3+e4);
    v1 = getCommandBufferElement_Gcode(1).FnX;                  v2 = getCommandBufferElement_Gcode(2).FnX;                         v3 = getCommandBufferElement_Gcode(3).FnX;                      v4 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(speedTargetX1 - v2) < 0.01*fabs(v2)+floatError );      CHECK( fabs(speedTargetX1 - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(descreteMoveSlow1.FnXY*cosX2) );
    v1 = getCommandBufferElement_Gcode(1).FnY;                  v2 = getCommandBufferElement_Gcode(2).FnY;                         v3 = getCommandBufferElement_Gcode(3).FnY;                      v4 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(speedTargetY1 - v2) < 0.01*fabs(v2)+floatError );      CHECK( fabs(speedTargetY1 - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(descreteMoveSlow1.FnXY*cosY2) );
    v1 = getCommandBufferElement_Gcode(1).FnE;                  v2 = getCommandBufferElement_Gcode(2).FnE;                         v3 = getCommandBufferElement_Gcode(3).FnE;                      v4 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(0 - v1) < floatError );                         CHECK( fabs(speedTargetE1 - v2) < 0.01*fabs(v2)+floatError );      CHECK( fabs(speedTargetE1 - v3) < 0.01*fabs(v3)+floatError );   CHECK( fabs(v4) < fabs(descreteMoveSlow1.FnXY*cosE2) );
    a1 = getCommandBufferElement_Gcode(1).AnX;                  a2 = getCommandBufferElement_Gcode(2).AnX;                         a3 = getCommandBufferElement_Gcode(3).AnX;                      a4 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX1 - a1) < fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                                CHECK( fabs(-aDefault*cosX1 - a3) < fabs(a3)+floatError );      CHECK( fabs(-aDefault*cosX2 - a4) < fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;                  a2 = getCommandBufferElement_Gcode(2).AnY;                         a3 = getCommandBufferElement_Gcode(3).AnY;                      a4 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY1 - a1) < fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                                CHECK( fabs(-aDefault*cosY1 - a3) < fabs(a3)+floatError );      CHECK( fabs(-aDefault*cosY2 - a4) < fabs(a4)+floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;                  a2 = getCommandBufferElement_Gcode(2).AnE;                         a3 = getCommandBufferElement_Gcode(3).AnE;                      a4 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(aDefault*cosE1 - a1) < fabs(a1)+floatError );   CHECK( fabs(0 - a2) < floatError );                                CHECK( fabs(-aDefault*cosE1 - a3) < fabs(a3)+floatError );      CHECK( fabs(-aDefault*cosE2 - a4) < fabs(a4)+floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Z)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, 10000, 0,     0, 1000, 0,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);                                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;                  z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK(z1 > 0);                                  CHECK(z2 > 0);                                              CHECK(z3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2+z3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;                  v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(descreteMoveXSlow.FnZ - v2) < floatError );     CHECK( fabs(descreteMoveXSlow.FnZ - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;                  a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(aDefaultZ - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefaultZ - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Z_backwards)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, -10000, 0,     0, 1000, 0,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);                                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;                  z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK(z1 < 0);                                  CHECK(z2 < 0);                                              CHECK(z3 < 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2+z3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;                  v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(-descreteMoveXSlow.FnZ - v2) < floatError );    CHECK( fabs(-descreteMoveXSlow.FnZ - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;                  a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(-aDefaultZ - a1) < floatError );    CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(aDefaultZ - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_Z_cross_speed_limit)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, 1000000, 0,     0, 1000000, 0,     0, 0};
    CHECK(maxSpeedZ < descreteMoveXSlow.FnZ);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);                                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;                  z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK(z1 > 0);                                  CHECK(z2 > 0);                                              CHECK(z3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2+z3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;                  v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(maxSpeedZ - v2) < floatError );                 CHECK( fabs(maxSpeedZ - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;                  a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(aDefaultZ - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefaultZ - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_Z)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, 1000, 0,     0, 3000, 0,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    long  z1, z2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;
    CHECK(z1 > 0);                                  CHECK(z2 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(descreteMoveXSlow.FnZ) );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;
    CHECK( fabs(aDefaultZ - a1) < floatError );     CHECK( fabs(-aDefaultZ - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_Z_backwards)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, -1000, 0,     0, 3000, 0,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2;
    long  y1, y2;
    long  z1, z2;
    float v1, v2;
    float a1, a2;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;
    CHECK(z1 < 0);                                  CHECK(z2 < 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(descreteMoveXSlow.FnZ) );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;
    CHECK( fabs(-aDefaultZ - a1) < floatError );    CHECK( fabs(aDefaultZ - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_XZ)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 10000, 0, 10000, 0,     1000, 1000, 0,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);
    CHECK(maxSpeedXY > descreteMoveXSlow.FnXY);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);                                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;                  z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK(z1 > 0);                                  CHECK(z2 > 0);                                              CHECK(z3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2+z3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;                  v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(descreteMoveXSlow.FnZ - v2) < floatError );     CHECK( fabs(descreteMoveXSlow.FnZ - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;                  a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(aDefaultZ - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefaultZ - a3) < floatError );

    x1 = getCommandBufferElement_Gcode(4).dXn;      x2 = getCommandBufferElement_Gcode(5).dXn;                  x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                              CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;      y2 = getCommandBufferElement_Gcode(5).dYn;                  y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(4).dZn;      z2 = getCommandBufferElement_Gcode(5).dZn;                  z3 = getCommandBufferElement_Gcode(6).dZn;
    CHECK_EQUAL(0, z1);                             CHECK_EQUAL(0, z2);                                         CHECK_EQUAL(0, z3);
    v1 = getCommandBufferElement_Gcode(4).FnX;      v2 = getCommandBufferElement_Gcode(5).FnX;                  v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(descreteMoveXSlow.FnZ - v2) < floatError );     CHECK( fabs(descreteMoveXSlow.FnZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;      v2 = getCommandBufferElement_Gcode(5).FnY;                  v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;      v2 = getCommandBufferElement_Gcode(5).FnZ;                  v3 = getCommandBufferElement_Gcode(6).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;      a2 = getCommandBufferElement_Gcode(5).AnX;                  a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aDefault - a1) < floatError );      CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;      a2 = getCommandBufferElement_Gcode(5).AnY;                  a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;      a2 = getCommandBufferElement_Gcode(5).AnZ;                  a3 = getCommandBufferElement_Gcode(6).AnZ;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_slow_ZE)
{
    const descreteCommand_Gcode descreteMoveXSlow = {MOVE_COMMAND, 0, 0, 10000, 10000,     0, 1000, 1000,     0, 0};
    CHECK(maxSpeedZ > descreteMoveXSlow.FnZ);
    CHECK(maxSpeedE > descreteMoveXSlow.FnE);

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXSlow);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                             CHECK_EQUAL(0, x2);                                         CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                             CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;      z2 = getCommandBufferElement_Gcode(2).dZn;                  z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK(z1 > 0);                                  CHECK(z2 > 0);                                              CHECK(z3 > 0);
    CHECK_EQUAL(descreteMoveXSlow.Zn, z1+z2+z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;                  e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                             CHECK_EQUAL(0, e2);                                         CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;                  v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;                  v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;      v2 = getCommandBufferElement_Gcode(2).FnZ;                  v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(descreteMoveXSlow.FnZ - v2) < floatError );     CHECK( fabs(descreteMoveXSlow.FnZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;                  v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(0 - v2) < floatError );                         CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;                  a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;                  a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;      a2 = getCommandBufferElement_Gcode(2).AnZ;                  a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(aDefaultZ - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(-aDefaultZ - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;      a2 = getCommandBufferElement_Gcode(2).AnE;                  a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );             CHECK( fabs(0 - a2) < floatError );                         CHECK( fabs(0 - a3) < floatError );

    x1 = getCommandBufferElement_Gcode(4).dXn;
    CHECK_EQUAL(0, x1);
    y1 = getCommandBufferElement_Gcode(4).dYn;
    CHECK_EQUAL(0, y1);
    z1 = getCommandBufferElement_Gcode(4).dZn;
    CHECK_EQUAL(0, z1);
    e1 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1>0);
    CHECK_EQUAL(descreteMoveXSlow.En, e1);
    v1 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(descreteMoveXSlow.FnE - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;
    CHECK( fabs(0 - a1) < floatError );
}


static const float homeCoarseSpeedXY = (float)HOME_COARSE_SPEED*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float homeCoarseSpeedZ = (float)HOME_COARSE_SPEED*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float homeFineSpeedXY = (float)HOME_FINE_SPEED*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
static const float homeFineSpeedZ = (float)HOME_FINE_SPEED*(float)STEPS_PER_MM_Z/(float)SECONDS_IN_MINUTE;
static const float homeFineDistanceXY = (float)HOME_FINE_DISTANCE*(float)STEPS_PER_MM_XY;
static const float homeFineDistanceZ = (float)HOME_FINE_DISTANCE*(float)STEPS_PER_MM_Z;



TEST(Descrete_command_analyser_Gcode, home_X_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_X_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_X_long_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_X_COMMAND, 10000, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );

    long startDistance = lroundf(pow(homeCoarseSpeedXY,2)/(2*aDefault));
    CHECK(abs(descreteHome.Xn) > 2*startDistance);

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK_EQUAL(startDistance, x1);                     CHECK_EQUAL(descreteHome.Xn - 2*startDistance, x2); CHECK_EQUAL(startDistance, x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;          z3 = getCommandBufferElement_Gcode(6).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;          e3 = getCommandBufferElement_Gcode(6).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(homeCoarseSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;          v3 = getCommandBufferElement_Gcode(6).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;          v3 = getCommandBufferElement_Gcode(6).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;          a3 = getCommandBufferElement_Gcode(6).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;          a3 = getCommandBufferElement_Gcode(6).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_X_negative_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_X_COMMAND, -1000, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_X_short_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_X_COMMAND, 100, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError ); CHECK( fabs(homeCoarseSpeedXY - v2) < floatError );  CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );

    long startDistance = lroundf(pow(homeCoarseSpeedXY,2)/(2*aDefault));
    CHECK(abs(descreteHome.Xn) < 2*startDistance);
    long shortDistance = lroundf(0.25+(float)descreteHome.Xn/2);
    float shortSpeed = sqrtf(2*aDefault*shortDistance);


    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;
    CHECK_EQUAL(shortDistance, x1);                     CHECK_EQUAL(descreteHome.Xn - shortDistance, x2);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(shortSpeed - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(-aDefault - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_Y_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Y_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_Y_long_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Y_COMMAND, 0, 10000, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );

    long startDistance = lroundf(pow(homeCoarseSpeedXY,2)/(2*aDefault));
    CHECK(abs(descreteHome.Yn) > 2*startDistance);

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(startDistance, y1);                     CHECK_EQUAL(descreteHome.Yn - 2*startDistance, y2); CHECK_EQUAL(startDistance, y3);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;          z3 = getCommandBufferElement_Gcode(6).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;          e3 = getCommandBufferElement_Gcode(6).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(homeCoarseSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;          v3 = getCommandBufferElement_Gcode(6).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;          v3 = getCommandBufferElement_Gcode(6).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;          a3 = getCommandBufferElement_Gcode(6).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;          a3 = getCommandBufferElement_Gcode(6).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_Y_negative_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Y_COMMAND, 0, -1000, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_Y_short_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Y_COMMAND, 0, 100, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );

    long startDistance = lroundf(pow(homeCoarseSpeedXY,2)/(2*aDefault));
    CHECK(abs(descreteHome.Yn) < 2*startDistance);
    long shortDistance = lroundf(0.25+(float)descreteHome.Yn/2);
    float shortSpeed = sqrtf(2*aDefault*shortDistance);


    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;
    CHECK_EQUAL(shortDistance, y1);                     CHECK_EQUAL(descreteHome.Yn - shortDistance, y2);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(shortSpeed - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(-aDefault - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
}


TEST(Descrete_command_analyser_Gcode, home_Z_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Z_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(-homeFineDistanceZ, z2);                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(homeCoarseSpeedZ - v1) < floatError );  CHECK( fabs(-homeCoarseSpeedZ - v2) < floatError ); CHECK( fabs(homeFineSpeedZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}


TEST(Descrete_command_analyser_Gcode, home_Z_long_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Z_COMMAND, 0, 0, -100000, 0,     0, 0, 0,     0, 0};

    CHECK(descreteHome.Zn < 0);

    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(-homeFineDistanceZ, z2);                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(homeCoarseSpeedZ - v1) < floatError );  CHECK( fabs(-homeCoarseSpeedZ - v2) < floatError ); CHECK( fabs(homeFineSpeedZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );

    long startDistance = lroundf(pow(homeCoarseSpeedZ,2)/(2*aDefaultZ));
    CHECK(abs(descreteHome.Zn) > 2*startDistance);

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;          z3 = getCommandBufferElement_Gcode(6).dZn;
    CHECK_EQUAL(-startDistance, z1);                    CHECK_EQUAL(descreteHome.Zn + 2*startDistance, z2); CHECK_EQUAL(-startDistance, z3);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;          e3 = getCommandBufferElement_Gcode(6).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;          v3 = getCommandBufferElement_Gcode(6).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(-homeCoarseSpeedZ - v2) < floatError ); CHECK( fabs(-homeCoarseSpeedZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;          v3 = getCommandBufferElement_Gcode(6).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;          a3 = getCommandBufferElement_Gcode(6).AnZ;
    CHECK( fabs(-aDefaultZ - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(aDefaultZ - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;          a3 = getCommandBufferElement_Gcode(6).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_Z_positive_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Z_COMMAND, 0, 0, 1000, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(-homeFineDistanceZ, z2);                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(homeCoarseSpeedZ - v1) < floatError );  CHECK( fabs(-homeCoarseSpeedZ - v2) < floatError ); CHECK( fabs(homeFineSpeedZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_Z_short_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_Z_COMMAND, 0, 0, -1000, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);                                 CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);                                 CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(-homeFineDistanceZ, z2);                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(homeCoarseSpeedZ - v1) < floatError );  CHECK( fabs(-homeCoarseSpeedZ - v2) < floatError ); CHECK( fabs(homeFineSpeedZ - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );

    long startDistance = lroundf(pow(homeCoarseSpeedZ,2)/(2*aDefaultZ));
    CHECK(abs(descreteHome.Zn) < 2*startDistance);
    long shortDistance = abs(lroundf(-0.25+(float)descreteHome.Zn/2));
    float shortSpeed = sqrtf(2*aDefaultZ*shortDistance);


    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(0, x2);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(0, y2);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;
    CHECK_EQUAL(-shortDistance, z1);                    CHECK_EQUAL(descreteHome.Zn + shortDistance, z2);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(-shortSpeed - v2) < 0.01*shortSpeed+floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;
    CHECK( fabs(-aDefaultZ - a1) < floatError );        CHECK( fabs(aDefaultZ - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XY_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XY_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,        getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XY_long_distance_1)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XY_COMMAND, 10000, 10000, 0, 0,     0, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,        getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );


    float distance = sqrtf((float)descreteHome.Xn*(float)descreteHome.Xn+(float)descreteHome.Yn*(float)descreteHome.Yn);
    float cosX = (float)descreteHome.Xn/distance;
    float cosY = (float)descreteHome.Yn/distance;
    float vX = homeCoarseSpeedXY*cosX;
    float vY = homeCoarseSpeedXY*cosY;
    float aX = aDefault*cosX;
    float aY = aDefault*cosY;

    float startDistance = pow(homeCoarseSpeedXY,2)/(2*aDefault);
    CHECK(distance > 2*startDistance);

    long startDistanceX = lroundf(startDistance*cosX);
    long startDistanceY = lroundf(startDistance*cosY);

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK_EQUAL(startDistanceX, x1);                    CHECK_EQUAL(descreteHome.Xn-2*startDistanceX, x2);  CHECK_EQUAL(startDistanceX, x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(startDistanceY, y1);                    CHECK_EQUAL(descreteHome.Yn-2*startDistanceY, y2);  CHECK_EQUAL(startDistanceY, y3);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;          z3 = getCommandBufferElement_Gcode(6).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;          e3 = getCommandBufferElement_Gcode(6).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vX - v2) < floatError );                CHECK( fabs(vX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vY - v2) < floatError );                CHECK( fabs(vY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;          v3 = getCommandBufferElement_Gcode(6).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;          v3 = getCommandBufferElement_Gcode(6).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aX - a1) < floatError );                CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(aY - a1) < floatError );                CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;          a3 = getCommandBufferElement_Gcode(6).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;          a3 = getCommandBufferElement_Gcode(6).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XY_long_distance_2)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XY_COMMAND, 0, 10000, 0, 0,     0, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,        getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );


    float distance = sqrtf((float)descreteHome.Xn*(float)descreteHome.Xn+(float)descreteHome.Yn*(float)descreteHome.Yn);
    float cosX = (float)descreteHome.Xn/distance;
    float cosY = (float)descreteHome.Yn/distance;
    float vX = homeCoarseSpeedXY*cosX;
    float vY = homeCoarseSpeedXY*cosY;
    float aX = aDefault*cosX;
    float aY = aDefault*cosY;

    float startDistance = pow(homeCoarseSpeedXY,2)/(2*aDefault);
    CHECK(distance > 2*startDistance);

    long startDistanceX = lroundf(startDistance*cosX);
    long startDistanceY = lroundf(startDistance*cosY);

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;          x3 = getCommandBufferElement_Gcode(6).dXn;
    CHECK_EQUAL(startDistanceX, x1);                    CHECK_EQUAL(descreteHome.Xn-2*startDistanceX, x2);  CHECK_EQUAL(startDistanceX, x3);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;          y3 = getCommandBufferElement_Gcode(6).dYn;
    CHECK_EQUAL(startDistanceY, y1);                    CHECK_EQUAL(descreteHome.Yn-2*startDistanceY, y2);  CHECK_EQUAL(startDistanceY, y3);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;          z3 = getCommandBufferElement_Gcode(6).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;          e3 = getCommandBufferElement_Gcode(6).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;          v3 = getCommandBufferElement_Gcode(6).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vX - v2) < floatError );                CHECK( fabs(vX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;          v3 = getCommandBufferElement_Gcode(6).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(vY - v2) < floatError );                CHECK( fabs(vY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;          v3 = getCommandBufferElement_Gcode(6).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;          v3 = getCommandBufferElement_Gcode(6).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;          a3 = getCommandBufferElement_Gcode(6).AnX;
    CHECK( fabs(aX - a1) < floatError );                CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;          a3 = getCommandBufferElement_Gcode(6).AnY;
    CHECK( fabs(aY - a1) < floatError );                CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aY - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;          a3 = getCommandBufferElement_Gcode(6).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;          a3 = getCommandBufferElement_Gcode(6).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XY_negative_distance_1)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XY_COMMAND, -1000, -1000, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,        getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XY_negative_distance_2)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XY_COMMAND, -1000, 1000, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,        getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XY_short_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XY_COMMAND, 100, 200, 0, 0,     0, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,        getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;
    long  z1, z2, z3;
    long  e1, e2, e3;
    float v1, v2, v3;
    float a1, a2, a3;


    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;          x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(0, x1);                                 CHECK_EQUAL(homeFineDistanceXY, x2);                CHECK_EQUAL(0, x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;          y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                                 CHECK_EQUAL(homeFineDistanceXY, y2);                CHECK_EQUAL(0, y3);
    z1 = getCommandBufferElement_Gcode(1).dZn;          z2 = getCommandBufferElement_Gcode(2).dZn;          z3 = getCommandBufferElement_Gcode(3).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);                                 CHECK_EQUAL(0, z3);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;          e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);                                 CHECK_EQUAL(0, e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;          v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;          v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-homeCoarseSpeedXY - v1) < floatError );CHECK( fabs(homeCoarseSpeedXY - v2) < floatError ); CHECK( fabs(-homeFineSpeedXY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnZ;          v2 = getCommandBufferElement_Gcode(2).FnZ;          v3 = getCommandBufferElement_Gcode(3).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;          v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );                 CHECK( fabs(0 - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;          a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;          a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnZ;          a2 = getCommandBufferElement_Gcode(2).AnZ;          a3 = getCommandBufferElement_Gcode(3).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnE;          a2 = getCommandBufferElement_Gcode(2).AnE;          a3 = getCommandBufferElement_Gcode(3).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(0 - a3) < floatError );


    float distance = sqrtf((float)descreteHome.Xn*(float)descreteHome.Xn+(float)descreteHome.Yn*(float)descreteHome.Yn);
    float cosX = (float)descreteHome.Xn/distance;
    float cosY = (float)descreteHome.Yn/distance;
    float vX = homeCoarseSpeedXY*cosX;
    float vY = homeCoarseSpeedXY*cosY;
    float aX = aDefault*cosX;
    float aY = aDefault*cosY;

    float startDistance = pow(homeCoarseSpeedXY,2)/(2*aDefault);
    CHECK(distance < 2*startDistance);

    long startDistanceX = lroundf(0.25+(float)descreteHome.Xn/2);
    long startDistanceY = lroundf(0.25+(float)descreteHome.Yn/2);

    x1 = getCommandBufferElement_Gcode(4).dXn;          x2 = getCommandBufferElement_Gcode(5).dXn;
    CHECK_EQUAL(startDistanceX, x1);                    CHECK_EQUAL(descreteHome.Xn-startDistanceX, x2);
    y1 = getCommandBufferElement_Gcode(4).dYn;          y2 = getCommandBufferElement_Gcode(5).dYn;
    CHECK_EQUAL(startDistanceY, y1);                    CHECK_EQUAL(descreteHome.Yn-startDistanceY, y2);
    z1 = getCommandBufferElement_Gcode(4).dZn;          z2 = getCommandBufferElement_Gcode(5).dZn;
    CHECK_EQUAL(0, z1);                                 CHECK_EQUAL(0, z2);
    e1 = getCommandBufferElement_Gcode(4).dEn;          e2 = getCommandBufferElement_Gcode(5).dEn;
    CHECK_EQUAL(0, e1);                                 CHECK_EQUAL(0, e2);
    v1 = getCommandBufferElement_Gcode(4).FnX;          v2 = getCommandBufferElement_Gcode(5).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(v2) < fabs(vX) );
    v1 = getCommandBufferElement_Gcode(4).FnY;          v2 = getCommandBufferElement_Gcode(5).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(v2) < fabs(vY) );
    v1 = getCommandBufferElement_Gcode(4).FnZ;          v2 = getCommandBufferElement_Gcode(5).FnZ;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(4).FnE;          v2 = getCommandBufferElement_Gcode(5).FnE;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnX;          a2 = getCommandBufferElement_Gcode(5).AnX;
    CHECK( fabs(aX - a1) < floatError );                CHECK( fabs(-aX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnY;          a2 = getCommandBufferElement_Gcode(5).AnY;
    CHECK( fabs(aY - a1) < floatError );                CHECK( fabs(-aY - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnZ;          a2 = getCommandBufferElement_Gcode(5).AnZ;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(4).AnE;          a2 = getCommandBufferElement_Gcode(5).AnE;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, home_XZ_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XZ_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(4).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(5).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(6).type);
}

TEST(Descrete_command_analyser_Gcode, home_YZ_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_YZ_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);
    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(4).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(5).type);
    CHECK_EQUAL(GO_HOME_Y_COMMAND,  getCommandBufferElement_Gcode(6).type);
}

TEST(Descrete_command_analyser_Gcode, home_XYZ_zero_distance)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_XYZ_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_Z_COMMAND,  getCommandBufferElement_Gcode(3).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND, getCommandBufferElement_Gcode(4).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(5).type);
    CHECK_EQUAL(GO_HOME_XY_COMMAND, getCommandBufferElement_Gcode(6).type);
}

TEST(Descrete_command_analyser_Gcode, home_X_zero_distance_do_not_smooth)
{
    const descreteCommand_Gcode descreteHome = {GO_HOME_X_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(descreteHome);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,       getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(GO_HOME_X_COMMAND,  getCommandBufferElement_Gcode(3).type);
}

TEST(Descrete_command_analyser_Gcode, set_new_coordinates)
{
    const descreteCommand_Gcode commandSetX  = {SET_COORDINATES_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    const descreteCommand_Gcode commandMoveX = {MOVE_COMMAND,            20000, 0, 0, 0,     1000, 0, 0,     0, 0};


    addElementToDescreteCommandBuffer_Gcode(commandSetX);
    addElementToDescreteCommandBuffer_Gcode(commandMoveX);
    descreteCommandAnalyser_Gcode();
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();


    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(MOVE_COMMAND,  getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(MOVE_COMMAND,  getCommandBufferElement_Gcode(2).type);
    CHECK_EQUAL(MOVE_COMMAND,  getCommandBufferElement_Gcode(3).type);


    long  x1, x2, x3;
    long  y1, y2, y3;

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;                  x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                                              CHECK(x3 > 0);
    CHECK_EQUAL(commandMoveX.Xn-commandSetX.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;  y2 = getCommandBufferElement_Gcode(2).dYn;                  y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);                         CHECK_EQUAL(0, y2);                                         CHECK_EQUAL(0, y3);
}

TEST(Descrete_command_analyser_Gcode, set_extruder_temperatre)
{
    const descreteCommand_Gcode commandSetExtrTemperature  = {HEAT_EXTRUDER_COMMAND, 0, 0, 0, 0,     0, 0, 0,     100, 0};

    addElementToDescreteCommandBuffer_Gcode(commandSetExtrTemperature);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();


    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(HEAT_EXTRUDER_COMMAND,              getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(commandSetExtrTemperature.extrT,    getCommandBufferElement_Gcode(1).extrT);
    CHECK_EQUAL(commandSetExtrTemperature.bedT,     getCommandBufferElement_Gcode(1).bedT);
}

TEST(Descrete_command_analyser_Gcode, set_bed_temperatre)
{
    const descreteCommand_Gcode commandSetBedTemperature  = {HEAT_BED_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 100};

    addElementToDescreteCommandBuffer_Gcode(commandSetBedTemperature);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();


    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(HEAT_BED_COMMAND,                   getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(commandSetBedTemperature.extrT,     getCommandBufferElement_Gcode(1).extrT);
    CHECK_EQUAL(commandSetBedTemperature.bedT,      getCommandBufferElement_Gcode(1).bedT);
}

TEST(Descrete_command_analyser_Gcode, wait_extruder_temperatre)
{
    const descreteCommand_Gcode commandSetExtrTemperature  = {WAIT_HEAT_EXTRUDER_COMMAND, 0, 0, 0, 0,     0, 0, 0,     100, 0};

    addElementToDescreteCommandBuffer_Gcode(commandSetExtrTemperature);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();


    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(WAIT_HEAT_EXTRUDER_COMMAND,         getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(commandSetExtrTemperature.extrT,    getCommandBufferElement_Gcode(1).extrT);
    CHECK_EQUAL(commandSetExtrTemperature.bedT,     getCommandBufferElement_Gcode(1).bedT);
}

TEST(Descrete_command_analyser_Gcode, wait_bed_temperatre)
{
    const descreteCommand_Gcode commandSetBedTemperature  = {WAIT_HEAT_BED_COMMAND, 0, 0, 0, 0,     0, 0, 0,     0, 100};

    addElementToDescreteCommandBuffer_Gcode(commandSetBedTemperature);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();


    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    CHECK_EQUAL(WAIT_HEAT_BED_COMMAND,              getCommandBufferElement_Gcode(1).type);
    CHECK_EQUAL(commandSetBedTemperature.extrT,     getCommandBufferElement_Gcode(1).extrT);
    CHECK_EQUAL(commandSetBedTemperature.bedT,      getCommandBufferElement_Gcode(1).bedT);
}

TEST(Descrete_command_analyser_Gcode, repeate_the_desctreate_command)
{
    const descreteCommand_Gcode command1 = {SET_COORDINATES_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,            20000, 0, 0, 0,     1000, 0, 0,     0, 0};
    const descreteCommand_Gcode command3 = {SET_COORDINATES_COMMAND, 20000, 0, 0, 0,     1000, 0, 0,     0, 1};

    addElementToDescreteCommandBuffer_Gcode(command1);
    CHECK(descreteCommandIsRepeated(command1));
    CHECK(!descreteCommandIsRepeated(command2));
    CHECK(!descreteCommandIsRepeated(command3));
}


TEST(Descrete_command_analyser_Gcode, short_travel_xy_1)
{
    const descreteCommand_Gcode command = {MOVE_COMMAND,  20,   112, 0, 0,     2000, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(command);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

}

TEST(Descrete_command_analyser_Gcode, short_travel_xy_2)
{
    const descreteCommand_Gcode command = {MOVE_COMMAND,  53,   91, 0, 0,     2000, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(command);
    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

}

TEST(Descrete_command_analyser_Gcode, motion_near_critical_angle_1)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND,  53,   91, 0, 0,     2000, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  73,  203, 0, 0,     2000, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    long dxNext = getDescreteCommandBufferElement_Gcode(3).Xn - getDescreteCommandBufferElement_Gcode(2).Xn;
    long dyNext = getDescreteCommandBufferElement_Gcode(3).Yn - getDescreteCommandBufferElement_Gcode(2).Yn;

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    long dxPrev = getDescreteCommandBufferElement_Gcode(2).Xn - getDescreteCommandBufferElement_Gcode(1).Xn;
    long dyPrev = getDescreteCommandBufferElement_Gcode(2).Yn - getDescreteCommandBufferElement_Gcode(1).Yn;

    CHECK_EQUAL(dxNext, 20);
    CHECK_EQUAL(dxPrev, 20);
    CHECK_EQUAL(dyNext, 112);
    CHECK_EQUAL(dyPrev, 112);
}


TEST(Descrete_command_analyser_Gcode, motion_near_critical_angle_2)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND, -23,  905, 0, 0,     2000, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  30,  996, 0, 0,     2000, 0, 0,     0, 0};
    const descreteCommand_Gcode command3 = {MOVE_COMMAND,  50, 1108, 0, 0,     2000, 0, 0,     0, 0};

    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    addElementToDescreteCommandBuffer_Gcode(command3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 7, checkFreeSpaceCommandBuffer_Gcode());
}

TEST(Descrete_command_analyser_Gcode, change_speed_without_mooving_at_the_end_X)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND,  24,  0, 0, 0,     1000, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  24,  0, 0, 0,     1200, 0, 0,     0, 0};

    long  x1, x2;

    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command1.Xn, x1+x2);

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command1.Xn, x1+x2);
}

TEST(Descrete_command_analyser_Gcode, change_speed_without_mooving_X_1)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND,  24,  0, 0, 0,     1000, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  24,  0, 0, 0,     1200, 0, 0,     0, 0};
    const descreteCommand_Gcode command3 = {MOVE_COMMAND,  40,  0, 0, 0,     1000, 0, 0,     0, 0};

    long  x1, x2;

    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command1.Xn, x1+x2);

    addElementToDescreteCommandBuffer_Gcode(command3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command2.Xn, x1+x2);

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();


    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;                      x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command3.Xn-command2.Xn, x1+x2);
}


TEST(Descrete_command_analyser_Gcode, change_speed_without_mooving_XY)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND,  24,  10, 0, 0,     1000, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  24,  10, 0, 0,     1200, 0, 0,     0, 0};
    const descreteCommand_Gcode command3 = {MOVE_COMMAND,  40,  16, 0, 0,     1000, 0, 0,     0, 0};

    long  x1, x2;
    long  y1, y2;


    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                      y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                                  CHECK(y2 > 0);
    CHECK_EQUAL(command1.Yn, y1+y2);

    addElementToDescreteCommandBuffer_Gcode(command3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;                      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;                      y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                                  CHECK(y2 > 0);
    CHECK_EQUAL(command1.Yn, y1+y2);


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;                      x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                                  CHECK(x2 > 0);
    CHECK_EQUAL(command3.Xn-command2.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(3).dYn;                      y2 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                                  CHECK(y2 > 0);
    CHECK_EQUAL(command3.Yn-command2.Yn, y1+y2);

}



TEST(Descrete_command_analyser_Gcode, change_speed_without_mooving_X_2)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND,  17,  0, 0, 0,     6400, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  27,  0, 0, 0,     800,  0, 0,     0, 0};
    const descreteCommand_Gcode command3 = {MOVE_COMMAND,  48,  0, 0, 0,     800,  0, 0,     0, 0};
    const descreteCommand_Gcode command4 = {MOVE_COMMAND,  48,  0, 0, 0,     6400, 0, 0,     0, 0};
    const descreteCommand_Gcode command5 = {MOVE_COMMAND,  64,  0, 0, 0,     800,  0, 0,     0, 0};

    long  x1, x2, x3;
    float v1, v2;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(17, x1);
    CHECK_EQUAL(command1.Xn, x1);


    addElementToDescreteCommandBuffer_Gcode(command3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;     x2 = getCommandBufferElement_Gcode(2).dXn;     x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                 CHECK(x2 > 0);                                 CHECK(x3 > 0);
    CHECK_EQUAL(17, x1);                           CHECK_EQUAL(7, x2);                            CHECK_EQUAL(3, x3);
    CHECK_EQUAL(command2.Xn, x1+x2+x3);
    a1 = getCommandBufferElement_Gcode(1).AnX;     a2 = getCommandBufferElement_Gcode(2).AnX;     a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK(a1 > 0);                                 CHECK(a2 > 0);                                 CHECK(a3 == 0);


    addElementToDescreteCommandBuffer_Gcode(command4);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;     x2 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                 CHECK(x2 > 0);
    CHECK_EQUAL(3, x1);                            CHECK_EQUAL(21, x2);
    v1 = getCommandBufferElement_Gcode(3).FnX;     v2 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( v1 > 0 );                               CHECK( v2 > 0);
    a1 = getCommandBufferElement_Gcode(3).AnX;     a2 = getCommandBufferElement_Gcode(4).AnX;
    CHECK(a1 < floatError);                        CHECK(a2 < floatError);
    CHECK_EQUAL(command3.Xn-command2.Xn, x2);


    addElementToDescreteCommandBuffer_Gcode(command5);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 6, checkFreeSpaceCommandBuffer_Gcode());


}

/*
TEST(Descrete_command_analyser_Gcode, change_speed_without_mooving_X_2)
{
    const descreteCommand_Gcode command1 = {MOVE_COMMAND,  17,  0, 0, 0,     6400, 0, 0,     0, 0};
    const descreteCommand_Gcode command2 = {MOVE_COMMAND,  27,  0, 0, 0,     800,  0, 0,     0, 0};
    const descreteCommand_Gcode command3 = {MOVE_COMMAND,  48,  0, 0, 0,     800,  0, 0,     0, 0};
    const descreteCommand_Gcode command4 = {MOVE_COMMAND,  48,  0, 0, 0,     6400, 0, 0,     0, 0};
    const descreteCommand_Gcode command5 = {MOVE_COMMAND,  64,  0, 0, 0,     800,  0, 0,     0, 0};

    long  x1, x2, x3;
    float v1, v2, v3;
    float a1, a2, a3;

    addElementToDescreteCommandBuffer_Gcode(command1);
    addElementToDescreteCommandBuffer_Gcode(command2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(17, x1);
    CHECK_EQUAL(command1.Xn, x1);


    addElementToDescreteCommandBuffer_Gcode(command3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;     x2 = getCommandBufferElement_Gcode(2).dXn;     x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                 CHECK(x2 > 0);                                 CHECK(x3 > 0);
    CHECK_EQUAL(17, x1);                           CHECK_EQUAL(7, x2);                            CHECK_EQUAL(3, x3);
    CHECK_EQUAL(command2.Xn, x1+x2+x3);
    a1 = getCommandBufferElement_Gcode(1).AnX;     a2 = getCommandBufferElement_Gcode(2).AnX;     a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK(a1 > 0);                                 CHECK(a2 > 0);                                 CHECK(a3 == 0);

    addElementToDescreteCommandBuffer_Gcode(command4);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;     x2 = getCommandBufferElement_Gcode(4).dXn;     x3 = getCommandBufferElement_Gcode(5).dXn;
    CHECK(x1 == 0);                                CHECK(x2 > 0);                                 CHECK(x3 > 0);
    CHECK_EQUAL(0, x1);                            CHECK_EQUAL(3, x2);                            CHECK_EQUAL(21, x3);
    v1 = getCommandBufferElement_Gcode(3).FnX;     v2 = getCommandBufferElement_Gcode(4).FnX;     v3 = getCommandBufferElement_Gcode(5).FnX;
    CHECK( fabs(v1 - 800) < floatError );          CHECK( fabs(v2 - 800) < floatError );          CHECK( fabs(v3 - 748.331) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;     a2 = getCommandBufferElement_Gcode(4).AnX;     a3 = getCommandBufferElement_Gcode(5).AnX;
    CHECK(fabs(a1) < floatError);                  CHECK(fabs(a2 + aDefault) < floatError);       CHECK(fabs(a3 + aDefault) < floatError);
    CHECK_EQUAL(command3.Xn-command2.Xn, x3);


    addElementToDescreteCommandBuffer_Gcode(command5);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 5, checkFreeSpaceCommandBuffer_Gcode());

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 7, checkFreeSpaceCommandBuffer_Gcode());





    x1 = getCommandBufferElement_Gcode(1).dXn;     x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                 CHECK(x2 > 0);
    CHECK_EQUAL(17, x1);                           CHECK_EQUAL(7, x2);
    CHECK_EQUAL(24, x1+x2);
    v1 = getCommandBufferElement_Gcode(1).FnX;     v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(v1 - 0) < floatError );            CHECK( fabs(v2 - 673.3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;     a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK(a1 > 0);                                 CHECK(a2 > 0);

    x1 = getCommandBufferElement_Gcode(3).dXn;     x2 = getCommandBufferElement_Gcode(4).dXn;     x3 = getCommandBufferElement_Gcode(5).dXn;
    CHECK(x1 == 0);                                CHECK(x2 > 0);                                 CHECK(x3 > 0);
    CHECK_EQUAL(0, x1);                            CHECK_EQUAL(3, x2);                            CHECK_EQUAL(21, x3);
    v1 = getCommandBufferElement_Gcode(3).FnX;     v2 = getCommandBufferElement_Gcode(4).FnX;     v3 = getCommandBufferElement_Gcode(5).FnX;
    CHECK( fabs(v1 - 800) < floatError );          CHECK( fabs(v2 - 800) < floatError );          CHECK( fabs(v3 - 748.331) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;     a2 = getCommandBufferElement_Gcode(4).AnX;     a3 = getCommandBufferElement_Gcode(5).AnX;
    CHECK(fabs(a1) < floatError);                  CHECK(fabs(a2 + aDefault) < floatError);       CHECK(fabs(a3 + aDefault) < floatError);
    CHECK(a1 == 0);                                CHECK(a2 < 0);                                 CHECK(a3 < 0);
    CHECK_EQUAL(command3.Xn-command2.Xn, x3);

}
*/
