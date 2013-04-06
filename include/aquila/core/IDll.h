/**
 *=============================================================================
 * 2010/05/06
 * $Id$
 *
 * Интерфейс DLL библиотеки
 *=============================================================================
 */

#pragma once
#include <exception>
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"

namespace aquila {
	namespace core {

class DllException : public std::exception {
public:
	DllException(const char* text) : std::exception(text) { }
};

class IDll : public IReferenceCounted {
public:
	virtual ~IDll() { }
	virtual FARPROC getProcAddress(const char* procName)=0;
};

	} // end namespace core
} // end namespace wquik
