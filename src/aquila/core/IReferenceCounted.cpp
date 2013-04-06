#include "aquila/core/IReferenceCounted.h"

namespace aquila {
	namespace core {

	IReferenceCounted::IReferenceCounted()
		: referenceCount(1)
	{

	}

	IReferenceCounted::~IReferenceCounted() {

	}

	void* IReferenceCounted::grab() {
		referenceCount ++;
		return this;
	}

	bool IReferenceCounted::drop() {
		referenceCount --;
		if ( referenceCount <= 0 ) {
			delete this;
			return true;
		}
		return false;
	}

	unsigned long IReferenceCounted::getRefCount() {
		return referenceCount;
	}

	} // end namespace core
} // end namespace aquila