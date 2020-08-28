#include "Driver_USBdrive.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

#include "Fake_fatfs.h"
#include "Mock_ff.h"

static const TCHAR zeroPath_USBdriver[PATH_LENGTH] = "";

static mountedStatus_USBdrive currentMountedStatus_USBdrive;
static TCHAR path[PATH_LENGTH];
static FATFS USBDISKFatFs;
static DIR directory;
static FILINFO fileInformation;
static FIL file;


void createDriver_USBdrive(void)
{
    currentMountedStatus_USBdrive = UNMOUNTED_USBDRIVE;
    memcpy(path, zeroPath_USBdriver, PATH_LENGTH);
    sprintf(fileInformation.fname, "%s", "");
    fileInformation.lfsize = _MAX_LFN;
    sprintf(fileInformation.lfname, "%s", "");
}

void mount_USBdrive(void)
{
    if(currentMountedStatus_USBdrive == MOUNTED_USBDRIVE)
        return;

    if(f_mount(&USBDISKFatFs, USBHPath, 0) == FR_OK)
    {
        currentMountedStatus_USBdrive = MOUNTED_USBDRIVE;
        sprintf(path, "%s", USBHPath);
        return;
    }

    currentMountedStatus_USBdrive = UNMOUNTED_USBDRIVE;
}

void unmount_USBdrive(void)
{
    if (currentMountedStatus_USBdrive == UNMOUNTED_USBDRIVE)
        return;

    sprintf(USBHPath, "%c",'\0');
    memcpy(path, zeroPath_USBdriver, PATH_LENGTH);

    while (f_mount(NULL, USBHPath, 0) != FR_OK) {};

    currentMountedStatus_USBdrive = UNMOUNTED_USBDRIVE;
}

mountedStatus_USBdrive getMountedStatus(void) { return currentMountedStatus_USBdrive;}


static wchar_t TCHAR2wchar_t(TCHAR character)
{
    if(character == (TCHAR) 0xA0) return *L"а";
    if(character == (TCHAR) 0xA1) return *L"б";
    if(character == (TCHAR) 0xA2) return *L"в";
    if(character == (TCHAR) 0xA3) return *L"г";
    if(character == (TCHAR) 0xA4) return *L"д";
    if(character == (TCHAR) 0xA5) return *L"е";
    if(character == (TCHAR) 0xF1) return *L"ё";
    if(character == (TCHAR) 0xA6) return *L"ж";
    if(character == (TCHAR) 0xA7) return *L"з";
    if(character == (TCHAR) 0xA8) return *L"и";
    if(character == (TCHAR) 0xA9) return *L"й";
    if(character == (TCHAR) 0xAA) return *L"к";
    if(character == (TCHAR) 0xAB) return *L"л";
    if(character == (TCHAR) 0xAC) return *L"м";
    if(character == (TCHAR) 0xAD) return *L"н";
    if(character == (TCHAR) 0xAE) return *L"о";
    if(character == (TCHAR) 0xAF) return *L"п";
    if(character == (TCHAR) 0xE0) return *L"р";
    if(character == (TCHAR) 0xE1) return *L"с";
    if(character == (TCHAR) 0xE2) return *L"т";
    if(character == (TCHAR) 0xE3) return *L"у";
    if(character == (TCHAR) 0xE4) return *L"ф";
    if(character == (TCHAR) 0xE5) return *L"х";
    if(character == (TCHAR) 0xE6) return *L"ц";
    if(character == (TCHAR) 0xE7) return *L"ч";
    if(character == (TCHAR) 0xE8) return *L"ш";
    if(character == (TCHAR) 0xE9) return *L"щ";
    if(character == (TCHAR) 0xEA) return *L"ъ";
    if(character == (TCHAR) 0xEB) return *L"ы";
    if(character == (TCHAR) 0xEC) return *L"ь";
    if(character == (TCHAR) 0xED) return *L"э";
    if(character == (TCHAR) 0xEE) return *L"ю";
    if(character == (TCHAR) 0xEF) return *L"я";
    if(character == (TCHAR) 0x80) return *L"А";
    if(character == (TCHAR) 0x81) return *L"Б";
    if(character == (TCHAR) 0x82) return *L"В";
    if(character == (TCHAR) 0x83) return *L"Г";
    if(character == (TCHAR) 0x84) return *L"Д";
    if(character == (TCHAR) 0x85) return *L"Е";
    if(character == (TCHAR) 0xF0) return *L"Ё";
    if(character == (TCHAR) 0x86) return *L"Ж";
    if(character == (TCHAR) 0x87) return *L"З";
    if(character == (TCHAR) 0x88) return *L"И";
    if(character == (TCHAR) 0x89) return *L"Й";
    if(character == (TCHAR) 0x8A) return *L"К";
    if(character == (TCHAR) 0x8B) return *L"Л";
    if(character == (TCHAR) 0x8C) return *L"М";
    if(character == (TCHAR) 0x8D) return *L"Н";
    if(character == (TCHAR) 0x8E) return *L"О";
    if(character == (TCHAR) 0x8F) return *L"П";
    if(character == (TCHAR) 0x90) return *L"Р";
    if(character == (TCHAR) 0x91) return *L"С";
    if(character == (TCHAR) 0x92) return *L"Т";
    if(character == (TCHAR) 0x93) return *L"У";
    if(character == (TCHAR) 0x94) return *L"Ф";
    if(character == (TCHAR) 0x95) return *L"Х";
    if(character == (TCHAR) 0x96) return *L"Ц";
    if(character == (TCHAR) 0x97) return *L"Ч";
    if(character == (TCHAR) 0x98) return *L"Ш";
    if(character == (TCHAR) 0x99) return *L"Щ";
    if(character == (TCHAR) 0x9A) return *L"Ъ";
    if(character == (TCHAR) 0x9B) return *L"Ы";
    if(character == (TCHAR) 0x9C) return *L"Ь";
    if(character == (TCHAR) 0x9D) return *L"Э";
    if(character == (TCHAR) 0x9E) return *L"Ю";
    if(character == (TCHAR) 0x9F) return *L"Я";
    return (wchar_t) character;
}


