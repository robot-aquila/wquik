#pragma once
#include "aquila/xltable/ICell.h"

namespace aquila {
	namespace xltable {

		class CellInteger : public ICell {
		public:
			CellInteger(int value) { this->value = value; }
			virtual ~CellInteger(void){ }
			virtual bool	isFloat() { return false; }
			virtual bool	isBoolean() { return false; }
			virtual bool	isString() { return false; }
			virtual bool	isError() { return false; }
			virtual bool	isBlank() { return false; }
			virtual bool	isInteger() { return true; }
			virtual bool	isSkip() { return false; }
			virtual double	asFloat() { return 0.0; }
			virtual bool	asBoolean() { return false; }
			virtual string	asString() { return ""; }
			virtual int		asInteger() { return value; }

		private:
			int value;
		};

	} // end namespace xltable
} // end namespace aquila