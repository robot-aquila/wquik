#pragma once
#include "aquila/xltable/ICell.h"

namespace aquila {
	namespace xltable {

		class CellString : public ICell {
		public:
			CellString(const char* value, int size) {
				this->value.append(value, size);
			}

			virtual ~CellString(void){ }
			virtual bool	isFloat() { return false; }
			virtual bool	isBoolean() { return false; }
			virtual bool	isString() { return true; }
			virtual bool	isError() { return false; }
			virtual bool	isBlank() { return false; }
			virtual bool	isInteger() { return false; }
			virtual bool	isSkip() { return false; }
			virtual double	asFloat() { return 0.0; }
			virtual bool	asBoolean() { return false; }
			virtual string	asString() { return value; }
			virtual int		asInteger() { return 0; }

		private:
			string value;
		};

	} // end namespace xltable
} // end namespace aquila