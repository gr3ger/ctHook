// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include "framework.h"
#include "detours.h"

using namespace std;

static char* (__cdecl* TrueSetLocale)(int , const char*) = std::setlocale;

char* HookedSetLocale(int category, const char* _locale)
{
  return TrueSetLocale(0, "en_US.UTF-8");
}

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  switch (ul_reason_for_call)
  {
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_ATTACH:
      DetourRestoreAfterWith();
      DetourTransactionBegin();
      DetourUpdateThread(GetCurrentThread());
      DetourAttach(&(PVOID&)TrueSetLocale, HookedSetLocale);
      DetourTransactionCommit();
      break;
    case DLL_PROCESS_DETACH:
      DetourTransactionBegin();
      DetourUpdateThread(GetCurrentThread());
      DetourDetach(&(PVOID&)TrueSetLocale, HookedSetLocale);
      DetourTransactionCommit();
      break;
  }
  return TRUE;
}