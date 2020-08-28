#ifndef MENU_CONSTRUCTOR
#define MENU_CONSTRUCTOR

#include "stdint.h"
#include <wchar.h>
#include "stdbool.h"

enum {MENU_TITLE_LENGTH = 20, MENU_NAME_LENGTH = 40};

typedef struct menuNode_this
{
    wchar_t title[MENU_TITLE_LENGTH];
    wchar_t name[MENU_NAME_LENGTH];
    struct menuNode_this * pUpNode;
    struct menuNode_this * pDownNode;
    struct menuNode_this * pLeftNode;
    struct menuNode_this * pRightNode;
    void (*pfnOk)(void);
    void (*pfnBack)(void);
    void (*pfnUp)(void);
    void (*pfnDown)(void);
} menuNode;


void createFirstNode_Menu(const wchar_t* titleNewNode, const wchar_t* nameNewNode);
void createRightNode_Menu(const wchar_t* titleNewNode, const wchar_t* nameNewNode);
void createDownNode_Menu(const wchar_t* nameNewNode);

void destroyFirstNode_Menu(void);
void destroyDownNode_Menu(void);
void destroyRightNode_Menu(void);
void destroyRightColomn_Menu(void);
void destroyAllNodes_Menu(void);

const menuNode* getCurrentNode_Menu(void);
const wchar_t* getTitle_Menu(void);
const wchar_t* getName_Menu(void);

_Bool ThereIsNodeBelow_Menu(void);
_Bool ThereIsNodeAbove_Menu(void);

void moveDown_Menu(void);
void moveUp_Menu(void);
void moveRight_Menu(void);
void moveLeft_Menu(void);
void moveToTheFirstNode_Menu(void);

void setFunctionOk(void (*function)(void));
void setFunctionBack(void (*function)(void));
void setFunctionUp(void (*function)(void));
void setFunctionDown(void (*function)(void));

#endif
