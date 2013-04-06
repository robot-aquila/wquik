/**
 * ============================================================================
 * 2011/04/04
 * $Id: DataBuffer.h 96 2011-08-11 17:36:58Z whirlwind $
 * ============================================================================
 */

#pragma once
#include "aquila/core/IDataBuffer.h"

namespace aquila {
	namespace core {

class DataBuffer : public IDataBuffer {
public:

	DataBuffer(DWORD bufferSize) : size(bufferSize) {
		ptr = new BYTE[bufferSize];
	}

	virtual ~DataBuffer() {
		delete[] ptr;
	}

	inline LPBYTE getPointer() {
		return ptr;
	}

	inline DWORD getSize() {
		return size;
	}

private:
	LPBYTE ptr;
	DWORD size;
};

	} // end namespace core
} // end namespace aquila
