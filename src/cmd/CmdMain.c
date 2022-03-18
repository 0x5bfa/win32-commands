// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"

BOOL ParseCmdSwitch(PCMD pCmd, int argc, LPWSTR argv[]);
DWORD FindCommand(LPWSTR lpCmdLine);
BOOL GetCmdLine(LPWSTR lpCmdLine);


int wmain(int argc, LPWSTR argv[]) {

    DbgPrint(L"== Entered main function for CMD ==\n");

    CMD Cmd = { 0 };
    DWORD dwResult = ERROR_SUCCESS;

    if (argc != 1) {

        if (CHECKRETURN(ParseCmdSwitch(&Cmd, argc, argv))) {

            return FAILURE;
        }
    }

    // Initialize command prompt
    if(CHECKRETURN(InitializeCmdPrompt(&Cmd))){

        return FAILURE;
    }

    // Temp rutine for test internam command
    // Only one command line is supported. (Does not support command line separators.)
    GetWindowsVersion();
    wprintf(L"(c) Microsoft Corporation. All rights reserved.\n\n");

    while (1) {

        // Display command prompt and get command line
        WCHAR szMultiCmdLine[600] = L"";
        GetCmdLine(&szMultiCmdLine);


        if (szMultiCmdLine[0] != L'\0') {

            FindCommand(szMultiCmdLine);
            wprintf(L"\n");
        }
    }

    return 0;
}


BOOL ParseCmdSwitch(PCMD pCmd, int argc, LPWSTR argv[]) {

    for (int i = 1; i < argc; i++) {

        if (CHECKRETURN(StrCmpIW(argv[1], L"/?"))) {

            DisplayTextMessage(MSG_HELP_CMD, NO_ARGS);
            DisplayTextMessage(MSG_HELP_CMD1, NO_ARGS);
            DisplayTextMessage(MSG_HELP_CMD_EXTENSIONS, NO_ARGS);
            DisplayTextMessage(MSG_HELP_CMD_EXTENSIONS1, NO_ARGS);
            DisplayTextMessage(MSG_HELP_CMD_COMPLETION1, NO_ARGS);
            DisplayTextMessage(MSG_HELP_CMD_COMPLETION2, NO_ARGS);
            CmdExit(0);
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/C")) || CHECKRETURN(StrCmpIW(argv[i], L"/R")) || !(pCmd->dwSwitch & SWITCH_EXECUTE_CMD_AND_EXIT)) {

            pCmd->dwSwitch |= SWITCH_EXECUTE_CMD_AND_EXIT;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/K")) || !(pCmd->dwSwitch & SWITCH_EXECUTE_CMD_AND_CONTINUE)) {

            pCmd->dwSwitch |= SWITCH_EXECUTE_CMD_AND_CONTINUE;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/S")) || !(pCmd->dwSwitch & SWITCH_CHANGE_STRING_TREATMENT)) {

            pCmd->dwSwitch |= SWITCH_CHANGE_STRING_TREATMENT;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/Q")) || !(pCmd->dwSwitch & SWITCH_ECHO_OFF)) {

            pCmd->dwSwitch |= SWITCH_ECHO_OFF;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/D")) || !(pCmd->dwSwitch & SWITCH_DISABLE_AUTORUN)) {

            pCmd->dwSwitch |= SWITCH_DISABLE_AUTORUN;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/A")) || !(pCmd->dwSwitch & SWITCH_OUTPUT_AS_ANSI)) {

            pCmd->dwSwitch |= SWITCH_OUTPUT_AS_ANSI;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/U")) || !(pCmd->dwSwitch & SWITCH_OUTPUT_AS_UNICODE)) {

            pCmd->dwSwitch |= SWITCH_OUTPUT_AS_UNICODE;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/T")) || !(pCmd->dwSwitch & SWITCH_SET_BACK_FORE_COLOR)) {

            pCmd->dwSwitch |= SWITCH_SET_BACK_FORE_COLOR;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/E:ON")) || CHECKRETURN(StrCmpIW(argv[i], L"/X")) || !(pCmd->dwSwitch & SWITCH_ENABLE_EXTENSION)) {

            pCmd->dwSwitch |= SWITCH_ENABLE_EXTENSION;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/E:OFF")) || CHECKRETURN(StrCmpIW(argv[i], L"/Y")) || !(pCmd->dwSwitch & SWITCH_DISABLE_EXTENSION)) {

            pCmd->dwSwitch |= SWITCH_DISABLE_EXTENSION;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/F:ON")) || !(pCmd->dwSwitch & SWITCH_ENABLE_COMPLETION)) {

            pCmd->dwSwitch |= SWITCH_ENABLE_COMPLETION;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/F:OFF")) || !(pCmd->dwSwitch & SWITCH_DISABLE_COMPLETION)) {

            pCmd->dwSwitch |= SWITCH_DISABLE_COMPLETION;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/V:ON")) || !(pCmd->dwSwitch & SWITCH_ENABLE_DELAYED_EXPANSION)) {

            pCmd->dwSwitch |= SWITCH_ENABLE_DELAYED_EXPANSION;
        }
        else if (CHECKRETURN(StrCmpIW(argv[i], L"/V:OFF")) || !(pCmd->dwSwitch & SWITCH_DISABLE_DELAYED_EXPANSION)) {

            pCmd->dwSwitch |= SWITCH_DISABLE_DELAYED_EXPANSION;
        }
    }

    return SUCCESS;
}


