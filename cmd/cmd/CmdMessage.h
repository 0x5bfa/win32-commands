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
// MessageId: MSG_NOYES_RESPONSE_DATA
//
// MessageText:
//
// NY%0
//
#define MSG_NOYES_RESPONSE_DATA          0x00002328L

//
// MessageId: MSG_BAD_PARM1
//
// MessageText:
//
// An incorrect parameter was
// entered for the command.
//
#define MSG_BAD_PARM1                    0x00002329L

//
// MessageId: MSG_BAD_SYNTAX
//
// MessageText:
//
// The syntax of the command is incorrect.
//
#define MSG_BAD_SYNTAX                   0x0000232AL

//
// MessageId: MSG_STRIKE_ANY_KEY
//
// MessageText:
//
// Press any key to continue . . . %0
//
#define MSG_STRIKE_ANY_KEY               0x0000232BL

//
// MessageId: MSG_CMD_DELETE
//
// MessageText:
//
// %1, Delete (Y/N)? %0
//
#define MSG_CMD_DELETE                   0x0000232CL

//
// MessageId: MSG_REN_INVAL_PATH_FILENAME
//
// MessageText:
//
// The system cannot accept the path
// or file name requested.
//
#define MSG_REN_INVAL_PATH_FILENAME      0x0000232EL

//
// MessageId: MSG_INVALID_DATE
//
// MessageText:
//
// The system cannot accept the date entered.
//
#define MSG_INVALID_DATE                 0x0000232FL

//
// MessageId: MSG_NO_BAT_LABEL
//
// MessageText:
//
// No batch label specified to GOTO command.
//
#define MSG_NO_BAT_LABEL                 0x00002330L

//
// MessageId: MSG_DIR_BAD_COMMAND_OR_FILE
//
// MessageText:
//
// '%1' is not recognized as an internal or external command,
// operable program or batch file.
//
#define MSG_DIR_BAD_COMMAND_OR_FILE      0x00002331L

//
// MessageId: MSG_REN_INVALID_TIME
//
// MessageText:
//
// The system cannot accept the time entered.
//
#define MSG_REN_INVALID_TIME             0x00002332L

//
// MessageId: MSG_C
//
// MessageText:
//
// ^C
//
#define MSG_C                            0x00002335L

//
// MessageId: MSG_FILES_COPIED
//
// MessageText:
//
// %1 file(s) copied.
//
#define MSG_FILES_COPIED                 0x00002336L

//
// MessageId: MSG_CURRENT_DATE
//
// MessageText:
//
// The current date is: %0
//
#define MSG_CURRENT_DATE                 0x00002337L

//
// MessageId: MSG_CURRENT_TIME
//
// MessageText:
//
// The current time is: %0
//
#define MSG_CURRENT_TIME                 0x00002338L

//
// MessageId: MSG_DIR_OF
//
// MessageText:
//
//  Directory of %1
// 
//
#define MSG_DIR_OF                       0x00002339L

//
// MessageId: MSG_OUT_OF_ENVIRON_SPACE
//
// MessageText:
//
// The system is out of environment space.
//
#define MSG_OUT_OF_ENVIRON_SPACE         0x0000233AL

//
// MessageId: MSG_EXEC_FAILURE
//
// MessageText:
//
// The system cannot execute the specified program.
//
#define MSG_EXEC_FAILURE                 0x0000233CL

//
// MessageId: MSG_LINES_TOO_LONG
//
// MessageText:
//
// The input line is too long.
//
#define MSG_LINES_TOO_LONG               0x0000233FL

//
// MessageId: MSG_CONT_LOST_BEF_COPY
//
// MessageText:
//
// The contents of the target file
// were lost.
//
#define MSG_CONT_LOST_BEF_COPY           0x00002340L

//
// MessageId: MSG_INSRT_DISK_BAT
//
// MessageText:
//
// Insert the diskette that contains the batch file
// and press any key when ready. %0
//
#define MSG_INSRT_DISK_BAT               0x00002341L

//
// MessageId: MSG_ENTER_NEW_DATE
//
// MessageText:
//
// Enter the new date: (mm-dd-yy) %0
//
#define MSG_ENTER_NEW_DATE               0x00002342L

//
// MessageId: MSG_ENTER_NEW_TIME
//
// MessageText:
//
// Enter the new time: %0
//
#define MSG_ENTER_NEW_TIME               0x00002343L

//
// MessageId: MSG_RDR_HNDL_CREATE
//
// MessageText:
//
// The handle could not be duplicated
// during redirection of handle %1.
//
#define MSG_RDR_HNDL_CREATE              0x00002344L

//
// MessageId: MSG_ECHO_OFF
//
// MessageText:
//
// ECHO is off.
//
#define MSG_ECHO_OFF                     0x00002345L

//
// MessageId: MSG_ECHO_ON
//
// MessageText:
//
// ECHO is on.
//
#define MSG_ECHO_ON                      0x00002346L

//
// MessageId: MSG_VERIFY_OFF
//
// MessageText:
//
// VERIFY is off.
//
#define MSG_VERIFY_OFF                   0x00002347L

//
// MessageId: MSG_VERIFY_ON
//
// MessageText:
//
// VERIFY is on.
//
#define MSG_VERIFY_ON                    0x00002348L

//
// MessageId: MSG_CANNOT_COPIED_ONTO_SELF
//
// MessageText:
//
// The file cannot be copied onto itself.
//
#define MSG_CANNOT_COPIED_ONTO_SELF      0x00002349L

//
// MessageId: MSG_SYNERR_GENL
//
// MessageText:
//
// %1 was unexpected at this time.
//
#define MSG_SYNERR_GENL                  0x0000234AL

//
// MessageId: MSG_PID_IS
//
// MessageText:
//
// The Process Identification Number is %1.
//
#define MSG_PID_IS                       0x0000234CL

//
// MessageId: MSG_DUP_FILENAME_OR_NOT_FD
//
// MessageText:
//
// A duplicate file name exists, or the file
// cannot be found.
//
#define MSG_DUP_FILENAME_OR_NOT_FD       0x0000234DL

//
// MessageId: MSG_ARE_YOU_SURE
//
// MessageText:
//
// %1, Are you sure (Y/N)? %0
//
#define MSG_ARE_YOU_SURE                 0x0000234EL

//
// MessageId: MSG_TOKEN_TOO_LONG
//
// MessageText:
//
// The following character string is too long:
// %1
//
#define MSG_TOKEN_TOO_LONG               0x0000234FL

//
// MessageId: MSG_MS_DOS_VERSION
//
// MessageText:
//
// Microsoft Windows [Version %1]%0
//
#define MSG_MS_DOS_VERSION               0x00002350L

//
// MessageId: MSG_PIPE_FAILURE
//
// MessageText:
//
// The handle could not be duplicated during
// a pipe operation.
//
#define MSG_PIPE_FAILURE                 0x00002351L

//
// MessageId: MSG_MS_MORE
//
// MessageText:
//
// More? %0
//
#define MSG_MS_MORE                      0x00002352L

//
// MessageId: MSG_REAL_MODE_ONLY
//
// MessageText:
//
// The system cannot complete the process.
//
#define MSG_REAL_MODE_ONLY               0x00002353L

//
// MessageId: MSG_TYPE_FILENAME
//
// MessageText:
//
// 
// %1
// 
// 
//
#define MSG_TYPE_FILENAME                0x00002354L

//
// MessageId: MSG_DR_VOL_SERIAL
//
// MessageText:
//
//  Volume Serial Number is %1
//
#define MSG_DR_VOL_SERIAL                0x0000235BL

//
// MessageId: MSG_DIR_EXISTS
//
// MessageText:
//
// A subdirectory or file %1 already exists.
//
#define MSG_DIR_EXISTS                   0x0000235CL

//
// MessageId: MSG_ERR_PROC_ARG
//
// MessageText:
//
// Error occurred while processing: %1.
//
#define MSG_ERR_PROC_ARG                 0x0000235DL

//
// MessageId: MSG_HAS_NO_LABEL
//
// MessageText:
//
//  Volume in drive %1 has no label.
//
#define MSG_HAS_NO_LABEL                 0x0000235EL

//
// MessageId: MSG_DR_VOL_LABEL
//
// MessageText:
//
//  Volume in drive %1 is %2
//
#define MSG_DR_VOL_LABEL                 0x0000235FL

//
// MessageId: MSG_KEYS_ON
//
// MessageText:
//
// KEYS is on.
//
#define MSG_KEYS_ON                      0x00002360L

//
// MessageId: MSG_KEYS_OFF
//
// MessageText:
//
// KEYS is off.
//
#define MSG_KEYS_OFF                     0x00002361L

//
// MessageId: MSG_START_INVALID_PARAMETER
//
// MessageText:
//
// The system cannot accept the START command parameter %1.
//
#define MSG_START_INVALID_PARAMETER      0x00002362L

//
// MessageId: MSG_CMD_FILE_NOT_FOUND
//
// MessageText:
//
// The system cannot find the file %1.
//
#define MSG_CMD_FILE_NOT_FOUND           0x00002363L

//
// MessageId: MSG_CMD_INVAL_PIPE
//
// MessageText:
//
// The process tried to write to a nonexistent pipe.
//
#define MSG_CMD_INVAL_PIPE               0x00002364L

//
// MessageId: MSG_CMD_NOT_RECOGNIZED
//
// MessageText:
//
// "%1" is not a recognized device.
//
#define MSG_CMD_NOT_RECOGNIZED           0x0000236BL

//
// MessageId: MSG_CMD_BATCH_FILE_MISSING
//
// MessageText:
//
// The batch file cannot be found.
//
#define MSG_CMD_BATCH_FILE_MISSING       0x0000236CL

//
// MessageId: MSG_DIRS_MOVED
//
// MessageText:
//
// %1 dir(s) moved.
//
#define MSG_DIRS_MOVED                   0x0000236DL

//
// MessageId: MSG_FILES_MOVED
//
// MessageText:
//
// %1 file(s) moved.
//
#define MSG_FILES_MOVED                  0x0000236EL

//
// MessageId: MSG_TRAPC
//
// MessageText:
//
// A program attempted to reference storage outside the
// limits of a stack segment.  The program was ended.
// 
// %1
//
#define MSG_TRAPC                        0x0000236FL

//
// MessageId: MSG_LITERAL_TEXT
//
// MessageText:
//
// %1%0
//
#define MSG_LITERAL_TEXT                 0x00002371L

//
// MessageId: MSG_NOT_IMPLEMENTED
//
// MessageText:
//
// Command not implemented.
//
#define MSG_NOT_IMPLEMENTED              0x00002372L

//
// MessageId: MSG_DIR
//
// MessageText:
//
// <DIR>       %0
//
#define MSG_DIR                          0x00002373L

//
// MessageId: MSG_NO_MEMORY
//
// MessageText:
//
// Out of memory.
//
#define MSG_NO_MEMORY                    0x00002374L

//
// MessageId: MSG_INVALID_SWITCH
//
// MessageText:
//
// Invalid switch - "%1".
//
#define MSG_INVALID_SWITCH               0x00002375L

//
// MessageId: MSG_PARAMETER_FORMAT_NOT_CORRECT
//
// MessageText:
//
// Parameter format not correct - "%1".
//
#define MSG_PARAMETER_FORMAT_NOT_CORRECT 0x00002376L

//
// MessageId: MSG_ERROR_IN_DIRCMD
//
// MessageText:
//
// (Error occurred in environment variable)
//
#define MSG_ERROR_IN_DIRCMD              0x00002377L

