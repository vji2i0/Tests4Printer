#ifndef MOCK_DRIVER_LCD
#define MOCK_DRIVER_LCD

#include "stdbool.h"



enum{LINELENGTH_LCD = 20, NUMBEROFLINES_LCD = 4};
enum{READY_LCD = 1, NOT_READY_LCD = 0};


void clear_display_LCD(void);
void return_home_LCD(void);
void set_dataLenght_numberOfLines_fontType_LCD(void);
void set_do_not_display_cursor_LCD(void);
void set_cursor_moving_to_the_right_LCD(void);
void move_to_line_LCD(int line);
void write_character(const char c);

#endif
