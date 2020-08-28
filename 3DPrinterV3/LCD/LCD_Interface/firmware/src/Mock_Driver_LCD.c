#include "Mock_Driver_LCD.h"
#include "stdbool.h"
#include "CppUTestExt/MockSupport_c.h"


void clear_display_LCD(void)
{
    mock_c()->actualCall("clear_display_LCD");
}

void return_home_LCD(void)
{
    mock_c()->actualCall("return_home_LCD");
}

void set_dataLenght_numberOfLines_fontType_LCD(void)
{
    mock_c()->actualCall("set_dataLenght_numberOfLines_fontType_LCD");
}

void set_do_not_display_cursor_LCD(void)
{
    mock_c()->actualCall("set_do_not_display_cursor_LCD");
}

void set_cursor_moving_to_the_right_LCD(void)
{
    mock_c()->actualCall("set_cursor_moving_to_the_right_LCD");
}

void move_to_line_LCD(int line)
{
    mock_c()->actualCall("move_to_line_LCD")
        ->withIntParameters("line", line);
}

void write_character(const char c)
{
    mock_c()->actualCall("write_character")
        ->withIntParameters("character", (int) c);
}

