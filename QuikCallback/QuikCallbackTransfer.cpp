#include "QuikCallbackTransfer.h"
#include "aquila/core/WinApi.h"
#include "aquila/core/Lock.h"
#include "aquila/core/CriticalSection.h"

static wquik::IQuikCallbackHandler* handler = NULL;

bool APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
   return TRUE;
}

QUIKCALLBACKTRANSFER_API void __stdcall ConnectionStatusCallback
	(long nConnectionEvent, long nExtendedErrorCode, LPSTR lpstrInfoMessage)
{
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
	if ( handler ) {
		handler->onTradeStatus(nMode, dNumber, dOrderNum, lpstrClassCode,
			lpstrSecCode, dPrice, nQty, dValue, nIsSell, nTradeDescriptor);
	}
}

QUIKCALLBACKTRANSFER_API void __stdcall setHandler
	(wquik::IQuikCallbackHandler* ch)
{
	handler = ch;
}

