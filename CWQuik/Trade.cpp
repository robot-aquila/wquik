#include "wquik/Trade.h"

namespace wquik {

Trade::Trade(double number, double orderNumber, const char* classCode,
	const char* secCode, double price, long qty, double value,
	bool isSell, long descriptor, ITrans2QuikAPI* quik)
:
	_number(number), _orderNumber(orderNumber), _classCode(classCode),
	_secCode(secCode), _price(price), _qty(qty), _value(value),
	_isSell(isSell), _descriptor(descriptor)
{
	_quik = (ITrans2QuikAPI*)quik->grab();
}

Trade::~Trade(void) {
	_quik->drop();
}

long Trade::getDate() {
	return _quik->TRADE_DATE(_descriptor);
}

long Trade::getSettleDate() {
	return _quik->TRADE_SETTLE_DATE(_descriptor);
}

long Trade::getTime() {
	return _quik->TRADE_TIME(_descriptor);
}

bool Trade::isMarginal() {
	return _quik->TRADE_IS_MARGINAL(_descriptor) == 0 ? false : true;
}

double Trade::getAccruedInt() {
	return _quik->TRADE_ACCRUED_INT(_descriptor);
}

double Trade::getYield() {
	return _quik->TRADE_YIELD(_descriptor);
}

double Trade::getTsCommission() {
	return _quik->TRADE_TS_COMMISSION(_descriptor);
}

double Trade::getClearingCenterCommission() {
	return _quik->TRADE_CLEARING_CENTER_COMMISSION(_descriptor);
}

double Trade::getExchangeCommission() {
	return _quik->TRADE_EXCHANGE_COMMISSION(_descriptor);
}

double Trade::getTradingSystemCommission() {
	return _quik->TRADE_TRADING_SYSTEM_COMMISSION(_descriptor);
}

double Trade::getPrice2() {
	return _quik->TRADE_PRICE2(_descriptor);
}

double Trade::getRepoRate() {
	return _quik->TRADE_REPO_RATE(_descriptor);
}

double Trade::getRepoValue() {
	return _quik->TRADE_REPO_VALUE(_descriptor);
}

double Trade::getRepo2Value() {
	return _quik->TRADE_REPO2_VALUE(_descriptor);
}

double Trade::getAccruedInt2() {
	return _quik->TRADE_ACCRUED_INT2(_descriptor);
}

long Trade::getRepoTerm() {
	return _quik->TRADE_REPO_TERM(_descriptor);
}

double Trade::getStartDiscount() {
	return _quik->TRADE_START_DISCOUNT(_descriptor);
}

double Trade::getLowerDiscount() {
	return _quik->TRADE_LOWER_DISCOUNT(_descriptor);
}

double Trade::getUpperDiscount() {
	return _quik->TRADE_UPPER_DISCOUNT(_descriptor);
}

long Trade::getBlockSecurities() {
	return _quik->TRADE_BLOCK_SECURITIES(_descriptor);
}

const char* Trade::getCurrency() {
	return (const char*)_quik->TRADE_CURRENCY(_descriptor);
}

const char* Trade::getSettleCurrency() {
	return (const char*)_quik->TRADE_SETTLE_CURRENCY(_descriptor);
}

const char* Trade::getSettleCode() {
	return (const char*)_quik->TRADE_SETTLE_CODE(_descriptor);
}

const char* Trade::getAccount() {
	return (const char*)_quik->TRADE_ACCOUNT(_descriptor);
}

const char* Trade::getBrokerRef() {
	return (const char*)_quik->TRADE_BROKERREF(_descriptor);
}

const char* Trade::getClientCode() {
	return (const char*)_quik->TRADE_CLIENT_CODE(_descriptor);
}

const char* Trade::getUserId() {
	return (const char*)_quik->TRADE_USERID(_descriptor);
}

const char* Trade::getFirmId() {
	return (const char*)_quik->TRADE_FIRMID(_descriptor);
}

const char* Trade::getPartnerFirmId() {
	return (const char*)_quik->TRADE_PARTNER_FIRMID(_descriptor);
}

const char* Trade::getExchangeCode() {
	return (const char*)_quik->TRADE_EXCHANGE_CODE(_descriptor);
}

const char* Trade::getStationId() {
	return (const char*)_quik->TRADE_STATION_ID(_descriptor);
}

double Trade::getNumber() {
	return _number;
}

double Trade::getOrderNumber() {
	return _orderNumber;
}

const char* Trade::getClassCode() {
	return (const char*)_classCode;
}

const char* Trade::getSecCode() {
	return (const char*)_secCode;
}

double Trade::getPrice() {
	return _price;
}

long Trade::getQty() {
	return _qty;
}

bool Trade::isSell() {
	return _isSell;
}

double Trade::getValue() {
	return _value;
}

} // end namespace wquik
