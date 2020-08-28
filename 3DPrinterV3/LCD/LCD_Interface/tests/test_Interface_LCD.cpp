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
#include "CharacterConverter_LCD.h"
#include "Interface_LCD.h"
#include "Mock_Driver_LCD.h"
#include <wchar.h>
#include "CppUTestExt/MockSupport_c.h"
}

TEST_GROUP(Interface_LCD)
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

TEST(Interface_LCD, create_LCD_test)
{

    mock_c()->expectOneCall("return_home_LCD");
    mock_c()->expectOneCall("clear_display_LCD");
    mock_c()->expectOneCall("set_dataLenght_numberOfLines_fontType_LCD");
    mock_c()->expectOneCall("set_do_not_display_cursor_LCD");
    mock_c()->expectOneCall("set_cursor_moving_to_the_right_LCD");

    create_LCD();
}

TEST(Interface_LCD, write_to_the_third_line)
{
    int line = 3;
    wchar_t string[] = L"abcdefghigklmnopqrst";

    mock_c()->expectOneCall("move_to_line_LCD")
        ->withIntParameters("line", line);
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[0]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[1]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[2]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[3]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[4]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[5]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[6]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[7]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[8]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[9]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[10]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[11]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[12]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[13]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[14]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[15]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[16]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[17]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[18]));
    mock_c()->expectOneCall("write_character")
        ->withIntParameters("character", (int) convertCharacter_LCD(string[19]));

    printLine_LCD(line, string);
}

TEST(Interface_LCD, write_to_the_wrong_line)
{
    int line = NUMBEROFLINES_INTERFACE_LCD + 1;
    wchar_t string[] = L"abcdefghigklmnopqrst";

    printLine_LCD(line, string);
}


