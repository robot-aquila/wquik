/**
 * ============================================================================
 * 2011/04/04
 * $Id: IDataBuffer.h 96 2011-08-11 17:36:58Z whirlwind $
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"

namespace aquila {
	namespace core {

class IDataBuffer : public IReferenceCounted {
public:
	virtual ~IDataBuffer() { }
	virtual LPBYTE getPointer()=0;
	virtual DWORD getSize()=0;
};

	} // end namespace core
} // end namespace aquila
