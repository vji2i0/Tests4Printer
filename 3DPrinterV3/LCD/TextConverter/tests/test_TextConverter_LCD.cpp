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
#include "TextConverter_LCD.h"
#include "FakeInterface_LCD.h"
#include <memory.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>
}

TEST_GROUP(TextConverter_LCD)
{
    void setup()
    {
        create_TextConverter_LCD();
    }
    void teardown()
    {
    }
};

static void WSTRNCMP_EQUAL(const wchar_t* expectedText, const wchar_t* givenText, unsigned int NumberOfCompared)
{
    if (NumberOfCompared>wcslen(expectedText)) NumberOfCompared=wcslen(expectedText);
    unsigned int i;
    for(i=0; i<NumberOfCompared; i++)
        CHECK_EQUAL((int)expectedText[i],(int)givenText[i]);

}

static void WSTRCMP_EQUAL(const wchar_t* expectedText, const wchar_t* givenText)
{
    unsigned int NumberOfCompared=wcslen(expectedText);
    unsigned int i;
    for(i=0; i<NumberOfCompared; i++)
        CHECK_EQUAL((int)expectedText[i],(int)givenText[i]);

}

TEST(TextConverter_LCD, Initialisation)
{

    int line;
    for (line = 1; line <= NUMBEROFLINES_TEXTCONVERTER_LCD; line++)
        WSTRNCMP_EQUAL(L"                    ", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    for (line = 1; line <= NUMBEROFLINES_INTERFACE_LCD; line++)
        WSTRNCMP_EQUAL(L"                    ", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}


TEST(TextConverter_LCD, Put_text_with_length_3_and_update)
{
    int line = 3;
    putLine_TextConverter_LCD(L"123",line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"123                 ", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"123                 ", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Put_russian_text_with_length_3_and_update)
{
    int line = 3;
    putLine_TextConverter_LCD(L"абв",line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"абв                 ", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"абв                 ", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Put_text_with_length_3_in_multiple_lines_update_and_check_no_intersections)
{
    int line1 = 3;
    putLine_TextConverter_LCD(L"123",line1);
    updateLine_TextConverter_LCD(line1);
    int line2 = 2;
    putLine_TextConverter_LCD(L"123",line2);
    updateLine_TextConverter_LCD(line2);
    WSTRNCMP_EQUAL(L"123                 ", getLine_TextConverter_LCD(line1), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"123                 ", getLine_LCD(line1), LINELENGTH_INTERFACE_LCD);
    WSTRNCMP_EQUAL(L"123                 ", getLine_TextConverter_LCD(line2), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"123                 ", getLine_LCD(line2), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Put_text_with_length_25_and_update)
{
    int line = 2;
    putLine_TextConverter_LCD(L"1234567890123456789012345",line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"12345678901234567890", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"12345678901234567890", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Put_text_with_length_20_and_update)
{
    int line = 4;
    putLine_TextConverter_LCD(L"12345678901234567890",line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"12345678901234567890", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"12345678901234567890", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Clear_line_and_update)
{
    int line = 4;
    putLine_TextConverter_LCD(L"123456789012345      ",line);
    updateLine_TextConverter_LCD(line);
    clearLine_TextConverter_LCD(line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"                    ", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"                    ", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Rewrite_line_and_update)
{
    int line = 2;
    putLine_TextConverter_LCD(L"123456789012345             ",line);
    putLine_TextConverter_LCD(L"abcdf",line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"abcdf               ", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"abcdf               ", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Put_text_with_length_3_out_of_bounce_and_update)
{
    int line = NUMBEROFLINES_TEXTCONVERTER_LCD+1    ;
    putLine_TextConverter_LCD(L"123",line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Shift_line_and_update)
{
    int line = 2;
    putLine_TextConverter_LCD(L"012345678901234567890",line);
    shiftLine_TextConverter_LCD(line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"12345678901234567890", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"12345678901234567890", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Shift_at_the_last_symbol_line_and_update)
{
    int line = 2;
    putLine_TextConverter_LCD(L"012345678901234567890",line);
    shiftLine_TextConverter_LCD(line);
    shiftLine_TextConverter_LCD(line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"01234567890123456789", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"01234567890123456789", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Shift_line_two_times_and_update)
{
    int line = 1;
    putLine_TextConverter_LCD(L"01234567890123456789012",line);
    shiftLine_TextConverter_LCD(line);
    shiftLine_TextConverter_LCD(line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"23456789012345678901", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"23456789012345678901", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Shift_line_two_times_then_home_line_and_update)
{
    int line = 1;
    putLine_TextConverter_LCD(L"01234567890123456789012345",line);
    shiftLine_TextConverter_LCD(line);
    shiftLine_TextConverter_LCD(line);
    homeLine_TextConverter_LCD(line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"01234567890123456789", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"01234567890123456789", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}


TEST(TextConverter_LCD, Shift_short_line_and_update)
{
    int line = 1;
    putLine_TextConverter_LCD(L"01234567890",line);
    shiftLine_TextConverter_LCD(line);
    updateLine_TextConverter_LCD(line);
    WSTRNCMP_EQUAL(L"01234567890          ", getLine_TextConverter_LCD(line), LINELENGTH_TEXTCONVERTER_LCD);
    WSTRNCMP_EQUAL(L"01234567890          ", getLine_LCD(line), LINELENGTH_INTERFACE_LCD);
}

TEST(TextConverter_LCD, Add_int_number_to_string)
{
    wchar_t string[MAXTEXTLENGTH];

    wcscpy(string, L"the number is ");

    addIntNumberToString(string, 10);

    WSTRCMP_EQUAL(L"the number is 10\0", string);
}

TEST(TextConverter_LCD, Add_float_negative_number_to_string)
{
    wchar_t string[MAXTEXTLENGTH];

    swprintf(string, MAXTEXTLENGTH, L"the number is ");
    addFloatNumberToString(string, -10.74, 2);

    WSTRCMP_EQUAL(L"the number is -10.74", string);
}

TEST(TextConverter_LCD, Add_float_positive_number_to_string)
{
    wchar_t string[MAXTEXTLENGTH];

    swprintf(string, MAXTEXTLENGTH, L"the number is ");
    addFloatNumberToString(string, 10.74, 0);

    WSTRCMP_EQUAL(L"the number is 11.0", string);
}
