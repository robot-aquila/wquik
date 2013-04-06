#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id$
 * Фасад к библиотеке XlTable
 *=============================================================================
 */

#include "aquila/xltable/IFacade.h"

namespace aquila {
	namespace xltable {

		class Facade : public IFacade {
		public:
			virtual ~Facade();

			Facade();

			IDataStream* createStream(LPBYTE buffer,
									  unsigned int bufferSize);

			IDataStream* createStream(IDataBuffer* buffer);

			ITableRange* readTable(const char* topic,
								   const char* item,
								   IDataStream* stream);
		};


	} // end namespace xltable
} // end namespace aquila
