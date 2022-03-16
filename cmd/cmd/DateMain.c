// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"


int DateMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered DateMain() function\n");

    if (argc == 1) {

        DisplayTextMessage(MSG_CURRENT_DATE, NO_ARGS);

        if (CHECKRETURN(DisplayDate()) || CHECKRETURN(EnterAndSetNewDate(NULL))) {

            return FAILURE;
        }

        return SUCCESS;
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                DisplayTextMessage(MSG_HELP_DATE, NO_ARGS);
                return SUCCESS;
            }
            else if (CharLowerW(argv[1][1]) == L't') {

                if (CHECKRETURN(DisplayDate())) {

                    return FAILURE;
                }

                return SUCCESS;
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            if (CHECKRETURN(EnterAndSetNewDate(argv[1]))) {

                return FAILURE;
            }
        }
    }

    return SUCCESS;
}


BOOL DisplayDate(void) {

    SYSTEMTIME stCurrentDate = { 0 };
    GetLocalTime(&stCurrentDate);

    WCHAR szLocalDateFormat[128] = L"";
    WCHAR szFormattedDate[128] = L"";

    if (CHECKRETURN(GetLocaleInfoW(GetUserDefaultLCID(), LOCALE_SSHORTDATE, szLocalDateFormat, 128))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    if (CHECKRETURN(GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &stCurrentDate, &szLocalDateFormat, &szFormattedDate, 128, NULL))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    wprintf(L"%s\n", szFormattedDate);

    return SUCCESS;
}


BOOL EnterAndSetNewDate(LPWSTR lpNewDateString) {

    WCHAR szEnteredDateString[256] = L"mm-dd-yy";

    while (TRUE) {


        if (lpNewDateString == NULL) {

            DisplayTextMessage(MSG_ENTER_NEW_DATE, NO_ARGS);
            fgetws(szEnteredDateString, 256, stdin);
            szEnteredDateString[wcslen(szEnteredDateString) - 1] = L'\0';
        }
        else {

            wcscpy(szEnteredDateString, lpNewDateString);
            lpNewDateString = NULL;
        }

        if (szEnteredDateString[0] == L'\0') break;

        // Constantly
        DisplayTextMessage(MSG_INVALID_DATE, NO_ARGS);
    }

    return SUCCESS;
}
