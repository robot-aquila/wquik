#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: IBlock.h 104 2011-08-15 09:47:48Z whirlwind $
 * »нтерфейс стратегии чтени€ блока данных XlTable
 *=============================================================================
 */

#include "aquila/core/IReferenceCounted.h"
#include "aquila/xltable/IDataStream.h"
#include "aquila/xltable/ICellAggregator.h"

using namespace aquila::core;

namespace aquila {
	namespace xltable {

		class IBlock : public IReferenceCounted {
		public:
			virtual ~IBlock(void) { }

			/**
			 * ѕрочитать блок данных
			 *
			 * ћетод разбирает очередной блок данных, формирует
			 * соответствующие экземпл€ры €чеек и передает их на сохранение
			 * агрегатору €чеек.
			 */
			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)=0;
		};

	} // end namespace xltable
} // end namespace aquila