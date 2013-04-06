#pragma once
#include "aquila/xltable/ICell.h"

namespace aquila {
	namespace xltable {

		class CellFloat : public ICell {
		public:
			CellFloat(double value) { this->value = value; }
			virtual ~CellFloat(void){ }
			virtual bool	isFloat() { return true; }
			virtual bool	isBoolean() { return false; }
			virtual bool	isString() { return false; }
			virtual bool	isError() { return false; }
			virtual bool	isBlank() { return false; }
			virtual bool	isInteger() { return false; }
			virtual bool	isSkip() { return false; }
			virtual double	asFloat() { return value; }
			virtual bool	asBoolean() { return false; }
			virtual string	asString() { return ""; }
			virtual int		asInteger() { return 0; }

		private:
			double value;
		};

	} // end namespace xltable
} // end namespace aquila