DWORD FindCommand(LPWSTR lpCmdLine) {

    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);

    if (CHECKRETURN(StrCmpIW(argv[0], L"ASSOC"))) {

        return AssocMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"CHCP"))) {

        return ChCpMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"CHDIR")) || CHECKRETURN(StrCmpIW(argv[0], L"CD"))) {

        return ChDirMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"CLS"))) {

        return ClsMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"COLOR"))) {

        return ColorMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"DATE"))) {

        return DateMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"DIR"))) {

        return DirMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"ECHO"))) {

        return EchoMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"EXIT"))) {

        return ExitMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"FTYPE"))) {

        return FTypeMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"MKDIR")) || CHECKRETURN(StrCmpIW(argv[0], L"MD"))) {

        return MkDirMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"PAUSE"))) {

        return PauseMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"PROMPT"))) {

        return PromptMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"TITLE"))) {

        return TitleMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"VER"))) {

        return VerMain(argc, argv);
    }
    else if (CHECKRETURN(StrCmpIW(argv[0], L"VOL"))) {

        return VolMain(argc, argv);
    }
    else {

        // Execute external commands
        if (CHECKRETURN(ExecuteExternalCommands(lpCmdLine))) {

            DisplayTextMessage(MSG_DIR_BAD_COMMAND_OR_FILE, ONE_ARG, argv[0]);
            return FAILURE;
        }
    }

    return SUCCESS;
}


// Temp function for test internam command
BOOL GetCmdLine(LPWSTR lpCmdLine) {

    WCHAR szCurrentDirectory[MAX_PATH] = L"";
    GetCurrentDirectoryW(MAX_PATH, szCurrentDirectory);

    // Use "-" before ">" to identify which app's prompt (such as the OS built-in command prompt).
    if (CHECKRETURN(StrCmpW(szDisplayPrompt, L""))) {

        wprintf(L"%s>", szCurrentDirectory);
    }
    else {

        wprintf(L"%s", szDisplayPrompt);
    }

    WCHAR szCmdLine[600] = L"";
    fgetws(szCmdLine, 600, stdin);

    // Remove line feed at the end of line
    LPWSTR lpCmdLineSearch = StrStrW(szCmdLine, L"\n");
    *lpCmdLineSearch = L'\0';

    DbgPrint(L"\nPrompt> \"%s\"\n", szCmdLine);

    StrCpyW(lpCmdLine, szCmdLine);

    return SUCCESS;
}


BOOL ExecuteExternalCommands(LPWSTR lpCmdLine) {

    STARTUPINFO StartUpInfo = { 0 };
    StartUpInfo.cb = sizeof(StartUpInfo);
    PROCESS_INFORMATION ProcessInfo = { 0 };

    // Start the child process
    if (CHECKRETURN(CreateProcessW(NULL, lpCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &StartUpInfo, &ProcessInfo))) {

        return FAILURE;
    }

    // Wait until child process exits
    WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(ProcessInfo.hProcess);
    CloseHandle(ProcessInfo.hThread);

    return SUCCESS;
}