const TCHAR* getPath_USBdrive(void){ return path;}

static void convertPathToWidePath(wchar_t* widePath)
{
    int letterNember;
    for (letterNember = 0; letterNember < PATH_LENGTH; letterNember++)
        widePath[letterNember] = TCHAR2wchar_t(path[letterNember]);
}

static wchar_t widePath[PATH_LENGTH];
const wchar_t* getWidePath_USBdrive(void)
{
    convertPathToWidePath(widePath);
    return (const wchar_t*) widePath;
}


void openDirectory_USBdrive(const TCHAR* pathToDirectory)
{
    f_closedir(&directory);

    if (currentMountedStatus_USBdrive == UNMOUNTED_USBDRIVE)
        return;

    if(f_opendir(&directory, pathToDirectory)!=FR_OK)
    {
        f_opendir(&directory, path);
        return;
    }

    sprintf(path, "%s", pathToDirectory);

}

void readItem_USBdrive()
{
    if (currentMountedStatus_USBdrive == UNMOUNTED_USBDRIVE)
        return;

    if(f_readdir(&directory, &fileInformation)!=FR_OK)
        return;
}

const TCHAR* getName_USBdrive(void) { return (const TCHAR*) fileInformation.fname;}

const TCHAR* getLongName_USBdrive(void) { return (const TCHAR*) fileInformation.lfname;}



static void convertLongNameToWideLongName(wchar_t* wideLongName, const TCHAR* longName)
{
    int letterNember;
    for (letterNember = 0; letterNember < MAX_WIDE_NAME_LENGTH; letterNember++)
        wideLongName[letterNember] = *L"\0";
    for (letterNember = 0; letterNember < MAX_WIDE_NAME_LENGTH; letterNember++)
        wideLongName[letterNember] = TCHAR2wchar_t(longName[letterNember]);
}

static wchar_t outputWideName[MAX_WIDE_NAME_LENGTH];
const wchar_t* getWideLongName_USBdrive(void)
{
    convertLongNameToWideLongName(outputWideName, fileInformation.lfname);
    return (const wchar_t*) outputWideName;
}

itemType_USBdrive getItemType_USBdrive(void)
{
    if (getName_USBdrive()[0] == '\0')
        return ITEM_IS_EMPTY;
    if (fileInformation.fattrib == AM_DIR)
        return ITEM_IS_DIRECTORY;
    return ITEM_IS_FILE;
}

void openFile_USBdrive(const TCHAR* pathToFile)
{
    f_close(&file);

    if (currentMountedStatus_USBdrive == UNMOUNTED_USBDRIVE)
        return;

    f_open(&file, pathToFile, FA_READ);
}

static TCHAR stringFromFile[STRING_FROM_FILE_LENGTH];
const TCHAR* getStringFromFile_USBdrive(void)
{
    if (currentMountedStatus_USBdrive == UNMOUNTED_USBDRIVE)
        return "";

    f_gets(stringFromFile, STRING_FROM_FILE_LENGTH, &file);
    return (const TCHAR*) stringFromFile;
}

_Bool endOfFile_USBdrive(void)
{
    if(f_eof(&file)==0)
        return false;
    return true;
}
