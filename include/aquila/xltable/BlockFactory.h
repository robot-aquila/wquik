#pragma once
/**
 *=============================================================================
 * 2011/03/30
 * $Id: BlockFactory.h 104 2011-08-15 09:47:48Z whirlwind $
 * Реализация фабрики стратегий чтения блоков XlTable.
 * Инстанцирует все доступные типы IBlock.
 *=============================================================================
 */

#include "aquila/xltable/IBlockFactory.h"
#include "aquila/xltable/XltException.h"
#include "aquila/xltable/BlockFloat.h"
#include "aquila/xltable/BlockString.h"
#include "aquila/xltable/BlockBoolean.h"
#include "aquila/xltable/BlockError.h"
#include "aquila/xltable/BlockBlank.h"
#include "aquila/xltable/BlockInteger.h"
#include "aquila/xltable/BlockSkip.h"

namespace aquila {
	namespace xltable {

		class BlockFactory : public IBlockFactory {
		public:
			virtual ~BlockFactory(void) { }

			BlockFactory() {

			}

			virtual IBlock* produceBlock(unsigned short tdt) {
				switch ( tdt ) {
					case 1: return new BlockFloat();
					case 2: return new BlockString();
					case 3: return new BlockBoolean();
					case 4: return new BlockError();
					case 5: return new BlockBlank();
					case 6: return new BlockInteger();
					case 7: return new BlockSkip();
					default:
						char buffer[255];
						sprintf_s(buffer, sizeof(buffer),
							"Unknown block type: %d", tdt);
						throw XltException(buffer);
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila