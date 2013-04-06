/**
 * ============================================================================
 * 2011/08/12
 * $Id: Cell.h 489 2013-02-05 16:06:16Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#pragma warning(disable:4290)
#include <string>
#include <exception>
#include "aquila/core/auto_grab.h"
#include "aquila/xltable/ICell.h"

using namespace std;

namespace aquila {
	namespace jddesvr {

class Cell {
public:
	Cell(aquila::xltable::ICell* native) : cell(native) {

	}

	virtual ~Cell() {
	}

	virtual bool isFloat() {
		return cell->isFloat();
	}

	virtual bool isBoolean() {
		return cell->isBoolean();
	}

	virtual bool isString() {
		return cell->isString();
	}

	virtual bool isInteger() {
		return cell->isInteger();
	}

	virtual bool isError() {
		return cell->isError();
	}

	virtual bool isBlank() {
		return cell->isBlank();
	}

	virtual bool isSkip() {
		return cell->isSkip();
	}

	virtual double asFloat() {
		return cell->asFloat();
	}

	virtual bool asBoolean() {
		return cell->asBoolean();
	}

	virtual string asString() {
		return cell->asString();
	}

	virtual int asInteger() {
		return cell->asInteger();
	}

private:
	auto_grab<aquila::xltable::ICell> cell;
};

	} // end namespace jddesvr
} // end namespace aquila