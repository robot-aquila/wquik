/**
 * ============================================================================
 * 2011/08/11
 * $Id: StandardLibrary.h 96 2011-08-11 17:36:58Z whirlwind $
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IDll.h"

namespace aquila {
	namespace core {

class StandardLibrary : public IDll {
public:
	StandardLibrary(const char* moduleName);
	FARPROC getProcAddress(const char* procName);
	virtual ~StandardLibrary(void);
private:
	void free();
private:
	HINSTANCE hlib;
};

	} // end namespace core
} // end namespace aquila