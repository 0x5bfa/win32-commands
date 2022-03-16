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
// MessageId: MSG_HELP_ICACLS
//
// MessageText:
//
// 
// ICACLS name /save aclfile [/T] [/C] [/L] [/Q]
//     stores the DACLs for the files and folders that match the name
//     into aclfile for later use with /restore. Note that SACLs,
//     owner, or integrity labels are not saved.
// 
// ICACLS directory [/substitute SidOld SidNew [...]] /restore aclfile
//                  [/C] [/L] [/Q]
//     applies the stored DACLs to files in directory.
// 
// ICACLS name /setowner user [/T] [/C] [/L] [/Q]
//     changes the owner of all matching names. This option does not
//     force a change of ownership; use the takeown.exe utility for
//     that purpose.
// 
// ICACLS name /findsid Sid [/T] [/C] [/L] [/Q]
//     finds all matching names that contain an ACL
//     explicitly mentioning Sid.
// 
// ICACLS name /verify [/T] [/C] [/L] [/Q]
//     finds all files whose ACL is not in canonical form or whose
//     lengths are inconsistent with ACE counts.
// 
// ICACLS name /reset [/T] [/C] [/L] [/Q]
//     replaces ACLs with default inherited ACLs for all matching files.
// 
// ICACLS name [/grant[:r] Sid:perm[...]]
//        [/deny Sid:perm [...]]
//        [/remove[:g|:d]] Sid[...]] [/T] [/C] [/L] [/Q]
//        [/setintegritylevel Level:policy[...]]
// 
//     /grant[:r] Sid:perm grants the specified user access rights. With :r,
//         the permissions replace any previously granted explicit permissions.
//         Without :r, the permissions are added to any previously granted
//         explicit permissions.
// 
//     /deny Sid:perm explicitly denies the specified user access rights.
//         An explicit deny ACE is added for the stated permissions and
//         the same permissions in any explicit grant are removed.
// 
//     /remove[:[g|d]] Sid removes all occurrences of Sid in the ACL. With
//         :g, it removes all occurrences of granted rights to that Sid. With
//         :d, it removes all occurrences of denied rights to that Sid.
// 
//     /setintegritylevel [(CI)(OI)]Level explicitly adds an integrity
//         ACE to all matching files.  The level is to be specified as one
//         of:
//             L[ow]
//             M[edium]
//             H[igh]
//         Inheritance options for the integrity ACE may precede the level
//         and are applied only to directories.
// 
//     /inheritance:e|d|r
//         e - enables inheritance
//         d - disables inheritance and copy the ACEs
//         r - remove all inherited ACEs
// 
// 
// Note:
//     Sids may be in either numerical or friendly name form. If a numerical
//     form is given, affix a * to the start of the SID.
// 
//     /T indicates that this operation is performed on all matching
//         files/directories below the directories specified in the name.
// 
//     /C indicates that this operation will continue on all file errors.
//         Error messages will still be displayed.
// 
//     /L indicates that this operation is performed on a symbolic link
//        itself versus its target.
// 
//     /Q indicates that icacls should suppress success messages.
// 
//     ICACLS preserves the canonical ordering of ACE entries:
//             Explicit denials
//             Explicit grants
//             Inherited denials
//             Inherited grants
// 
//     perm is a permission mask and can be specified in one of two forms:
//         a sequence of simple rights:
//                 N - no access
//                 F - full access
//                 M - modify access
//                 RX - read and execute access
//                 R - read-only access
//                 W - write-only access
//                 D - delete access
//         a comma-separated list in parentheses of specific rights:
//                 DE - delete
//                 RC - read control
//                 WDAC - write DAC
//                 WO - write owner
//                 S - synchronize
//                 AS - access system security
//                 MA - maximum allowed
//                 GR - generic read
//                 GW - generic write
//                 GE - generic execute
//                 GA - generic all
//                 RD - read data/list directory
//                 WD - write data/add file
//                 AD - append data/add subdirectory
//                 REA - read extended attributes
//                 WEA - write extended attributes
//                 X - execute/traverse
//                 DC - delete child
//                 RA - read attributes
//                 WA - write attributes
//         inheritance rights may precede either form and are applied
//         only to directories:
//                 (OI) - object inherit
//                 (CI) - container inherit
//                 (IO) - inherit only
//                 (NP) - don't propagate inherit
//                 (I) - permission inherited from parent container
// 
// Examples:
// 
//         icacls c:\windows\* /save AclFile /T
//         - Will save the ACLs for all files under c:\windows
//           and its subdirectories to AclFile.
// 
//         icacls c:\windows\ /restore AclFile
//         - Will restore the Acls for every file within
//           AclFile that exists in c:\windows and its subdirectories.
// 
//         icacls file /grant Administrator:(D,WDAC)
//         - Will grant the user Administrator Delete and Write DAC
//           permissions to file.
// 
//         icacls file /grant *S-1-1-0:(D,WDAC)
//         - Will grant the user defined by sid S-1-1-0 Delete and
//           Write DAC permissions to file.
//
#define MSG_HELP_ICACLS                  0x00002711L

