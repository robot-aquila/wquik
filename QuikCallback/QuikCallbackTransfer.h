#pragma once

#include <windows.h>
#include "wquik/IQuikCallbackHandler.h"

#ifdef QUIKCALLBACK_EXPORTS
#define QUIKCALLBACKTRANSFER_API extern "C" __declspec(dllexport)
#else
#define QUIKCALLBACKTRANSFER_API extern "C" __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

QUIKCALLBACKTRANSFER_API void __stdcall ConnectionStatusCallback
	(long nConnectionEvent, long nExtendedErrorCode, LPSTR lpstrInfoMessage);

QUIKCALLBACKTRANSFER_API void __stdcall TransactionReplyCallback
	(long nTransactionResult, long nTransactionExtendedErrorCode,
	long nTransactionReplyCode, DWORD dwTransId, double dOrderNum,
	LPSTR lpstrTransactionReplyMessage);

QUIKCALLBACKTRANSFER_API void __stdcall OrderStatusCallback
	(long nMode, DWORD dwTransID, double dNumber, LPSTR lpstrClassCode,
	LPSTR lpstrSecCode, double dPrice, long nBalance, double dValue,
	long nIsSell, long nStatus, long nOrderDescriptor);

QUIKCALLBACKTRANSFER_API void __stdcall TradeStatusCallback
	(long nMode, double dNumber, double dOrderNum, LPSTR lpstrClassCode,
	LPSTR lpstrSecCode, double dPrice, long nQty, double dValue,
	long nIsSell, long nTradeDescriptor);

QUIKCALLBACKTRANSFER_API void __stdcall setHandler
	(wquik::IQuikCallbackHandler* handler);

#ifdef __cplusplus
}
#endif
