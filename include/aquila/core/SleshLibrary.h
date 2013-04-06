/**
 *=============================================================================
 * Данный класс представляет собой специфический загрузчик DLL.
 * Разработан для загрузки нескольких экземпляров dll. Например, библиотеки
 * TRANS2QUIK.dll, с целью обеспечения возможности работы с несколькими разными
 * экземплярами QUIK-а (при загрузке стандартными средствами это невозможно). 
 *
 * В основе реализации загрузчика лежит код, взятый отсюда:
 *
 *	http://forum.antichat.ru/threadnav132116-1-10.html
 *
 * Спасибо товарищу slesh за выполненную работу!
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
