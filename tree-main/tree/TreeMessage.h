// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MSG_INVALID_SWITCH
//
// MessageText:
//
// Invalid switch - /%1
//
#define MSG_INVALID_SWITCH               0x00002AF8L

//
// MessageId: MSG_INVALID_PATH
//
// MessageText:
//
// Invalid path - %1
//
#define MSG_INVALID_PATH                 0x00002AF9L

//
// MessageId: MSG_NO_SUBDIRECTORIES
//
// MessageText:
//
// No subfolders exist %1
//
#define MSG_NO_SUBDIRECTORIES            0x00002AFAL

//
// MessageId: MSG_DIR_LISTING_NO_VOLUME_NAME
//
// MessageText:
//
// Folder PATH listing
//
#define MSG_DIR_LISTING_NO_VOLUME_NAME   0x00002AFBL

//
// MessageId: MSG_DIR_LISTING_WITH_VOLUME_NAME
//
// MessageText:
//
// Folder PATH listing for volume %1
//
#define MSG_DIR_LISTING_WITH_VOLUME_NAME 0x00002AFCL

//
// MessageId: MSG_32_BIT_SERIAL_NUMBER
//
// MessageText:
//
// Volume serial number is %1-%2
//
#define MSG_32_BIT_SERIAL_NUMBER         0x00002AFDL

//
// MessageId: MSG_64_BIT_SERIAL_NUMBER
//
// MessageText:
//
// Volume serial number is %1 %2:%3
//
#define MSG_64_BIT_SERIAL_NUMBER         0x00002AFEL

//
// MessageId: MSG_HELP_MESSAGE
//
// MessageText:
//
// Graphically displays the folder structure of a drive or path.
// 
// TREE [drive:][path] [/F] [/A]
// 
//    /F   Display the names of the files in each folder.
//    /A   Use ASCII instead of extended characters.
// 
//
#define MSG_HELP_MESSAGE                 0x00002AFFL

//
// MessageId: MSG_PARAMETER_NOT_CORRECT
//
// MessageText:
//
// Parameter format not correct - %1
//
#define MSG_PARAMETER_NOT_CORRECT        0x00002B03L

//
// MessageId: MSG_TOO_MANY_PARAMETERS
//
// MessageText:
//
// Too many parameters - %1
//
#define MSG_TOO_MANY_PARAMETERS          0x00002B04L

//
// MessageId: MSG_INVALID_DRIVE
//
// MessageText:
//
// Invalid drive specification
//
#define MSG_INVALID_DRIVE                0x00002B05L

