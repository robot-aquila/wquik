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
 * Интерфейс объектной оболочки потока.
 */
class IThread : public IReferenceCounted {
public:

	IThread() { }

	virtual ~IThread() { }

	/** 
	 * Запустить поток.
	 */
	virtual void start() throw(std::exception, WinApiErrorException)=0;

	/**
	 * Проверка факта исполнения потока.
	 */
	virtual bool isAlive()=0;

	/**
	 * Ожидать завершения потока.
	 *
	 * Выбрасывает исключение, если поток не был запущен или функция
	 * WinApi вернула ошибку.
	 */
	virtual void join() throw(std::exception, WinApiErrorException)=0;

	/**
	 * Получить код завершения потока.
	 *
	 * Выбрасывает исключение, если поток не был запущен.
	 */
	virtual DWORD getExitCode() throw(std::exception, WinApiErrorException)=0;

	/**
	 * Получить дескриптор потока.
	 */
	virtual HANDLE getHandle()=0;

	/**
	 * Получить идентификатор потока.
	 */
	virtual DWORD getId()=0;

};

	} // end namespace core
} // end namespace aquila