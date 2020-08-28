#include "FakeInterface_LCD.h"
#include "string.h"
#include "stdbool.h"
#include <wchar.h>

static wchar_t virtual_LCD[NUMBEROFLINES_INTERFACE_LCD][LINELENGTH_INTERFACE_LCD];

const static wchar_t EMPTY_STRING[] = L"                    ";



static int lineNumber(int line) {return line-1;}
static _Bool wrongLine(int line)
{
    if (line < 1)
        return true;
    if (line > NUMBEROFLINES_INTERFACE_LCD)
        return true;
    return false;
}

void create_LCD(void)
{
    int line;
    for (line=1; line<=NUMBEROFLINES_INTERFACE_LCD; line++)
        wmemcpy(virtual_LCD[lineNumber(line)], EMPTY_STRING, LINELENGTH_INTERFACE_LCD);
}

void printLine_LCD(int line, const wchar_t* textToPrint)
{
    if(wrongLine(line))
        return;
    wmemcpy(virtual_LCD[lineNumber(line)], textToPrint, LINELENGTH_INTERFACE_LCD);
}

const wchar_t* getLine_LCD(int line)
{
    if(wrongLine(line))
        return L"";
    return virtual_LCD[lineNumber(line)];
}