//
// MessageId: MSG_FILES_COUNT_FREE
//
// MessageText:
//
//      %1 File(s) %2 bytes
//
#define MSG_FILES_COUNT_FREE             0x00002378L

//
// MessageId: MSG_FILES_TOTAL_FREE
//
// MessageText:
//
//      %1 Dir(s)  %2 bytes free
//
#define MSG_FILES_TOTAL_FREE             0x00002379L

//
// MessageId: MSG_FILE_TOTAL
//
// MessageText:
//
//      Total Files Listed:
//
#define MSG_FILE_TOTAL                   0x0000237AL

//
// MessageId: MSG_BATCH_TERM
//
// MessageText:
//
// Terminate batch job (Y/N)? %0
//
#define MSG_BATCH_TERM                   0x0000237BL

//
// MessageId: MSG_BAD_CURDIR
//
// MessageText:
//
// The current directory is invalid.
//
#define MSG_BAD_CURDIR                   0x0000237CL

//
// MessageId: MSG_HELP_CHDIR
//
// MessageText:
//
// Displays the name of or changes the current directory.
// 
// CHDIR [/D] [drive:][path]
// CHDIR [..]
// CD [/D] [drive:][path]
// CD [..]
// 
//   ..   Specifies that you want to change to the parent directory.
// 
// Type CD drive: to display the current directory in the specified drive.
// Type CD without parameters to display the current drive and directory.
// 
// Use the /D switch to change current drive in addition to changing current
// directory for a drive.
//
#define MSG_HELP_CHDIR                   0x0000237DL

//
// MessageId: MSG_HELP_CLS
//
// MessageText:
//
// Clears the screen.
// 
// CLS
//
#define MSG_HELP_CLS                     0x0000237EL

//
// MessageId: MSG_HELP_COPY
//
// MessageText:
//
// Copies one or more files to another location.
// 
// COPY [/D] [/V] [/N] [/Y | /-Y] [/Z] [/L] [/A | /B ] source [/A | /B]
//      [+ source [/A | /B] [+ ...]] [destination [/A | /B]]
// 
//   source       Specifies the file or files to be copied.
//   /A           Indicates an ASCII text file.
//   /B           Indicates a binary file.
//   /D           Allow the destination file to be created decrypted
//   destination  Specifies the directory and/or filename for the new file(s).
//   /V           Verifies that new files are written correctly.
//   /N           Uses short filename, if available, when copying a file with a
//                non-8dot3 name.
//   /Y           Suppresses prompting to confirm you want to overwrite an
//                existing destination file.
//   /-Y          Causes prompting to confirm you want to overwrite an
//                existing destination file.
//   /Z           Copies networked files in restartable mode.
//   /L           If the source is a symbolic link, copy the link to the target
//                instead of the actual file the source link points to.
// 
// The switch /Y may be preset in the COPYCMD environment variable.
// This may be overridden with /-Y on the command line.  Default is
// to prompt on overwrites unless COPY command is being executed from
// within a batch script.
// 
// To append files, specify a single file for destination, but multiple files
// for source (using wildcards or file1+file2+file3 format).
//
#define MSG_HELP_COPY                    0x0000237FL

//
// MessageId: MSG_HELP_DATE
//
// MessageText:
//
// Displays or sets the date.
// 
// DATE [/T | date]
// 
// Type DATE without parameters to display the current date setting and
// a prompt for a new one.  Press ENTER to keep the same date.
//
#define MSG_HELP_DATE                    0x00002380L

//
// MessageId: MSG_HELP_DEL_ERASE
//
// MessageText:
//
// Deletes one or more files.
// 
// DEL [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names
// ERASE [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names
// 
//   names         Specifies a list of one or more files or directories.
//                 Wildcards may be used to delete multiple files. If a
//                 directory is specified, all files within the directory
//                 will be deleted.
// 
//   /P            Prompts for confirmation before deleting each file.
//   /F            Force deleting of read-only files.
//   /S            Delete specified files from all subdirectories.
//   /Q            Quiet mode, do not ask if ok to delete on global wildcard
//   /A            Selects files to delete based on attributes
//   attributes    R  Read-only files            S  System files
//                 H  Hidden files               A  Files ready for archiving
//                 I  Not content indexed Files  L  Reparse Points
//                 O  Offline files              -  Prefix meaning not
//
#define MSG_HELP_DEL_ERASE               0x00002381L

//
// MessageId: MSG_HELP_DIR
//
// MessageText:
//
// Displays a list of files and subdirectories in a directory.
// 
// DIR [drive:][path][filename] [/A[[:]attributes]] [/B] [/C] [/D] [/L] [/N]
//   [/O[[:]sortorder]] [/P] [/Q] [/R] [/S] [/T[[:]timefield]] [/W] [/X] [/4]
// 
//   [drive:][path][filename]
//               Specifies drive, directory, and/or files to list.
// 
//   /A          Displays files with specified attributes.
//   attributes   D  Directories                R  Read-only files
//                H  Hidden files               A  Files ready for archiving
//                S  System files               I  Not content indexed files
//                L  Reparse Points             O  Offline files
//                -  Prefix meaning not
//   /B          Uses bare format (no heading information or summary).
//   /C          Display the thousand separator in file sizes.  This is the
//               default.  Use /-C to disable display of separator.
//   /D          Same as wide but files are list sorted by column.
//   /L          Uses lowercase.
//   /N          New long list format where filenames are on the far right.
//   /O          List by files in sorted order.
//   sortorder    N  By name (alphabetic)       S  By size (smallest first)
//                E  By extension (alphabetic)  D  By date/time (oldest first)
//                G  Group directories first    -  Prefix to reverse order
//   /P          Pauses after each screenful of information.
//   /Q          Display the owner of the file.
//   /R          Display alternate data streams of the file.
//   /S          Displays files in specified directory and all subdirectories.
//   /T          Controls which time field displayed or used for sorting
//   timefield   C  Creation
//               A  Last Access
//               W  Last Written
//   /W          Uses wide list format.
//   /X          This displays the short names generated for non-8dot3 file
//               names.  The format is that of /N with the short name inserted
//               before the long name. If no short name is present, blanks are
//               displayed in its place.
//   /4          Displays four-digit years
// 
// Switches may be preset in the DIRCMD environment variable.  Override
// preset switches by prefixing any switch with - (hyphen)--for example, /-W.
//
#define MSG_HELP_DIR                     0x00002382L

//
// MessageId: MSG_HELP_EXIT
//
// MessageText:
//
// Quits the CMD.EXE program (command interpreter) or the current batch
// script.
// 
// EXIT [/B] [exitCode]
// 
//   /B          specifies to exit the current batch script instead of
//               CMD.EXE.  If executed from outside a batch script, it
//               will quit CMD.EXE
// 
//   exitCode    specifies a numeric number.  if /B is specified, sets
//               ERRORLEVEL that number.  If quitting CMD.EXE, sets the process
//               exit code with that number.
//
#define MSG_HELP_EXIT                    0x00002383L

//
// MessageId: MSG_HELP_MKDIR
//
// MessageText:
//
// Creates a directory.
// 
// MKDIR [drive:]path
// MD [drive:]path
//
#define MSG_HELP_MKDIR                   0x00002384L

//
// MessageId: MSG_HELP_PATH
//
// MessageText:
//
// Displays or sets a search path for executable files.
// 
// PATH [[drive:]path[;...][;%%PATH%%]
// PATH ;
// 
// Type PATH ; to clear all search-path settings and direct cmd.exe to search
// only in the current directory.
// Type PATH without parameters to display the current path.
// Including %%PATH%% in the new path setting causes the old path to be
// appended to the new setting.
//
#define MSG_HELP_PATH                    0x00002385L

//
// MessageId: MSG_HELP_PROMPT
//
// MessageText:
//
// Changes the cmd.exe command prompt.
// 
// PROMPT [text]
// 
//   text    Specifies a new command prompt.
// 
// Prompt can be made up of normal characters and the following special codes:
// 
//   $A   & (Ampersand)
//   $B   | (pipe)
//   $C   ( (Left parenthesis)
//   $D   Current date
//   $E   Escape code (ASCII code 27)
//   $F   ) (Right parenthesis)
//   $G   > (greater-than sign)
//   $H   Backspace (erases previous character)
//   $L   < (less-than sign)
//   $N   Current drive
//   $P   Current drive and path
//   $Q   = (equal sign)
//   $S     (space)
//   $T   Current time
//   $V   Windows version number
//   $_   Carriage return and linefeed
//   $$   $ (dollar sign)
//
#define MSG_HELP_PROMPT                  0x00002386L

//
// MessageId: MSG_HELP_RMDIR
//
// MessageText:
//
// Removes (deletes) a directory.
// 
// RMDIR [/S] [/Q] [drive:]path
// RD [/S] [/Q] [drive:]path
// 
//     /S      Removes all directories and files in the specified directory
//             in addition to the directory itself.  Used to remove a directory
//             tree.
// 
//     /Q      Quiet mode, do not ask if ok to remove a directory tree with /S
//
#define MSG_HELP_RMDIR                   0x00002387L

//
// MessageId: MSG_HELP_RENAME
//
// MessageText:
//
// Renames a file or files.
// 
// RENAME [drive:][path]filename1 filename2.
// REN [drive:][path]filename1 filename2.
// 
// Note that you cannot specify a new drive or path for your destination file.
//
#define MSG_HELP_RENAME                  0x00002388L

//
// MessageId: MSG_HELP_SET
//
// MessageText:
//
// Displays, sets, or removes cmd.exe environment variables.
// 
// SET [variable=[string]]
// 
//   variable  Specifies the environment-variable name.
//   string    Specifies a series of characters to assign to the variable.
// 
// Type SET without parameters to display the current environment variables.
//
#define MSG_HELP_SET                     0x00002389L

//
// MessageId: MSG_HELP_TIME
//
// MessageText:
//
// Displays or sets the system time.
// 
// TIME [/T | time]
// 
// Type TIME with no parameters to display the current time setting and a prompt
// for a new one.  Press ENTER to keep the same time.
//
#define MSG_HELP_TIME                    0x0000238AL

//
// MessageId: MSG_HELP_TYPE
//
// MessageText:
//
// Displays the contents of a text file or files.
// 
// TYPE [drive:][path]filename
//
#define MSG_HELP_TYPE                    0x0000238BL

//
// MessageId: MSG_HELP_VER
//
// MessageText:
//
// Displays the Windows version.
// 
// VER
//
#define MSG_HELP_VER                     0x0000238CL

//
// MessageId: MSG_HELP_VERIFY
//
// MessageText:
//
// Tells cmd.exe whether to verify that your files are written correctly to a
// disk.
// 
// VERIFY [ON | OFF]
// 
// Type VERIFY without a parameter to display the current VERIFY setting.
//
#define MSG_HELP_VERIFY                  0x0000238DL

//
// MessageId: MSG_HELP_VOL
//
// MessageText:
//
// Displays the disk volume label and serial number, if they exist.
// 
// VOL [drive:]
//
#define MSG_HELP_VOL                     0x0000238EL

//
// MessageId: MSG_HELP_CALL
//
// MessageText:
//
// Calls one batch program from another.
// 
// CALL [drive:][path]filename [batch-parameters]
// 
//   batch-parameters   Specifies any command-line information required by the
//                      batch program.
//
#define MSG_HELP_CALL                    0x0000238FL

//
// MessageId: MSG_HELP_REM
//
// MessageText:
//
// Records comments (remarks) in a batch file or CONFIG.SYS.
// 
// REM [comment]
//
#define MSG_HELP_REM                     0x00002390L

