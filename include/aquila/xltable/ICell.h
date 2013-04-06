#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id$
 * ��������� ������ XlTable
 *=============================================================================
 */

#include "aquila/core/IReferenceCounted.h"
#include <string>

using namespace std;
using namespace aquila::core;

namespace aquila {
	namespace xltable {

		class ICell : public IReferenceCounted {
		public:
			virtual ~ICell(void){}

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� ������ ���� float
			 */
			virtual bool isFloat()=0;

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� ������ ������ ����
			 */
			virtual bool isBoolean()=0;

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� ������ ���������� ����
			 */
			virtual bool isString()=0;

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� ������ �������������� ����
			 */
			virtual bool isInteger()=0;

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� ������ ���� ������
			 */
			virtual bool isError()=0;

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� ������ ������
			 */
			virtual bool isBlank()=0;

			/**
			 * �������� ����
			 *
			 * ���������� true, ���� �������� ������ ��������� (�������)
			 */
			virtual bool isSkip()=0;

			/**
			 * �������� � ���� ������������� �����
			 *
			 * ���������� �������� ������ ���� float
			 * ��� 0.0, ��� ����� ������� ����.
			 */
			virtual double asFloat()=0;

			/**
			 * �������� � ���� ������ ��������
			 *
			 * ��� ����� ������ ���� ���������� �������� ������.
			 * ��� ����� ������� ���� ������ ���������� false.
			 */
			virtual bool asBoolean()=0;

			/**
			 * �������� � ���� ������
			 *
			 * ��� ����� ���������� ���� ���������� �������� ������.
			 * ��� ����� ������ ����� ������ ���������� ������ ������.
			 */
			virtual string asString()=0;

			/**
			 * �������� � ���� ������
			 *
			 * ��� ����� �������������� ���� ���������� �������� ������.
			 * ��� ����� ������ ����� ������ ���������� 0.
			 */
			virtual int asInteger()=0;

		};

	} // end namespace xltable
} // end namespace aquila