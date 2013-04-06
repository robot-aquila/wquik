#include "wquik/Order.h"

namespace wquik {

Order::Order(long transId, double number, const char* classCode,
	const char* secCode, double price, long balance, double value,
	bool isSell, long status, long descriptor, ITrans2QuikAPI* quik)
:
	_transId(transId), _number(number), _classCode(classCode),
	_secCode(secCode), _price(price), _balance(balance), _value(value),
	_isSell(isSell), _status(status), _descriptor(descriptor)
{
	_quik = (ITrans2QuikAPI*)quik->grab();
}

Order::~Order(void) {
	_quik->drop();
}

long Order::getQty() {
	return _quik->ORDER_QTY(_descriptor);
}

long Order::getDate() {
	return _quik->ORDER_DATE(_descriptor);
}

long Order::getTime() {
	return _quik->ORDER_TIME(_descriptor);
}

long Order::getActivationTime() {
	return _quik->ORDER_ACTIVATION_TIME(_descriptor);
}

long Order::getWithdrawTime() {
	return _quik->ORDER_WITHDRAW_TIME(_descriptor);
}

long Order::getExpiry() {
	return _quik->ORDER_EXPIRY(_descriptor);
}

double Order::getAccruedInt() {
	return _quik->ORDER_ACCRUED_INT(_descriptor);
}

double Order::getYield() {
	return _quik->ORDER_YIELD(_descriptor);
}

long Order::getUID() {
	return _quik->ORDER_UID(_descriptor);
}

const char* Order::getUserId() {
	return (const char*)_quik->ORDER_USERID(_descriptor);
}

const char* Order::getAccount() {
	return (const char*)_quik->ORDER_ACCOUNT(_descriptor);
}

const char* Order::getBrokerRef() {
	return (const char*)_quik->ORDER_BROKERREF(_descriptor);
}

const char* Order::getClientCode() {
	return (const char*)_quik->ORDER_CLIENT_CODE(_descriptor);
}

const char* Order::getFirmId() {
	return (const char*)_quik->ORDER_FIRMID(_descriptor);
}

long Order::getTransId() {
	return _transId;
}

double Order::getNumber() {
	return _number;
}

const char* Order::getClassCode() {
	return _classCode;
}

const char* Order::getSecCode() {
	return _secCode;
}

double Order::getPrice() {
	return _price;
}

long Order::getBalance() {
	return _balance;
}

double Order::getValue() {
	if ( _price <= 0.0000001 ) {
		return 0;
	}
	return _value;
}

bool Order::isSell() {
	return _isSell;
}

long Order::getStatus() {
	return _status;
}

} // end namespace wquik
