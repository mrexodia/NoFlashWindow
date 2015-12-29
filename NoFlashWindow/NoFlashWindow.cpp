#include <windows.h>

static void DisableFlashWindow()
{
    HINSTANCE hUser32 = GetModuleHandleW(L"user32.dll");
    if (!hUser32)
    {
        OutputDebugStringW(L"[NoFlashWindow] GetModuleHandleW failed for user32.dll...");
        return;
    }

    PVOID pFlashWindow = (PVOID)GetProcAddress(hUser32, "FlashWindow");
    if (pFlashWindow)
    {
        BYTE ret4[] = { 0xC2, 0x04, 0x00 };
        if (WriteProcessMemory(GetCurrentProcess(), pFlashWindow, ret4, sizeof(ret4), NULL))
            OutputDebugStringW(L"[NoFlashWindow] FlashWindow disabled!");
        else
            OutputDebugStringW(L"[NoFlashWindow] WriteProcessMemory failed for FlashWindow...");
    }
    else
        OutputDebugStringW(L"[NoFlashWindow] GetProcAddress failed for FlashWindow...");

    PVOID pFlashWindowEx = (PVOID)GetProcAddress(hUser32, "FlashWindowEx");
    if (pFlashWindowEx)
    {
        BYTE ret8[] = { 0xC2, 0x08, 0x00 };
        if (WriteProcessMemory(GetCurrentProcess(), pFlashWindowEx, ret8, sizeof(ret8), NULL))
            OutputDebugStringW(L"[NoFlashWindow] FlashWindowEx disabled!");
        else
            OutputDebugStringW(L"[NoFlashWindow] WriteProcessMemory failed for FlashWindowEx...");
    }
    else
        OutputDebugStringW(L"[NoFlashWindow] GetProcAddress failed for FlashWindowEx...");
}

extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableFlashWindow();
        break;
    }
    return TRUE; // succesful
}