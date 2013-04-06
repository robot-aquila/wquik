/**
 *=============================================================================
 * ������ ����� ������������ ����� ������������� ��������� DLL.
 * ���������� ��� �������� ���������� ����������� dll. ��������, ����������
 * TRANS2QUIK.dll, � ����� ����������� ����������� ������ � ����������� �������
 * ������������ QUIK-� (��� �������� ������������ ���������� ��� ����������). 
 *
 * � ������ ���������� ���������� ����� ���, ������ ������:
 *
 *	http://forum.antichat.ru/threadnav132116-1-10.html
 *
 * ������� �������� slesh �� ����������� ������!
 *
 *=============================================================================
 */

#pragma once
#include <string>
#include "aquila/core/IDll.h"

using namespace std;

namespace aquila {
	namespace core {

class SleshLibrary : public IDll {
public:
	SleshLibrary(const char* moduleName);
	FARPROC getProcAddress(const char* procName);
	virtual ~SleshLibrary(void);
private:
	void free();
	void getLastError(string & str, LPCSTR lpszFunction);
	void progressReloc(ULONG retadr);
	void progressImport(ULONG retadr);

private:
	HMODULE hmod;
};

	} // end namespace core
} // end namespace aquila
