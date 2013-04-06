/**
 * ============================================================================
 * 2011/07/23
 * $Id: IThread.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/WinApiErrorException.h"
#include <exception>
#include <windows.h>

namespace aquila {
	namespace core {

/**
 * ��������� ��������� �������� ������.
 */
class IThread : public IReferenceCounted {
public:

	IThread() { }

	virtual ~IThread() { }

	/** 
	 * ��������� �����.
	 */
	virtual void start() throw(std::exception, WinApiErrorException)=0;

	/**
	 * �������� ����� ���������� ������.
	 */
	virtual bool isAlive()=0;

	/**
	 * ������� ���������� ������.
	 *
	 * ����������� ����������, ���� ����� �� ��� ������� ��� �������
	 * WinApi ������� ������.
	 */
	virtual void join() throw(std::exception, WinApiErrorException)=0;

	/**
	 * �������� ��� ���������� ������.
	 *
	 * ����������� ����������, ���� ����� �� ��� �������.
	 */
	virtual DWORD getExitCode() throw(std::exception, WinApiErrorException)=0;

	/**
	 * �������� ���������� ������.
	 */
	virtual HANDLE getHandle()=0;

	/**
	 * �������� ������������� ������.
	 */
	virtual DWORD getId()=0;

};

	} // end namespace core
} // end namespace aquila