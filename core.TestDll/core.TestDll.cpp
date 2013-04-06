// core.TestDll.cpp : Defines the entry point for the DLL application.
//
#include "core.TestDll.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

static int library_value = 0;

CORETESTDLL_API void __stdcall setValue(int value) {
	library_value = value;
}

CORETESTDLL_API int __stdcall getSum(int value) {
	return value + library_value;
}

