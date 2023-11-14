/*++

Copyright (c) ssYanhuo.  All rights reserved.

!!!!!!!!!!!!!!!IMPORTANT NOTE!!!!!!!!!!!!!!!
Remember to edit "Config.c" before compile!!!

Abstract:

    This Uefi application helps launch Power Monkey and boot custom image (e.g. Windows) automatically.

--*/

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathToText.h>

#include <Config.c>  //Edit this before compile.

extern CONST UINT32 _gUefiDriverRevision = 0;

CHAR8* gEfiCallerBaseName = "PMLoader";

EFI_STATUS
EFIAPI
UefiUnload(
    IN EFI_HANDLE ImageHandle
)
{
    ASSERT(FALSE);
}

EFI_STATUS
EFIAPI
ConvertTextToPath(
    IN CHAR16* Text,
    OUT EFI_DEVICE_PATH_PROTOCOL** Path
)
{
    EFI_STATUS efiStatus;
    EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL* DevicePathFromText;

    efiStatus = gBS->LocateProtocol(&gEfiDevicePathFromTextProtocolGuid, NULL, (VOID**)&DevicePathFromText);
    if (EFI_ERROR(efiStatus)) {
        Print(L"Error locating DevicePathFromText protocol: %r\n", efiStatus);
        return efiStatus;
    }

    *Path = DevicePathFromText->ConvertTextToDevicePath(Text);

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
LoadAndStartEFIFile(
    IN CHAR16* FilePath
)
{
    EFI_STATUS efiStatus;
    VOID* ImageHandle;

    EFI_DEVICE_PATH_PROTOCOL* Path = NULL;

    efiStatus = ConvertTextToPath(FilePath, &Path);
    if (EFI_ERROR(efiStatus)) {
        Print(L"Error converting file path: %r\n", efiStatus);
        return efiStatus;
    }

    efiStatus = gBS->LoadImage(FALSE, gImageHandle, Path, NULL, 0, &ImageHandle);
    if (EFI_ERROR(efiStatus)) {
        Print(L"Error loading image: %r\n", efiStatus);
        return efiStatus;
    }
    Print(L"Load");

    efiStatus = gBS->StartImage(ImageHandle, NULL, NULL);
    if (EFI_ERROR(efiStatus)) {
        Print(L"Error starting image: %r\n", efiStatus);
        return efiStatus;
    }

    return efiStatus;
}

EFI_STATUS
EFIAPI
UefiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE* SystemTable
)
{
    EFI_STATUS efiStatus;

    efiStatus = LoadAndStartEFIFile(cPowerMonkeyDevicePath);
    if (EFI_ERROR(efiStatus))
    {
        Print(L"Failed to start image: %lx\n", efiStatus);
        goto Exit;
    }

    efiStatus = LoadAndStartEFIFile(cCustomBootImageDevicePath);
    if (EFI_ERROR(efiStatus))
    {
        Print(L"Failed to start image: %lx\n", efiStatus);
        goto Exit;
    }


Exit:
    return efiStatus;
}

