#pragma once
#include <windows.h>
#include <string>
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace wquik {

typedef struct {
	long			replyCode;
	unsigned long	transId;
	double			orderNumber;
	std::string		resultMessage;
} TransactionResult;

class IOrder : public IReferenceCounted
{
public:
	virtual ~IOrder(void){};
	virtual long getQty()=0;
	virtual long getDate()=0;
	virtual long getTime()=0;
	virtual long getActivationTime()=0;
	virtual long getWithdrawTime()=0;
	virtual long getExpiry()=0;
	virtual double getAccruedInt()=0;
	virtual double getYield()=0;
	virtual long getUID()=0;
	virtual const char* getUserId()=0;
	virtual const char* getAccount()=0;
	virtual const char* getBrokerRef()=0;
	virtual const char* getClientCode()=0;
	virtual const char* getFirmId()=0;

	virtual long getTransId()=0;
	virtual double getNumber()=0;
	virtual const char* getClassCode()=0;
	virtual const char* getSecCode()=0;
	virtual double getPrice()=0;
	virtual long getBalance()=0;
	virtual double getValue()=0;
	virtual bool isSell()=0;
	virtual long getStatus()=0;
};

class ITrade : public IReferenceCounted
{
public:
	virtual ~ITrade(void){};
	virtual long getDate()=0;
	virtual long getSettleDate()=0;
	virtual long getTime()=0;
	virtual bool isMarginal()=0;
	virtual double getAccruedInt()=0;
	virtual double getYield()=0;
	virtual double getTsCommission()=0;
	virtual double getClearingCenterCommission()=0;
	virtual double getExchangeCommission()=0;
	virtual double getTradingSystemCommission()=0;
	virtual double getPrice2()=0;
	virtual double getRepoRate()=0;
	virtual double getRepoValue()=0;
	virtual double getRepo2Value()=0;
	virtual double getAccruedInt2()=0;
	virtual long getRepoTerm()=0;
	virtual double getStartDiscount()=0;
	virtual double getLowerDiscount()=0;
	virtual double getUpperDiscount()=0;
	virtual long getBlockSecurities()=0;
	virtual const char* getCurrency()=0;
	virtual const char* getSettleCurrency()=0;
	virtual const char* getSettleCode()=0;
	virtual const char* getAccount()=0;
	virtual const char* getBrokerRef()=0;
	virtual const char* getClientCode()=0;
	virtual const char* getUserId()=0;
	virtual const char* getFirmId()=0;
	virtual const char* getPartnerFirmId()=0;
	virtual const char* getExchangeCode()=0;
	virtual const char* getStationId()=0;

	virtual double getNumber()=0;
	virtual double getOrderNumber()=0;
	virtual const char* getClassCode()=0;
	virtual const char* getSecCode()=0;
	virtual double getPrice()=0;
	virtual long getQty()=0;
	virtual bool isSell()=0;
	virtual double getValue()=0;
};

class ITransactionDriverCallback
{
public:
	virtual ~ITransactionDriverCallback(void){};
	virtual void onConnectionStatus
		(long eventId, long errorCode, const char* message)=0;
	virtual void onTransactionReply
		(long result, long errorCode, const TransactionResult* tr)=0;
	virtual void onOrderStatus(long mode, IOrder* order)=0;
	virtual void onTradeStatus(long mode, ITrade* trade)=0;
};

class ITransactionDriver : public IReferenceCounted
{
public:
	virtual ~ITransactionDriver(void){};
	virtual void setAsyncMode()=0;
	virtual void setSyncMode()=0;
	virtual bool isSyncMode()=0;
	virtual bool isAsyncMode()=0;
	virtual void connect(const char* path)=0;
	virtual void disconnect()=0;
	virtual bool isQuikConnected()=0;
	virtual bool isDllConnected()=0;
	virtual void sendSyncTransaction(const char* str, TransactionResult* tr)=0;
	virtual void sendAsyncTransaction(const char* str)=0;
	virtual void setCallbackHandler(ITransactionDriverCallback* cb)=0;
};

} // end namespace wquik