//
// MessageId: MSG_HELP_PAUSE
//
// MessageText:
//
// Suspends processing of a batch program and displays the message
//     Press any key to continue . . . %0
// 
// PAUSE
//
#define MSG_HELP_PAUSE                   0x00002391L

//
// MessageId: MSG_HELP_ECHO
//
// MessageText:
//
// Displays messages, or turns command-echoing on or off.
// 
//   ECHO [ON | OFF]
//   ECHO [message]
// 
// Type ECHO without parameters to display the current echo setting.
//
#define MSG_HELP_ECHO                    0x00002392L

//
// MessageId: MSG_HELP_GOTO
//
// MessageText:
//
// Directs cmd.exe to a labeled line in a batch program.
// 
// GOTO label
// 
//   label   Specifies a text string used in the batch program as a label.
// 
// You type a label on a line by itself, beginning with a colon.
//
#define MSG_HELP_GOTO                    0x00002393L

//
// MessageId: MSG_HELP_SHIFT
//
// MessageText:
//
// Changes the position of replaceable parameters in a batch file.
// 
// SHIFT [/n]
//
#define MSG_HELP_SHIFT                   0x00002394L

//
// MessageId: MSG_HELP_IF
//
// MessageText:
//
// Performs conditional processing in batch programs.
// 
// IF [NOT] ERRORLEVEL number command
// IF [NOT] string1==string2 command
// IF [NOT] EXIST filename command
// 
//   NOT               Specifies that Windows should carry out
//                     the command only if the condition is false.
// 
//   ERRORLEVEL number Specifies a true condition if the last program run
//                     returned an exit code equal to or greater than the number
//                     specified.
// 
//   string1==string2  Specifies a true condition if the specified text strings
//                     match.
// 
//   EXIST filename    Specifies a true condition if the specified filename
//                     exists.
// 
//   command           Specifies the command to carry out if the condition is
//                     met.  Command can be followed by ELSE command which
//                     will execute the command after the ELSE keyword if the
//                     specified condition is FALSE
// 
// The ELSE clause must occur on the same line as the command after the IF.  For
// example:
// 
//     IF EXIST filename. (
//         del filename.
//     ) ELSE (
//         echo filename. missing.
//     )
// 
// The following would NOT work because the del command needs to be terminated
// by a newline:
// 
//     IF EXIST filename. del filename. ELSE echo filename. missing
// 
// Nor would the following work, since the ELSE command must be on the same line
// as the end of the IF command:
// 
//     IF EXIST filename. del filename.
//     ELSE echo filename. missing
// 
// The following would work if you want it all on one line:
// 
//     IF EXIST filename. (del filename.) ELSE echo filename. missing
//
#define MSG_HELP_IF                      0x00002395L

//
// MessageId: MSG_HELP_FOR
//
// MessageText:
//
// Runs a specified command for each file in a set of files.
// 
// FOR %%variable IN (set) DO command [command-parameters]
// 
//   %%variable  Specifies a single letter replaceable parameter.
//   (set)      Specifies a set of one or more files.  Wildcards may be used.
//   command    Specifies the command to carry out for each file.
//   command-parameters
//              Specifies parameters or switches for the specified command.
// 
// To use the FOR command in a batch program, specify %%%%variable instead
// of %%variable.  Variable names are case sensitive, so %%i is different
// from %%I.
//
#define MSG_HELP_FOR                     0x00002396L

//
// MessageId: MSG_HELP_START
//
// MessageText:
//
// Starts a separate window to run a specified program or command.
// 
// START ["title"] [/D path] [/I] [/MIN] [/MAX] [/SEPARATE | /SHARED]
//       [/LOW | /NORMAL | /HIGH | /REALTIME | /ABOVENORMAL | /BELOWNORMAL]
//       [/NODE <NUMA node>] [/AFFINITY <hex affinity mask>] [/WAIT] [/B]
//       [command/program] [parameters]
// 
//     "title"     Title to display in window title bar.
//     path        Starting directory.
//     B           Start application without creating a new window. The
//                 application has ^C handling ignored. Unless the application
//                 enables ^C processing, ^Break is the only way to interrupt
//                 the application.
//     I           The new environment will be the original environment passed
//                 to the cmd.exe and not the current environment.
//     MIN         Start window minimized.
//     MAX         Start window maximized.
//     SEPARATE    Start 16-bit Windows program in separate memory space.
//     SHARED      Start 16-bit Windows program in shared memory space.
//     LOW         Start application in the IDLE priority class.
//     NORMAL      Start application in the NORMAL priority class.
//     HIGH        Start application in the HIGH priority class.
//     REALTIME    Start application in the REALTIME priority class.
//     ABOVENORMAL Start application in the ABOVENORMAL priority class.
//     BELOWNORMAL Start application in the BELOWNORMAL priority class.
//     NODE        Specifies the preferred Non-Uniform Memory Architecture (NUMA)
//                 node as a decimal integer.
//     AFFINITY    Specifies the processor affinity mask as a hexadecimal number.
//                 The process is restricted to running on these processors.
// 
//                 The affinity mask is interpreted differently when /AFFINITY and
//                 /NODE are combined.  Specify the affinity mask as if the NUMA
//                 node's processor mask is right shifted to begin at bit zero.
//                 The process is restricted to running on those processors in
//                 common between the specified affinity mask and the NUMA node.
//                 If no processors are in common, the process is restricted to
//                 running on the specified NUMA node.
//     WAIT        Start application and wait for it to terminate.
//     command/program
//                 If it is an internal cmd command or a batch file then
//                 the command processor is run with the /K switch to cmd.exe.
//                 This means that the window will remain after the command
//                 has been run.
// 
//                 If it is not an internal cmd command or batch file then
//                 it is a program and will run as either a windowed application
//                 or a console application.
// 
//     parameters  These are the parameters passed to the command/program.
// 
// NOTE: The SEPARATE and SHARED options are not supported on 64-bit platforms.
// 
// Specifying /NODE allows processes to be created in a way that leverages memory
// locality on NUMA systems.  For example, two processes that communicate with
// each other heavily through shared memory can be created to share the same
// preferred NUMA node in order to minimize memory latencies.  They allocate
// memory from the same NUMA node when possible, and they are free to run on
// processors outside the specified node.
// 
//     start /NODE 1 application1.exe
//     start /NODE 1 application2.exe
// 
// These two processes can be further constrained to run on specific processors
// within the same NUMA node.  In the following example, application1 runs on the
// low-order two processors of the node, while application2 runs on the next two
// processors of the node.  This example assumes the specified node has at least
// four logical processors.  Note that the node number can be changed to any valid
// node number for that computer without having to change the affinity mask.
// 
//     start /NODE 1 /AFFINITY 0x3 application1.exe
//     start /NODE 1 /AFFINITY 0xc application2.exe
//
#define MSG_HELP_START                   0x00002397L

//
// MessageId: MSG_HELP_BREAK
//
// MessageText:
//
// Sets or Clears Extended CTRL+C checking on DOS system
// 
// This is present for Compatibility with DOS systems. It has no effect
// under Windows.
//
#define MSG_HELP_BREAK                   0x00002398L

//
// MessageId: MSG_HELP_CMD
//
// MessageText:
//
// Starts a new instance of the Windows command interpreter
// 
// CMD [/A | /U] [/Q] [/D] [/E:ON | /E:OFF] [/F:ON | /F:OFF] [/V:ON | /V:OFF]
//     [[/S] [/C | /K] string]
// 
// /C      Carries out the command specified by string and then terminates
// /K      Carries out the command specified by string but remains
// /S      Modifies the treatment of string after /C or /K (see below)
// /Q      Turns echo off
// /D      Disable execution of AutoRun commands from registry (see below)
// /A      Causes the output of internal commands to a pipe or file to be ANSI
// /U      Causes the output of internal commands to a pipe or file to be
//         Unicode
// /T:fg   Sets the foreground/background colors (see COLOR /? for more info)
// /E:ON   Enable command extensions (see below)
// /E:OFF  Disable command extensions (see below)
// /F:ON   Enable file and directory name completion characters (see below)
// /F:OFF  Disable file and directory name completion characters (see below)
// /V:ON   Enable delayed environment variable expansion using ! as the
//         delimiter. For example, /V:ON would allow !var! to expand the
//         variable var at execution time.  The %var% syntax expands variables
//         at input time, which is quite a different thing when inside of a FOR
//         loop.
// /V:OFF  Disable delayed environment expansion.
// 
// Note that multiple commands separated by the command separator '&&'
// are accepted for string if surrounded by quotes.  Also, for compatibility
// reasons, /X is the same as /E:ON, /Y is the same as /E:OFF and /R is the
// same as /C.  Any other switches are ignored.
// 
// If /C or /K is specified, then the remainder of the command line after
// the switch is processed as a command line, where the following logic is
// used to process quote (") characters:
// 
//     1.  If all of the following conditions are met, then quote characters
//         on the command line are preserved:
// 
//         - no /S switch
//         - exactly two quote characters
//         - no special characters between the two quote characters,
//           where special is one of: &<>()@^|
//         - there are one or more whitespace characters between the
//           two quote characters
//         - the string between the two quote characters is the name
//           of an executable file.
// 
//     2.  Otherwise, old behavior is to see if the first character is
//         a quote character and if so, strip the leading character and
//         remove the last quote character on the command line, preserving
//         any text after the last quote character.
// 
//
#define MSG_HELP_CMD                     0x00002399L

//
// MessageId: MSG_HELP_CMD1
//
// MessageText:
//
// If /D was NOT specified on the command line, then when CMD.EXE starts, it
// looks for the following REG_SZ/REG_EXPAND_SZ registry variables, and if
// either or both are present, they are executed first.
// 
//     HKEY_LOCAL_MACHINE\Software\Microsoft\Command Processor\AutoRun
// 
//         and/or
// 
//     HKEY_CURRENT_USER\Software\Microsoft\Command Processor\AutoRun
//
#define MSG_HELP_CMD1                    0x0000239AL

//
// MessageId: MSG_HELP_CMD_EXTENSIONS
//
// MessageText:
//
// 
// Command Extensions are enabled by default.  You may also disable
// extensions for a particular invocation by using the /E:OFF switch.  You
// can enable or disable extensions for all invocations of CMD.EXE on a
// machine and/or user logon session by setting either or both of the
// following REG_DWORD values in the registry using REGEDIT.EXE:
// 
//     HKEY_LOCAL_MACHINE\Software\Microsoft\Command Processor\EnableExtensions
// 
//         and/or
// 
//     HKEY_CURRENT_USER\Software\Microsoft\Command Processor\EnableExtensions
// 
// to either 0x1 or 0x0.  The user specific setting takes precedence over
// the machine setting.  The command line switches take precedence over the
// registry settings.
// 
// In a batch file, the SETLOCAL ENABLEEXTENSIONS or DISABLEEXTENSIONS arguments
// takes precedence over the /E:ON or /E:OFF switch. See SETLOCAL /? for details.
// 
// The command extensions involve changes and/or additions to the following
// commands:
// 
//     DEL or ERASE
//     COLOR
//     CD or CHDIR
//     MD or MKDIR
//     PROMPT
//     PUSHD
//     POPD
//     SET
//     SETLOCAL
//     ENDLOCAL
//     IF
//     FOR
//     CALL
//     SHIFT
//     GOTO
//     START (also includes changes to external command invocation)
//     ASSOC
//     FTYPE
// 
// To get specific details, type commandname /? to view the specifics.
//
#define MSG_HELP_CMD_EXTENSIONS          0x0000239BL

