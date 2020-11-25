#ifndef TEXT_CONVERTER
#define TEXT_CONVERTER

#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>

enum{LINELENGTH_TEXTCONVERTER_LCD = 20, NUMBEROFLINES_TEXTCONVERTER_LCD = 4, MAXTEXTLENGTH = 100};

extern const wchar_t EMPTY_STRING[];

void create_TextConverter_LCD(void);
const wchar_t* getLine_TextConverter_LCD(int line);
void putLine_TextConverter_LCD(const wchar_t* text, int line);
void updateLine_TextConverter_LCD(int line);
void clearLine_TextConverter_LCD(int line);
void shiftLine_TextConverter_LCD(int line);
void homeLine_TextConverter_LCD(int line);
void addIntNumberToString(wchar_t* string, int number);
void addFloatNumberToString(wchar_t* string, float number, int digits);

#endif
