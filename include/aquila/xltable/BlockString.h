#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: BlockString.h 104 2011-08-15 09:47:48Z whirlwind $
 * –еализаци€ стратегии чтени€ последовательности строковых €чеек
 *=============================================================================
 */

#include "aquila/xltable/IBlock.h"

namespace aquila {
	namespace xltable {

		class BlockString : public IBlock {
		public:

			virtual ~BlockString(void) { }

			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)
			{
				int size;
				int count = stream->readWord();
				while ( count > 0 ) {
					size = stream->readByte();
					cells->addString(stream->readString(size), size);
					count -= (size + 1);
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila