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
#include "Driver_LCD.h"
}

TEST_GROUP(Driver_LCD)
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

void RS_high_LCD() { mock_c()->actualCall("RS_high_LCD");}
void RS_low_LCD() { mock_c()->actualCall("RS_low_LCD");}
void RW_high_LCD() { mock_c()->actualCall("RW_high_LCD");}
void RW_low_LCD() { mock_c()->actualCall("RW_low_LCD");}
void E_high_LCD() { mock_c()->actualCall("E_high_LCD");}
void E_low_LCD() { mock_c()->actualCall("E_low_LCD");}
void DB0_high_LCD() { mock_c()->actualCall("DB0_high_LCD");}
void DB0_low_LCD() { mock_c()->actualCall("DB0_low_LCD");}
void DB1_high_LCD() { mock_c()->actualCall("DB1_high_LCD");}
void DB1_low_LCD() { mock_c()->actualCall("DB1_low_LCD");}
void DB2_high_LCD() { mock_c()->actualCall("DB2_high_LCD");}
void DB2_low_LCD() { mock_c()->actualCall("DB2_low_LCD");}
void DB3_high_LCD() { mock_c()->actualCall("DB3_high_LCD");}
void DB3_low_LCD() { mock_c()->actualCall("DB3_low_LCD");}
void DB4_high_LCD() { mock_c()->actualCall("DB4_high_LCD");}
void DB4_low_LCD() { mock_c()->actualCall("DB4_low_LCD");}
void DB5_high_LCD() { mock_c()->actualCall("DB5_high_LCD");}
void DB5_low_LCD() { mock_c()->actualCall("DB5_low_LCD");}
void DB6_high_LCD() { mock_c()->actualCall("DB6_high_LCD");}
void DB6_low_LCD() { mock_c()->actualCall("DB6_low_LCD");}
void DB7_high_LCD() { mock_c()->actualCall("DB7_high_LCD");}
void DB7_low_LCD() { mock_c()->actualCall("DB7_low_LCD");}
int Ready_LCD(void)
{
    mock_c()->actualCall("Ready_LCD");
    return mock_c()->returnValue().value.intValue;
}

static void expectData_LCD(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0)
{
    if (d0==1) mock_c()->expectOneCall("DB0_high_LCD");
        else mock_c()->expectOneCall("DB0_low_LCD");
    if (d1==1) mock_c()->expectOneCall("DB1_high_LCD");
        else mock_c()->expectOneCall("DB1_low_LCD");
    if (d2==1) mock_c()->expectOneCall("DB2_high_LCD");
        else mock_c()->expectOneCall("DB2_low_LCD");
    if (d3==1) mock_c()->expectOneCall("DB3_high_LCD");
        else mock_c()->expectOneCall("DB3_low_LCD");
    if (d4==1) mock_c()->expectOneCall("DB4_high_LCD");
        else mock_c()->expectOneCall("DB4_low_LCD");
    if (d5==1) mock_c()->expectOneCall("DB5_high_LCD");
        else mock_c()->expectOneCall("DB5_low_LCD");
    if (d6==1) mock_c()->expectOneCall("DB6_high_LCD");
        else mock_c()->expectOneCall("DB6_low_LCD");
    if (d7==1) mock_c()->expectOneCall("DB7_high_LCD");
        else mock_c()->expectOneCall("DB7_low_LCD");
}

TEST(Driver_LCD, Clear_display_LCD)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,0,0,0,0,0,0,1);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    clear_display_LCD();
}

TEST(Driver_LCD, Clear_display_LCD_not_ready_immediately)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) NOT_READY_LCD);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) NOT_READY_LCD);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,0,0,0,0,0,0,1);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    clear_display_LCD();
}


TEST(Driver_LCD, Return_home_LCD)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,0,0,0,0,0,1,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    return_home_LCD();
}


TEST(Driver_LCD, Set_dataLenght_to_8bit_numberOfLines_to_2_fontType_LCD_to_5x8)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,0,1,1,1,0,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    set_dataLenght_numberOfLines_fontType_LCD();
}

TEST(Driver_LCD, Set_do_not_display_cursor_and_blinking_cursor)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,0,0,0,1,1,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    set_do_not_display_cursor_LCD();
}

TEST(Driver_LCD, Set_cursor_moving_to_the_right)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,0,0,1,0,1,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    set_cursor_moving_to_the_right_LCD();
}

TEST(Driver_LCD, Move_to_line_1_LCD_given_4_lines_total)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(1,0,0,0,0,0,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    move_to_line_LCD(1);
}

TEST(Driver_LCD, Move_to_line_2_LCD_given_4_lines_total)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(1,1,0,0,0,0,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    move_to_line_LCD(2);
}

TEST(Driver_LCD, Move_to_line_3_LCD_given_4_lines_total)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(1,0,0,1,0,1,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    move_to_line_LCD(3);
}

TEST(Driver_LCD, Move_to_line_4_LCD_given_4_lines_total)
{
    mock_c()->expectOneCall("RS_low_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(1,1,0,1,0,1,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    move_to_line_LCD(4);
}

TEST(Driver_LCD, Move_to_unexisting_line_5_and_unexisting_line_0_LCD_given_4_lines_total)
{
    move_to_line_LCD(5);
    move_to_line_LCD(0);
}

TEST(Driver_LCD, Write_character_a_LCD)
{
    mock_c()->expectOneCall("RS_high_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,1,1,0,0,0,0,1);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    write_character('a');
}

TEST(Driver_LCD, Write_character_z_LCD)
{
    mock_c()->expectOneCall("RS_high_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(0,1,1,1,1,0,1,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    write_character('z');
}

TEST(Driver_LCD, Write_character_russian_Z_LCD)
{
    mock_c()->expectOneCall("RS_high_LCD");
    mock_c()->expectOneCall("RW_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);
    mock_c()->expectOneCall("E_high_LCD");
    expectData_LCD(1,0,1,0,0,1,0,0);
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    mock_c()->expectOneCall("E_low_LCD");
    mock_c()->expectOneCall("Ready_LCD")
        ->andReturnIntValue((int) READY_LCD);

    write_character((char) 0xA4);
}