//
// MessageId: MSG_HELP_CMD_EXTENSIONS1
//
// MessageText:
//
// 
// Delayed environment variable expansion is NOT enabled by default.  You
// can enable or disable delayed environment variable expansion for a
// particular invocation of CMD.EXE with the /V:ON or /V:OFF switch.  You
// can enable or disable delayed expansion for all invocations of CMD.EXE on a
// machine and/or user logon session by setting either or both of the
// following REG_DWORD values in the registry using REGEDIT.EXE:
// 
//     HKEY_LOCAL_MACHINE\Software\Microsoft\Command Processor\DelayedExpansion
// 
//         and/or
// 
//     HKEY_CURRENT_USER\Software\Microsoft\Command Processor\DelayedExpansion
// 
// to either 0x1 or 0x0.  The user specific setting takes precedence over
// the machine setting.  The command line switches take precedence over the
// registry settings.
// 
// In a batch file the SETLOCAL ENABLEDELAYEDEXPANSION or DISABLEDELAYEDEXPANSION
// arguments takes precedence over the /V:ON or /V:OFF switch. See SETLOCAL /?
// for details.
// 
// If delayed environment variable expansion is enabled, then the exclamation
// character can be used to substitute the value of an environment variable
// at execution time.
//
#define MSG_HELP_CMD_EXTENSIONS1         0x0000239CL

//
// MessageId: MSG_HELP_CMD_COMPLETION1
//
// MessageText:
//
// 
// You can enable or disable file name completion for a particular
// invocation of CMD.EXE with the /F:ON or /F:OFF switch.  You can enable
// or disable completion for all invocations of CMD.EXE on a machine and/or
// user logon session by setting either or both of the following REG_DWORD
// values in the registry using REGEDIT.EXE:
// 
//     HKEY_LOCAL_MACHINE\Software\Microsoft\Command Processor\CompletionChar
//     HKEY_LOCAL_MACHINE\Software\Microsoft\Command Processor\PathCompletionChar
// 
//         and/or
// 
//     HKEY_CURRENT_USER\Software\Microsoft\Command Processor\CompletionChar
//     HKEY_CURRENT_USER\Software\Microsoft\Command Processor\PathCompletionChar
// 
// with the hex value of a control character to use for a particular
// function (e.g.  0x4 is Ctrl-D and 0x6 is Ctrl-F).  The user specific
// settings take precedence over the machine settings.  The command line
// switches take precedence over the registry settings.
// 
// If completion is enabled with the /F:ON switch, the two control
// characters used are Ctrl-D for directory name completion and Ctrl-F for
// file name completion.  To disable a particular completion character in
// the registry, use the value for space (0x20) as it is not a valid
// control character.
//
#define MSG_HELP_CMD_COMPLETION1         0x0000239DL

//
// MessageId: MSG_HELP_CMD_COMPLETION2
//
// MessageText:
//
// 
// Completion is invoked when you type either of the two control
// characters.  The completion function takes the path string to the left
// of the cursor appends a wild card character to it if none is already
// present and builds up a list of paths that match.  It then displays the
// first matching path.  If no paths match, it just beeps and leaves the
// display alone.  Thereafter, repeated pressing of the same control
// character will cycle through the list of matching paths.  Pressing the
// Shift key with the control character will move through the list
// backwards.  If you edit the line in any way and press the control
// character again, the saved list of matching paths is discarded and a new
// one generated.  The same occurs if you switch between file and directory
// name completion.  The only difference between the two control characters
// is the file completion character matches both file and directory names,
// while the directory completion character only matches directory names.
// If file completion is used on any of the built in directory commands
// (CD, MD or RD) then directory completion is assumed.
// 
// The completion code deals correctly with file names that contain spaces
// or other special characters by placing quotes around the matching path.
// Also, if you back up, then invoke completion from within a line, the
// text to the right of the cursor at the point completion was invoked is
// discarded.
// 
// The special characters that require quotes are:
//      <space>
//      &()[]{}^=;!%'+,`~
//
#define MSG_HELP_CMD_COMPLETION2         0x0000239EL

//
// MessageId: MSG_EXT_ENABLED
//
// MessageText:
//
// Command Processor Extensions Enabled
//
#define MSG_EXT_ENABLED                  0x0000239FL

//
// MessageId: MSG_EXT_ENABLED_BY_DEFAULT
//
// MessageText:
//
// Command Processor Extensions enabled by default.  Use CMD /? for details.
//
#define MSG_EXT_ENABLED_BY_DEFAULT       0x000023A0L

//
// MessageId: MSG_FILE_DELETED
//
// MessageText:
//
// Deleted file - %1
//
#define MSG_FILE_DELETED                 0x000023A1L

//
// MessageId: MSG_HELP_ASSOC
//
// MessageText:
//
// Displays or modifies file extension associations
// 
// ASSOC [.ext[=[fileType]]]
// 
//   .ext      Specifies the file extension to associate the file type with
//   fileType  Specifies the file type to associate with the file extension
// 
// Type ASSOC without parameters to display the current file associations.
// If ASSOC is invoked with just a file extension, it displays the current
// file association for that file extension.  Specify nothing for the file
// type and the command will delete the association for the file extension.
//
#define MSG_HELP_ASSOC                   0x000023A2L

//
// MessageId: MSG_ASSOC_NOT_FOUND
//
// MessageText:
//
// File association not found for extension %1
//
#define MSG_ASSOC_NOT_FOUND              0x000023A3L

//
// MessageId: MSG_HELP_FTYPE
//
// MessageText:
//
// Displays or modifies file types used in file extension associations
// 
// FTYPE [fileType[=[openCommandString]]]
// 
//   fileType  Specifies the file type to examine or change
//   openCommandString Specifies the open command to use when launching files
//                     of this type.
// 
// Type FTYPE without parameters to display the current file types that
// have open command strings defined.  FTYPE is invoked with just a file
// type, it displays the current open command string for that file type.
// Specify nothing for the open command string and the FTYPE command will
// delete the open command string for the file type.  Within an open
// command string %%0 or %%1 are substituted with the file name being
// launched through the assocation.  %%* gets all the parameters and %%2
// gets the 1st parameter, %%3 the second, etc.  %%~n gets all the remaining
// parameters starting with the nth parameter, where n may be between 2 and 9,
// inclusive.  For example:
// 
//     ASSOC .pl=PerlScript
//     FTYPE PerlScript=perl.exe %%1 %%*
// 
// would allow you to invoke a Perl script as follows:
// 
//     script.pl 1 2 3
// 
// If you want to eliminate the need to type the extensions, then do the
// following:
// 
//     set PATHEXT=.pl;%%PATHEXT%%
// 
// and the script could be invoked as follows:
// 
//     script 1 2 3
//
#define MSG_HELP_FTYPE                   0x000023A4L

//
// MessageId: MSG_FTYPE_NOT_FOUND
//
// MessageText:
//
// File type '%1' not found or no open command associated with it.
//
#define MSG_FTYPE_NOT_FOUND              0x000023A5L

//
// MessageId: MSG_SETLOCAL_BAD_ARG
//
// MessageText:
//
// Invalid parameter to SETLOCAL command
//
#define MSG_SETLOCAL_BAD_ARG             0x000023A6L

//
// MessageId: MSG_NO_COPYFILEEX
//
// MessageText:
//
// The restartable option to the COPY command is not supported by
// this version of the operating system.
//
#define MSG_NO_COPYFILEEX                0x000023A7L

//
// MessageId: MSG_PATH_OPERATOR_INVALID
//
// MessageText:
//
// The following usage of the path operator in batch-parameter
// substitution is invalid: %1
// 
// For valid formats type CALL /? or FOR /?
//
#define MSG_PATH_OPERATOR_INVALID        0x000023A8L

//
// MessageId: MSG_ENV_VAR_NOT_FOUND
//
// MessageText:
//
// Environment variable %1 not defined
//
#define MSG_ENV_VAR_NOT_FOUND            0x000023A9L

//
// MessageId: MSG_CALL_LABEL_INVALID
//
// MessageText:
//
// Invalid attempt to call batch label outside of batch script.
//
#define MSG_CALL_LABEL_INVALID           0x000023AAL

//
// MessageId: MSG_MISSING_BAT_LABEL
//
// MessageText:
//
// The system cannot find the batch label specified - %1
//
#define MSG_MISSING_BAT_LABEL            0x000023ABL

//
// MessageId: MSG_UNICODE_NOT_SUPPORTED
//
// MessageText:
//
// The unicode output option to CMD.EXE is not supported by this
// version of the operating system.
//
#define MSG_UNICODE_NOT_SUPPORTED        0x000023ACL

//
// MessageId: MSG_HELP_DEL_ERASE_X
//
// MessageText:
//
// 
// If Command Extensions are enabled DEL and ERASE change as follows:
// 
// The display semantics of the /S switch are reversed in that it shows
// you only the files that are deleted, not the ones it could not find.
//
#define MSG_HELP_DEL_ERASE_X             0x000023ADL

//
// MessageId: MSG_HELP_CHDIR_X
//
// MessageText:
//
// 
// If Command Extensions are enabled CHDIR changes as follows:
// 
// The current directory string is converted to use the same case as
// the on disk names.  So CD C:\TEMP would actually set the current
// directory to C:\Temp if that is the case on disk.
// 
// CHDIR command does not treat spaces as delimiters, so it is possible to
// CD into a subdirectory name that contains a space without surrounding
// the name with quotes.  For example:
// 
//     cd \winnt\profiles\username\programs\start menu
// 
// is the same as:
// 
//     cd "\winnt\profiles\username\programs\start menu"
// 
// which is what you would have to type if extensions were disabled.
//
#define MSG_HELP_CHDIR_X                 0x000023AEL

//
// MessageId: MSG_HELP_MKDIR_X
//
// MessageText:
//
// 
// If Command Extensions are enabled MKDIR changes as follows:
// 
// MKDIR creates any intermediate directories in the path, if needed.
// For example, assume \a does not exist then:
// 
//     mkdir \a\b\c\d
// 
// is the same as:
// 
//     mkdir \a
//     chdir \a
//     mkdir b
//     chdir b
//     mkdir c
//     chdir c
//     mkdir d
// 
// which is what you would have to type if extensions were disabled.
//
#define MSG_HELP_MKDIR_X                 0x000023AFL

//
// MessageId: MSG_HELP_DATE_X
//
// MessageText:
//
// 
// If Command Extensions are enabled the DATE command supports
// the /T switch which tells the command to just output the
// current date, without prompting for a new date.
//
#define MSG_HELP_DATE_X                  0x000023B0L

//
// MessageId: MSG_HELP_TIME_X
//
// MessageText:
//
// 
// If Command Extensions are enabled the TIME command supports
// the /T switch which tells the command to just output the
// current time, without prompting for a new time.
//
#define MSG_HELP_TIME_X                  0x000023B1L

//
// MessageId: MSG_HELP_PROMPT_X
//
// MessageText:
//
// 
// If Command Extensions are enabled the PROMPT command supports
// the following additional formatting characters:
// 
//   $+   zero or more plus sign (+) characters depending upon the
//        depth of the PUSHD directory stack, one character for each
//        level pushed.
// 
//   $M   Displays the remote name associated with the current drive
//        letter or the empty string if current drive is not a network
//        drive.
//
#define MSG_HELP_PROMPT_X                0x000023B2L

//
// MessageId: MSG_HELP_PUSHDIR_X
//
// MessageText:
//
// 
// If Command Extensions are enabled the PUSHD command accepts
// network paths in addition to the normal drive letter and path.
// If a network path is specified, PUSHD will create a temporary
// drive letter that points to that specified network resource and
// then change the current drive and directory, using the newly
// defined drive letter.  Temporary drive letters are allocated from
// Z: on down, using the first unused drive letter found.
//
#define MSG_HELP_PUSHDIR_X               0x000023B3L

