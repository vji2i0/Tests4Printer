#ifndef FAKE_INTERFACE_LCD
#define FAKE_INTERFACE_LCD

//enum{LINELENGTH_LCD = 20, NUMBEROFLINES_LCD = 4};

enum{LINELENGTH_INTERFACE_LCD = 20, NUMBEROFLINES_INTERFACE_LCD = 4};

void create_LCD(void);
void printLine_LCD(int line, const wchar_t* textToPrint);
const wchar_t* getLine_LCD(int line);

#endif
