#ifndef INTERFACE_LCD
#define INTERFACE_LCD

#include "stdint.h"
#include <wchar.h>

enum{LINELENGTH_INTERFACE_LCD = 20, NUMBEROFLINES_INTERFACE_LCD = 4};

void create_LCD(void);
void printLine_LCD(int line, const wchar_t* textToPrint);


#endif
