#include<iostream>

#include<windows.h>
#include<TlHelp32.h>
#include "pch.h"
#include "Utils.h"

DWORD WINAPI HackThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Hack thread initiated.." << std::endl;

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    bool bHealth = false, bAmmo = false, bRecoil = false;
  
    while (1) {

        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
            if (bHealth) {
                *(uintptr_t*)(*((uintptr_t*)(moduleBase + 0x10F4F4)) + 0xF8) = 6969;
                std::cout << "Health cheat enabled" << std::endl;
            }
            else {
                std::cout << "Health cheat disabled" << std::endl;
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bAmmo = !bAmmo;
            if (bAmmo) {
                *(int*)mem::findDMAAddy(moduleBase + 0x10F4F4, { 0x374, 0x14, 0x0 }) = 6969;
                std::cout << "Ammo cheat enabled" << std::endl;
            }
            else {
                std::cout << "Ammo cheat disabled" << std::endl;
            }

        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bRecoil = !bRecoil;
            if (bRecoil) {
                mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
                std::cout << "Recoil cheat enabled" << std::endl;
            }
            else {
                mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
                std::cout << "Recoil cheat disabled" << std::endl;

            }
        }
    }
    FreeConsole();
    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule,0, nullptr ));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

