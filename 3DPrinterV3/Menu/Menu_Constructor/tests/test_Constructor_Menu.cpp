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
#include <wchar.h>
#include "stdbool.h"
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



TEST_GROUP(Menu_Constructor)
{
    const wchar_t* firstTitle_Menu = L"Main menu";
    const wchar_t* firstName_Menu = L"Print";

    const wchar_t* secondTitle_Menu = L"Second menu";
    const wchar_t* secondName_Menu = L"Settings";

    const wchar_t* thirdTitle_Menu = L"Third menu";
    const wchar_t* thirdName_Menu = L"Settings 2";

    void setup()
    {
        createFirstNode_Menu(firstTitle_Menu, firstName_Menu);
    }
    void teardown()
    {
        destroyFirstNode_Menu();
        mock_c()->checkExpectations();
        mock_c()->clear();
    }
};

TEST(Menu_Constructor, create_the_first_node)
{
    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);

    CHECK(getCurrentNode_Menu()->pDownNode == NULL);
    CHECK(getCurrentNode_Menu()->pUpNode == NULL);
    CHECK(getCurrentNode_Menu()->pLeftNode == NULL);
    CHECK(getCurrentNode_Menu()->pRightNode == NULL);
    CHECK(getCurrentNode_Menu()->pfnOk == NULL);
    CHECK(getCurrentNode_Menu()->pfnBack == NULL);
    CHECK(getCurrentNode_Menu()->pfnUp == NULL);
    CHECK(getCurrentNode_Menu()->pfnDown == NULL);
}

TEST(Menu_Constructor, create_down_node)
{

    createDownNode_Menu(secondName_Menu);
    moveDown_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(secondName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), secondName_Menu);

    CHECK(getCurrentNode_Menu()->pDownNode == NULL);
    CHECK(getCurrentNode_Menu()->pLeftNode == NULL);
    CHECK(getCurrentNode_Menu()->pRightNode == NULL);
    CHECK(getCurrentNode_Menu()->pfnOk == NULL);
    CHECK(getCurrentNode_Menu()->pfnBack == NULL);
    CHECK(getCurrentNode_Menu()->pfnUp == NULL);
    CHECK(getCurrentNode_Menu()->pfnDown == NULL);

    moveUp_Menu();
    destroyDownNode_Menu();
}

TEST(Menu_Constructor, create_right_node)
{

    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();

    WSTRCMP_EQUAL(secondTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), secondTitle_Menu);

    WSTRCMP_EQUAL(secondName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), secondName_Menu);

    CHECK(getCurrentNode_Menu()->pDownNode == NULL);
    CHECK(getCurrentNode_Menu()->pUpNode == NULL);
    CHECK(getCurrentNode_Menu()->pRightNode == NULL);
    CHECK(getCurrentNode_Menu()->pfnOk == NULL);
    CHECK(getCurrentNode_Menu()->pfnBack == NULL);
    CHECK(getCurrentNode_Menu()->pfnUp == NULL);
    CHECK(getCurrentNode_Menu()->pfnDown == NULL);

    moveLeft_Menu();
    destroyRightNode_Menu();
}

TEST(Menu_Constructor, move_from_right_colomn_to_left_colomn)
{
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    moveLeft_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);

    moveRight_Menu();
    destroyDownNode_Menu();
    moveLeft_Menu();
    destroyRightNode_Menu();
}

TEST(Menu_Constructor, do_not_allow_to_move_to_the_empty_node)
{
    moveRight_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);

    moveLeft_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);

    moveDown_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);

    moveUp_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);
}

TEST(Menu_Constructor, destroy_the_right_colomn)
{
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(secondName_Menu);
    moveDown_Menu();
    moveLeft_Menu();
    destroyRightColomn_Menu();
}

TEST(Menu_Constructor, destroy_the_right_colomn_only_one_item)
{
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    destroyRightColomn_Menu();
}

void Ok_function(void) { mock_c()->actualCall("Ok_function"); }
void Back_function(void) { mock_c()->actualCall("Back_function"); }
void Up_function(void) { mock_c()->actualCall("Up_function"); }
void Down_function(void) { mock_c()->actualCall("Down_function"); }

TEST(Menu_Constructor, set_the_functions)
{
    mock_c()->expectOneCall("Ok_function");
    mock_c()->expectOneCall("Back_function");
    mock_c()->expectOneCall("Up_function");
    mock_c()->expectOneCall("Down_function");

    setFunctionOk(&Ok_function);
    setFunctionBack(&Back_function);
    setFunctionUp(&Up_function);
    setFunctionDown(&Down_function);

    getCurrentNode_Menu()->pfnOk();
    getCurrentNode_Menu()->pfnBack();
    getCurrentNode_Menu()->pfnUp();
    getCurrentNode_Menu()->pfnDown();
}

TEST(Menu_Constructor, destroy_everything_except_for_the_first_node)
{
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(thirdName_Menu);
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveLeft_Menu();

    destroyAllNodes_Menu();
}

TEST(Menu_Constructor, move_to_the_first_node)
{
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(thirdName_Menu);
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createDownNode_Menu(thirdName_Menu);
    moveDown_Menu();
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveRight_Menu();
    createDownNode_Menu(thirdName_Menu);
    createRightNode_Menu(secondTitle_Menu, secondName_Menu);
    moveLeft_Menu();

    moveUp_Menu();

    moveLeft_Menu();

    moveToTheFirstNode_Menu();

    WSTRCMP_EQUAL(firstTitle_Menu, getTitle_Menu());
    WSTRCMP_EQUAL(getTitle_Menu(), firstTitle_Menu);

    WSTRCMP_EQUAL(firstName_Menu, getName_Menu());
    WSTRCMP_EQUAL(getName_Menu(), firstName_Menu);

    destroyAllNodes_Menu();
}

TEST(Menu_Constructor, check_the_existence_of_node_below)
{
    CHECK(!ThereIsNodeBelow_Menu());
    createDownNode_Menu(secondName_Menu);
    CHECK(ThereIsNodeBelow_Menu());
    moveDown_Menu();
    CHECK(!ThereIsNodeBelow_Menu());

    destroyAllNodes_Menu();
}

TEST(Menu_Constructor, check_the_existence_of_node_above)
{
    CHECK(!ThereIsNodeAbove_Menu());
    createDownNode_Menu(secondName_Menu);
    CHECK(!ThereIsNodeAbove_Menu());
    moveDown_Menu();
    CHECK(ThereIsNodeAbove_Menu());

    destroyAllNodes_Menu();
}
