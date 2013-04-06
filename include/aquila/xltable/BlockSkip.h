#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: BlockSkip.h 104 2011-08-15 09:47:48Z whirlwind $
 * ���������� ��������� ������ ������������������ ����������� �����
 *=============================================================================
 */

#include "aquila/xltable/IBlock.h"

namespace aquila {
	namespace xltable {

		class BlockSkip : public IBlock {
		public:

			virtual ~BlockSkip(void) { }

			virtual void readBlock(IDataStream* stream,
								   ICellAggregator* cells)
			{
				stream->readWord(); // ����� ������ 2
				int count = stream->readWord(); // ���������� ����������
				for ( int i = 0; i < count; i ++ ) {
					cells->addSkip();
				}
			}

		};

	} // end namespace xltable
} // end namespace aquila