#include "Fake_FunctionsForButtons.h"

#include "Constructor_Menu.h"
#include "stdint.h"
#include <wchar.h>
#include "stdbool.h"

void simpleNavigationDown_Menu(void) { moveDown_Menu(); }
void simpleNavigationUp_Menu(void) { moveUp_Menu(); }
void simpleNavigationOk_Menu(void) { moveRight_Menu(); }
void simpleNavigationBack_Menu(void) { moveLeft_Menu(); }

void printOk_Menu(void) {}

void changeFilamentOk_Menu(void) { moveRight_Menu(); }

void setTheTemperatureOk_Menu(void) {}
void setTheTemperatureBack_Menu(void) { moveLeft_Menu(); }
void setTheTemperatureUp_Menu(void) {}
void setTheTemperatureDown_Menu(void) {}

void englishOk_Menu(void) {}
void englishBack_Menu(void) { moveLeft_Menu(); }
void russianOk_Menu(void) {}
void russianBack_Menu(void) { moveLeft_Menu(); }

void helpOk_Menu(void) {}
void helpBack_Menu(void) {}
