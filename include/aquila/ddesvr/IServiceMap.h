/**
 * ============================================================================
 * 2011/07/29
 * $Id: IServiceMap.h 101 2011-08-11 18:37:57Z whirlwind $
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/ICriticalSection.h"
#include "aquila/dde/ICallbackHandler.h"
#include <exception>
#include <string>

using namespace std;
using namespace aquila::core;
using namespace aquila::dde;

namespace aquila {
	namespace ddesvr {

/**
 * Интерфейс карты сервисов. Карта сервисов обеспечивает доступ к обработчику
 * транзакций на основе строкового или целочисленного идентификатора.
 */
class IServiceMap : public IReferenceCounted {
public:

	/**
	 * Проверить наличие сервиса по имени сервиса.
	 */
	virtual bool has(string name)=0;

	/**
	 * Проверить наличие сервиса по идентификатору сервиса.
	 */
	virtual bool has(long serviceId)=0;

	/**
	 * Добавить сервис. Выбрасывает исключение, если сервис с указанным именем
	 * уже зарегистрирован.
	 */
	virtual long add(string name, ICallbackHandler* pHandler)
		throw (exception)=0;

	/**
	 * Удалить сервис по имени. Выбрасывает исключение, если сервис с
	 * указанным именем не найден.
	 */
	virtual void remove(string name) throw (exception)=0;

	/**
	 * Удалить сервис по идентификатору. Выбрасывает исключение, если
	 * сервис с указанным идентификатором не найден.
	 */
	virtual void remove(long serviceId) throw (exception)=0;

	/**
	 * Удалить все сервисы.
	 */
	virtual void removeAll()=0;

	/**
	 * Получить имя сервиса по идентификатора. Выбрасывает исключение,
	 * если сервис с указанным идентификатором не найден.
	 */
	virtual string getName(long serviceId) throw (exception)=0;

	/**
	 * Получить идентификатор сервиса по имени. Выбрасывает исключение,
	 * если сервис с указанным именем не найден.
	 */
	virtual long getId(string name) throw (exception)=0;

	/**
	 * Получить обработчик, соответствующий сервису с указанным
	 * идентификатором. Выбрасывает исключение, если сервис с указанным
	 * идентификатором не найден.
	 */
	virtual ICallbackHandler* get(long serviceId) throw (exception)=0;

	/**
	 * Получить обработчик, соответствующий сервисву с указанным именем.
	 * Выбрасывает исключение, если сервис с указанным именем не найден.
	 */
	virtual ICallbackHandler* get(string name) throw (exception)=0;

	/**
	 * Получить критическую секцию, использующуюся для блокировки при
	 * выполнении операций. Критическая секция может быть использована для
	 * организации последовательности вызовов.
	 */
	virtual ICriticalSection* getCriticalSection()=0;

	virtual ~IServiceMap() { }

};

	} // end namespace ddesvr
} // end namespace aquila