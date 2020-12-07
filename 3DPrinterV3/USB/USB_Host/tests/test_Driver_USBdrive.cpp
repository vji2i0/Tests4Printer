//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved
//-    For use by owners of Test-Driven Development for Embedded C,
//-    and attendees of Renaissance Software Consulting, Co. training
//-    classes.
//-
//-    Available at http://pragprog.com/titles/jgade/
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3
//-
//-    Authorized users may use this source code in your own
//-    projects, however the source code may not be used to
//-    create training material, courses, books, articles, and
//-    the like. We make no guarantees that this source code is
//-    fit for any purpose.
//-
//-    www.renaissancesoftware.net james@renaissancesoftware.net
//- ------------------------------------------------------------------


#include "CppUTest/TestHarness.h"


extern "C"
{
    #include "CppUTestExt/MockSupport_c.h"
    #include "Driver_USBdrive.h"
    #include "Mock_ff.h"
    #include "Fake_fatfs.h"
    #include "wchar.h"
    #include "stdbool.h"
}

TEST_GROUP(Driver_USBdrive)
{
    void setup()
    {
        createDriver_USBdrive();
        USBHPath[0] = 'f';
        USBHPath[1] = ':';
    }
    void teardown()
    {
        mock_c()->checkExpectations();
        mock_c()->clear();
    }
};

TEST(Driver_USBdrive, initialization_check)
{
    CHECK_EQUAL(getMountedStatus(), UNMOUNTED_USBDRIVE);
    STRCMP_EQUAL(getPath_USBdrive(), "");
    STRCMP_EQUAL(getName_USBdrive(), "");
    STRCMP_EQUAL(getLongName_USBdrive(), "");
    CHECK_EQUAL(getItemType_USBdrive(), ITEM_IS_EMPTY);
}

TEST(Driver_USBdrive, mount_usb_drive_successful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);


        mount_USBdrive();

    CHECK_EQUAL(getMountedStatus(), MOUNTED_USBDRIVE);
    STRCMP_EQUAL(USBHPath, getPath_USBdrive());
}

TEST(Driver_USBdrive, mount_usb_drive_unsuccessful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_NOT_READY);


        mount_USBdrive();

    CHECK_EQUAL(getMountedStatus(), UNMOUNTED_USBDRIVE);
}

TEST(Driver_USBdrive, do_not_mount_the_mounted_usb_drive)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);


        mount_USBdrive();
        mount_USBdrive();

    CHECK_EQUAL(getMountedStatus(), MOUNTED_USBDRIVE);
}

TEST(Driver_USBdrive, mount_usb_drive_successful_then_unmount_usb_drive_successful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);


    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    CHECK_EQUAL(getMountedStatus(), MOUNTED_USBDRIVE);
    unmount_USBdrive();
    CHECK_EQUAL(getMountedStatus(), UNMOUNTED_USBDRIVE);
}

TEST(Driver_USBdrive, mount_usb_drive_successful_then_unmount_usb_drive_unsuccessful_then_successful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_NOT_READY);

    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);


    mount_USBdrive();
    CHECK_EQUAL(getMountedStatus(), MOUNTED_USBDRIVE);
    unmount_USBdrive();
    CHECK_EQUAL(getMountedStatus(), UNMOUNTED_USBDRIVE);
}

TEST(Driver_USBdrive, do_nothing_when_trying_to_unmount_unmounted_usb_drive)
{

    CHECK_EQUAL(getMountedStatus(), UNMOUNTED_USBDRIVE);
    unmount_USBdrive();
    CHECK_EQUAL(getMountedStatus(), UNMOUNTED_USBDRIVE);
}


TEST(Driver_USBdrive, open_root_directory_of_mounted_usb_drive_successful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", USBHPath)
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive(USBHPath);
    STRCMP_EQUAL(USBHPath, getPath_USBdrive());
}

TEST(Driver_USBdrive, open_arbitrary_directory_of_mounted_usb_drive_successful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", "f:/dir1")
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive("f:/dir1");
    STRCMP_EQUAL("f:/dir1", getPath_USBdrive());
}


