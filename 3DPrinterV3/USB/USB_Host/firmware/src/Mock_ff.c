#include "Mock_ff.h"
#include "Fake_fatfs.h"
#include "CppUTestExt/MockSupport_c.h"
#include "stdio.h"

FRESULT f_mount (FATFS* fs, const TCHAR* USBHPath, BYTE opt)
{
    mock_c()->actualCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", opt);
    return (FRESULT) mock_c()->returnValue().value.intValue;
}

FRESULT f_opendir (DIR* dp, const TCHAR* path)
{
    mock_c()->actualCall("f_opendir")
        ->withConstPointerParameters("path", path);
    return (FRESULT) mock_c()->returnValue().value.intValue;
}

FRESULT f_closedir (DIR* dp)
{
    mock_c()->actualCall("f_closedir");
    return (FRESULT) mock_c()->returnValue().value.intValue;
}

static void directoryName(FILINFO* fno)
{
    sprintf(fno->fname,"%s", "dir1");
    sprintf(fno->lfname,"%s", "dir1");
    fno->fattrib = AM_DIR;
}

FRESULT f_readdir (DIR* dp, FILINFO* fno)
{
    directoryName(fno);
    mock_c()->actualCall("f_readdir");
    return (FRESULT) mock_c()->returnValue().value.intValue;
}

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode)
{
    mock_c()->actualCall("f_open");
    return (FRESULT) mock_c()->returnValue().value.intValue;
}

FRESULT f_close (FIL* fp)
{
    mock_c()->actualCall("f_close");
    return (FRESULT) mock_c()->returnValue().value.intValue;
}

TCHAR* f_gets (TCHAR* buff, int len, FIL* fp)
{
    sprintf(buff, "%s", "some string");
    mock_c()->actualCall("f_gets");
    return "OK";
}

int f_eof(FIL* fp)
{
    mock_c()->actualCall("f_eof");
    return mock_c()->returnValue().value.intValue;
}
