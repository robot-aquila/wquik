#pragma once
#include "aquila/xltable/ICellFactory.h"
#include "aquila/xltable/CellBoolean.h"
#include "aquila/xltable/CellEmpty.h"
#include "aquila/xltable/CellFloat.h"
#include "aquila/xltable/CellInteger.h"
#include "aquila/xltable/CellString.h"

namespace aquila {
	namespace xltable {

		class CellFactory : public ICellFactory {
		public:
			virtual ~CellFactory(void){ }

			virtual ICell* createFloat(double value) {
				return new CellFloat(value);
			}

			virtual ICell* createBoolean(bool value) {
				return new CellBoolean(value);
			}

			virtual ICell* createString(const char* lpstr, int size) {
				return new CellString(lpstr, size);
			}

			virtual ICell* createInteger(int value) {
				return new CellInteger(value);
			}

			virtual ICell* createError() {
				return new CellEmpty(CELL_TYPE_ERROR);
			}

			virtual ICell* createBlank() {
				return new CellEmpty(CELL_TYPE_BLANK);
			}

			virtual ICell* createSkip() {
				return new CellEmpty(CELL_TYPE_SKIP);
			}

		};

	} // end namespace xltable
} // end namespace aquila