TEST(Driver_USBdrive, open_arbitrary_directory_of_mounted_usb_drive_unsuccessful)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", "f:/")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", "f:/dir1")
        ->andReturnIntValue((int) !FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", getPath_USBdrive())
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive("f:/");
    STRCMP_EQUAL("f:/", getPath_USBdrive());
    openDirectory_USBdrive("f:/dir1");
    STRCMP_EQUAL("f:/", getPath_USBdrive());
}


TEST(Driver_USBdrive, do_not_open_root_directory_of_unmounted_usb_drive)
{
    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    openDirectory_USBdrive(USBHPath);
}

TEST(Driver_USBdrive, open_directory_of_mounted_usb_drive_get_first_item)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", USBHPath)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_readdir")
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive(USBHPath);
    readItem_USBdrive();
}

TEST(Driver_USBdrive, open_directory_of_unmounted_usb_drive_try_to_get_first_item)
{
    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    openDirectory_USBdrive(USBHPath);
    readItem_USBdrive();
}


static void WSTRCMP_EQUAL(const wchar_t* expectedText, const wchar_t* givenText)
{
    unsigned int NumberOfCompared=wcslen(expectedText);
    unsigned int i;
    for(i=0; i<NumberOfCompared; i++)
        CHECK_EQUAL((int)expectedText[i],(int)givenText[i]);

}

TEST(Driver_USBdrive, open_directory_get_name_and_long_name_and_wide_long_name_of_item_english)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", USBHPath)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_readdir")
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive(USBHPath);
    readItem_USBdrive();

    STRCMP_EQUAL("dir1", getName_USBdrive());
    STRCMP_EQUAL("dir1", getLongName_USBdrive());
    WSTRCMP_EQUAL(L" dir1", getWideLongName_USBdrive());
    WSTRCMP_EQUAL(getWideLongName_USBdrive(), L" dir1");
}

TEST(Driver_USBdrive, open_directory_get_type_of_item)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", USBHPath)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_readdir")
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive(USBHPath);
    readItem_USBdrive();

    CHECK_EQUAL(getItemType_USBdrive(), ITEM_IS_DIRECTORY);
}

TEST(Driver_USBdrive, open_directory_get_wide_path_english)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_closedir")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_opendir")
        ->withConstPointerParameters("path", "f:/dir1")
        ->andReturnIntValue((int) FR_OK);

    mount_USBdrive();
    openDirectory_USBdrive("f:/dir1");
    WSTRCMP_EQUAL(L"f:/dir1", getWidePath_USBdrive());
    WSTRCMP_EQUAL(getWidePath_USBdrive(), L"f:/dir1");
}

TEST(Driver_USBdrive, open_file_of_mounted_drive)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_close")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_open")
        ->andReturnIntValue((int) FR_OK);


    mount_USBdrive();
    openFile_USBdrive("f:/pathToTheFile.g");
}

TEST(Driver_USBdrive, do_not_open_file_of_unmounted_drive)
{
    mock_c()->expectOneCall("f_close")
        ->andReturnIntValue((int) FR_OK);

    openFile_USBdrive("f:/pathToTheFile.g");
}

TEST(Driver_USBdrive, get_string_from_file_of_mounted_drive)
{
    mock_c()->expectOneCall("f_mount")
        ->withConstPointerParameters("USBHPath", USBHPath)
        ->withIntParameters("opt", 0)
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_close")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_open")
        ->andReturnIntValue((int) FR_OK);

    mock_c()->expectOneCall("f_gets");

    mount_USBdrive();
    openFile_USBdrive("f:/pathToTheFile.g");
    STRCMP_EQUAL("some string", getStringFromFile_USBdrive());
}

TEST(Driver_USBdrive, do_not_get_string_from_file_of_unmounted_drive)
{
    mock_c()->expectOneCall("f_close")
        ->andReturnIntValue((int) FR_OK);

    openFile_USBdrive("f:/pathToTheFile.g");
    STRCMP_EQUAL("", getStringFromFile_USBdrive());
}

TEST(Driver_USBdrive, the_file_is_ended)
{
    mock_c()->expectOneCall("f_eof")
        ->andReturnIntValue(-1);

    CHECK_EQUAL(true, endOfFile_USBdrive());
}

TEST(Driver_USBdrive, the_file_is_not_ended)
{
    mock_c()->expectOneCall("f_eof")
        ->andReturnIntValue(0);

    CHECK_EQUAL(false, endOfFile_USBdrive());
}


