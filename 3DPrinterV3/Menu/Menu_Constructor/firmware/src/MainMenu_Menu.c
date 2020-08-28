#include "MainMenu_Menu.h"

#include "Constructor_Menu.h"
#include "stdint.h"
#include <wchar.h>
#include "stdbool.h"

#include "Fake_FunctionsForButtons.h"


void setMainMenu_Menu(void)
{
    createFirstNode_Menu(L"MAIN MENU", L" Print");
    setFunctionUp(NULL);
    setFunctionDown(&simpleNavigationDown_Menu);
    setFunctionOk(&printOk_Menu);
    setFunctionBack(NULL);


    createDownNode_Menu(L" Change filament");
    moveDown_Menu();
    setFunctionUp(&simpleNavigationUp_Menu);
    setFunctionDown(&simpleNavigationDown_Menu);
    setFunctionOk(&changeFilamentOk_Menu);
    setFunctionBack(NULL);

        createRightNode_Menu(L"CHANGE FILAMENT", L" Set the temperature");
        moveRight_Menu();
        setFunctionUp(&setTheTemperatureUp_Menu);
        setFunctionDown(&setTheTemperatureDown_Menu);
        setFunctionOk(&setTheTemperatureOk_Menu);
        setFunctionBack(&setTheTemperatureBack_Menu);

        moveLeft_Menu();

    createDownNode_Menu(L" Language");
    moveDown_Menu();
    setFunctionUp(&simpleNavigationUp_Menu);
    setFunctionDown(&simpleNavigationDown_Menu);
    setFunctionOk(&simpleNavigationOk_Menu);
    setFunctionBack(NULL);

        createRightNode_Menu(L"LANGUAGE", L" English");
        moveRight_Menu();
        setFunctionUp(NULL);
        setFunctionDown(&simpleNavigationDown_Menu);
        setFunctionOk(&englishOk_Menu);
        setFunctionBack(&englishBack_Menu);

        createDownNode_Menu(L" Russian");
        moveDown_Menu();
        setFunctionUp(&simpleNavigationUp_Menu);
        setFunctionDown(NULL);
        setFunctionOk(&russianOk_Menu);
        setFunctionBack(&russianBack_Menu);

        moveLeft_Menu();

    createDownNode_Menu(L" Help");
    moveDown_Menu();
    setFunctionUp(&simpleNavigationUp_Menu);
    setFunctionDown(NULL);
    setFunctionOk(&helpOk_Menu);
    setFunctionBack(&helpBack_Menu);

    moveToTheFirstNode_Menu();
}
