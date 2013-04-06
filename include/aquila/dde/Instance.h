/**
 * ============================================================================
 * 2011/07/18
 * $Id: Instance.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/IWinApi.h"
#include "aquila/dde/IInstance.h"
#include "aquila/dde/ICallbackHandler.h"
#include "aquila/core/auto_grab.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

/**
 * Экземпляр DDE. Синглтон. Непотокобезопасный.
 */
class Instance : public IInstance {
public:

	virtual ~Instance();

	Instance(IWinApi* pWinApi, ICallbackHandler *pCallbackHandler,
			int iCodePage)
		throw (std::exception);

	IString* createString(std::string str)
		throw (std::exception);

	IString* wrapString(HSZ hsz);

	IData* wrapData(HDDEDATA hData);

	IConversation* wrapConversation(HCONV hConv);

	int getLastError();

	void nameService(IString* name, UINT afCmd)
		throw (std::string);

	DWORD getId();

	IWinApi* getWinApi();

	ICallbackHandler* getCallbackHandler();

	int getCodePage();

	static HDDEDATA CALLBACK CallbackFunction(UINT uType, UINT uFmt,
		HCONV hconv, HSZ hsz1, HSZ hsz2, HDDEDATA hdata, ULONG_PTR dwData1,
		ULONG_PTR dwData2);

private:
	auto_grab<ICallbackHandler> callbackHandler;
	auto_grab<IWinApi> winApi;
	DWORD idInst;
	int codePage;

};

	} // end namespace dde
} // end namespace aquila