//
// MessageId: MSG_HELP_ICACLS2
//
// MessageText:
//
// 
// ICACLS name /save aclfile [/T] [/C]
//     stores the DACLs for the files and folders that match the name
//     into aclfile for later use with /restore. Note that SACLs,
//     owner, or integrity labels are not saved.
// 
// ICACLS directory [/substitute SidOld SidNew [...]] /restore aclfile [/C]
//     applies the stored DACLs to files in directory.
// 
// ICACLS name /setowner user [/T] [/C]
//     changes the owner of all matching names. This option does not
//     force a change of ownership; use the takeown.exe utility for
//     that purpose.
// 
// ICACLS name /findsid Sid [/T] [/C]
//     finds all matching names that contain an ACL
//     explicitly mentioning Sid.
// 
// ICACLS name /verify [/T] [/C]
//     finds all files whose ACL is not in canonical form or whose
//     lengths are inconsistent with ACE counts.
// 
// ICACLS name /reset [/T] [/C]
//     replaces ACLs with default inherited ACLs for all matching files.
// 
// ICACLS name [/grant[:r] Sid:perm[...]]
//        [/deny Sid:perm [...]]
//        [/remove[:g|:d]] Sid[...]] [/T] [/C]
// 
//     /grant[:r] Sid:perm grants the specified user access rights. With :r,
//         the permissions replace any previously granted explicit permissions.
//         Without :r, the permissions are added to any previously granted
//         explicit permissions.
// 
//     /deny Sid:perm explicitly denies the specified user access rights.
//         An explicit deny ACE is added for the stated permissions and
//         the same permissions in any explicit grant are removed.
// 
//     /remove[:[g|d]] Sid removes all occurrences of Sid in the ACL. With
//         :g, it removes all occurrences of granted rights to that Sid. With
//         :d, it removes all occurrences of denied rights to that Sid.
// 
//     /inheritance:e|d|r
//         e - enables inheritance
//         d - disables inheritance and copy the ACEs
//         r - remove all inherited ACEs
// 
// 
// 
// Note:
//     Sids may be in either numerical or friendly name form. If a numerical
//     form is given, affix a * to the start of the SID.
// 
//     /T indicates that this operation is performed on all matching
//         files/directories below the directories specified in the name.
// 
//     /C indicates that this operation will continue on all file errors.
//         Error messages will still be displayed.
// 
//     ICACLS preserves the canonical ordering of ACE entries:
//             Explicit denials
//             Explicit grants
//             Inherited denials
//             Inherited grants
// 
//     perm is a permission mask and can be specified in one of two forms:
//         a sequence of simple rights:
//                 N - no access
//                 F - full access
//                 M - modify access
//                 RX - read and execute access
//                 R - read-only access
//                 D - delete access
//         a comma-separated list in parenthesis of specific rights:
//                 DE - delete
//                 RC - read control
//                 WDAC - write DAC
//                 WO - write owner
//                 S - synchronize
//                 AS - access system security
//                 MA - maximum allowed
//                 GR - generic read
//                 GW - generic write
//                 GE - generic execute
//                 GA - generic all
//                 RD - read data/list directory
//                 WD - write data/add file
//                 AD - append data/add subdirectory
//                 REA - read extended attributes
//                 WEA - write extended attributes
//                 X - execute/traverse
//                 DC - delete child
//                 RA - read attributes
//                 WA - write attributes
//         inheritance rights may precede either form and are applied
//         only to directories:
//                 (OI) - object inherit
//                 (CI) - container inherit
//                 (IO) - inherit only
//                 (NP) - don't propagate inherit
//                 (I) - permission inherited from parent container
// 
// Examples:
// 
//         icacls c:\windows\* /save AclFile /T
//         - Will save the ACLs for all files under c:\windows
//           and its subdirectories to AclFile.
// 
//         icacls c:\windows\ /restore AclFile
//         - Will restore the Acls for every file within
//           AclFile that exists in c:\windows and its subdirectories.
// 
//         icacls file /grant Administrator:(D,WDAC)
//         - Will grant the user Administrator Delete and Write DAC
//           permissions to file.
// 
//         icacls file /grant *S-1-1-0:(D,WDAC)
//         - Will grant the user defined by sid S-1-1-0 Delete and
//           Write DAC permissions to file.
//
#define MSG_HELP_ICACLS2                 0x00002712L

//
// MessageId: MSG_BAD_PARM
//
// MessageText:
//
// Invalid parameter "%1"
//
#define MSG_BAD_PARM                     0x00002713L

//
// MessageId: MSG_ACCESS_DENIED
//
// MessageText:
//
// ACCESS_DENIED%0
//
#define MSG_ACCESS_DENIED                0x00002714L

//
// MessageId: MSG_PROCESSING_FILE
//
// MessageText:
//
// processed file: %1
//
#define MSG_PROCESSING_FILE              0x00002715L

