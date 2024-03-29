;// Copyright (c) 2021 WindowsCommands
;// Licensed under the MIT License.

MessageId=0x00002711
SymbolicName=MSG_HELP_ICACLS
Language=English

ICACLS name /save aclfile [/T] [/C] [/L] [/Q]
    stores the DACLs for the files and folders that match the name
    into aclfile for later use with /restore. Note that SACLs,
    owner, or integrity labels are not saved.

ICACLS directory [/substitute SidOld SidNew [...]] /restore aclfile
                 [/C] [/L] [/Q]
    applies the stored DACLs to files in directory.

ICACLS name /setowner user [/T] [/C] [/L] [/Q]
    changes the owner of all matching names. This option does not
    force a change of ownership; use the takeown.exe utility for
    that purpose.

ICACLS name /findsid Sid [/T] [/C] [/L] [/Q]
    finds all matching names that contain an ACL
    explicitly mentioning Sid.

ICACLS name /verify [/T] [/C] [/L] [/Q]
    finds all files whose ACL is not in canonical form or whose
    lengths are inconsistent with ACE counts.

ICACLS name /reset [/T] [/C] [/L] [/Q]
    replaces ACLs with default inherited ACLs for all matching files.

ICACLS name [/grant[:r] Sid:perm[...]]
       [/deny Sid:perm [...]]
       [/remove[:g|:d]] Sid[...]] [/T] [/C] [/L] [/Q]
       [/setintegritylevel Level:policy[...]]

    /grant[:r] Sid:perm grants the specified user access rights. With :r,
        the permissions replace any previously granted explicit permissions.
        Without :r, the permissions are added to any previously granted
        explicit permissions.

    /deny Sid:perm explicitly denies the specified user access rights.
        An explicit deny ACE is added for the stated permissions and
        the same permissions in any explicit grant are removed.

    /remove[:[g|d]] Sid removes all occurrences of Sid in the ACL. With
        :g, it removes all occurrences of granted rights to that Sid. With
        :d, it removes all occurrences of denied rights to that Sid.

    /setintegritylevel [(CI)(OI)]Level explicitly adds an integrity
        ACE to all matching files.  The level is to be specified as one
        of:
            L[ow]
            M[edium]
            H[igh]
        Inheritance options for the integrity ACE may precede the level
        and are applied only to directories.

    /inheritance:e|d|r
        e - enables inheritance
        d - disables inheritance and copy the ACEs
        r - remove all inherited ACEs


Note:
    Sids may be in either numerical or friendly name form. If a numerical
    form is given, affix a * to the start of the SID.

    /T indicates that this operation is performed on all matching
        files/directories below the directories specified in the name.

    /C indicates that this operation will continue on all file errors.
        Error messages will still be displayed.

    /L indicates that this operation is performed on a symbolic link
       itself versus its target.

    /Q indicates that icacls should suppress success messages.

    ICACLS preserves the canonical ordering of ACE entries:
            Explicit denials
            Explicit grants
            Inherited denials
            Inherited grants

    perm is a permission mask and can be specified in one of two forms:
        a sequence of simple rights:
                N - no access
                F - full access
                M - modify access
                RX - read and execute access
                R - read-only access
                W - write-only access
                D - delete access
        a comma-separated list in parentheses of specific rights:
                DE - delete
                RC - read control
                WDAC - write DAC
                WO - write owner
                S - synchronize
                AS - access system security
                MA - maximum allowed
                GR - generic read
                GW - generic write
                GE - generic execute
                GA - generic all
                RD - read data/list directory
                WD - write data/add file
                AD - append data/add subdirectory
                REA - read extended attributes
                WEA - write extended attributes
                X - execute/traverse
                DC - delete child
                RA - read attributes
                WA - write attributes
        inheritance rights may precede either form and are applied
        only to directories:
                (OI) - object inherit
                (CI) - container inherit
                (IO) - inherit only
                (NP) - don't propagate inherit
                (I) - permission inherited from parent container

Examples:

        icacls c:\windows\* /save AclFile /T
        - Will save the ACLs for all files under c:\windows
          and its subdirectories to AclFile.

        icacls c:\windows\ /restore AclFile
        - Will restore the Acls for every file within
          AclFile that exists in c:\windows and its subdirectories.

        icacls file /grant Administrator:(D,WDAC)
        - Will grant the user Administrator Delete and Write DAC
          permissions to file.

        icacls file /grant *S-1-1-0:(D,WDAC)
        - Will grant the user defined by sid S-1-1-0 Delete and
          Write DAC permissions to file.
.

MessageId=0x00002712
SymbolicName=MSG_HELP_ICACLS2
Language=English

ICACLS name /save aclfile [/T] [/C]
    stores the DACLs for the files and folders that match the name
    into aclfile for later use with /restore. Note that SACLs,
    owner, or integrity labels are not saved.

ICACLS directory [/substitute SidOld SidNew [...]] /restore aclfile [/C]
    applies the stored DACLs to files in directory.

ICACLS name /setowner user [/T] [/C]
    changes the owner of all matching names. This option does not
    force a change of ownership; use the takeown.exe utility for
    that purpose.

ICACLS name /findsid Sid [/T] [/C]
    finds all matching names that contain an ACL
    explicitly mentioning Sid.

ICACLS name /verify [/T] [/C]
    finds all files whose ACL is not in canonical form or whose
    lengths are inconsistent with ACE counts.

ICACLS name /reset [/T] [/C]
    replaces ACLs with default inherited ACLs for all matching files.

ICACLS name [/grant[:r] Sid:perm[...]]
       [/deny Sid:perm [...]]
       [/remove[:g|:d]] Sid[...]] [/T] [/C]

    /grant[:r] Sid:perm grants the specified user access rights. With :r,
        the permissions replace any previously granted explicit permissions.
        Without :r, the permissions are added to any previously granted
        explicit permissions.

    /deny Sid:perm explicitly denies the specified user access rights.
        An explicit deny ACE is added for the stated permissions and
        the same permissions in any explicit grant are removed.

    /remove[:[g|d]] Sid removes all occurrences of Sid in the ACL. With
        :g, it removes all occurrences of granted rights to that Sid. With
        :d, it removes all occurrences of denied rights to that Sid.

    /inheritance:e|d|r
        e - enables inheritance
        d - disables inheritance and copy the ACEs
        r - remove all inherited ACEs



Note:
    Sids may be in either numerical or friendly name form. If a numerical
    form is given, affix a * to the start of the SID.

    /T indicates that this operation is performed on all matching
        files/directories below the directories specified in the name.

    /C indicates that this operation will continue on all file errors.
        Error messages will still be displayed.

    ICACLS preserves the canonical ordering of ACE entries:
            Explicit denials
            Explicit grants
            Inherited denials
            Inherited grants

    perm is a permission mask and can be specified in one of two forms:
        a sequence of simple rights:
                N - no access
                F - full access
                M - modify access
                RX - read and execute access
                R - read-only access
                D - delete access
        a comma-separated list in parenthesis of specific rights:
                DE - delete
                RC - read control
                WDAC - write DAC
                WO - write owner
                S - synchronize
                AS - access system security
                MA - maximum allowed
                GR - generic read
                GW - generic write
                GE - generic execute
                GA - generic all
                RD - read data/list directory
                WD - write data/add file
                AD - append data/add subdirectory
                REA - read extended attributes
                WEA - write extended attributes
                X - execute/traverse
                DC - delete child
                RA - read attributes
                WA - write attributes
        inheritance rights may precede either form and are applied
        only to directories:
                (OI) - object inherit
                (CI) - container inherit
                (IO) - inherit only
                (NP) - don't propagate inherit
                (I) - permission inherited from parent container

Examples:

        icacls c:\windows\* /save AclFile /T
        - Will save the ACLs for all files under c:\windows
          and its subdirectories to AclFile.

        icacls c:\windows\ /restore AclFile
        - Will restore the Acls for every file within
          AclFile that exists in c:\windows and its subdirectories.

        icacls file /grant Administrator:(D,WDAC)
        - Will grant the user Administrator Delete and Write DAC
          permissions to file.

        icacls file /grant *S-1-1-0:(D,WDAC)
        - Will grant the user defined by sid S-1-1-0 Delete and
          Write DAC permissions to file.
