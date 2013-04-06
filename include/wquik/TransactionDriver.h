#pragma once
#include "wquik/ITransactionDriver.h"
#include "wquik/ITrans2QuikAPI.h"
#include "wquik/IQuikCallbackAPI.h"
#include "wquik/TransactionDriverException.h"

namespace wquik {

class TransactionDriver :
	public ITransactionDriver,
	public IQuikCallbackHandler
{
public:
	TransactionDriver(ITrans2QuikAPI* quik, IQuikCallbackAPI* callback);
	virtual ~TransactionDriver(void);

	virtual void setAsyncMode();
	virtual void setSyncMode();
	virtual bool isSyncMode();
	virtual bool isAsyncMode();
	virtual void connect(const char* path);
	virtual void disconnect();
	virtual bool isQuikConnected();
	virtual bool isDllConnected();
	virtual void sendSyncTransaction(const char* str, TransactionResult* tr);
	virtual void sendAsyncTransaction(const char* str);
	virtual void setCallbackHandler(ITransactionDriverCallback* cb);

	virtual void onConnectionStatus(long nConnectionEvent, long nExtendedErrorCode, LPSTR lpstrInfoMessage);
	virtual void onTransactionReply(long nTransactionResult, long nTransactionExtendedErrorCode, long nTransactionReplyCode, DWORD dwTransId, double dOrderNum, LPSTR lpstrTransactionReplyMessage);
	virtual void onOrderStatus(long nMode, DWORD dwTransID, double dNumber, LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice, long nBalance, double dValue, long nIsSell, long nStatus, long nOrderDescriptor);
	virtual void onTradeStatus(long nMode, double dNumber, double dOrderNum, LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice, long nQty, double dValue, long nIsSell, long nTradeDescriptor);

private:
	void setTransactionReplyCallback(TRANS2QUIK_TRANSACTION_REPLY_CALLBACK cb);

private:
	bool						_isSyncMode;
	bool						_isConnected;
	ITrans2QuikAPI*				_quik;
	IQuikCallbackAPI*			_callback;
	ITransactionDriverCallback* _callbackHandler;

#ifdef CWQUIK_TESTING
#pragma message ("TransactionDriver was generated with additional methods")
public:
	ITrans2QuikAPI* getTrans2QuikAPI() { return _quik; }
	IQuikCallbackAPI* getQuikCallbackAPI() { return _callback; }
#endif

};

} // end namespace wquik