//
// MessageId: MSG_HELP_POPDIR_X
//
// MessageText:
//
// 
// If Command Extensions are enabled the POPD command will delete
// any temporary drive letter created by PUSHD when you POPD that
// drive off the pushed directory stack.
//
#define MSG_HELP_POPDIR_X                0x000023B4L

//
// MessageId: MSG_HELP_SET_X
//
// MessageText:
//
// 
// If Command Extensions are enabled SET changes as follows:
// 
// SET command invoked with just a variable name, no equal sign or value
// will display the value of all variables whose prefix matches the name
// given to the SET command.  For example:
// 
//     SET P
// 
// would display all variables that begin with the letter 'P'
// 
// SET command will set the ERRORLEVEL to 1 if the variable name is not
// found in the current environment.
// 
// SET command will not allow an equal sign to be part of the name of
// a variable.
// 
// Two new switches have been added to the SET command:
// 
//     SET /A expression
//     SET /P variable=[promptString]
// 
// The /A switch specifies that the string to the right of the equal sign
// is a numerical expression that is evaluated.  The expression evaluator
// is pretty simple and supports the following operations, in decreasing
// order of precedence:
// 
//     ()                  - grouping
//     ! ~ -               - unary operators
//     * / %%               - arithmetic operators
//     + -                 - arithmetic operators
//     << >>               - logical shift
//     &                   - bitwise and
//     ^                   - bitwise exclusive or
//     |                   - bitwise or
//     = *= /= %%= += -=    - assignment
//       &= ^= |= <<= >>=
//     ,                   - expression separator
// 
// If you use any of the logical or modulus operators, you will need to
// enclose the expression string in quotes.  Any non-numeric strings in the
// expression are treated as environment variable names whose values are
// converted to numbers before using them.  If an environment variable name
// is specified but is not defined in the current environment, then a value
// of zero is used.  This allows you to do arithmetic with environment
// variable values without having to type all those %% signs to get their
// values.  If SET /A is executed from the command line outside of a
// command script, then it displays the final value of the expression.  The
// assignment operator requires an environment variable name to the left of
// the assignment operator.  Numeric values are decimal numbers, unless
// prefixed by 0x for hexadecimal numbers, and 0 for octal numbers.
// So 0x12 is the same as 18 is the same as 022. Please note that the octal
// notation can be confusing: 08 and 09 are not valid numbers because 8 and
// 9 are not valid octal digits.
//
#define MSG_HELP_SET_X                   0x000023B5L

//
// MessageId: MSG_HELP_SET_X1
//
// MessageText:
//
// 
// The /P switch allows you to set the value of a variable to a line of input
// entered by the user.  Displays the specified promptString before reading
// the line of input.  The promptString can be empty.
// 
// Environment variable substitution has been enhanced as follows:
// 
//     %%PATH:str1=str2%%
// 
// would expand the PATH environment variable, substituting each occurrence
// of "str1" in the expanded result with "str2".  "str2" can be the empty
// string to effectively delete all occurrences of "str1" from the expanded
// output.  "str1" can begin with an asterisk, in which case it will match
// everything from the beginning of the expanded output to the first
// occurrence of the remaining portion of str1.
// 
// May also specify substrings for an expansion.
// 
//     %%PATH:~10,5%%
// 
// would expand the PATH environment variable, and then use only the 5
// characters that begin at the 11th (offset 10) character of the expanded
// result.  If the length is not specified, then it defaults to the
// remainder of the variable value.  If either number (offset or length) is
// negative, then the number used is the length of the environment variable
// value added to the offset or length specified.
// 
//     %%PATH:~-10%%
// 
// would extract the last 10 characters of the PATH variable.
// 
//     %%PATH:~0,-2%%
// 
// would extract all but the last 2 characters of the PATH variable.
//
#define MSG_HELP_SET_X1                  0x000023B6L

//
// MessageId: MSG_HELP_SET_X2
//
// MessageText:
//
// 
// Finally, support for delayed environment variable expansion has been
// added.  This support is always disabled by default, but may be
// enabled/disabled via the /V command line switch to CMD.EXE.  See CMD /?
// 
// Delayed environment variable expansion is useful for getting around
// the limitations of the current expansion which happens when a line
// of text is read, not when it is executed.  The following example
// demonstrates the problem with immediate variable expansion:
// 
//     set VAR=before
//     if "%%VAR%%" == "before" (
//         set VAR=after
//         if "%%VAR%%" == "after" @echo If you see this, it worked
//     )
// 
// would never display the message, since the %%VAR%% in BOTH IF statements
// is substituted when the first IF statement is read, since it logically
// includes the body of the IF, which is a compound statement.  So the
// IF inside the compound statement is really comparing "before" with
// "after" which will never be equal.  Similarly, the following example
// will not work as expected:
// 
//     set LIST=
//     for %%i in (*) do set LIST=%%LIST%% %%i
//     echo %%LIST%%
// 
// in that it will NOT build up a list of files in the current directory,
// but instead will just set the LIST variable to the last file found.
// Again, this is because the %%LIST%% is expanded just once when the
// FOR statement is read, and at that time the LIST variable is empty.
// So the actual FOR loop we are executing is:
// 
//     for %%i in (*) do set LIST= %%i
// 
// which just keeps setting LIST to the last file found.
// 
// Delayed environment variable expansion allows you to use a different
// character (the exclamation mark) to expand environment variables at
// execution time.  If delayed variable expansion is enabled, the above
// examples could be written as follows to work as intended:
// 
//     set VAR=before
//     if "%%VAR%%" == "before" (
//         set VAR=after
//         if "!VAR!" == "after" @echo If you see this, it worked
//     )
// 
//     set LIST=
//     for %%i in (*) do set LIST=!LIST! %%i
//     echo %%LIST%%
//
#define MSG_HELP_SET_X2                  0x000023B7L

//
// MessageId: MSG_HELP_SET_X3
//
// MessageText:
//
// 
// If Command Extensions are enabled, then there are several dynamic
// environment variables that can be expanded but which don't show up in
// the list of variables displayed by SET.  These variable values are
// computed dynamically each time the value of the variable is expanded.
// If the user explicitly defines a variable with one of these names, then
// that definition will override the dynamic one described below:
// 
// %%CD%% - expands to the current directory string.
// 
// %%DATE%% - expands to current date using same format as DATE command.
// 
// %%TIME%% - expands to current time using same format as TIME command.
// 
// %%RANDOM%% - expands to a random decimal number between 0 and 32767.
// 
// %%ERRORLEVEL%% - expands to the current ERRORLEVEL value
// 
// %%CMDEXTVERSION%% - expands to the current Command Processor Extensions
//     version number.
// 
// %%CMDCMDLINE%% - expands to the original command line that invoked the
//     Command Processor.
// 
// %%HIGHESTNUMANODENUMBER%% - expands to the highest NUMA node number
//     on this machine.
//
#define MSG_HELP_SET_X3                  0x000023B8L

//
// MessageId: MSG_HELP_GOTO_X
//
// MessageText:
//
// 
// If Command Extensions are enabled GOTO changes as follows:
// 
// GOTO command now accepts a target label of :EOF which transfers control
// to the end of the current batch script file.  This is an easy way to
// exit a batch script file without defining a label.  Type CALL /?  for a
// description of extensions to the CALL command that make this feature
// useful.
//
#define MSG_HELP_GOTO_X                  0x000023B9L

//
// MessageId: MSG_HELP_SHIFT_X
//
// MessageText:
//
// 
// If Command Extensions are enabled the SHIFT command supports
// the /n switch which tells the command to start shifting at the
// nth argument, where n may be between zero and eight.  For example:
// 
//     SHIFT /2
// 
// would shift %%3 to %%2, %%4 to %%3, etc. and leave %%0 and %%1 unaffected.
//
#define MSG_HELP_SHIFT_X                 0x000023BAL

//
// MessageId: MSG_HELP_CALL_X
//
// MessageText:
//
// 
// If Command Extensions are enabled CALL changes as follows:
// 
// CALL command now accepts labels as the target of the CALL.  The syntax
// is:
// 
//     CALL :label arguments
// 
// A new batch file context is created with the specified arguments and
// control is passed to the statement after the label specified.  You must
// "exit" twice by reaching the end of the batch script file twice.  The
// first time you read the end, control will return to just after the CALL
// statement.  The second time will exit the batch script.  Type GOTO /?
// for a description of the GOTO :EOF extension that will allow you to
// "return" from a batch script.
// 
// In addition, expansion of batch script argument references (%%0, %%1,
// etc.) have been changed as follows:
// 
// 
//     %%* in a batch script refers to all the arguments (e.g. %%1 %%2 %%3
//         %%4 %%5 ...)
// 
//     Substitution of batch parameters (%%n) has been enhanced.  You can
//     now use the following optional syntax:
// 
//         %%~1         - expands %%1 removing any surrounding quotes (")
//         %%~f1        - expands %%1 to a fully qualified path name
//         %%~d1        - expands %%1 to a drive letter only
//         %%~p1        - expands %%1 to a path only
//         %%~n1        - expands %%1 to a file name only
//         %%~x1        - expands %%1 to a file extension only
//         %%~s1        - expanded path contains short names only
//         %%~a1        - expands %%1 to file attributes
//         %%~t1        - expands %%1 to date/time of file
//         %%~z1        - expands %%1 to size of file
//         %%~$PATH:1   - searches the directories listed in the PATH
//                        environment variable and expands %%1 to the fully
//                        qualified name of the first one found.  If the
//                        environment variable name is not defined or the
//                        file is not found by the search, then this
//                        modifier expands to the empty string
//
#define MSG_HELP_CALL_X                  0x000023BBL

//
// MessageId: MSG_HELP_CALL_X1
//
// MessageText:
//
// 
//     The modifiers can be combined to get compound results:
// 
//         %%~dp1       - expands %%1 to a drive letter and path only
//         %%~nx1       - expands %%1 to a file name and extension only
//         %%~dp$PATH:1 - searches the directories listed in the PATH
//                        environment variable for %%1 and expands to the
//                        drive letter and path of the first one found.
//         %%~ftza1     - expands %%1 to a DIR like output line
// 
//     In the above examples %%1 and PATH can be replaced by other
//     valid values.  The %%~ syntax is terminated by a valid argument
//     number.  The %%~ modifiers may not be used with %%*
//
#define MSG_HELP_CALL_X1                 0x000023BCL

//
// MessageId: MSG_HELP_SETLOCAL_X
//
// MessageText:
//
// 
// If Command Extensions are enabled SETLOCAL changes as follows:
// 
// SETLOCAL batch command now accepts optional arguments:
//         ENABLEEXTENSIONS / DISABLEEXTENSIONS
//             enable or disable command processor extensions. These
//             arguments takes precedence over the CMD /E:ON or /E:OFF
//             switches. See CMD /? for details.
//         ENABLEDELAYEDEXPANSION / DISABLEDELAYEDEXPANSION
//             enable or disable delayed environment variable
//             expansion. These arguments takes precedence over the CMD
//             /V:ON or /V:OFF switches. See CMD /? for details.
// These modifications last until the matching ENDLOCAL command,
// regardless of their setting prior to the SETLOCAL command.
// 
// The SETLOCAL command will set the ERRORLEVEL value if given
// an argument.  It will be zero if one of the two valid arguments
// is given and one otherwise.  You can use this in batch scripts
// to determine if the extensions are available, using the following
// technique:
// 
//     VERIFY OTHER 2>nul
//     SETLOCAL ENABLEEXTENSIONS
//     IF ERRORLEVEL 1 echo Unable to enable extensions
// 
// This works because on old versions of CMD.EXE, SETLOCAL does NOT
// set the ERRORLEVEL value. The VERIFY command with a bad argument
// initializes the ERRORLEVEL value to a non-zero value.
//
#define MSG_HELP_SETLOCAL_X              0x000023BDL

