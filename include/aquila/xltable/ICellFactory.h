#pragma once
#include "aquila/xltable/ICell.h"

namespace aquila {
	namespace xltable {

		class ICellFactory : public IReferenceCounted {
		public:
			virtual ~ICellFactory(void){}
			virtual ICell* createFloat(double value)=0;
			virtual ICell* createBoolean(bool value)=0;
			virtual ICell* createString(const char* lpstr, int size)=0;
			virtual ICell* createInteger(int value)=0;
			virtual ICell* createError()=0;
			virtual ICell* createBlank()=0;
			virtual ICell* createSkip()=0;
		};

	} // end namespace xltable
} // end namespace aquila