// core.TestDll.cpp : Defines the entry point for the DLL application.
//
#include "core.TestDll.h"

static int library_value = 0;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		library_value = TEST_PROCESS_ATTACH_MARKER;
		break;
	case DLL_PROCESS_DETACH:
		library_value = TEST_PROCESS_DETACH_MARKER;
		break;
	case DLL_THREAD_ATTACH:
		library_value = TEST_THREAD_ATTACH_MARKER;
		break;
	case DLL_THREAD_DETACH:
		library_value = TEST_THREAD_DETACH_MARKER;
		break;
	}
    return TRUE;
}

CORETESTDLL_API void __stdcall setValue(int value) {
	library_value = value;
}

CORETESTDLL_API int __stdcall getSum(int value) {
	return value + library_value;
}

