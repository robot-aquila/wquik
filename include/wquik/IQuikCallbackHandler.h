#pragma once

#include <windows.h>

namespace wquik {

class IQuikCallbackHandler {
public:
	virtual ~IQuikCallbackHandler(void){}

	virtual void onConnectionStatus(long nConnectionEvent,
		long nExtendedErrorCode, LPSTR lpstrInfoMessage)=0;

	virtual void onTransactionReply(long nTransactionResult,
		long nTransactionExtendedErrorCode, long nTransactionReplyCode,
		DWORD dwTransId, double dOrderNum,
		LPSTR lpstrTransactionReplyMessage)=0;

	virtual void onOrderStatus(long nMode, DWORD dwTransID, double dNumber,
		LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice,
		long nBalance, double dValue, long nIsSell, long nStatus,
		long nOrderDescriptor)=0;

	virtual void onTradeStatus(long nMode, double dNumber, double dOrderNum,
		LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice, long nQty,
		double dValue, long nIsSell, long nTradeDescriptor)=0;

};

} // end namespace wquik
