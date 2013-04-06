#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: TableRange.h 235 2012-07-23 15:52:48Z whirlwind $
 * ���������� ������� ������� � ������������ � �������� XlTable
 *=============================================================================
 */

#include "aquila/xltable/ITableRange.h"
#include "aquila/xltable/ICellAggregator.h"
#include "aquila/xltable/XltException.h"

namespace aquila {
	namespace xltable {

		class TableRange : public ITableRange {
		public:

			/**
			 * �����������
			 * rows - ���������� �����
			 * cols - ���������� �������
			 * lpszTopic - ����������� �� ������ ���� (������ ������
			 *             ������� ��������� DDE-����������)
			 * lpszItem - ��������� �� ������ ������ (������ ������
			 *            ������� ��������� DDE-����������)
			 * cells - ������ ����� ������� (������ ����������� �������
			 *         ������)
			 */
			TableRange(int rows, int cols,
					   const char* lpszTopic, const char* lpszItem,
					   ICellAggregator* cells)
			{
				this->rows = rows;
				this->cols = cols;
				this->cells = (ICellAggregator*)cells->grab();
				topic = lpszTopic;
				item = lpszItem;
			}

			virtual ~TableRange(void) {
				cells->drop();
			}

			const char* getTopic() {
				return topic.c_str();
			}

			const char* getItem() {
				return item.c_str();
			}

			int getRows() {
				return rows;
			}

			int getCols() {
				return cols;
			}

			ICell* getCell(int row, int col) {
				if ( row >= rows )
					throw XltException("Row index out of range");
				if ( col >= cols )
					throw XltException("Col index out of range");
				return cells->getCell(row * cols + col);
			}

		private:
			int rows;
			int cols;
			string topic;
			string item;
			ICellAggregator* cells;

		};

	} // end namespace xltable
} // end namespace aquila