//
// MessageId: MSG_HELP_ENDLOCAL_X
//
// MessageText:
//
// 
// If Command Extensions are enabled ENDLOCAL changes as follows:
// 
// If the corresponding SETLOCAL enable or disabled command extensions
// using the new ENABLEEXTENSIONS or DISABLEEXTENSIONS options, then
// after the ENDLOCAL, the enabled/disabled state of command extensions
// will be restored to what it was prior to the matching SETLOCAL
// command execution.
//
#define MSG_HELP_ENDLOCAL_X              0x000023BEL

//
// MessageId: MSG_HELP_START_X
//
// MessageText:
//
// 
// If Command Extensions are enabled, external command invocation
// through the command line or the START command changes as follows:
// 
// non-executable files may be invoked through their file association just
//     by typing the name of the file as a command.  (e.g.  WORD.DOC would
//     launch the application associated with the .DOC file extension).
//     See the ASSOC and FTYPE commands for how to create these
//     associations from within a command script.
// 
// When executing an application that is a 32-bit GUI application, CMD.EXE
//     does not wait for the application to terminate before returning to
//     the command prompt.  This new behavior does NOT occur if executing
//     within a command script.
// 
// When executing a command line whose first token is the string "CMD "
//     without an extension or path qualifier, then "CMD" is replaced with
//     the value of the COMSPEC variable.  This prevents picking up CMD.EXE
//     from the current directory.
// 
// When executing a command line whose first token does NOT contain an
//     extension, then CMD.EXE uses the value of the PATHEXT
//     environment variable to determine which extensions to look for
//     and in what order.  The default value for the PATHEXT variable
//     is:
// 
//         .COM;.EXE;.BAT;.CMD
// 
//     Notice the syntax is the same as the PATH variable, with
//     semicolons separating the different elements.
// 
// When searching for an executable, if there is no match on any extension,
// then looks to see if the name matches a directory name.  If it does, the
// START command launches the Explorer on that path.  If done from the
// command line, it is the equivalent to doing a CD /D to that path.
//
#define MSG_HELP_START_X                 0x000023BFL

//
// MessageId: MSG_HELP_BREAK_X
//
// MessageText:
//
// 
// If Command Extensions are enabled, and running on the Windows
// platform, then the BREAK command will enter a hard coded breakpoint
// if being debugged by a debugger.
//
#define MSG_HELP_BREAK_X                 0x000023C0L

//
// MessageId: MSG_HELP_FOR_X
//
// MessageText:
//
// 
// If Command Extensions are enabled, the following additional
// forms of the FOR command are supported:
// 
// FOR /D %%variable IN (set) DO command [command-parameters]
// 
//     If set contains wildcards, then specifies to match against directory
//     names instead of file names.
// 
// FOR /R [[drive:]path] %%variable IN (set) DO command [command-parameters]
// 
//     Walks the directory tree rooted at [drive:]path, executing the FOR
//     statement in each directory of the tree.  If no directory
//     specification is specified after /R then the current directory is
//     assumed.  If set is just a single period (.) character then it
//     will just enumerate the directory tree.
// 
// FOR /L %%variable IN (start,step,end) DO command [command-parameters]
// 
//     The set is a sequence of numbers from start to end, by step amount.
//     So (1,1,5) would generate the sequence 1 2 3 4 5 and (5,-1,1) would
//     generate the sequence (5 4 3 2 1)
// 
// FOR /F ["options"] %%variable IN (file-set) DO command [command-parameters]
// FOR /F ["options"] %%variable IN ("string") DO command [command-parameters]
// FOR /F ["options"] %%variable IN ('command') DO command [command-parameters]
// 
//     or, if usebackq option present:
// 
// FOR /F ["options"] %%variable IN (file-set) DO command [command-parameters]
// FOR /F ["options"] %%variable IN ('string') DO command [command-parameters]
// FOR /F ["options"] %%variable IN (`command`) DO command [command-parameters]
// 
//     file-set is one or more file names.  Each file is opened, read
//     and processed before going on to the next file in file-set.
//     Processing consists of reading in the file, breaking it up into
//     individual lines of text and then parsing each line into zero or
//     more tokens.  The body of the for loop is then called with the
//     variable value(s) set to the found token string(s).  By default, /F
//     passes the first blank separated token from each line of each file.
//     Blank lines are skipped.  You can override the default parsing
//     behavior by specifying the optional "options" parameter.  This
//     is a quoted string which contains one or more keywords to specify
//     different parsing options.  The keywords are:
//
#define MSG_HELP_FOR_X                   0x000023C1L

//
// MessageId: MSG_HELP_FOR_X1
//
// MessageText:
//
// 
//         eol=c           - specifies an end of line comment character
//                           (just one)
//         skip=n          - specifies the number of lines to skip at the
//                           beginning of the file.
//         delims=xxx      - specifies a delimiter set.  This replaces the
//                           default delimiter set of space and tab.
//         tokens=x,y,m-n  - specifies which tokens from each line are to
//                           be passed to the for body for each iteration.
//                           This will cause additional variable names to
//                           be allocated.  The m-n form is a range,
//                           specifying the mth through the nth tokens.  If
//                           the last character in the tokens= string is an
//                           asterisk, then an additional variable is
//                           allocated and receives the remaining text on
//                           the line after the last token parsed.
//         usebackq        - specifies that the new semantics are in force,
//                           where a back quoted string is executed as a
//                           command and a single quoted string is a
//                           literal string command and allows the use of
//                           double quotes to quote file names in
//                           file-set.
// 
//     Some examples might help:
// 
// FOR /F "eol=; tokens=2,3* delims=, " %%i in (myfile.txt) do @echo %%i %%j %%k
//
#define MSG_HELP_FOR_X1                  0x000023C2L

//
// MessageId: MSG_HELP_FOR_X2
//
// MessageText:
//
// 
//     would parse each line in myfile.txt, ignoring lines that begin with
//     a semicolon, passing the 2nd and 3rd token from each line to the for
//     body, with tokens delimited by commas and/or spaces.  Notice the for
//     body statements reference %%i to get the 2nd token, %%j to get the
//     3rd token, and %%k to get all remaining tokens after the 3rd.  For
//     file names that contain spaces, you need to quote the filenames with
//     double quotes.  In order to use double quotes in this manner, you also
//     need to use the usebackq option, otherwise the double quotes will be
//     interpreted as defining a literal string to parse.
// 
//     %%i is explicitly declared in the for statement and the %%j and %%k
//     are implicitly declared via the tokens= option.  You can specify up
//     to 26 tokens via the tokens= line, provided it does not cause an
//     attempt to declare a variable higher than the letter 'z' or 'Z'.
//     Remember, FOR variables are single-letter, case sensitive, global,
//     and you can't have more than 52 total active at any one time.
// 
//     You can also use the FOR /F parsing logic on an immediate string, by
//     making the file-set between the parenthesis a quoted string,
//     using single quote characters.  It will be treated as a single line
//     of input from a file and parsed.
// 
//     Finally, you can use the FOR /F command to parse the output of a
//     command.  You do this by making the file-set between the
//     parenthesis a back quoted string.  It will be treated as a command
//     line, which is passed to a child CMD.EXE and the output is captured
//     into memory and parsed as if it was a file.  So the following
//     example:
// 
//       FOR /F "usebackq delims==" %%i IN (`set`) DO @echo %%i
// 
//     would enumerate the environment variable names in the current
//     environment.
//
#define MSG_HELP_FOR_X2                  0x000023C3L

//
// MessageId: MSG_HELP_FOR_X3
//
// MessageText:
//
// 
// In addition, substitution of FOR variable references has been enhanced.
// You can now use the following optional syntax:
// 
//     %%~I         - expands %%I removing any surrounding quotes (")
//     %%~fI        - expands %%I to a fully qualified path name
//     %%~dI        - expands %%I to a drive letter only
//     %%~pI        - expands %%I to a path only
//     %%~nI        - expands %%I to a file name only
//     %%~xI        - expands %%I to a file extension only
//     %%~sI        - expanded path contains short names only
//     %%~aI        - expands %%I to file attributes of file
//     %%~tI        - expands %%I to date/time of file
//     %%~zI        - expands %%I to size of file
//     %%~$PATH:I   - searches the directories listed in the PATH
//                    environment variable and expands %%I to the
//                    fully qualified name of the first one found.
//                    If the environment variable name is not
//                    defined or the file is not found by the
//                    search, then this modifier expands to the
//                    empty string
// 
// The modifiers can be combined to get compound results:
// 
//     %%~dpI       - expands %%I to a drive letter and path only
//     %%~nxI       - expands %%I to a file name and extension only
//     %%~fsI       - expands %%I to a full path name with short names only
//     %%~dp$PATH:I - searches the directories listed in the PATH
//                    environment variable for %%I and expands to the
//                    drive letter and path of the first one found.
//     %%~ftzaI     - expands %%I to a DIR like output line
// 
// In the above examples %%I and PATH can be replaced by other valid
// values.  The %%~ syntax is terminated by a valid FOR variable name.
// Picking upper case variable names like %%I makes it more readable and
// avoids confusion with the modifiers, which are not case sensitive.
//
#define MSG_HELP_FOR_X3                  0x000023C4L

//
// MessageId: MSG_HELP_IF_X
//
// MessageText:
//
// 
// If Command Extensions are enabled IF changes as follows:
// 
//     IF [/I] string1 compare-op string2 command
//     IF CMDEXTVERSION number command
//     IF DEFINED variable command
// 
// where compare-op may be one of:
// 
//     EQU - equal
//     NEQ - not equal
//     LSS - less than
//     LEQ - less than or equal
//     GTR - greater than
//     GEQ - greater than or equal
// 
// and the /I switch, if specified, says to do case insensitive string
// compares.  The /I switch can also be used on the string1==string2 form
// of IF.  These comparisons are generic, in that if both string1 and
// string2 are both comprised of all numeric digits, then the strings are
// converted to numbers and a numeric comparison is performed.
// 
// The CMDEXTVERSION conditional works just like ERRORLEVEL, except it is
// comparing against an internal version number associated with the Command
// Extensions.  The first version is 1.  It will be incremented by one when
// significant enhancements are added to the Command Extensions.
// CMDEXTVERSION conditional is never true when Command Extensions are
// disabled.
// 
// The DEFINED conditional works just like EXIST except it takes an
// environment variable name and returns true if the environment variable
// is defined.
//
#define MSG_HELP_IF_X                    0x000023C5L

//
// MessageId: MSG_HELP_IF_X1
//
// MessageText:
//
// 
// %%ERRORLEVEL%% will expand into a string representation of
// the current value of ERRORLEVEL, provided that there is not already
// an environment variable with the name ERRORLEVEL, in which case you
// will get its value instead.  After running a program, the following
// illustrates ERRORLEVEL use:
// 
//     goto answer%%ERRORLEVEL%%
//     :answer0
//     echo Program had return code 0
//     :answer1
//     echo Program had return code 1
// 
// You can also use numerical comparisons above:
// 
//     IF %%ERRORLEVEL%% LEQ 1 goto okay
// 
// %%CMDCMDLINE%% will expand into the original command line passed to
// CMD.EXE prior to any processing by CMD.EXE, provided that there is not
// already an environment variable with the name CMDCMDLINE, in which case
// you will get its value instead.
// 
// %%CMDEXTVERSION%% will expand into a string representation of the
// current value of CMDEXTVERSION, provided that there is not already
// an environment variable with the name CMDEXTVERSION, in which case you
// will get its value instead.
//
#define MSG_HELP_IF_X1                   0x000023C6L

