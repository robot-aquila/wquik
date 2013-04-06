#pragma once

namespace wquik {

#define FN(fn) FN_ ## fn				// function name
#define FNP(fn) FNT_ ## fn				// function pointer
#define FNPT(fn) (__stdcall *FNP(fn))	// function pointer typedef
#define FNPA(fn) fptr_ ## fn			// function pointer attribute
#define FNPAD(fn) FNP(fn) FNPA(fn)		// function pointer attribute declaration
#define FNPI(lib, fn) FNPA(fn) = (FNP(fn))lib->getProcAddress(FN(fn))

} // end namespace wquik
