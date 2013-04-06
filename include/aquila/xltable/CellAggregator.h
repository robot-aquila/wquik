#pragma once

#include <vector>
#include "aquila/xltable/ICellFactory.h"
#include "aquila/xltable/ICellAggregator.h"

using namespace std;

namespace aquila {
	namespace xltable {

		class CellAggregator : public ICellAggregator {
		public:
			CellAggregator(ICellFactory* factory) {
				this->factory = (ICellFactory*)factory->grab();
			}

			virtual ~CellAggregator(void){
				factory->drop();
				for ( unsigned int i = 0; i < cells.size(); i ++ ) {
					cells[i]->drop();
				}
			}

			unsigned int getCellCount() {
				return cells.size();
			}

			ICell* getCell(unsigned int index) {
				if ( index >= cells.size() ) {
					throw XltException("Cell index out of range");
				}
				return cells[index];
			}

			unsigned int addCell(ICell* cell) {
				cells.push_back(cell);
				return cells.size() - 1;
			}

			unsigned int addFloat(double value) {
				return addCell(factory->createFloat(value));
			}

			unsigned int addBoolean(bool value) {
				return addCell(factory->createBoolean(value));
			}

			unsigned int addString(const char* lpstr, int size) {
				return addCell(factory->createString(lpstr, size));
			}

			unsigned int addInteger(int value) {
				return addCell(factory->createInteger(value));
			}

			unsigned int addError() {
				return addCell(factory->createError());
			}

			unsigned int addBlank() {
				return addCell(factory->createBlank());
			}

			unsigned int addSkip() {
				return addCell(factory->createSkip());
			}

		private:
			vector<ICell*> cells;
			ICellFactory* factory;

		};

	} // end namespace xltable
} // end namespace aquila
