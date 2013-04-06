#pragma once
#include "aquila/xltable/ICell.h"

namespace aquila {
	namespace xltable {

#define CELL_TYPE_ERROR		1
#define CELL_TYPE_BLANK		2
#define CELL_TYPE_SKIP		3

		class CellEmpty : public ICell {
		public:
			CellEmpty(int emptyType) { type = emptyType; }
			virtual ~CellEmpty(void){ }
			virtual bool	isFloat() { return false; }
			virtual bool	isBoolean() { return false; }
			virtual bool	isString() { return false; }
			virtual bool	isInteger() { return false; }
			virtual bool	isError() { return type == CELL_TYPE_ERROR; }
			virtual bool	isBlank() { return type == CELL_TYPE_BLANK; }
			virtual bool	isSkip() { return type == CELL_TYPE_SKIP; }
			virtual double	asFloat() { return 0.0; }
			virtual bool	asBoolean() { return false; }
			virtual string	asString() { return ""; }
			virtual int		asInteger() { return 0; }

		private:
			int type;
		};

	} // end namespace xltable
} // end namespace aquila