//
// MessageId: MSG_HELP_KEYS
//
// MessageText:
//
// Enables or disables command line editing on DOS system
// 
// This is present for Compatibility with DOS systems. It has no effect
// under Windows, as command line editing is always enabled.
//
#define MSG_HELP_KEYS                    0x000023C7L

//
// MessageId: MSG_NO_UNC_INITDIR
//
// MessageText:
//
// '%1'
// CMD.EXE was started with the above path as the current directory.
// UNC paths are not supported.  Defaulting to Windows directory.
//
#define MSG_NO_UNC_INITDIR               0x000023C8L

//
// MessageId: MSG_NO_UNC_CURDIR
//
// MessageText:
//
// '%1'
// CMD does not support UNC paths as current directories.
//
#define MSG_NO_UNC_CURDIR                0x000023C9L

//
// MessageId: MSG_SIM_UNC_CURDIR
//
// MessageText:
//
// UNC paths not supported for current directory. Using
// 
//     PUSHD %1
// 
// to create temporary drive letter to support UNC current
// directory.  Use POPD or EXIT to delete temporary drive
// letter.
//
#define MSG_SIM_UNC_CURDIR               0x000023CAL

//
// MessageId: MSG_SHIFT_BAD_ARG
//
// MessageText:
//
// Invalid parameter to SHIFT command
//
#define MSG_SHIFT_BAD_ARG                0x000023CBL

//
// MessageId: MSG_SET_A_MISMATCHED_PARENS
//
// MessageText:
//
// Unbalanced parenthesis.
//
#define MSG_SET_A_MISMATCHED_PARENS      0x000023CCL

//
// MessageId: MSG_SET_A_MISSING_OPERAND
//
// MessageText:
//
// Missing operand.
//
#define MSG_SET_A_MISSING_OPERAND        0x000023CDL

//
// MessageId: MSG_SET_A_MISSING_OPERATOR
//
// MessageText:
//
// Missing operator.
//
#define MSG_SET_A_MISSING_OPERATOR       0x000023CEL

//
// MessageId: MSG_SET_A_INVALID_NUMBER
//
// MessageText:
//
// Invalid number.  Numeric constants are either decimal (17),
// hexadecimal (0x11), or octal (021).
//
#define MSG_SET_A_INVALID_NUMBER         0x000023CFL

//
// MessageId: MSG_SET_NUMBER_TOO_LARGE
//
// MessageText:
//
// Invalid number.  Numbers are limited to 32-bits of precision.
//
#define MSG_SET_NUMBER_TOO_LARGE         0x000023D0L

//
// MessageId: MSG_SET_A_DIVIDE_BY_ZERO
//
// MessageText:
//
// Divide by zero error.
//
#define MSG_SET_A_DIVIDE_BY_ZERO         0x000023D1L

//
// MessageId: MSG_INVALID_COMSPEC
//
// MessageText:
//
// The COMSPEC environment variable does not point to CMD.EXE.
//
#define MSG_INVALID_COMSPEC              0x000023D2L

//
// MessageId: MSG_MOVE_COPY_OVERWRITE
//
// MessageText:
//
// Overwrite %1? (Yes/No/All): %0
//
#define MSG_MOVE_COPY_OVERWRITE          0x000023D3L

//
// MessageId: MSG_NOYESALL_RESPONSE_DATA
//
// MessageText:
//
// NYA%0
//
#define MSG_NOYESALL_RESPONSE_DATA       0x000023D4L

//
// MessageId: MSG_JUNCTION
//
// MessageText:
//
// <JUNCTION> %0
//
#define MSG_JUNCTION                     0x000023D5L

//
// MessageId: MSG_DIR_SYMLINK
//
// MessageText:
//
// <SYMLINKD> %0
//
#define MSG_DIR_SYMLINK                  0x000023D6L

//
// MessageId: MSG_FILE_SYMLINK
//
// MessageText:
//
// <SYMLINK> %0
//
#define MSG_FILE_SYMLINK                 0x000023D7L

//
// MessageId: MSG_DIR_TOO_LONG
//
// MessageText:
//
// The directory name %1\%2 is too long.
//
#define MSG_DIR_TOO_LONG                 0x000023D8L

//
// MessageId: MSG_FULL_PATH_TOO_LONG
//
// MessageText:
//
// The full path of %1 is too long.
//
#define MSG_FULL_PATH_TOO_LONG           0x000023D9L

//
// MessageId: MSG_PATH_TOO_LONG
//
// MessageText:
//
// The path %1\%2 is too long.
//
#define MSG_PATH_TOO_LONG                0x000023DAL

//
// MessageId: MSG_FTYPE_CMD_TOO_LONG
//
// MessageText:
//
// The FTYPE %1 is too long.
//
#define MSG_FTYPE_CMD_TOO_LONG           0x000023DBL

//
// MessageId: MSG_CANNOT_LOAD_LIB
//
// MessageText:
//
// Unable to find library %1.
//
#define MSG_CANNOT_LOAD_LIB              0x000023DCL

//
// MessageId: MSG_CANNOT_FIND_FUNC_NAME
//
// MessageText:
//
// Cannot find function %1!S!:%2!S!.
//
#define MSG_CANNOT_FIND_FUNC_NAME        0x000023DDL

//
// MessageId: MSG_CANNOT_FIND_FUNC_ORDINAL
//
// MessageText:
//
// Cannot find ordinal %1!S!:%2!d!.
//
#define MSG_CANNOT_FIND_FUNC_ORDINAL     0x000023DEL

//
// MessageId: MSG_CMD_LINE_TOO_LONG
//
// MessageText:
//
// The command line is too long.
//
#define MSG_CMD_LINE_TOO_LONG            0x000023DFL

//
// MessageId: MSG_FILE_WAS_COPIED
//
// MessageText:
//
// The file %1 was copied, but CMD is unable to reset the
// READ_ONLY attribute.
//
#define MSG_FILE_WAS_COPIED              0x000023E0L

//
// MessageId: MSG_FILE_NOT_FOUND
//
// MessageText:
//
// File Not Found
//
#define MSG_FILE_NOT_FOUND               0x00002711L

//
// MessageId: MSG_NOT_FOUND
//
// MessageText:
//
// Could Not Find %1
//
#define MSG_NOT_FOUND                    0x00002712L

//
// MessageId: MSG_TIME_NOT_SUPPORTED
//
// MessageText:
//
// The FAT File System only support Last Write Times
//
#define MSG_TIME_NOT_SUPPORTED           0x00002713L

//
// MessageId: MSG_HELP_SETLOCAL
//
// MessageText:
//
// Begins localization of environment changes in a batch file.  Environment
// changes made after SETLOCAL has been issued are local to the batch file.
// ENDLOCAL must be issued to restore the previous settings.  When the end
// of a batch script is reached, an implied ENDLOCAL is executed for any
// outstanding SETLOCAL commands issued by that batch script.
// 
// SETLOCAL
//
#define MSG_HELP_SETLOCAL                0x00002714L

//
// MessageId: MSG_HELP_ENDLOCAL
//
// MessageText:
//
// Ends localization of environment changes in a batch file.
// Environment changes made after ENDLOCAL has been issued are
// not local to the batch file; the previous settings are not
// restored on termination of the batch file.
// 
// ENDLOCAL
//
#define MSG_HELP_ENDLOCAL                0x00002715L

//
// MessageId: MSG_HELP_TITLE
//
// MessageText:
//
// Sets the window title for the command prompt window.
// 
// TITLE [string]
// 
//   string       Specifies the title for the command prompt window.
//
#define MSG_HELP_TITLE                   0x00002716L

//
// MessageId: MSG_HELP_APPEND
//
// MessageText:
//
// Allows programs to open data files in specified directories as if they were
// in the current directory.
// 
// APPEND [[drive:]path[;...]] [/X[:ON | :OFF]] [/PATH:ON | /PATH:OFF] [/E]
// APPEND ;
// 
//   [drive:]path Specifies a drive and directory to append.
//   /X:ON        Applies appended directories to file searches and
//                application execution.
//   /X:OFF       Applies appended directories only to requests to open files.
//                /X:OFF is the default setting.
//   /PATH:ON     Applies the appended directories to file requests that already
//                specify a path.  /PATH:ON is the default setting.
//   /PATH:OFF    Turns off the effect of /PATH:ON.
//   /E           Stores a copy of the appended directory list in an environment
//                variable named APPEND.  /E may be used only the first time
//                you use APPEND after starting up your system.
// 
// Type APPEND ; to clear the appended directory list.
// Type APPEND without parameters to display the appended directory list.
//
#define MSG_HELP_APPEND                  0x00002717L

//
// MessageId: MSG_HELP_MOVE
//
// MessageText:
//
// Moves files and renames files and directories.
// 
// To move one or more files:
// MOVE [/Y | /-Y] [drive:][path]filename1[,...] destination
// 
// To rename a directory:
// MOVE [/Y | /-Y] [drive:][path]dirname1 dirname2
// 
//   [drive:][path]filename1 Specifies the location and name of the file
//                           or files you want to move.
//   destination             Specifies the new location of the file. Destination
//                           can consist of a drive letter and colon, a
//                           directory name, or a combination. If you are moving
//                           only one file, you can also include a filename if
//                           you want to rename the file when you move it.
//   [drive:][path]dirname1  Specifies the directory you want to rename.
//   dirname2                Specifies the new name of the directory.
// 
//   /Y                      Suppresses prompting to confirm you want to
//                           overwrite an existing destination file.
//   /-Y                     Causes prompting to confirm you want to overwrite
//                           an existing destination file.
// 
// The switch /Y may be present in the COPYCMD environment variable.
// This may be overridden with /-Y on the command line.  Default is
// to prompt on overwrites unless MOVE command is being executed from
// within a batch script.
//
#define MSG_HELP_MOVE                    0x00002718L

//
// MessageId: MSG_HELP_PUSHDIR
//
// MessageText:
//
// Stores the current directory for use by the POPD command, then
// changes to the specified directory.
// 
// PUSHD [path | ..]
// 
//   path        Specifies the directory to make the current directory.
//
#define MSG_HELP_PUSHDIR                 0x00002719L

//
// MessageId: MSG_HELP_POPDIR
//
// MessageText:
//
// Changes to the directory stored by the PUSHD command.
// 
// POPD
// 
//
#define MSG_HELP_POPDIR                  0x0000271AL

//
// MessageId: MSG_FILE_NAME_PRECEEDING_ERROR
//
// MessageText:
//
// %1 - %0
//
#define MSG_FILE_NAME_PRECEEDING_ERROR   0x0000271BL

//
// MessageId: MSG_MAX_SETLOCAL
//
// MessageText:
//
// Maximum setlocal recursion level reached.
//
#define MSG_MAX_SETLOCAL                 0x0000271CL

//
// MessageId: MSG_ENTER_JAPAN_DATE
//
// MessageText:
//
// Enter the new date: (yy-mm-dd) %0
//
#define MSG_ENTER_JAPAN_DATE             0x0000271DL

//
// MessageId: MSG_ENTER_DEF_DATE
//
// MessageText:
//
// Enter the new date: (dd-mm-yy) %0
//
#define MSG_ENTER_DEF_DATE               0x0000271EL

//
// MessageId: MSG_VERIFY_FAIL
//
// MessageText:
//
// ERROR Verify - %1
//
#define MSG_VERIFY_FAIL                  0x0000271FL

