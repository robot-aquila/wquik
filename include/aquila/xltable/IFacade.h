#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id$
 * ��������� ������ � ���������� XlTable
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
			 * ������� ����� ������
			 *
			 * ������� ������ ������� � ������ �� ������ ��������� � �������
			 * ������� ������.
			 */
			virtual IDataStream* createStream(LPBYTE buffer,
											  unsigned int bufferSize)=0;

			virtual IDataStream* createStream(IDataBuffer* buffer)=0;

			/**
			 * ��������� �������
			 */
			virtual ITableRange* readTable(const char* topic,
										   const char* item,
										   IDataStream* stream)=0;
		};


	} // end namespace xltable
}
