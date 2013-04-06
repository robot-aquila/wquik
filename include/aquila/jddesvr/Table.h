/**
 * ============================================================================
 * 2011/08/12
 * $Id: Table.h 543 2013-02-25 06:35:27Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#pragma warning(disable:4290)
#include <string>
#include "aquila/core/auto_grab.h"
#include "aquila/xltable/ITableRange.h"
#include "aquila/jddesvr/Cell.h"

using namespace std;

namespace aquila {
	namespace jddesvr {

/**
 * Класс-адаптер таблицы xlTable для использования на стороне Java.
 */
class Table {
public:
	Table(aquila::xltable::ITableRange* native) : table(native) {

	}

	virtual ~Table() {

	}

	virtual Table* makeCopy() {
		Table* copy = new Table(table.get());
		return copy;
	}

	virtual string getTopic() {
		return table->getTopic();
	}

	virtual string getItem() {
		return table->getItem();
	}

	virtual int getRows() {
		return table->getRows();
	}

	virtual int getCols() {
		return table->getCols();
	}

	virtual Cell getCell(int row, int col) throw (exception) {
		return Cell(table->getCell(row, col));
	}

private:
	auto_grab<aquila::xltable::ITableRange> table;
};

	} // end namespace jddesvr
} // end namespace aquila