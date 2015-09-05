#pragma once

#include <windows.h>

#define FUNCTION_NAME_getSum		"_getSum@4"
#define FUNCTION_NAME_setValue		"_setValue@4"
#define TEST_PROCESS_ATTACH_MARKER	99182
#define TEST_PROCESS_DETACH_MARKER	TEST_PROCESS_ATTACH_MARKER + 1
#define TEST_THREAD_ATTACH_MARKER	TEST_PROCESS_ATTACH_MARKER + 2
#define TEST_THREAD_DETACH_MARKER	TEST_PROCESS_ATTACH_MARKER + 3

#ifdef CORETESTDLL_EXPORTS
#define CORETESTDLL_API extern "C" __declspec(dllexport)
#else
#define CORETESTDLL_API extern "C" __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

CORETESTDLL_API void __stdcall setValue(int value);
CORETESTDLL_API int __stdcall getSum(int value);

#ifdef __cplusplus
}
#endif