//
// MessageId: MSG_MOVE_MULTIPLE_FAIL
//
// MessageText:
//
// Cannot move multiple files to a single file.
//
#define MSG_MOVE_MULTIPLE_FAIL           0x00002720L

//
// MessageId: MSG_RDR_HNDL_OPEN
//
// MessageText:
//
// The handle could not be opened
// during redirection of handle %1.
//
#define MSG_RDR_HNDL_OPEN                0x00002721L

//
// MessageId: MSG_PROGRESS
//
// MessageText:
//
// %r%1%% copied %0
//
#define MSG_PROGRESS                     0x00002722L

//
// MessageId: MSG_HELP_COLOR
//
// MessageText:
//
// Sets the default console foreground and background colors.
// 
// COLOR [attr]
// 
//   attr        Specifies color attribute of console output
// 
// Color attributes are specified by TWO hex digits -- the first
// corresponds to the background; the second the foreground.  Each digit
// can be any of the following values:
// 
//     0 = Black       8 = Gray
//     1 = Blue        9 = Light Blue
//     2 = Green       A = Light Green
//     3 = Aqua        B = Light Aqua
//     4 = Red         C = Light Red
//     5 = Purple      D = Light Purple
//     6 = Yellow      E = Light Yellow
//     7 = White       F = Bright White
// 
// If no argument is given, this command restores the color to what it was
// when CMD.EXE started.  This value either comes from the current console
// window, the /T command line switch or from the DefaultColor registry
// value.
// 
// The COLOR command sets ERRORLEVEL to 1 if an attempt is made to execute
// the COLOR command with a foreground and background color that are the
// same.
// 
// Example: "COLOR fc" produces light red on bright white
//
#define MSG_HELP_COLOR                   0x00002723L

//
// MessageId: MSG_MAX_PATH_EXCEEDED
//
// MessageText:
//
// Maximum path length exceeded - %1
//
#define MSG_MAX_PATH_EXCEEDED            0x00002724L

//
// MessageId: MSG_ERROR_BATCH_RECURSION
//
// MessageText:
//
// ******  B A T C H   R E C U R S I O N  exceeds STACK limits ******
// Recursion Count=%1!d!, Stack Usage=%2!d! percent
// ******       B A T C H   PROCESSING IS   A B O R T E D      ******
//
#define MSG_ERROR_BATCH_RECURSION        0x00002727L

//
// MessageId: MSG_ERROR_PUSHD_DEPTH_EXCEEDED
//
// MessageText:
//
// There are too many directories already in the PUSHD stack.
//
#define MSG_ERROR_PUSHD_DEPTH_EXCEEDED   0x00002728L

//
// MessageId: MSG_DISABLED_BY_POLICY
//
// MessageText:
//
// 
// The command prompt has been disabled by your administrator.
// 
//
#define MSG_DISABLED_BY_POLICY           0x00002729L

//
// MessageId: MSG_HELP_MKLINK
//
// MessageText:
//
// Creates a symbolic link.
// 
// MKLINK [[/D] | [/H] | [/J]] Link Target
// 
//         /D      Creates a directory symbolic link.  Default is a file
//                 symbolic link.
//         /H      Creates a hard link instead of a symbolic link.
//         /J      Creates a Directory Junction.
//         Link    Specifies the new symbolic link name.
//         Target  Specifies the path (relative or absolute) that the new link
//                 refers to.
//
#define MSG_HELP_MKLINK                  0x0000272AL

//
// MessageId: MSG_HARDLINK_CREATED
//
// MessageText:
//
// Hardlink created for %1!s! <<===>> %2!s!
//
#define MSG_HARDLINK_CREATED             0x0000272BL

//
// MessageId: MSG_SYMLINK_CREATED
//
// MessageText:
//
// symbolic link created for %1!s! <<===>> %2!s!
//
#define MSG_SYMLINK_CREATED              0x0000272CL

//
// MessageId: MSG_JUNCTION_CREATED
//
// MessageText:
//
// Junction created for %1!s! <<===>> %2!s!
//
#define MSG_JUNCTION_CREATED             0x0000272DL

//
// MessageId: MSG_NTFS_ARE_REQUIRED
//
// MessageText:
//
// Local NTFS volumes are required to complete the operation.
//
#define MSG_NTFS_ARE_REQUIRED            0x0000272EL

//
// MessageId: MSG_MUST_BE_ON_THE_SAME_NTFS
//
// MessageText:
//
// The new link and the existing file must be on the same NTFS volume.
//
#define MSG_MUST_BE_ON_THE_SAME_NTFS     0x0000272FL

//
// MessageId: MSG_DOES_NOT_SUPPORT_SYMLINK
//
// MessageText:
//
// The device does not support symbolic links.
//
#define MSG_DOES_NOT_SUPPORT_SYMLINK     0x00002730L

//
// MessageId: MSG_NOT_ENOUGH_PRIVILEGE
//
// MessageText:
//
// You do not have sufficient privilege to perform this operation.
//
#define MSG_NOT_ENOUGH_PRIVILEGE         0x00002731L

//
// MessageId: MSG_HELP_TRANSACTION
//
// MessageText:
//
// Allows control of file operations via transactions to commit or abort
// changes.
// 
// TRANSACTION [/START | /COMMIT | /ROLLBACK | /SUSPEND | /RESUME]
// 
//    /START    - Start a new transaction.  Only one can be pending
//                at a time.
// 
//    /COMMIT   - Commit all changes for the current transaction.
// 
//    /ROLLBACK - Rolls back all changes for the current transaction.
// 
//    /SUSPEND  - Disables the running transaction, leaving it pending,
//                and continue in non-transacted mode.
// 
//    /RESUME   - Enable the transaction disabled with suspend.
// 
// For both commit and rollback, the transaction is then closed after
// the command executes.
// 
// If no argument is given, this command displays the current state of the
// transaction for CMD.EXE.
//
#define MSG_HELP_TRANSACTION             0x00002732L

//
// MessageId: MSG_TRANSACTION_ID
//
// MessageText:
//
// Transaction ID: %1
//
#define MSG_TRANSACTION_ID               0x00002733L

//
// MessageId: MSG_TRANSACTION_IS_IN_PROGRESS
//
// MessageText:
//
// An active transaction is in progress.
//
#define MSG_TRANSACTION_IS_IN_PROGRESS   0x00002734L

//
// MessageId: MSG_NO_ACTIVE_TRANSACTION
//
// MessageText:
//
// There is no active transaction.
//
#define MSG_NO_ACTIVE_TRANSACTION        0x00002735L

//
// MessageId: MSG_ACTIVE_TRANSACTION_STARTED
//
// MessageText:
//
// A transaction has been successfully started.
//
#define MSG_ACTIVE_TRANSACTION_STARTED   0x00002736L

//
// MessageId: MSG_NO_TRANSACTION
//
// MessageText:
//
// There is no transaction to commit, rollback, suspend or resume.
//
#define MSG_NO_TRANSACTION               0x00002737L

//
// MessageId: MSG_ACTIVE_TRANSACTION_IS_ALREADY
//
// MessageText:
//
// An active transaction is already in progress. A new one cannot
// be started until the current one is committed or rolled back.
//
#define MSG_ACTIVE_TRANSACTION_IS_ALREADY 0x00002738L

//
// MessageId: MSG_INHERITED_TRANSACTION
//
// MessageText:
//
// Cannot commit or rollback a transaction that has been inherited
// from another process.
//
#define MSG_INHERITED_TRANSACTION        0x00002739L

//
// MessageId: MSG_CANNNOT_COMMIT_TRANSACTION
//
// MessageText:
//
// Cannot commit a transaction that was started outside of a batch
// file from within a batch file.
//
#define MSG_CANNNOT_COMMIT_TRANSACTION   0x0000273AL

//
// MessageId: MSG_TRANSACTION_ALREADY_SUSPENDED
//
// MessageText:
//
// Cannot suspend a transaction because a transaction is already
// suspended.
//
#define MSG_TRANSACTION_ALREADY_SUSPENDED 0x0000273BL

//
// MessageId: MSG_NO_SUSPENDED_TRANSACTION
//
// MessageText:
//
// Cannot resume a transaction because no transaction is currently
// suspended.
//
#define MSG_NO_SUSPENDED_TRANSACTION     0x0000273CL

//
// MessageId: MSG_CANNNOT_RESUME_TRANSACTION
//
// MessageText:
//
// Cannot resume a transaction suspended in a previous batch file.
//
#define MSG_CANNNOT_RESUME_TRANSACTION   0x0000273DL

//
// MessageId: MSG_TRANSACTION_RESUMED
//
// MessageText:
//
// Transaction successfully resumed.
//
#define MSG_TRANSACTION_RESUMED          0x0000273EL

//
// MessageId: MSG_TRANSACTION_SUSPENDED
//
// MessageText:
//
// Transaction successfully suspended.
//
#define MSG_TRANSACTION_SUSPENDED        0x0000273FL

//
// MessageId: MSG_STILL_RUNNING_TRANSACTION
//
// MessageText:
//
// There are still %1 process(es) running within this
// transaction.  Commit or rollback will continue once those
// processes have terminated.
//
#define MSG_STILL_RUNNING_TRANSACTION    0x00002740L

//
// MessageId: MSG_THIS_TRANSACTION_ALREADY_ROLLED_BACK
//
// MessageText:
//
// This transaction has already been rolled back.
//
#define MSG_THIS_TRANSACTION_ALREADY_ROLLED_BACK 0x00002741L

//
// MessageId: MSG_CURRENT_TRANSACTION_ALREADY_ROLLED_BACK
//
// MessageText:
//
// The current transaction has been rolled back.
//
#define MSG_CURRENT_TRANSACTION_ALREADY_ROLLED_BACK 0x00002742L

//
// MessageId: MSG_CMD_EXITED_SO_ROLLED_BACK
//
// MessageText:
//
// The current transaction has been rolled back because
// CMD exited or the batch file completed.
//
#define MSG_CMD_EXITED_SO_ROLLED_BACK    0x00002743L

//
// MessageId: MSG_THIS_TRANSACTION_ALREADY_COMMITTED
//
// MessageText:
//
// This transaction has already been committed.
//
#define MSG_THIS_TRANSACTION_ALREADY_COMMITTED 0x00002744L

//
// MessageId: MSG_CURRENT_TRANSACTION_ALREADY_COMMITTED
//
// MessageText:
//
// The current transaction has been committed.
//
#define MSG_CURRENT_TRANSACTION_ALREADY_COMMITTED 0x00002745L

//
// MessageId: MSG_CURRENT_TRANSACTION_ALREADY_COMMITTED_OR_ABORTED
//
// MessageText:
//
// The current transaction has been committed or aborted outside of
// CMD, and has been successfully abandoned.
//
#define MSG_CURRENT_TRANSACTION_ALREADY_COMMITTED_OR_ABORTED 0x00002746L

//
// MessageId: MSG_CANNOR_QUERY_TRANSACTION_STATE
//
// MessageText:
//
// Failed to query transaction state.  Unknown outcome state is %1
//
#define MSG_CANNOR_QUERY_TRANSACTION_STATE 0x00002747L

//
// MessageId: MSG_TITLE_ADMINISTRATOR
//
// MessageText:
//
// Administrator: %0
//
#define MSG_TITLE_ADMINISTRATOR          0x00002748L

//
// MessageId: MSG_LOCAL_VOL_ARE_REQUIRED
//
// MessageText:
//
// Local volumes are required to complete the operation.
//
#define MSG_LOCAL_VOL_ARE_REQUIRED       0x00002749L

