#pragma once
#include "aquila/xltable/ICell.h"

namespace aquila {
	namespace xltable {

		class CellBoolean : public ICell {
		public:
			CellBoolean(bool value) { this->value = value; }
			virtual ~CellBoolean(void){ }
			virtual bool	isFloat() { return false; }
			virtual bool	isBoolean() { return true; }
			virtual bool	isString() { return false; }
			virtual bool	isError() { return false; }
			virtual bool	isBlank() { return false; }
			virtual bool	isInteger() { return false; }
			virtual bool	isSkip() { return false; }
			virtual double	asFloat() { return 0.0; }
			virtual bool	asBoolean() { return value; }
			virtual string	asString() { return ""; }
			virtual int		asInteger() { return 0; }

		private:
			bool value;
		};

	} // end namespace xltable
} // end namespace aquila