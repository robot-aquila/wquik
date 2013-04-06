#pragma once

#include "wquik/ITransactionDriver.h"
#include "wquik/ITrans2QuikAPI.h"

namespace wquik {

class Order : public IOrder
{
public:
	Order(long transId, double number, const char* classCode,
		const char* secCode, double price, long balance, double value,
		bool isSell, long status, long descriptor, ITrans2QuikAPI* quik);
	virtual ~Order(void);
	virtual long getQty();
	virtual long getDate();
	virtual long getTime();
	virtual long getActivationTime();
	virtual long getWithdrawTime();
	virtual long getExpiry();
	virtual double getAccruedInt();
	virtual double getYield();
	virtual long getUID();
	virtual const char* getUserId();
	virtual const char* getAccount();
	virtual const char* getBrokerRef();
	virtual const char* getClientCode();
	virtual const char* getFirmId();

	virtual long getTransId();
	virtual double getNumber();
	virtual const char* getClassCode();
	virtual const char* getSecCode();
	virtual double getPrice();
	virtual long getBalance();
	virtual double getValue();
	virtual bool isSell();
	virtual long getStatus();

private:
	long			_transId;
	double			_number;
	const char*		_classCode;
	const char*		_secCode;
	double			_price;
	long			_balance;
	double			_value;
	bool			_isSell;
	long			_status;
	long			_descriptor;
	ITrans2QuikAPI*	_quik;

public:
#ifdef CWQUIK_TESTING
#pragma message ("Order was generated with additional methods")
public:
	ITrans2QuikAPI* getTrans2QuikAPI() { return _quik; }
#endif

};

} // end namespace wquik
