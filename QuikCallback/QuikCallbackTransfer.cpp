#include "QuikCallbackTransfer.h"
#include "aquila/core/auto_drop.h"
#include "aquila/core/auto_grab.h"
#include "aquila/core/WinApi.h"
#include "aquila/core/Lock.h"
#include "aquila/core/CriticalSection.h"

using namespace aquila::core;

static wquik::IQuikCallbackHandler* handler = NULL;
static auto_drop<IWinApi> p_winApi;
static auto_grab<ICriticalSection> p_cs;

bool APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		p_winApi = WinApi::getInstance();
		p_cs = new CriticalSection(p_winApi);
		break;
	}
	return TRUE;
}

QUIKCALLBACKTRANSFER_API void __stdcall ConnectionStatusCallback
	(long nConnectionEvent, long nExtendedErrorCode, LPSTR lpstrInfoMessage)
{
	Lock x(p_cs);
	if ( handler ) {
		handler->onConnectionStatus
			(nConnectionEvent, nExtendedErrorCode, lpstrInfoMessage);
	}
}

QUIKCALLBACKTRANSFER_API void __stdcall TransactionReplyCallback
	(long nTransactionResult, long nTransactionExtendedErrorCode,
	long nTransactionReplyCode, DWORD dwTrandId, double dOrderNum,
	LPSTR lpstrTransactionReplyMessage)
{
	Lock x(p_cs);
	if ( handler ) {
		handler->onTransactionReply
			(nTransactionResult, nTransactionExtendedErrorCode,
			nTransactionReplyCode, dwTrandId, dOrderNum,
			lpstrTransactionReplyMessage);
	}
}

QUIKCALLBACKTRANSFER_API void __stdcall OrderStatusCallback
	(long nMode, DWORD dwTrandId, double dNumber, LPSTR lpstrClassCode,
	LPSTR lpstrSecCode, double dPrice, long nBalance, double dValue,
	long nIsSell, long nStatus, long nOrderDescriptor)
{
	Lock x(p_cs);
	if ( handler ) {
		handler->onOrderStatus(nMode, dwTrandId, dNumber, lpstrClassCode,
			lpstrSecCode, dPrice, nBalance, dValue, nIsSell, nStatus,
			nOrderDescriptor);
	}
}

QUIKCALLBACKTRANSFER_API void __stdcall TradeStatusCallback
	(long nMode, double dNumber, double dOrderNum, LPSTR lpstrClassCode,
	LPSTR lpstrSecCode, double dPrice, long nQty, double dValue, long nIsSell,
	long nTradeDescriptor)
{
	Lock x(p_cs);
	if ( handler ) {
		handler->onTradeStatus(nMode, dNumber, dOrderNum, lpstrClassCode,
			lpstrSecCode, dPrice, nQty, dValue, nIsSell, nTradeDescriptor);
	}
}

QUIKCALLBACKTRANSFER_API void __stdcall setHandler
	(wquik::IQuikCallbackHandler* ch)
{
	Lock x(p_cs);
	handler = ch;
}

