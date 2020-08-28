#include "Driver_LCD.h"
#include "stdbool.h"

/*
void create_LCD(void)
{

}
*/

void clear_display_LCD(void)
{
    int status_LCD;
    RS_low_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    DB0_high_LCD();
    DB1_low_LCD();
    DB2_low_LCD();
    DB3_low_LCD();
    DB4_low_LCD();
    DB5_low_LCD();
    DB6_low_LCD();
    DB7_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}

void return_home_LCD(void)
{
    int status_LCD;
    RS_low_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    DB0_low_LCD();
    DB1_high_LCD();
    DB2_low_LCD();
    DB3_low_LCD();
    DB4_low_LCD();
    DB5_low_LCD();
    DB6_low_LCD();
    DB7_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}

void set_dataLenght_numberOfLines_fontType_LCD(void)
{
    int status_LCD;
    RS_low_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_low_LCD();
    DB3_high_LCD();
    DB4_high_LCD();
    DB5_high_LCD();
    DB6_low_LCD();
    DB7_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}

void set_do_not_display_cursor_LCD(void)
{
    int status_LCD;
    RS_low_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_high_LCD();
    DB3_high_LCD();
    DB4_low_LCD();
    DB5_low_LCD();
    DB6_low_LCD();
    DB7_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}

void set_cursor_moving_to_the_right_LCD(void)
{
    int status_LCD;
    RS_low_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_high_LCD();
    DB3_low_LCD();
    DB4_high_LCD();
    DB5_low_LCD();
    DB6_low_LCD();
    DB7_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}

static void first_line_DDRAM_address(void)
{
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_low_LCD();
    DB3_low_LCD();
    DB4_low_LCD();
    DB5_low_LCD();
    DB6_low_LCD();
    DB7_high_LCD();
}

static void second_line_DDRAM_address(void)
{
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_low_LCD();
    DB3_low_LCD();
    DB4_low_LCD();
    DB5_low_LCD();
    DB6_high_LCD();
    DB7_high_LCD();
}

static void third_line_DDRAM_address(void)
{
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_high_LCD();
    DB3_low_LCD();
    DB4_high_LCD();
    DB5_low_LCD();
    DB6_low_LCD();
    DB7_high_LCD();
}

static void fourth_line_DDRAM_address(void)
{
    DB0_low_LCD();
    DB1_low_LCD();
    DB2_high_LCD();
    DB3_low_LCD();
    DB4_high_LCD();
    DB5_low_LCD();
    DB6_high_LCD();
    DB7_high_LCD();
}

void move_to_line_LCD(int line)
{
    if (line < 1)
        return;
    if (line > NUMBEROFLINES_LCD)
        return;

    int status_LCD;
    RS_low_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    if (line == 1) first_line_DDRAM_address();
    if (line == 2) second_line_DDRAM_address();
    if (line == 3) third_line_DDRAM_address();
    if (line == 4) fourth_line_DDRAM_address();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}


static void char_2_data_LCD(const char c)
{
    if (c>>0 & 1) DB0_high_LCD(); else DB0_low_LCD();
    if (c>>1 & 1) DB1_high_LCD(); else DB1_low_LCD();
    if (c>>2 & 1) DB2_high_LCD(); else DB2_low_LCD();
    if (c>>3 & 1) DB3_high_LCD(); else DB3_low_LCD();
    if (c>>4 & 1) DB4_high_LCD(); else DB4_low_LCD();
    if (c>>5 & 1) DB5_high_LCD(); else DB5_low_LCD();
    if (c>>6 & 1) DB6_high_LCD(); else DB6_low_LCD();
    if (c>>7 & 1) DB7_high_LCD(); else DB7_low_LCD();
}

void write_character(const char c)
{
    int status_LCD;
    RS_high_LCD();
    RW_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_high_LCD();
    char_2_data_LCD(c);
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
    E_low_LCD();
    status_LCD = NOT_READY_LCD;
    while (status_LCD != READY_LCD) { status_LCD = Ready_LCD();}
}
