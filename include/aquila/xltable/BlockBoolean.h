#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: BlockBoolean.h 104 2011-08-15 09:47:48Z whirlwind $
 * –еализаци€ стратегии чтени€ последовательности булевых €чеек
 *=============================================================================
 */

#include "aquila/xltable/IBlock.h"

namespace aquila {
	namespace xltable {

		class BlockBoolean : public IBlock {
		public:

			virtual ~BlockBoolean(void) { }

			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)
			{
				int count = stream->readWord() / sizeof(WORD);
				for ( int i = 0; i < count; i ++ ) {
					cells->addBoolean(stream->readWord() == 1);
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila