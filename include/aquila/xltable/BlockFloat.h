#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: BlockFloat.h 104 2011-08-15 09:47:48Z whirlwind $
 * –еализаци€ стратегии чтени€ последовательности float €чеек
 *=============================================================================
 */

#include "aquila/xltable/IBlock.h"

namespace aquila {
	namespace xltable {

		class BlockFloat : public IBlock {
		public:

			virtual ~BlockFloat(void) { }

			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)
			{
				int count = stream->readWord() / sizeof(double);
				for ( int i = 0; i < count; i ++ ) {
					cells->addFloat(stream->readFloat());
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila