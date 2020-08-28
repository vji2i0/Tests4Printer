#ifndef DRIVER_LCD
#define DRIVER_LCD

#include "stdbool.h"



enum{LINELENGTH_LCD = 20, NUMBEROFLINES_LCD = 4};
enum{READY_LCD = 1, NOT_READY_LCD = 0};


//void create_LCD(void);
void clear_display_LCD(void);
void return_home_LCD(void);
void set_dataLenght_numberOfLines_fontType_LCD(void);
void set_do_not_display_cursor_LCD(void);
void set_cursor_moving_to_the_right_LCD(void);
void move_to_line_LCD(int line);
void write_character(const char c);
/*
void printLine_LCD(int line, const wchar_t* textToPrint);
*/

void RS_high_LCD(void);
void RS_low_LCD(void);
void RW_high_LCD(void);
void RW_low_LCD(void);
void E_high_LCD(void);
void E_low_LCD(void);
void DB0_high_LCD(void);
void DB0_low_LCD(void);
void DB1_high_LCD(void);
void DB1_low_LCD(void);
void DB2_high_LCD(void);
void DB2_low_LCD(void);
void DB3_high_LCD(void);
void DB3_low_LCD(void);
void DB4_high_LCD(void);
void DB4_low_LCD(void);
void DB5_high_LCD(void);
void DB5_low_LCD(void);
void DB6_high_LCD(void);
void DB6_low_LCD(void);
void DB7_high_LCD(void);
void DB7_low_LCD(void);
int Ready_LCD(void);


#endif
