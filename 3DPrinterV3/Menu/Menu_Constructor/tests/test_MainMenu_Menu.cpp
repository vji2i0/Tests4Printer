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
#include "Constructor_Menu.h"
#include "MainMenu_Menu.h"
#include <wchar.h>
#include "CppUTestExt/MockSupport_c.h"
}

/*
static void WSTRNCMP_EQUAL(const wchar_t* expectedText, const wchar_t* givenText, unsigned int NumberOfCompared)
{
    if (NumberOfCompared>wcslen(expectedText)) NumberOfCompared=wcslen(expectedText);
    unsigned int i;
    for(i=0; i<NumberOfCompared; i++)
        CHECK_EQUAL((int)expectedText[i],(int)givenText[i]);

}
*/



static void WSTRCMP_EQUAL(const wchar_t* expectedText, const wchar_t* givenText)
{
    unsigned int NumberOfCompared=wcslen(expectedText);
    unsigned int i;
    for(i=0; i<NumberOfCompared; i++)
        CHECK_EQUAL((int)expectedText[i],(int)givenText[i]);

}




TEST_GROUP(Menu_MainMenu)
{

    void setup()
    {
        setMainMenu_Menu();
    }
    void teardown()
    {
        destroyAllNodes_Menu();
        destroyFirstNode_Menu();
        //mock_c()->checkExpectations();
        //mock_c()->clear();
    }
};

TEST(Menu_MainMenu, check_the_titles_and_names)
{
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Print", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Print");

    moveDown_Menu();
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Change filament", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Change filament");

        moveRight_Menu();
        WSTRCMP_EQUAL(L"CHANGE FILAMENT", getTitle_Menu());
        WSTRCMP_EQUAL(getTitle_Menu(), L"CHANGE FILAMENT");
        WSTRCMP_EQUAL(L" Set the temperature", getName_Menu());
        WSTRCMP_EQUAL(getName_Menu(), L" Set the temperature");

    moveLeft_Menu();
    moveDown_Menu();
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Language", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Language");

        moveRight_Menu();
        WSTRCMP_EQUAL(L"LANGUAGE", getTitle_Menu());
        WSTRCMP_EQUAL(getTitle_Menu(), L"LANGUAGE");
        WSTRCMP_EQUAL(L" English", getName_Menu());
        WSTRCMP_EQUAL(getName_Menu(), L" English");

        moveDown_Menu();
        WSTRCMP_EQUAL(L"LANGUAGE", getTitle_Menu());
        WSTRCMP_EQUAL(getTitle_Menu(), L"LANGUAGE");
        WSTRCMP_EQUAL(L" Russian", getName_Menu());
        WSTRCMP_EQUAL(getName_Menu(), L" Russian");

    moveLeft_Menu();
    moveDown_Menu();
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Help", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Help");
}

TEST(Menu_MainMenu, check_the_titles_and_names_using_buttons)
{
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Print", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Print");


    getCurrentNode_Menu()->pfnDown();
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Change filament", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Change filament");

        getCurrentNode_Menu()->pfnOk();
        WSTRCMP_EQUAL(L"CHANGE FILAMENT", getTitle_Menu());
        WSTRCMP_EQUAL(getTitle_Menu(), L"CHANGE FILAMENT");
        WSTRCMP_EQUAL(L" Set the temperature", getName_Menu());
        WSTRCMP_EQUAL(getName_Menu(), L" Set the temperature");

    getCurrentNode_Menu()->pfnBack();
    getCurrentNode_Menu()->pfnDown();
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Language", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Language");

        getCurrentNode_Menu()->pfnOk();
        WSTRCMP_EQUAL(L"LANGUAGE", getTitle_Menu());
        WSTRCMP_EQUAL(getTitle_Menu(), L"LANGUAGE");
        WSTRCMP_EQUAL(L" English", getName_Menu());
        WSTRCMP_EQUAL(getName_Menu(), L" English");

        getCurrentNode_Menu()->pfnDown();
        WSTRCMP_EQUAL(L"LANGUAGE", getTitle_Menu());
        WSTRCMP_EQUAL(getTitle_Menu(), L"LANGUAGE");
        WSTRCMP_EQUAL(L" Russian", getName_Menu());
        WSTRCMP_EQUAL(getName_Menu(), L" Russian");

    getCurrentNode_Menu()->pfnBack();
    getCurrentNode_Menu()->pfnDown();
    WSTRCMP_EQUAL(L"MAIN MENU", getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), L"MAIN MENU");
    WSTRCMP_EQUAL(L" Help", getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), L" Help");
}
