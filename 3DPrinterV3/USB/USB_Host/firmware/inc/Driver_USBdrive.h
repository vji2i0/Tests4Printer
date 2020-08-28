#ifndef DRIVER_USBDRIVE
#define DRIVER_USBDRIVE

#include "wchar.h"
#include "stdbool.h"

#include "Mock_ff.h"


typedef enum {MOUNTED_USBDRIVE = 1, UNMOUNTED_USBDRIVE = 0} mountedStatus_USBdrive;
enum {PATH_LENGTH = 100};
enum {MAX_WIDE_NAME_LENGTH = 100};
enum {STRING_FROM_FILE_LENGTH = 100};
typedef enum {ITEM_IS_EMPTY = 0, ITEM_IS_FILE = 1, ITEM_IS_DIRECTORY = 2} itemType_USBdrive;



void createDriver_USBdrive(void);
void mount_USBdrive(void);
void unmount_USBdrive(void);
mountedStatus_USBdrive getMountedStatus(void);
const TCHAR* getPath_USBdrive(void);
const wchar_t* getWidePath_USBdrive(void);
void openDirectory_USBdrive(const TCHAR* pathToDirectory);
void readItem_USBdrive(void);
const TCHAR* getName_USBdrive(void);
const TCHAR* getLongName_USBdrive(void);
const wchar_t* getWideLongName_USBdrive(void);
itemType_USBdrive getItemType_USBdrive(void);
void openFile_USBdrive(const TCHAR* pathToFile);
const TCHAR* getStringFromFile_USBdrive(void);
_Bool endOfFile_USBdrive(void);


#endif
