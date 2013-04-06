/**
 * ============================================================================
 * 2011/04/01
 * $Id: IReferenceCounted.h 96 2011-08-11 17:36:58Z whirlwind $
 * Базовый объект:
 * - запрет на копирование объектов
 * - автоуничтожение при нулевом счетчике ссылок
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
	 * Увеличить счетчик ссылок
	 *
	 * Увеличивает счетчик ссылок и возвращает указатель на объект.
	 */
	virtual void* grab(void);

	/**
	 * Уменьшить счетчик ссылок
	 *
	 * Уменьшает счетчик ссылок и удаляет объект, если нет больше ссылок.
	 * Возвращает true если объект был удален.
	 */
	virtual bool drop(void);

	/**
	 * Получить счетчик ссылок
	 *
	 * Возвращает значение счетчика ссылок.
	 */
	virtual unsigned long getRefCount();

private:
	IReferenceCounted(const IReferenceCounted&);
	const IReferenceCounted& operator=(const IReferenceCounted&);

	unsigned long referenceCount;
};

	} // end namespace core
} // end namespace namespace
