/**
 * ============================================================================
 * 2011/07/12
 * $Id: IInstance.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/dde/IString.h"
#include "aquila/dde/IData.h"
#include "aquila/dde/IConversation.h"

namespace aquila {
	namespace dde {

/**
 * Интерфейс объектной оболочки экземпляра DDE.
 * Методы, которые не реализованы, так как не задействованы
 * сервером DDE, выступающим в роли приемника данных из QUIK.
 *	connect
 *	createData
 *	postAdvice
 *	enableCallback
 */
class IInstance : public IReferenceCounted {
public:

	IInstance() { }

	virtual ~IInstance() { }

	/**
	 * Создать новую DDE строку.
	 *
	 * Счетчик ссылок возвращаемого экземпляра IString равен 1.
	 * Кодировка строк устанавливается единая для экземпляра инстанса.
	 */
	virtual IString* createString(std::string str)=0;

	/**
	 * Обернуть существующую DDE строку.
	 *
	 * Используется для работы с входящими строками.
	 * Счетчик ссылок возвращаемого экземпляра IString равен 1.
	 * Кодировка строк устанавливается единая для экземпляра инстанса.
	 * Возвращает NULL, если аргумент равен NULL.
	 */
	virtual IString* wrapString(HSZ hsz)=0;

	/**
	 * Обернуть существующие DDE данные.
	 *
	 * Используется для работы с входящими данными.
	 * Счетчик ссылок возвращаемого экземпляра IData равен 1.
	 */
	virtual IData* wrapData(HDDEDATA hData)=0;

	/**
	 * Обернуть существующий дескриптор подключения.
	 *
	 * Используется для работы с входящими данными.
	 * Счетчик ссылок возвращаемого экземпляра равен 1.
	 */
	virtual IConversation* wrapConversation(HCONV hConv)=0;

	/**
	 * Получить код последней ошибки.
	 */
	virtual int getLastError()=0;

	/**
	 * Зарегистрировать/удалить DDE-сервис.
	 */
	virtual void nameService(IString* name, UINT afCmd)=0;

	/**
	 * Получить идентификатор инстанса.
	 *
	 * Возвращает идентификатор инстанса, полученный в результате
	 * вызова DdeInitialize.
	 */
	virtual DWORD getId()=0;

	/**
	 * Получить кодировку строк.
	 */
	virtual int getCodePage()=0;

};

	} // end namespace dde
} // end namespace aquila
