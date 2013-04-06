#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id$
 * Интерфейс фасада к библиотеке XlTable
 *=============================================================================
 */

#include "aquila/core/IDataBuffer.h"
#include "aquila/core/IReferenceCounted.h"
#include "aquila/xltable/IDataStream.h"
#include "aquila/xltable/ITableRange.h"

using namespace aquila::core;

namespace aquila {
	namespace xltable {

		class IFacade : public IReferenceCounted {
		public:
			virtual ~IFacade() { }

			/**
			 * Создать поток данных
			 *
			 * Создает объект доступа к данным на основе указателя и размера
			 * буффера данных.
			 */
			virtual IDataStream* createStream(LPBYTE buffer,
											  unsigned int bufferSize)=0;

			virtual IDataStream* createStream(IDataBuffer* buffer)=0;

			/**
			 * Прочитать таблицу
			 */
			virtual ITableRange* readTable(const char* topic,
										   const char* item,
										   IDataStream* stream)=0;
		};


	} // end namespace xltable
}
