#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: BlockInteger.h 104 2011-08-15 09:47:48Z whirlwind $
 * –еализаци€ стратегии чтени€ последовательности целочисленных €чеек
 *=============================================================================
 */

#include "aquila/xltable/IBlock.h"

namespace aquila {
	namespace xltable {

		class BlockInteger : public IBlock {
		public:

			virtual ~BlockInteger(void) { }

			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)
			{
				int count = stream->readWord() / sizeof(WORD);
				for ( int i = 0; i < count; i ++ ) {
					cells->addInteger(stream->readWord());
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila