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
	 * �����������.
	 *
	 * pInstance - ��������� DDE.
	 * pWinApi - �������� ��� ��������� WinApi. ����������� �����������
	 * ������� ������ ����� �������.
	 * hConv - ���������� �����������.
	 */
	Conversation(IInstance* pInstance, IWinApi* pWinApi, HCONV hConv);

	virtual ~Conversation();

	/**
	 * �������� ���������� �����������.
	 */
	HCONV getHandle();

	/**
	 * �������� ��������� �������� WinApi-�������.
	 */
	IWinApi* getWinApi();

	/**
	 * �������� ��������� �������� DDE.
	 */
	IInstance* getInstance();

	/**
	 * �������� ��� �������.
	 */
	string getServiceName();

	/**
	 * �������� �����.
	 */
	string getTopic();

private:
	HCONV handle;
	auto_grab<IWinApi> winApi;
	auto_grab<IInstance> instance;
};

	} // end namespace dde
} // end namespace aquila
