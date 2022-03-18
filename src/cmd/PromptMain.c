// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"

WCHAR szDisplayPrompt[256] = L"";


int PromptMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered PromptMain() function\n");

    if (argc == 1) {

        // Set an empty string
        StrCpyW(szDisplayPrompt, L"");

        return SUCCESS;
    }
    else {

        WCHAR szEnteredPrompt[256] = L"";

        for (int i = 1; i < argc; i++) {

            if (CHECKRETURN(StrCmpW(argv[i], L"/?"))) {

                DisplayTextMessage(MSG_HELP_PROMPT, NO_ARGS);
                return SUCCESS;
            }
            else {

                if (argv[i][0] == L'$' && argv[i][2] == L'\0') {

                    argv[i]++;

                    switch ((int)CharUpperW(argv[i][0])) {

                    case L'A':

                        StrCatW(szEnteredPrompt, L"&");
                        break;

                    case L'B':

                        StrCatW(szEnteredPrompt, L"|");
                        break;

                    case L'C':

                        StrCatW(szEnteredPrompt, L"(");
                        break;

                    case L'D':

                        StrCatW(szEnteredPrompt, L"");
                        break;

                    case L'E':

                        StrCatW(szEnteredPrompt, L"\x1b");
                        break;

                    case L'F':

                        StrCatW(szEnteredPrompt, L")");
                        break;

                    case L'G':

                        StrCatW(szEnteredPrompt, L">");
                        break;

                    case L'H':

                        StrCatW(szEnteredPrompt, L"\x8");
                        break;

                    case L'L':

                        StrCatW(szEnteredPrompt, L"<");
                        break;

                    case L'N':

                        StrCatW(szEnteredPrompt, L"");
                        break;

                    case L'P':

                        StrCatW(szEnteredPrompt, L"");
                        break;

                    case L'Q':

                        StrCatW(szEnteredPrompt, L"=");
                        break;

                    case L'S':

                        StrCatW(szEnteredPrompt, L" ");
                        break;

                    case L'T':

                        StrCatW(szEnteredPrompt, L"");
                        break;

                    case L'V':

                        StrCatW(szEnteredPrompt, L"");
                        break;

                    case L'_':

                        StrCatW(szEnteredPrompt, L"\r\n");
                        break;

                    case L'$':

                        StrCatW(szEnteredPrompt, L"$");
                        break;

                    default: break;
                    }
                }
                else {

                    // Verify string
                    for (int j = 0; j < wcslen(argv[i]); j++) {

                        if (argv[i][j] == L'&' || argv[i][j] == L'|' || argv[i][j] == L'(' || argv[i][j] == L')' ||
                            argv[i][j] == L'>' || argv[i][j] == L'<' || argv[i][j] == L'=' || argv[i][j] == L' ') {

                            DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                            return FAILURE;
                        }
                    }

                    StrCatW(szEnteredPrompt, argv[i]);
                }

                if (i < argc - 1) {

                    StrCatW(szEnteredPrompt, L" ");
                }
            }
        }

        StrCpyW(szDisplayPrompt, szEnteredPrompt);
    }

    return SUCCESS;
}
