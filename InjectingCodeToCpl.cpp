// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <sstream>
#include <string.h>

//Cplapplet
extern "C" __declspec(dllexport) LONG Cplapplet(HWND hwndCpl, UINT msg, LPARAM lParam1, LPARAM lParam2)
{
    STARTUPINFO             startupInfo;
    PROCESS_INFORMATION     processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    std::wostringstream s;
    s << L"C:\\Windows\\System32\\cmd.exe";
    std::wstring cmdLine = s.str();

    GetStartupInfoW(&startupInfo);
    if (!CreateProcessW(NULL, &cmdLine[0], NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)
        )
    {
        printf("CreateProcess failed (%d) \n", GetLastError());
    }
    WaitForSingleObject(processInfo.hProcess, 300);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    MessageBoxA(NULL, "Hello CMD has been launched by .CPL file - YAHUDPOWER.", "Control Panel", 0);
    return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        Cplapplet(NULL, NULL, NULL, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}