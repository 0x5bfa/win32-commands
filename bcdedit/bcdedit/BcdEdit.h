// Copyright (c) 2021 WindowsComands
// Licensed under the MIT License.

#pragma once
#include <stdio.h>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")



#define FAILURE 0
#define SUCCESS 1

#define CHECKRETURN(x) ((x) == 0)

typedef struct _BCDEDIT {

    LPWSTR lpName;



}BCDEDIT, *PBCDEDIT;



// BCD Objects

// {emssettings}
#define GUID_EMS_SETTINGS_GROUP_STR                L"{0CE4991B-E6B3-4B16-B23C-5E0D9250E5D9}"

// {resumeloadersettings}
#define GUID_RESUME_LOADER_SETTINGS_GROUP_STR      L"{1AFA9C49-16AB-4A5C-4A90-212802DA9460}"

// {default}
#define GUID_DEFAULT_BOOT_ENTRY_STR                L"{1CAE1EB7-A0DF-4D4D-9851-4860E34EF535}"

// {kerneldbgsettings}
#define GUID_KERNEL_DEBUGGER_SETTINGS_GROUP_STR    L"{313E8EED-7098-4586-A9BF-309C61F8D449}"

// {dbgsettings} | {eventsettings}
#define GUID_DEBUGGER_SETTINGS_GROUP_STR           L"{4636856E-540F-4170-A130-A84776F4C654}"

// {legacy} | {ntldr}
#define GUID_WINDOWS_LEGACY_NTLDR_STR              L"{466F5A88-0AF2-4F76-9038-095B170DC21C}"

// {badmemory}
#define GUID_BAD_MEMORY_GROUP_STR                  L"{5189B25C-5558-4BF2-BCA4-289B11BD29E2}"

// {bootloadersettings}
#define GUID_BOOT_LOADER_SETTINGS_GROUP_STR        L"{6EFB52BF-1766-41DB-A6B3-0EE5EFF72BD7}"

// 
#define GUID_WINDOWS_SETUP_EFI_STR                 L"{7254A080-1510-4E85-AC0F-E7FB3D444736}"

// {globalsettings}
#define GUID_GLOBAL_SETTINGS_GROUP_STR             L"{7EA2E1AC-2E61-4728-AAA3-896D9D0A9F0E}"

// {hypervisorsettings}
#define GUID_HYPERVISOR_SETTINGS_GROUP_STR         L"{7FF607E0-4395-11DB-B0DE-0800200C9A66}"

// {bootmgr}
#define GUID_WINDOWS_BOOTMGR_STR                   L"{9DEA862C-5CDD-4E70-ACC1-F32B344D4795}"

// 
#define GUID_WINDOWS_OS_TARGET_TEMPLATE_PCAT_STR   L"{A1943BBC-EA85-487C-97C7-C9EDE908A38A}"

// {fwbootmgr}
#define GUID_FIRMWARE_BOOTMGR_STR                  L"{A5A30FA2-3D06-4E9F-B5F4-A01DF9D1FCBA}"

// {ramdiskoptions}
#define GUID_WINDOWS_SETUP_RAMDISK_OPTIONS_STR     L"{AE5534E0-A924-466C-B836-758539A3EE3A}"

// 
#define GUID_WINDOWS_OS_TARGET_TEMPLATE_EFI_STR    L"{B012B84D-C47C-4ED5-B722-C0C42163E569}"

// {memdiag}
#define GUID_WINDOWS_MEMORY_TESTER_STR             L"{B2721D73-1DB4-4C62-BF78-C548A880142D}"

// 
#define GUID_WINDOWS_SETUP_PCAT_STR                L"{CBD971BF-B7B8-4885-951A-FA03044F5D71}"

// {current}
#define GUID_CURRENT_BOOT_ENTRY_STR                L"{FA926493-6F1C-4193-A414-58F0B2456D1E}"
