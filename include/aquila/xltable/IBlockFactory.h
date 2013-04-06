#pragma once
/**
 *=============================================================================
 * 2011/03/30
 * $Id: IBlockFactory.h 104 2011-08-15 09:47:48Z whirlwind $
 * ��������� ������� ��������� ������ ������ XlTable
 *=============================================================================
 */

#include "aquila/core/IReferenceCounted.h"
#include "aquila/xltable/IBlock.h"

using namespace aquila::core;

namespace aquila {
	namespace xltable {

		class IBlockFactory : public IReferenceCounted {
		public:
			virtual ~IBlockFactory(void) { }

			/**
			 * ��������� �����
			 *
			 * ������� ��������� ������, ��������������� ���������� ����
			 * ����� tdt (��. ������ XlTable). ����������� ���������� ������
			 * XltException � ������, ���� ������� ������������ �������������
			 * ���� �����.
			 */
			virtual IBlock* produceBlock(unsigned short tdt)=0;

		};

	} // end namespace xltable
} // end namespace aquila