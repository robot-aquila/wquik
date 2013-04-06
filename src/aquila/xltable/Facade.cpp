/**
 * ============================================================================
 * 2011/08/12
 * $Id: Facade.cpp 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */
#include "aquila/xltable/Facade.h"
#include "aquila/xltable/DataStream.h"
#include "aquila/xltable/CellAggregator.h"
#include "aquila/xltable/CellFactory.h"
#include "aquila/xltable/BlockFactory.h"
#include "aquila/xltable/BlockRegistry.h"
#include "aquila/xltable/TableRange.h"
#include "aquila/core/auto_drop.h"

using namespace aquila::core;

namespace aquila {
	namespace xltable {

Facade::Facade() {

}

Facade::~Facade() {

}

IDataStream* Facade::createStream(LPBYTE buffer,
							      unsigned int bufferSize)
{
	return new DataStream(buffer, bufferSize);
}

IDataStream* Facade::createStream(IDataBuffer* buffer) {
	return new DataStream(buffer);
}

ITableRange* Facade::readTable(const char* topic,
						       const char* item,
						       IDataStream* stream)
{
	stream->readDword(); // skip table data type & size
	int rows = stream->readWord();
	int cols = stream->readWord();

	auto_drop<ICellFactory> cellFactory(new CellFactory());
	auto_drop<ICellAggregator> cellAggregator(new CellAggregator(cellFactory));
	ITableRange* table = new TableRange(rows,cols,topic,item,cellAggregator);

	auto_drop<IBlockFactory> blockFactory(new BlockFactory());
	auto_drop<IBlockFactory> blockRegistry(new BlockRegistry(blockFactory));

	try {
		unsigned int totalCellCount = cols * rows;
		while ( cellAggregator->getCellCount() < totalCellCount ) {
			blockRegistry->produceBlock(stream->readWord())
				->readBlock(stream, cellAggregator);
		}
		return table;
	} catch ( ... ) {
		table->drop();
		throw;
	}
}

	} // end namespace xltable
} // end namespace aquila