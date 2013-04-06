/**
 * ============================================================================
 * 2011/08/11
 * $Id: StandardLibrary.cpp 96 2011-08-11 17:36:58Z whirlwind $
 * ============================================================================
 */

#include "aquila/core/StandardLibrary.h"
#include <string>

using namespace std;

namespace aquila {
	namespace core {

StandardLibrary::StandardLibrary(const char* modName) {
	hlib = LoadLibrary(modName);
	if ( hlib == NULL ) {
		string s = "Unable to load dll: ";
		s += modName;
		throw DllException(s.c_str());
	}
}

StandardLibrary::~StandardLibrary(void) {
	free();
}

void StandardLibrary::free() {
	FreeLibrary(hlib);
}

FARPROC StandardLibrary::getProcAddress(const char *procName) {
	FARPROC addr = GetProcAddress(hlib, procName);
	if ( addr == NULL ) {
		string s = "Procedure not found: ";
		s += procName;
		throw DllException(s.c_str());
	}
	return addr;
}

	} // end namespace core
} // end namespace aquila