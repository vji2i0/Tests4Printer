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
#include <wchar.h>
}

TEST_GROUP(CharacterConverter_LCD)
{
    char expecterLetter;
    char givenLetter;

    void setup()
    {
    }
    void teardown()
    {
    }
};

TEST(CharacterConverter_LCD, Default)
{
    expecterLetter = 'a';
    givenLetter = convertCharacter_LCD(*L"a");
    CHECK_EQUAL(expecterLetter, givenLetter);
}

TEST(CharacterConverter_LCD, Question_mark)
{
    expecterLetter = '?';
    givenLetter = convertCharacter_LCD(*L"?");
    CHECK_EQUAL(expecterLetter, givenLetter);
}

TEST(CharacterConverter_LCD, Russian_letter)
{
    expecterLetter = (char) 66;
    givenLetter = convertCharacter_LCD(*L"В");
    CHECK_EQUAL(expecterLetter, givenLetter);
}

TEST(CharacterConverter_LCD, Special_symbols)
{
    expecterLetter = '>';
    givenLetter = convertCharacter_LCD(*L">");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '<';
    givenLetter = convertCharacter_LCD(*L"<");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = ')';
    givenLetter = convertCharacter_LCD(*L")");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '(';
    givenLetter = convertCharacter_LCD(*L"(");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '\"';
    givenLetter = convertCharacter_LCD(*L"\"");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '_';
    givenLetter = convertCharacter_LCD(*L"_");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '%';
    givenLetter = convertCharacter_LCD(*L"%");
    CHECK_EQUAL(expecterLetter, givenLetter);
}

TEST(CharacterConverter_LCD, Numbers)
{
    expecterLetter = '1';
    givenLetter = convertCharacter_LCD(*L"1");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '2';
    givenLetter = convertCharacter_LCD(*L"2");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '3';
    givenLetter = convertCharacter_LCD(*L"3");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '4';
    givenLetter = convertCharacter_LCD(*L"4");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '5';
    givenLetter = convertCharacter_LCD(*L"5");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '6';
    givenLetter = convertCharacter_LCD(*L"6");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '7';
    givenLetter = convertCharacter_LCD(*L"7");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '8';
    givenLetter = convertCharacter_LCD(*L"8");
    CHECK_EQUAL(expecterLetter, givenLetter);

    expecterLetter = '9';
    givenLetter = convertCharacter_LCD(*L"9");
    CHECK_EQUAL(expecterLetter, givenLetter);
}
