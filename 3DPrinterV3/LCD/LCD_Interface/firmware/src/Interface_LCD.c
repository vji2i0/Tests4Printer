#include "Interface_LCD.h"
#include "Mock_Driver_LCD.h"
#include "CharacterConverter_LCD.h"
#include "stdint.h"
#include <wchar.h>
#include "stdbool.h"

void create_LCD(void)
{
    return_home_LCD();
    clear_display_LCD();
    set_dataLenght_numberOfLines_fontType_LCD();
    set_do_not_display_cursor_LCD();
    set_cursor_moving_to_the_right_LCD();
}

static _Bool wrongInterfaceLine_LCD(int line)
{
    if(line > NUMBEROFLINES_INTERFACE_LCD)
        return true;
    if(line < 1)
        return true;
    return false;
}

void printLine_LCD(int line, const wchar_t* textToPrint)
{
    if(wrongInterfaceLine_LCD(line))
        return;

    move_to_line_LCD(line);

    int colomn;
    for(colomn = 1; colomn <= LINELENGTH_INTERFACE_LCD; colomn++)
    {
        write_character(convertCharacter_LCD(textToPrint[colomn-1]));
    }
}
