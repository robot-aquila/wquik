#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: BlockError.h 104 2011-08-15 09:47:48Z whirlwind $
 * –еализаци€ стратегии чтени€ последовательности €чеек с ошибками
 *=============================================================================
 */

#include "aquila/xltable/IBlock.h"

namespace aquila {
	namespace xltable {

		class BlockError : public IBlock {
		public:

			virtual ~BlockError(void) { }

			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)
			{
				int count = stream->readWord() / sizeof(WORD);
				for ( int i = 0; i < count; i ++ ) {
					stream->readWord(); // код ошибки
					cells->addError();
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila