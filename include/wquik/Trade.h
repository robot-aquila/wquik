#pragma once

#include "wquik/ITransactionDriver.h"
#include "wquik/ITrans2QuikAPI.h"

namespace wquik {

class Trade : public ITrade
{
public:
	Trade(double number, double orderNumber, const char* classCode,
		const char* secCode, double price, long qty, double value,
		bool isSell, long descriptor, ITrans2QuikAPI* quik);
	virtual ~Trade(void);
	virtual long getDate();
	virtual long getSettleDate();
	virtual long getTime();
	virtual bool isMarginal();
	virtual double getAccruedInt();
	virtual double getYield();
	virtual double getTsCommission();
	virtual double getClearingCenterCommission();
	virtual double getExchangeCommission();
	virtual double getTradingSystemCommission();
	virtual double getPrice2();
	virtual double getRepoRate();
	virtual double getRepoValue();
	virtual double getRepo2Value();
	virtual double getAccruedInt2();
	virtual long getRepoTerm();
	virtual double getStartDiscount();
	virtual double getLowerDiscount();
	virtual double getUpperDiscount();
	virtual long getBlockSecurities();
	virtual const char* getCurrency();
	virtual const char* getSettleCurrency();
	virtual const char* getSettleCode();
	virtual const char* getAccount();
	virtual const char* getBrokerRef();
	virtual const char* getClientCode();
	virtual const char* getUserId();
	virtual const char* getFirmId();
	virtual const char* getPartnerFirmId();
	virtual const char* getExchangeCode();
	virtual const char* getStationId();

	virtual double getNumber();
	virtual double getOrderNumber();
	virtual const char* getClassCode();
	virtual const char* getSecCode();
	virtual double getPrice();
	virtual long getQty();
	virtual bool isSell();
	virtual double getValue();
private:
	double			_number;
	double			_orderNumber;
	const char*		_classCode;
	const char*		_secCode;
	double			_price;
	long			_qty;
	double			_value;
	bool			_isSell;
	long			_descriptor;
	ITrans2QuikAPI*	_quik;

public:
#ifdef CWQUIK_TESTING
#pragma message ("Trade was generated with additional methods")
public:
	ITrans2QuikAPI* getTrans2QuikAPI() { return _quik; }
#endif

};

} // end namespace wquik
