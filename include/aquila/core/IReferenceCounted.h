/**
 * ============================================================================
 * 2011/04/01
 * $Id: IReferenceCounted.h 96 2011-08-11 17:36:58Z whirlwind $
 * ������� ������:
 * - ������ �� ����������� ��������
 * - ��������������� ��� ������� �������� ������
 * ============================================================================
 */
#pragma once

namespace aquila {
	namespace core {

class IReferenceCounted {
public:
	virtual ~IReferenceCounted(void);

	IReferenceCounted(void);

	/**
	 * ��������� ������� ������
	 *
	 * ����������� ������� ������ � ���������� ��������� �� ������.
	 */
	virtual void* grab(void);

	/**
	 * ��������� ������� ������
	 *
	 * ��������� ������� ������ � ������� ������, ���� ��� ������ ������.
	 * ���������� true ���� ������ ��� ������.
	 */
	virtual bool drop(void);

	/**
	 * �������� ������� ������
	 *
	 * ���������� �������� �������� ������.
	 */
	virtual unsigned long getRefCount();

private:
	IReferenceCounted(const IReferenceCounted&);
	const IReferenceCounted& operator=(const IReferenceCounted&);

	unsigned long referenceCount;
};

	} // end namespace core
} // end namespace namespace
