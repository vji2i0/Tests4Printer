#include "CharacterConverter_LCD.h"

#include "stdint.h"
#include "unistd.h"
#include <wchar.h>


char convertCharacter_LCD(wchar_t letter)
{
    //English alphabed
    if (letter == *L"a") return 'a';
    if (letter == *L"b") return 'b';
    if (letter == *L"c") return 'c';
    if (letter == *L"d") return 'd';
    if (letter == *L"e") return 'e';
    if (letter == *L"f") return 'f';
    if (letter == *L"g") return 'g';
    if (letter == *L"h") return 'h';
    if (letter == *L"i") return 'i';
    if (letter == *L"j") return 'j';
    if (letter == *L"k") return 'k';
    if (letter == *L"l") return 'l';
    if (letter == *L"m") return 'm';
    if (letter == *L"n") return 'n';
    if (letter == *L"o") return 'o';
    if (letter == *L"p") return 'p';
    if (letter == *L"q") return 'q';
    if (letter == *L"r") return 'r';
    if (letter == *L"s") return 's';
    if (letter == *L"t") return 't';
    if (letter == *L"u") return 'u';
    if (letter == *L"v") return 'v';
    if (letter == *L"w") return 'w';
    if (letter == *L"x") return 'x';
    if (letter == *L"y") return 'y';
    if (letter == *L"z") return 'z';
    if (letter == *L"A") return 'A';
    if (letter == *L"B") return 'B';
    if (letter == *L"C") return 'C';
    if (letter == *L"D") return 'D';
    if (letter == *L"E") return 'E';
    if (letter == *L"F") return 'F';
    if (letter == *L"G") return 'G';
    if (letter == *L"H") return 'H';
    if (letter == *L"I") return 'I';
    if (letter == *L"J") return 'J';
    if (letter == *L"K") return 'K';
    if (letter == *L"L") return 'L';
    if (letter == *L"M") return 'M';
    if (letter == *L"N") return 'N';
    if (letter == *L"O") return 'O';
    if (letter == *L"P") return 'P';
    if (letter == *L"Q") return 'Q';
    if (letter == *L"R") return 'R';
    if (letter == *L"S") return 'S';
    if (letter == *L"T") return 'T';
    if (letter == *L"U") return 'U';
    if (letter == *L"V") return 'V';
    if (letter == *L"W") return 'W';
    if (letter == *L"X") return 'X';
    if (letter == *L"Y") return 'Y';
    if (letter == *L"Z") return 'Z';
    //Russian alphabed
    if (letter == *L"а") return (char)0x61;//0b01100001;
    if (letter == *L"б") return (char)0xB2;//0b10110010;
    if (letter == *L"в") return (char)0xB3;//0b10110011;
    if (letter == *L"г") return (char)0xB4;//0b10110100;
    if (letter == *L"д") return (char)0xE3;//0b11100011;
    if (letter == *L"е") return (char)0x65;//0b01100101;
    if (letter == *L"ё") return (char)0xB5;//0b10110101;
    if (letter == *L"ж") return (char)0xB6;//0b10110110;
    if (letter == *L"з") return (char)0xB7;//0b10110111;
    if (letter == *L"и") return (char)0xB8;//0b10111000;
    if (letter == *L"й") return (char)0xB9;//0b10111001;
    if (letter == *L"к") return (char)0xBA;//0b10111010;
    if (letter == *L"л") return (char)0xBB;//0b10111011;
    if (letter == *L"м") return (char)0xBC;//0b10111100;
    if (letter == *L"н") return (char)0xBD;//0b10111101;
    if (letter == *L"о") return (char)0x6F;//0b01101111;
    if (letter == *L"п") return (char)0xBE;//0b10111110;
    if (letter == *L"р") return (char)0x70;//0b01110000;
    if (letter == *L"с") return (char)0x63;//0b01100011;
    if (letter == *L"т") return (char)0xBF;//0b10111111;
    if (letter == *L"у") return (char)0x79;//0b01111001;
    if (letter == *L"ф") return (char)0xE4;//0b11100100;
    if (letter == *L"х") return (char)0x78;//0b01111000;
    if (letter == *L"ц") return (char)0xE5;//0b11100101;
    if (letter == *L"ч") return (char)0xC0;//0b11000000;
    if (letter == *L"ш") return (char)0xC1;//0b11000001;
    if (letter == *L"щ") return (char)0xE6;//0b11100110;
    if (letter == *L"ъ") return (char)0xC2;//0b11000010;
    if (letter == *L"ы") return (char)0xC3;//0b11000011;
    if (letter == *L"ь") return (char)0xC4;//0b11000100;
    if (letter == *L"э") return (char)0xC5;//0b11000101;
    if (letter == *L"ю") return (char)0xC6;//0b11000110;
    if (letter == *L"я") return (char)0xC7;//0b11000111;
    if (letter == *L"А") return (char)0x41;//0b01000001;
    if (letter == *L"Б") return (char)0xA0;//0b10100000;
    if (letter == *L"В") return (char)0x42;//0b01000010;
    if (letter == *L"Г") return (char)0xA1;//0b10100001;
    if (letter == *L"Д") return (char)0xE0;//0b11100000;
    if (letter == *L"Е") return (char)0x45;//0b01000101;
    if (letter == *L"Ё") return (char)0x45;//0b01000101;
    if (letter == *L"Ж") return (char)0xA3;//0b10100011;
    if (letter == *L"З") return (char)0xA4;//0b10100100;
    if (letter == *L"И") return (char)0xA5;//0b10100101;
    if (letter == *L"Й") return (char)0xA6;//0b10100110;
    if (letter == *L"К") return (char)0x4B;//0b01001011;
    if (letter == *L"Л") return (char)0xA7;//0b10100111;
    if (letter == *L"М") return (char)0x4D;//0b01001101;
    if (letter == *L"Н") return (char)0x48;//0b01001000;
    if (letter == *L"О") return (char)0x4F;//0b01001111;
    if (letter == *L"П") return (char)0xA8;//0b10101000;
    if (letter == *L"Р") return (char)0x50;//0b01010000;
    if (letter == *L"С") return (char)0x43;//0b01000011;
    if (letter == *L"Т") return (char)0x54;//0b01010100;
    if (letter == *L"У") return (char)0xA9;//0b10101001;
    if (letter == *L"Ф") return (char)0xAA;//0b10101010;
    if (letter == *L"Х") return (char)0x58;//0b01011000;
    if (letter == *L"Ц") return (char)0xE1;//0b11100001;
    if (letter == *L"Ч") return (char)0xAB;//0b10101011;
    if (letter == *L"Ш") return (char)0xAC;//0b10101100;
    if (letter == *L"Щ") return (char)0xE2;//0b11100010;
    if (letter == *L"Ъ") return (char)0xAD;//0b10101101;
    if (letter == *L"Ы") return (char)0xAE;//0b10101110;
    if (letter == *L"Ь") return (char)0x62;//0b01100010;
    if (letter == *L"Э") return (char)0xAF;//0b10101111;
    if (letter == *L"Ю") return (char)0xB0;//0b10110000;
    if (letter == *L"Я") return (char)0xB1;//0b10110001;
    //Special characters
    if (letter == *L">") return '>';
    if (letter == *L"<") return '<';
    if (letter == *L")") return ')';
    if (letter == *L"(") return '(';
    if (letter == *L"\"") return '\"';
    if (letter == *L"!") return '!';
    if (letter == *L"?") return '?';
    if (letter == *L"#") return '#';
    if (letter == *L"$") return '$';
    if (letter == *L"%") return '%';
    if (letter == *L"\'") return '\'';
    if (letter == *L"*") return '*';
    if (letter == *L"-") return '-';
    if (letter == *L"+") return '+';
    if (letter == *L".") return '.';
    if (letter == *L",") return ',';
    if (letter == *L"_") return '_';
    if (letter == *L"=") return '=';
    if (letter == *L"^") return '^';
    if (letter == *L"/") return '/';
    if (letter == *L":") return ':';
    if (letter == *L";") return ';';
    if (letter == *L" ") return ' ';
    //Numbers
    if (letter == *L"0") return '0';
    if (letter == *L"1") return '1';
    if (letter == *L"2") return '2';
    if (letter == *L"3") return '3';
    if (letter == *L"4") return '4';
    if (letter == *L"5") return '5';
    if (letter == *L"6") return '6';
    if (letter == *L"7") return '7';
    if (letter == *L"8") return '8';
    if (letter == *L"9") return '9';
    //Default character
    return '?';
}
