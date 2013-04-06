/**
 * ============================================================================
 * 2011/07/08
 * $Id: Conversation.h 189 2012-01-30 16:03:21Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#include "aquila/core/auto_grab.h"
#include "aquila/core/IWinApi.h"
#include "aquila/dde/IConversation.h"
#include "aquila/dde/IInstance.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

class Conversation : public IConversation {
public:

	/**
	 * Конструктор.
	 *
	 * pInstance - экземпляр DDE.
	 * pWinApi - оболочка над функциями WinApi. Конструктор увеличивает
	 * счетчик ссылок этого объекта.
	 * hConv - дескриптор подключения.
	 */
	Conversation(IInstance* pInstance, IWinApi* pWinApi, HCONV hConv);

	virtual ~Conversation();

	/**
	 * Получить дескриптор подключения.
	 */
	HCONV getHandle();

	/**
	 * Получить экземпляр враппера WinApi-функций.
	 */
	IWinApi* getWinApi();

	/**
	 * Получить экземпляр инстанса DDE.
	 */
	IInstance* getInstance();

	/**
	 * Получить имя сервиса.
	 */
	string getServiceName();

	/**
	 * Получить топик.
	 */
	string getTopic();

private:
	HCONV handle;
	auto_grab<IWinApi> winApi;
	auto_grab<IInstance> instance;
};

	} // end namespace dde
} // end namespace aquila