//
// MessageId: MSG_USER_NOT_FOUND
//
// MessageText:
//
// <User name not found>%0
//
#define MSG_USER_NOT_FOUND               0x00002716L

//
// MessageId: MSG_OI_INHERITANCE
//
// MessageText:
//
// (OI)%0
//
#define MSG_OI_INHERITANCE               0x00002717L

//
// MessageId: MSG_CI_INHERITANCE
//
// MessageText:
//
// (CI)%0
//
#define MSG_CI_INHERITANCE               0x00002718L

//
// MessageId: MSG_NP_INHERITANCE
//
// MessageText:
//
// (NP)%0
//
#define MSG_NP_INHERITANCE               0x00002719L

//
// MessageId: MSG_IO_INHERITANCE
//
// MessageText:
//
// (IO)%0
//
#define MSG_IO_INHERITANCE               0x0000271AL

//
// MessageId: MSG_DENY_ACCESS
//
// MessageText:
//
// (DENY)%0
//
#define MSG_DENY_ACCESS                  0x0000271BL

//
// MessageId: MSG_SPECIAL_ACCESS
//
// MessageText:
//
// (special access:)
//
#define MSG_SPECIAL_ACCESS               0x0000271CL

//
// MessageId: MSG_SHARING_VIOLATION
//
// MessageText:
//
// sharing violation:%0
//
#define MSG_SHARING_VIOLATION            0x0000271DL

//
// MessageId: MSG_SET_OWNERSHIP_FAILD
//
// MessageText:
//
// Set ownership failed
// %0
//
#define MSG_SET_OWNERSHIP_FAILD          0x0000271EL

//
// MessageId: MSG_ACCESS_DENIED2
//
// MessageText:
//
// Access denied: %0
//
#define MSG_ACCESS_DENIED2               0x0000271FL

//
// MessageId: MSG_HAVE_ALL_CONTROL
//
// MessageText:
//
//  No permissions are set. All users have full control.%0
//
#define MSG_HAVE_ALL_CONTROL             0x00002720L

//
// MessageId: MSG_NOT_IN_CANONICAL_ORDER
//
// MessageText:
//
// %1: Ace entries not in canonical order.
//
#define MSG_NOT_IN_CANONICAL_ORDER       0x00002721L

//
// MessageId: MSG_BAD_ACL_LENGTH
//
// MessageText:
//
// %1: Acl length is incorrect.
//
#define MSG_BAD_ACL_LENGTH               0x00002722L

//
// MessageId: MSG_ACLS_SUCCESSFULLY_SAVED
//
// MessageText:
//
// Acls were successfully saved.
//
#define MSG_ACLS_SUCCESSFULLY_SAVED      0x00002723L

//
// MessageId: MSG_ACLS_SUCCESSFULLY_RESTORED
//
// MessageText:
//
// Acls successfully restored.
//
#define MSG_ACLS_SUCCESSFULLY_RESTORED   0x00002724L

//
// MessageId: MSG_SID_FOUND
//
// MessageText:
//
// SID Found: %1.
//
#define MSG_SID_FOUND                    0x00002725L

//
// MessageId: MSG_NO_ERRORS_ON_VERIFYING
//
// MessageText:
//
// No errors were found while verifying ACLs.
//
#define MSG_NO_ERRORS_ON_VERIFYING       0x00002726L

//
// MessageId: MSG_ACLS_SUCCESSFULLY_MODIFIED
//
// MessageText:
//
// The Acls were successfully modified.
//
#define MSG_ACLS_SUCCESSFULLY_MODIFIED   0x00002727L

//
// MessageId: MSG_ACLS_SUCCESSFULLY_RESET
//
// MessageText:
//
// The ACLs were successfully reset.
//
#define MSG_ACLS_SUCCESSFULLY_RESET      0x00002728L

//
// MessageId: MSG_ACLS_SUCCESSFULLY_SET
//
// MessageText:
//
// The owner was successfully set.
//
#define MSG_ACLS_SUCCESSFULLY_SET        0x00002729L

//
// MessageId: MSG_NO_FILES_MATCHED_SID
//
// MessageText:
//
// No files with a matching SID was found
//
#define MSG_NO_FILES_MATCHED_SID         0x0000272AL

//
// MessageId: MSG_EXIT_STATUS
//
// MessageText:
//
// Successfully processed %1 files; Failed processing %2 files
//
#define MSG_EXIT_STATUS                  0x0000272BL

//
// MessageId: MSG_THIS_OPERATION_NOT_ALLOWED
//
// MessageText:
//
// This operation is not allowed as it would create an un-usable ACL.
//
#define MSG_THIS_OPERATION_NOT_ALLOWED   0x0000272CL

//
// MessageId: MSG_FIRST_PARM_MUST_BE
//
// MessageText:
//
// First parameter must be a file name pattern or "/?"
//
#define MSG_FIRST_PARM_MUST_BE           0x0000272DL

