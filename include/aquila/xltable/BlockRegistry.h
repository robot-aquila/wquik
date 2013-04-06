#pragma once
/**
 *=============================================================================
 * 2011/03/30
 * $Id: BlockRegistry.h 104 2011-08-15 09:47:48Z whirlwind $
 * –еестр стратегий чтени€ блоков XlTable.
 *  еширует полученные от декорированной фабрики экземпл€ры и своевременно
 * удал€ет их при уничтожении реестра. “аким образом, пользовательский код
 * может не заморачиватьс€ производством, хранением и удалением стратегий
 * разбора блоков.
 *=============================================================================
 */

#include <map>
#include "aquila/xltable/IBlockFactory.h"

using namespace std;

namespace aquila {
	namespace xltable {

		class BlockRegistry : public IBlockFactory {
		public:
			virtual ~BlockRegistry(void) {
				factory->drop();
				map<unsigned short,IBlock*>::iterator it;
				for ( it = cache.begin(); it != cache.end(); it ++ ) {
					(*it).second->drop();
				}
			}

			BlockRegistry(IBlockFactory* factory) {
				this->factory = (IBlockFactory*)factory->grab();
			}

			virtual IBlock* produceBlock(unsigned short tdt) {
				map<unsigned short,IBlock*>::iterator it = cache.find(tdt);
				if ( it == cache.end() ) {
					IBlock* block = factory->produceBlock(tdt);
					cache[tdt] = block;
					return block;
				} else {
					return (*it).second;
				}
			}

		private:
			IBlockFactory* factory;
			map<unsigned short,IBlock*> cache;

		};

	} // end namespace xltable
} // end namespace aquila