.

MessageId=0x00002713
SymbolicName=MSG_BAD_PARM
Language=English
Invalid parameter "%1"
.

MessageId=0x00002714
SymbolicName=MSG_ACCESS_DENIED
Language=English
ACCESS_DENIED%0
.

MessageId=0x00002715
SymbolicName=MSG_PROCESSING_FILE
Language=English
processed file: %1
.

MessageId=0x00002716
SymbolicName=MSG_USER_NOT_FOUND
Language=English
<User name not found>%0
.

MessageId=0x00002717
SymbolicName=MSG_OI_INHERITANCE
Language=English
(OI)%0
.

MessageId=0x00002718
SymbolicName=MSG_CI_INHERITANCE
Language=English
(CI)%0
.

MessageId=0x00002719
SymbolicName=MSG_NP_INHERITANCE
Language=English
(NP)%0
.

MessageId=0x0000271A
SymbolicName=MSG_IO_INHERITANCE
Language=English
(IO)%0
.

MessageId=0x0000271B
SymbolicName=MSG_DENY_ACCESS
Language=English
(DENY)%0
.

MessageId=0x0000271C
SymbolicName=MSG_SPECIAL_ACCESS
Language=English
(special access:)
.

MessageId=0x0000271D
SymbolicName=MSG_SHARING_VIOLATION
Language=English
sharing violation:%0
.

MessageId=0x0000271E
SymbolicName=MSG_SET_OWNERSHIP_FAILD
Language=English
Set ownership failed
%0
.

MessageId=0x0000271F
SymbolicName=MSG_ACCESS_DENIED2
Language=English
Access denied: %0
.

MessageId=0x00002720
SymbolicName=MSG_HAVE_ALL_CONTROL
Language=English
 No permissions are set. All users have full control.%0
.

MessageId=0x00002721
SymbolicName=MSG_NOT_IN_CANONICAL_ORDER
Language=English
%1: Ace entries not in canonical order.
.

MessageId=0x00002722
SymbolicName=MSG_BAD_ACL_LENGTH
Language=English
%1: Acl length is incorrect.
.

MessageId=0x00002723
SymbolicName=MSG_ACLS_SUCCESSFULLY_SAVED
Language=English
Acls were successfully saved.
.

MessageId=0x00002724
SymbolicName=MSG_ACLS_SUCCESSFULLY_RESTORED
Language=English
Acls successfully restored.
.

MessageId=0x00002725
SymbolicName=MSG_SID_FOUND
Language=English
SID Found: %1.
.

MessageId=0x00002726
SymbolicName=MSG_NO_ERRORS_ON_VERIFYING
Language=English
No errors were found while verifying ACLs.
.

MessageId=0x00002727
SymbolicName=MSG_ACLS_SUCCESSFULLY_MODIFIED
Language=English
The Acls were successfully modified.
.

MessageId=0x00002728
SymbolicName=MSG_ACLS_SUCCESSFULLY_RESET
Language=English
The ACLs were successfully reset.
.

MessageId=0x00002729
SymbolicName=MSG_ACLS_SUCCESSFULLY_SET
Language=English
The owner was successfully set.
.

MessageId=0x0000272A
SymbolicName=MSG_NO_FILES_MATCHED_SID
Language=English
No files with a matching SID was found
.

MessageId=0x0000272B
SymbolicName=MSG_EXIT_STATUS
Language=English
Successfully processed %1 files; Failed processing %2 files
.

MessageId=0x0000272C
SymbolicName=MSG_THIS_OPERATION_NOT_ALLOWED
Language=English
This operation is not allowed as it would create an un-usable ACL.
.

MessageId=0x0000272D
SymbolicName=MSG_FIRST_PARM_MUST_BE
Language=English
First parameter must be a file name pattern or "/?"
.

