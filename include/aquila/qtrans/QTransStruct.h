/**
 * ============================================================================
 * 2013-03-14
 * $Id: QTransStruct.h 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */

#pragma once
#include <string>

using namespace std;

struct QTransOrderStatus {
	long mode;
	unsigned long transId;
	unsigned long orderId;
	string classCode;
	string secCode;
	double price;
	long balance;
	double value;
	bool isSell;
	long status;
	unsigned long orderDescriptor;
};

struct QTransTradeStatus {
	long mode;
	unsigned long id;
	unsigned long orderId;
	string classCode;
	string secCode;
	double price;
	long qty;
	double value;
	bool isSell;
	unsigned long tradeDescriptor;
};


