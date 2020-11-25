#include "Constructor_Menu.h"

#include "stdint.h"
#include <wchar.h>
#include "stdbool.h"
#include <stdlib.h>

static menuNode* pMenuNode = NULL;

void createFirstNode_Menu(const wchar_t* titleNewNode, const wchar_t* nameNewNode)
{
    pMenuNode = malloc(sizeof(menuNode));
    wmemcpy(pMenuNode->title, titleNewNode, MENU_TITLE_LENGTH);
    wmemcpy(pMenuNode->name, nameNewNode, MENU_NAME_LENGTH);
    pMenuNode->pUpNode = NULL;
    pMenuNode->pDownNode = NULL;
    pMenuNode->pRightNode = NULL;
    pMenuNode->pLeftNode = NULL;
    pMenuNode->pfnOk = NULL;
    pMenuNode->pfnBack = NULL;
    pMenuNode->pfnUp = NULL;
    pMenuNode->pfnDown = NULL;
}

void createRightNode_Menu(const wchar_t* titleNewNode, const wchar_t* nameNewNode)
{
    pMenuNode->pRightNode = malloc(sizeof(menuNode));
    pMenuNode->pRightNode->pLeftNode = pMenuNode;
    wmemcpy(pMenuNode->pRightNode->title, titleNewNode, MENU_TITLE_LENGTH);
    wmemcpy(pMenuNode->pRightNode->name, nameNewNode, MENU_NAME_LENGTH);
    pMenuNode->pRightNode->pDownNode = NULL;
    pMenuNode->pRightNode->pUpNode = NULL;
    pMenuNode->pRightNode->pRightNode = NULL;
    pMenuNode->pRightNode->pfnOk = NULL;
    pMenuNode->pRightNode->pfnBack = NULL;
    pMenuNode->pRightNode->pfnUp = NULL;
    pMenuNode->pRightNode->pfnDown = NULL;
}

void createDownNode_Menu(const wchar_t* nameNewNode)
{
    pMenuNode->pDownNode = malloc(sizeof(menuNode));
    pMenuNode->pDownNode->pUpNode = pMenuNode;
    wmemcpy(pMenuNode->pDownNode->title, pMenuNode->title, MENU_TITLE_LENGTH);
    wmemcpy(pMenuNode->pDownNode->name, nameNewNode, MENU_NAME_LENGTH);
    pMenuNode->pDownNode->pDownNode = NULL;
    pMenuNode->pDownNode->pRightNode = NULL;
    pMenuNode->pDownNode->pLeftNode = pMenuNode->pLeftNode;
    pMenuNode->pDownNode->pfnOk = NULL;
    pMenuNode->pDownNode->pfnBack = NULL;
    pMenuNode->pDownNode->pfnUp = NULL;
    pMenuNode->pDownNode->pfnDown = NULL;
}




static _Bool onlyFirstNodeRemains(void)
{
    if (pMenuNode->pUpNode != NULL)
        return false;
    if (pMenuNode->pDownNode != NULL)
        return false;
    if (pMenuNode->pRightNode != NULL)
        return false;
    if (pMenuNode->pLeftNode != NULL)
        return false;
    return true;
}

void destroyFirstNode_Menu()
{
    free(pMenuNode);
    pMenuNode = NULL;
}

void destroyDownNode_Menu()
{
    free(pMenuNode->pDownNode);
    pMenuNode->pDownNode = NULL;
}

void destroyRightNode_Menu(void)
{
    free(pMenuNode->pRightNode);
    pMenuNode->pRightNode = NULL;
}

void destroyRightColomn_Menu()
{
    menuNode* pMenuNodeBuf = pMenuNode;
    if (pMenuNodeBuf->pRightNode == NULL)
        return;
    pMenuNodeBuf = pMenuNodeBuf->pRightNode;
    while(pMenuNodeBuf->pDownNode != NULL)
    {
        pMenuNodeBuf = pMenuNodeBuf->pDownNode;
    }
    while (pMenuNodeBuf->pUpNode != NULL)
    {
        pMenuNodeBuf = pMenuNodeBuf->pUpNode;
        free(pMenuNodeBuf->pDownNode);
    }
    free(pMenuNode->pRightNode);
    pMenuNode->pRightNode = NULL;
}

void destroyAllNodes_Menu()
{
    while(!onlyFirstNodeRemains())
    {
        if(pMenuNode->pDownNode != NULL) { moveDown_Menu(); continue; }
        if(pMenuNode->pRightNode != NULL) { moveRight_Menu(); continue; }
        if(pMenuNode->pUpNode != NULL) { moveUp_Menu(); destroyDownNode_Menu(); continue; }
        if(pMenuNode->pLeftNode != NULL) { moveLeft_Menu(); destroyRightNode_Menu(); continue; }
        break;
    }
}



const menuNode* getCurrentNode_Menu() { return pMenuNode; }

const wchar_t* getTitle_Menu() { return pMenuNode->title; }

const wchar_t* getName_Menu() { return pMenuNode->name; }




_Bool ThereIsNodeBelow_Menu() { return pMenuNode->pDownNode != NULL; }


_Bool ThereIsNodeAbove_Menu() {return pMenuNode->pUpNode != NULL;}



void moveDown_Menu()
{
    if (pMenuNode->pDownNode == NULL)
        return;
    pMenuNode = pMenuNode->pDownNode;
}

void moveUp_Menu()
{
    if (pMenuNode->pUpNode == NULL)
        return;
    pMenuNode = pMenuNode->pUpNode;
}

void moveRight_Menu(void)
{
    if (pMenuNode->pRightNode == NULL)
        return;
    pMenuNode = pMenuNode->pRightNode;
}

void moveLeft_Menu(void)
{
    if (pMenuNode->pLeftNode == NULL)
        return;
    pMenuNode = pMenuNode->pLeftNode;
}

void moveToTheFirstNode_Menu()
{

    while(pMenuNode->pLeftNode != NULL)
    {
        moveLeft_Menu();
    }

    while(pMenuNode->pUpNode != NULL)
    {
        moveUp_Menu();
    }
}



void setFunctionOk(void (*function)(void))
{
    pMenuNode->pfnOk = function;
}

void setFunctionBack(void (*function)(void))
{
    pMenuNode->pfnBack = function;
}

void setFunctionUp(void (*function)(void))
{
    pMenuNode->pfnUp = function;
}

void setFunctionDown(void (*function)(void))
{
    pMenuNode->pfnDown = function;
}


