// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"


int TitleMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered TitleMain() function\n");

    if (argc == 1) return SUCCESS;
    else {

        if (argv[1][0] == L'/' && argv[1][1] == L'?') {

            DisplayTextMessage(MSG_HELP_TITLE, NO_ARGS);
            return SUCCESS;
        }
        else {

            if (CHECKRETURN(CmdSetConsoleTitle(argv[1]))) {

                return FAILURE;
            }
        }
    }

    return SUCCESS;
}


BOOL CmdSetConsoleTitle(LPWSTR lpConsoleTitle) {

    WCHAR szTitle[1024] = L"";

    switch(DoThisRunAsAdministrator()){

    default:
    case 0:

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;

    case 2: {

        LPWSTR lpMessage = GetTextMessage(MSG_TITLE_ADMINISTRATOR, NO_ARGS);
        wcscpy(szTitle, lpMessage);
        LocalFree(lpMessage);
        break;
    }
    }

    wcscat(szTitle, lpConsoleTitle);

    if (CHECKRETURN(SetConsoleTitleW(szTitle))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
    }

    return SUCCESS;
}


BOOL DoThisRunAsAdministrator(void) {

    // Error: 0, Member: 1, Not member: 2

    SID_IDENTIFIER_AUTHORITY SidIdentifierAuthority = SECURITY_NT_AUTHORITY;
    PSID sidAdministratorGroup = NULL;
    BOOL bIsAdminGroupMember = FALSE;

    if (CHECKRETURN(AllocateAndInitializeSid(&SidIdentifierAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &sidAdministratorGroup))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    if (CHECKRETURN(CheckTokenMembership(NULL, sidAdministratorGroup, &bIsAdminGroupMember))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        FreeSid(sidAdministratorGroup);
        return FAILURE;
    }

    FreeSid(sidAdministratorGroup);

    return bIsAdminGroupMember + 1;
}
