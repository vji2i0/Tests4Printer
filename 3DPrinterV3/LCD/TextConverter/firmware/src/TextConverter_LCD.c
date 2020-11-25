#include "TextConverter_LCD.h"

#include "FakeInterface_LCD.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <wchar.h>
#include <stdlib.h>

const wchar_t EMPTY_STRING[] = L"                    ";

static wchar_t toPrint_LCD[NUMBEROFLINES_TEXTCONVERTER_LCD][LINELENGTH_TEXTCONVERTER_LCD];
static wchar_t text_LCD[NUMBEROFLINES_TEXTCONVERTER_LCD][MAXTEXTLENGTH+1];


static int lineNumber(int line) {return line-1;}

static _Bool wrongLine(int line)
{
    if (line < 1)
        return true;
    if (line > NUMBEROFLINES_TEXTCONVERTER_LCD)
        return true;
    return false;
}

void create_TextConverter_LCD(void)
{
    int line;
    for (line=1; line<=NUMBEROFLINES_TEXTCONVERTER_LCD; line++)
        wmemcpy(toPrint_LCD[lineNumber(line)], EMPTY_STRING, LINELENGTH_TEXTCONVERTER_LCD);
    create_LCD();
}

const wchar_t* getLine_TextConverter_LCD(int line)
{
    if (wrongLine(line))
        return L"";
    return toPrint_LCD[lineNumber(line)];
}

void putLine_TextConverter_LCD(const wchar_t* text, int line)
{
    if (wrongLine(line))
        return;
    wcscpy(text_LCD[lineNumber(line)], text);
    int textLength = wcslen(text);

    if (textLength < LINELENGTH_TEXTCONVERTER_LCD)
        swprintf(&text_LCD[lineNumber(line)][textLength], LINELENGTH_TEXTCONVERTER_LCD-textLength+1, EMPTY_STRING);
    wmemcpy(toPrint_LCD[lineNumber(line)], text_LCD[lineNumber(line)], LINELENGTH_TEXTCONVERTER_LCD);
}

void updateLine_TextConverter_LCD(int line)
{
    if (wrongLine(line))
        return;
    printLine_LCD(line, toPrint_LCD[lineNumber(line)]);
}


void clearLine_TextConverter_LCD(int line)
{
    if (wrongLine(line))
        return;
    putLine_TextConverter_LCD(L"", line);
}

static _Bool lineEnds(const wchar_t* string)
{
    return string[LINELENGTH_TEXTCONVERTER_LCD] == '\0';
}

void shiftLine_TextConverter_LCD(int line)
{
    if(wrongLine(line))
        return;
    if (lineEnds(text_LCD[lineNumber(line)]))
        return;

    wchar_t strToFind[LINELENGTH_TEXTCONVERTER_LCD+1];
    wmemcpy(strToFind, toPrint_LCD[lineNumber(line)], LINELENGTH_TEXTCONVERTER_LCD);
    strToFind[LINELENGTH_TEXTCONVERTER_LCD] = '\0';

    wchar_t* pToFirstLetter = wcsstr(text_LCD[lineNumber(line)], strToFind);
    if (lineEnds(pToFirstLetter))
        wmemcpy(toPrint_LCD[lineNumber(line)], text_LCD[lineNumber(line)], LINELENGTH_TEXTCONVERTER_LCD);
    if (!lineEnds(pToFirstLetter))
        wmemcpy(toPrint_LCD[lineNumber(line)], &pToFirstLetter[1], LINELENGTH_TEXTCONVERTER_LCD);
}

void homeLine_TextConverter_LCD(int line)
{
    wmemcpy(toPrint_LCD[lineNumber(line)], text_LCD[lineNumber(line)], LINELENGTH_TEXTCONVERTER_LCD);
}

void addIntNumberToString(wchar_t* string, int number)
{
    swprintf(&string[wcslen(string)], MAXTEXTLENGTH-wcslen(string), L"%d", number);
}

static int digitsBeforeDot(float number, int digits)
{
    if (digits < 0)
        return 0;
    if (digits == 0)
        return abs((int)round(number));
    return abs((int)(number));
}

static int digitsAfterDot(float number, int digits)
{
    if (digits<=0)
        return 0;
    return abs((int)round(pow(10.0, digits)*(number-(int)number)));
}

void addFloatNumberToString(wchar_t* string, float number, int digits)
{
    if (number < 0)
        swprintf(&string[wcslen(string)], MAXTEXTLENGTH-wcslen(string), L"-%d.%d", digitsBeforeDot(number, digits), digitsAfterDot(number, digits));
    if (number >= 0)
        swprintf(&string[wcslen(string)], MAXTEXTLENGTH-wcslen(string), L"%d.%d", digitsBeforeDot(number, digits), digitsAfterDot(number, digits));
}

