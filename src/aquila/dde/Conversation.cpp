/**
 * ============================================================================
 * 2011/07/18
 * $Id: Conversation.cpp 189 2012-01-30 16:03:21Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/dde/Conversation.h"
#include "aquila/core/auto_drop.h"

namespace aquila {
	namespace dde {

Conversation::Conversation(IInstance* pInstance, IWinApi* pWinApi, HCONV hConv)
:	instance(pInstance),
	winApi(pWinApi),
	handle(hConv)
{

}

Conversation::~Conversation() {

}

HCONV Conversation::getHandle() {
	return handle;
}

IWinApi* Conversation::getWinApi() {
	return winApi;
}

IInstance* Conversation::getInstance() {
	return instance;
}

string Conversation::getServiceName() {
	CONVINFO ci;
	::ZeroMemory(&ci, sizeof(ci));
	ci.cb = sizeof(ci);
	winApi->DdeQueryConvInfo(handle, QID_SYNC, &ci);
	auto_drop<IString> name(instance->wrapString(ci.hszServiceReq));
	return name->getString();
}

string Conversation::getTopic() {
	CONVINFO ci;
	::ZeroMemory(&ci, sizeof(ci));
	ci.cb = sizeof(ci);
	winApi->DdeQueryConvInfo(handle, QID_SYNC, &ci);
	auto_drop<IString> str(instance->wrapString(ci.hszTopic));
	return str->getString();
}


	} // end namespace dde
} // end namespace aquila