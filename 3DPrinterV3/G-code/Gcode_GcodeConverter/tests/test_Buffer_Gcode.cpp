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
static const float maxSpeedXY = (float)MAX_SPEED_MM_MIN_XY*(float)STEPS_PER_MM_XY/(float)SECONDS_IN_MINUTE;
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
    const descreteCommand_Gcode descreteMoveXFast = {MOVE_COMMAND, 1000, 0, 0, 0,     3000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXFast = {MOVE_COMMAND, -1000, 0, 0, 0,     3000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND,   100, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 20000, 0, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND,   -100, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, -20000, 0, 0, 0,     1000, 0, 0,     0, 0};
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


TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_X_conserve_speed_smoothly)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, 10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, 10100, 0, 0, 0,     1000, 0, 0,     0, 0};
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
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(descreteMoveXSlow1.FnXY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn - descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(descreteMoveXSlow1.FnXY - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );


    smoothStop_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 4, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;  x2 = getCommandBufferElement_Gcode(2).dXn;  x3 = getCommandBufferElement_Gcode(3).dXn;  x4 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                              CHECK(x2 > 0);                              CHECK(x3 > 0);                              CHECK(x4 > 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn, x1+x2+x3+x4);
    CHECK_EQUAL(lroundf(pow(vTarget1, 2)/2/aDefault), x3+x4);
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


TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_X_backwards_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveXSlow1 = {MOVE_COMMAND, -10000, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXSlow2 = {MOVE_COMMAND, -10100, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

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
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(-descreteMoveXSlow1.FnXY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXSlow2.Xn - descreteMoveXSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(0, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(-descreteMoveXSlow1.FnXY - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, three_commands_small_steps_X)
{
    const descreteCommand_Gcode descreteMoveX1 = {MOVE_COMMAND, 100, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveX1.FnXY);
    const descreteCommand_Gcode descreteMoveX2 = {MOVE_COMMAND, 200, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveX2.FnXY);
    const descreteCommand_Gcode descreteMoveX3 = {MOVE_COMMAND, 300, 0, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveX3.FnXY);

    float speedFinal1 = sqrt(2*(float)descreteMoveX1.Xn*aDefault);
    float speedFinal2 = sqrt(2*(float)(descreteMoveX2.Xn-descreteMoveX1.Xn)*aDefault+pow(speedFinal1,2));

    long  x1;
    long  y1;
    float v1;
    float a1;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveX1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveX2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK_EQUAL(descreteMoveX1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(descreteMoveX1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(0 - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(descreteMoveX3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(2).dXn;
    CHECK_EQUAL(descreteMoveX2.Xn-descreteMoveX1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(descreteMoveX2.Yn-descreteMoveX1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(speedFinal1 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(0 - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(descreteMoveX3.Xn-descreteMoveX2.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(descreteMoveX3.Yn-descreteMoveX2.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedFinal2 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(0 - a1) < floatError );
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
    const descreteCommand_Gcode descreteMoveYFast = {MOVE_COMMAND, 0, 1000, 0, 0,     3000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveYFast = {MOVE_COMMAND, 0, -1000, 0, 0,     3000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0,   100, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, 20000, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0,   -100, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, -20000, 0, 0,     1000, 0, 0,     0, 0};
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

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_Y_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, 10100, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 == 0);                                     CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(descreteMoveYSlow1.FnXY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault - a1) < floatError );          CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn - descreteMoveYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn - descreteMoveYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(descreteMoveYSlow1.FnXY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_Y_backwards_conserve_speed)
{
    const descreteCommand_Gcode descreteMoveYSlow1 = {MOVE_COMMAND, 0, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveYSlow2 = {MOVE_COMMAND, 0, -10100, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveYSlow2.FnXY);

    long  x1, x2;
    long  y1, y2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveYSlow2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 == 0);                                     CHECK(x2 == 0);
    CHECK_EQUAL(descreteMoveYSlow1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 < 0);                                      CHECK(y2 < 0);
    CHECK_EQUAL(descreteMoveYSlow1.Yn, y1+y2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(0 - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );                 CHECK( fabs(-descreteMoveYSlow1.FnXY - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );                 CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );         CHECK( fabs(0 - a2) < floatError );


    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 == 0);
    CHECK_EQUAL(descreteMoveYSlow2.Xn - descreteMoveYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveYSlow2.Yn - descreteMoveYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(-descreteMoveYSlow1.FnXY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, three_commands_small_steps_Y)
{
    const descreteCommand_Gcode descreteMoveY1 = {MOVE_COMMAND, 0, 100, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveY1.FnXY);
    const descreteCommand_Gcode descreteMoveY2 = {MOVE_COMMAND, 0, 200, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveY2.FnXY);
    const descreteCommand_Gcode descreteMoveY3 = {MOVE_COMMAND, 0, 300, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveY3.FnXY);

    float speedFinal1 = sqrt(2*(float)descreteMoveY1.Yn*aDefault);
    float speedFinal2 = sqrt(2*(float)(descreteMoveY2.Yn-descreteMoveY1.Yn)*aDefault+pow(speedFinal1,2));

    long  x1;
    long  y1;
    float v1;
    float a1;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveY1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveY2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 1, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;
    CHECK_EQUAL(descreteMoveY1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(1).dYn;
    CHECK_EQUAL(descreteMoveY1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(1).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;
    CHECK( fabs(0 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;
    CHECK( fabs(aDefault - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(descreteMoveY3);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(2).dXn;
    CHECK_EQUAL(descreteMoveY2.Xn-descreteMoveY1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(2).dYn;
    CHECK_EQUAL(descreteMoveY2.Yn-descreteMoveY1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(speedFinal1 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault - a1) < floatError );

    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK_EQUAL(descreteMoveY3.Xn-descreteMoveY2.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK_EQUAL(descreteMoveY3.Yn-descreteMoveY2.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedFinal2 - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(0 - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault - a1) < floatError );
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
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, 200, 100, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, 100, 200, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, 200, 200, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, -200, -100, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, -100, -200, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYFast = {MOVE_COMMAND, -200, -200, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,       100,    50, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     20000, 10000, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,        50,   100, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     10000, 20000, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,        50,    50, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,       -100,    -50, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,        -50,   -100, 0, 0,     1000, 0, 0,     0, 0};
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
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,        -50,    -50, 0, 0,     1000, 0, 0,     0, 0};
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

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XY_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     20000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     20100, 10050, 0, 0,     1000, 0, 0,     0, 0};
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

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XY_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     10000, 20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     10050, 20100, 0, 0,     1000, 0, 0,     0, 0};
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

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XY_conserve_speed_3)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     10000, 10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     10100, 10100, 0, 0,     1000, 0, 0,     0, 0};
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

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XY_conserve_speed_1_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     -20000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -20100, -10050, 0, 0,     1000, 0, 0,     0, 0};
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

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XY_conserve_speed_2_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     -10000, -20000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -10050, -20100, 0, 0,     1000, 0, 0,     0, 0};
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

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XY_conserve_speed_3_backwards)
{
    const descreteCommand_Gcode descreteMoveXYSlow1 = {MOVE_COMMAND,     -10000, -10000, 0, 0,     1000, 0, 0,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYSlow1.FnXY);
    const descreteCommand_Gcode descreteMoveXYSlow2 = {MOVE_COMMAND,     -10100, -10100, 0, 0,     1000, 0, 0,     0, 0};
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

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn, 2)+pow((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn,2));
    cosX = ((float)descreteMoveXYSlow2.Xn-(float)descreteMoveXYSlow1.Xn)/distance;
    cosY = ((float)descreteMoveXYSlow2.Yn-(float)descreteMoveXYSlow1.Yn)/distance;
    speedTargetX = cosX*descreteMoveXYSlow2.FnXY;
    speedTargetY = cosY*descreteMoveXYSlow2.FnXY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Xn-descreteMoveXYSlow1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 < 0);
    CHECK_EQUAL(descreteMoveXYSlow2.Yn-descreteMoveXYSlow1.Yn, y1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                  CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                  CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 < 0);                                  CHECK(e2 < 0);                                    CHECK(e3 < 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 < 0);                                  CHECK(e2 < 0);                                    CHECK(e3 < 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                  CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK_EQUAL(speedTargetX, v2);
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;        x3 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);                                    CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;        y3 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);                                    CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;        e3 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);                                  CHECK(e2 > 0);                                    CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;        v3 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetX - v2) < floatError );    CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;        v3 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetY - v2) < floatError );    CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;        v3 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(speedTargetE - v2) < floatError );    CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;        a3 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;        a3 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(0 - a2) < floatError );               CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XYE_1)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 100, 50, 0, 100,     1000, 0, 2000,     0, 0};
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                  CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, one_command_move_fast_XYE_2)
{
    const descreteCommand_Gcode descreteMoveXYE = {MOVE_COMMAND, 50, 100, 0, 100,     1000, 0, 2000,     0, 0};
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

    x1 = getCommandBufferElement_Gcode(1).dXn;      x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                  CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;      y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                  CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYE.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;      e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                  CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveXYE.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;      v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(speedTargetX) );
    v1 = getCommandBufferElement_Gcode(1).FnY;      v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(speedTargetY) );
    v1 = getCommandBufferElement_Gcode(1).FnE;      v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < floatError );             CHECK( fabs(v2) < fabs(speedTargetE) );
    a1 = getCommandBufferElement_Gcode(1).AnX;      a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError ); CHECK( fabs(-aDefault*cosX - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;      a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError ); CHECK( fabs(-aDefault*cosY - a2) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XYE_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYE1 = {MOVE_COMMAND,       100,    50, 0,    100,     1000, 0, 2000,     0, 0};
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

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Xn-descreteMoveXYE1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Yn-descreteMoveXYE1.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(2).dEn;          e2 = getCommandBufferElement_Gcode(3).dEn;          e3 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                      CHECK(e2 > 0);                                      CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.En-descreteMoveXYE1.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnE;          v2 = getCommandBufferElement_Gcode(3).FnE;          v3 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );      CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_start_XYE_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYE1 = {MOVE_COMMAND,        50,   100, 0,    100,     1000, 0, 2000,     0, 0};
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

    x1 = getCommandBufferElement_Gcode(2).dXn;          x2 = getCommandBufferElement_Gcode(3).dXn;          x3 = getCommandBufferElement_Gcode(4).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);                                      CHECK(x3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Xn-descreteMoveXYE1.Xn, x1+x2+x3);
    y1 = getCommandBufferElement_Gcode(2).dYn;          y2 = getCommandBufferElement_Gcode(3).dYn;          y3 = getCommandBufferElement_Gcode(4).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);                                      CHECK(y3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Yn-descreteMoveXYE1.Yn, y1+y2+y3);
    e1 = getCommandBufferElement_Gcode(2).dEn;          e2 = getCommandBufferElement_Gcode(3).dEn;          e3 = getCommandBufferElement_Gcode(4).dEn;
    CHECK(e1 > 0);                                      CHECK(e2 > 0);                                      CHECK(e3 > 0);
    CHECK_EQUAL(descreteMoveXYE2.En-descreteMoveXYE1.En, e1+e2+e3);
    v1 = getCommandBufferElement_Gcode(2).FnX;          v2 = getCommandBufferElement_Gcode(3).FnX;          v3 = getCommandBufferElement_Gcode(4).FnX;
    CHECK( fabs(v1) < fabs(speedTargetX) );             CHECK( fabs(speedTargetX - v2) < floatError );      CHECK( fabs(speedTargetX - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnY;          v2 = getCommandBufferElement_Gcode(3).FnY;          v3 = getCommandBufferElement_Gcode(4).FnY;
    CHECK( fabs(v1) < fabs(speedTargetY) );             CHECK( fabs(speedTargetY - v2) < floatError );      CHECK( fabs(speedTargetY - v3) < floatError );
    v1 = getCommandBufferElement_Gcode(2).FnE;          v2 = getCommandBufferElement_Gcode(3).FnE;          v3 = getCommandBufferElement_Gcode(4).FnE;
    CHECK( fabs(v1) < fabs(speedTargetE) );             CHECK( fabs(speedTargetE - v2) < floatError );      CHECK( fabs(speedTargetE - v3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnX;          a2 = getCommandBufferElement_Gcode(3).AnX;          a3 = getCommandBufferElement_Gcode(4).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosX - a3) < floatError );
    a1 = getCommandBufferElement_Gcode(2).AnY;          a2 = getCommandBufferElement_Gcode(3).AnY;          a3 = getCommandBufferElement_Gcode(4).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );                 CHECK( fabs(-aDefault*cosY - a3) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XYE_conserve_speed_1)
{
    const descreteCommand_Gcode descreteMoveXYE1 = {MOVE_COMMAND,     20000, 10000, 0, 20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE1.FnXY)-fabs(descreteMoveXYE1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    const descreteCommand_Gcode descreteMoveXYE2 = {MOVE_COMMAND,     20100, 10050, 0, 20100,     1000, 0, 2000,     0, 0};
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

    long  x1, x2;
    long  y1, y2;
    long  e1, e2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                      CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveXYE1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );         CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );         CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );         CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn,2)+pow((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn,2));
    cosX = ((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn)/distance;
    cosY = ((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn)/distance;
    tgEX = ((float)descreteMoveXYE2.En-(float)descreteMoveXYE1.En)/((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn);
    speedTargetX = (float)descreteMoveXYE2.FnXY*cosX;
    speedTargetY = (float)descreteMoveXYE2.FnXY*cosY;
    speedTargetE = (float)descreteMoveXYE2.FnXY*cosX*tgEX;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Xn-descreteMoveXYE1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Yn-descreteMoveXYE1.Yn, y1);
    e1 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);
    CHECK_EQUAL(descreteMoveXYE2.En-descreteMoveXYE1.En, e1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(speedTargetE - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}

TEST(Descrete_command_analyser_Gcode, two_commands_move_fast_stop_XYE_conserve_speed_2)
{
    const descreteCommand_Gcode descreteMoveXYE1 = {MOVE_COMMAND,     10000, 20000, 0, 20000,     1000, 0, 2000,     0, 0};
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    CHECK(fabs(fabs((STEPS_PER_MM_E/STEPS_PER_MM_XY)*descreteMoveXYE1.FnXY)-fabs(descreteMoveXYE1.FnE))<floatError);
    CHECK(maxSpeedXY > descreteMoveXYE1.FnXY);
    const descreteCommand_Gcode descreteMoveXYE2 = {MOVE_COMMAND,     10050, 20100, 0, 20100,     1000, 0, 2000,     0, 0};
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

    long  x1, x2;
    long  y1, y2;
    long  e1, e2;
    float v1, v2;
    float a1, a2;

    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE1);
    addElementToDescreteCommandBuffer_Gcode(descreteMoveXYE2);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 2, checkFreeSpaceCommandBuffer_Gcode());

    x1 = getCommandBufferElement_Gcode(1).dXn;          x2 = getCommandBufferElement_Gcode(2).dXn;
    CHECK(x1 > 0);                                      CHECK(x2 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Xn, x1+x2);
    y1 = getCommandBufferElement_Gcode(1).dYn;          y2 = getCommandBufferElement_Gcode(2).dYn;
    CHECK(y1 > 0);                                      CHECK(y2 > 0);
    CHECK_EQUAL(descreteMoveXYE1.Yn, y1+y2);
    e1 = getCommandBufferElement_Gcode(1).dEn;          e2 = getCommandBufferElement_Gcode(2).dEn;
    CHECK(e1 > 0);                                      CHECK(e2 > 0);
    CHECK_EQUAL(descreteMoveXYE1.En, e1+e2);
    v1 = getCommandBufferElement_Gcode(1).FnX;          v2 = getCommandBufferElement_Gcode(2).FnX;
    CHECK( fabs(0 - v1) < fabs(speedTargetX) );         CHECK( fabs(speedTargetX - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnY;          v2 = getCommandBufferElement_Gcode(2).FnY;
    CHECK( fabs(0 - v1) < fabs(speedTargetY) );         CHECK( fabs(speedTargetY - v2) < floatError );
    v1 = getCommandBufferElement_Gcode(1).FnE;          v2 = getCommandBufferElement_Gcode(2).FnE;
    CHECK( fabs(0 - v1) < fabs(speedTargetE) );         CHECK( fabs(speedTargetE - v2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnX;          a2 = getCommandBufferElement_Gcode(2).AnX;
    CHECK( fabs(aDefault*cosX - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );
    a1 = getCommandBufferElement_Gcode(1).AnY;          a2 = getCommandBufferElement_Gcode(2).AnY;
    CHECK( fabs(aDefault*cosY - a1) < floatError );     CHECK( fabs(0 - a2) < floatError );



    addElementToDescreteCommandBuffer_Gcode(defaultDescreteCommand);
    descreteCommandAnalyser_Gcode();

    CHECK_EQUAL(COMMAND_BUFFER_LENGTH - 3, checkFreeSpaceCommandBuffer_Gcode());

    distance = sqrt(pow((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn,2)+pow((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn,2));
    cosX = ((float)descreteMoveXYE2.Xn-(float)descreteMoveXYE1.Xn)/distance;
    cosY = ((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn)/distance;
    tgEY = ((float)descreteMoveXYE2.En-(float)descreteMoveXYE1.En)/((float)descreteMoveXYE2.Yn-(float)descreteMoveXYE1.Yn);
    speedTargetX = (float)descreteMoveXYE2.FnXY*cosX;
    speedTargetY = (float)descreteMoveXYE2.FnXY*cosY;
    speedTargetE = (float)descreteMoveXYE2.FnXY*cosY*tgEY;

    x1 = getCommandBufferElement_Gcode(3).dXn;
    CHECK(x1 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Xn-descreteMoveXYE1.Xn, x1);
    y1 = getCommandBufferElement_Gcode(3).dYn;
    CHECK(y1 > 0);
    CHECK_EQUAL(descreteMoveXYE2.Yn-descreteMoveXYE1.Yn, y1);
    e1 = getCommandBufferElement_Gcode(3).dEn;
    CHECK(e1 > 0);
    CHECK_EQUAL(descreteMoveXYE2.En-descreteMoveXYE1.En, e1);
    v1 = getCommandBufferElement_Gcode(3).FnX;
    CHECK( fabs(speedTargetX - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnY;
    CHECK( fabs(speedTargetY - v1) < floatError );
    v1 = getCommandBufferElement_Gcode(3).FnE;
    CHECK( fabs(speedTargetE - v1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnX;
    CHECK( fabs(-aDefault*cosX - a1) < floatError );
    a1 = getCommandBufferElement_Gcode(3).AnY;
    CHECK( fabs(-aDefault*cosY - a1) < floatError );
}


