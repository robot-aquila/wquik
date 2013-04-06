#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: ICellAggregator.h 104 2011-08-15 09:47:48Z whirlwind $
 * ��������� ����� XlTable
 *=============================================================================
 */

#include "aquila/xltable/ICell.h"
#include "aquila/xltable/XltException.h"

namespace aquila {
	namespace xltable {

		class ICellAggregator : public IReferenceCounted {
		public:
			virtual ~ICellAggregator(void) { }

			/**
			 * �������� ���������� �����
			 *
			 * ���������� ���������� �������������� �����.
			 */
			virtual unsigned int getCellCount()=0;

			/**
			 * �������� ������ �� �������
			 *
			 * ���������� ��������� ������ � ��������� ��������.
			 * ����������� ����������, ����������� ��
			 * XltException, ���� ������ � ����� ��������
			 * ����������� ��� �� �������������������.
			 */
			virtual ICell* getCell(unsigned int index)=0;

			/**
			 * �������� ������ ������������� ����
			 */
			virtual unsigned int addFloat(double value)=0;

			/**
			 * �������� ������ ������ ����
			 */
			virtual unsigned int addBoolean(bool value)=0;

			/**
			 * �������� ������ ���������� ����
			 */
			virtual unsigned int addString(const char* lpstr, int size)=0;

			/**
			 * �������� ������ �������������� ����
			 */
			virtual unsigned int addInteger(int value)=0;

			/**
			 * �������� ������ ���� ������
			 */
			virtual unsigned int addError()=0;

			/**
			 * �������� ������ ������
			 */
			virtual unsigned int addBlank()=0;

			/**
			 * �������� �������
			 */
			virtual unsigned int addSkip()=0;

		};

	} // end namespace xltable
} // end namespace aquila