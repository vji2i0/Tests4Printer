#include "MainMenu_Menu.h"

#include "Constructor_Menu.h"
#include "Fake_FunctionsForButtons.h"

#include "stdint.h"
#include "stdio.h"
#include <wchar.h>
#include "stdbool.h"




void setMainMenu_Menu(void)
{
    createFirstNode_Menu(L"MAIN MENU", L" Print");
    setFunctionUp(&simpleNavigationUp_Menu);
    setFunctionDown(&simpleNavigationDown_Menu);
    setFunctionOk(&printOk_Menu);
    setFunctionBack(&emptyFunction_Menu);


    createDownNode_Menu(L" Change filament");
    moveDown_Menu();
    setFunctionUp(&simpleNavigationUp_Menu);
    setFunctionDown(&simpleNavigationDown_Menu);
    setFunctionOk(&changeFilamentOk_Menu);
    setFunctionBack(&emptyFunction_Menu);

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
    setFunctionBack(&emptyFunction_Menu);

        createRightNode_Menu(L"LANGUAGE", L" English");
        moveRight_Menu();
        setFunctionUp(&emptyFunction_Menu);
        setFunctionDown(&simpleNavigationDown_Menu);
        setFunctionOk(&englishOk_Menu);
        setFunctionBack(&simpleNavigationBack_Menu);

        createDownNode_Menu(L" Russian");
        moveDown_Menu();
        setFunctionUp(&simpleNavigationUp_Menu);
        setFunctionDown(&emptyFunction_Menu);
        setFunctionOk(&russianOk_Menu);
        setFunctionBack(&simpleNavigationBack_Menu);

        moveLeft_Menu();

    createDownNode_Menu(L" Help");
    moveDown_Menu();
    setFunctionUp(&simpleNavigationUp_Menu);
    setFunctionDown(&simpleNavigationDown_Menu);
    setFunctionOk(&helpOk_Menu);
    setFunctionBack(&helpBack_Menu);

    moveToTheFirstNode_Menu();
}
