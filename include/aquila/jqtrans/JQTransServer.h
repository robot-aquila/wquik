/**
 * ============================================================================
 * 2013/01/28
 * $Id: JQTransServer.h 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */

#pragma once

#include <iostream>
#include "aquila/qtrans/QTrans.h"

namespace aquila {
	namespace jqtrans {

#define TRANS2QUIK_DLL	"TRANS2QUIK.dll"
#define CURRENT_DLL		"JQTrans.dll"

/**
 * «аменить им€ текущего модул€ на указанное.
 */
std::string replace_mod(std::string new_module) {
	std::string curr = CURRENT_DLL;
	HMODULE h = ::GetModuleHandleA(curr.c_str());
	char path[MAX_PATH + 1] = { 0 };
	DWORD len = ::GetModuleFileNameA(h, path, MAX_PATH);
	std::string result(path, len - curr.length());
	result.append(new_module);
	return result;
}

class JQTransServer {
public:
	JQTransServer(JQTransHandler* handler) throw (std::exception) {
		try {
			trans = new qtrans::QTrans(handler, replace_mod(TRANS2QUIK_DLL));
			trans->init();
		} catch ( std::exception & e ) {
			delete trans;
			cerr << "Cannot instantiate QTrans: " << e.what() << endl;
			throw e;
		}
	}

	virtual void connect(std::string connParam) throw (std::exception) {
		try {
			trans->connect(connParam);
		} catch ( qtrans::QTransException &e ) {
			throw std::exception(e.what());
		}
	}

	virtual void disconnect() throw (std::exception) {
		try {
			trans->disconnect();
		} catch ( qtrans::QTransException &e ) {
			throw std::exception(e.what());
		}
	}

	virtual void send(std::string transactionString) throw (std::exception) {
		try {
			trans->send(transactionString);
		} catch ( qtrans::QTransException &e ) {
			throw std::exception(e.what());
		}
	}

	virtual bool isDllConnected() {
		return trans->isDllConnected();
	}

	virtual bool isQuikConnected() {
		return trans->isQuikConnected();
	}

	virtual std::string getOrderAccount(unsigned long orderDescriptor) {
		return trans->getOrderAccount(orderDescriptor);
	}

	virtual std::string getOrderClientCode(unsigned long orderDescriptor) {
		return trans->getOrderClientCode(orderDescriptor);
	}

	virtual std::string getOrderFirmId(unsigned long orderDescriptor) {
		return trans->getOrderFirmId(orderDescriptor);
	}

	virtual unsigned long getOrderQty(unsigned long orderDescriptor) {
		return trans->getOrderQty(orderDescriptor);
	}

	virtual unsigned long getOrderDate(unsigned long orderDescriptor) {
		return trans->getOrderDate(orderDescriptor);
	}

	virtual unsigned long getOrderTime(unsigned long orderDescriptor) {
		return trans->getOrderTime(orderDescriptor);
	}

	virtual unsigned long getOrderActivationTime(unsigned long orderDescriptor) {
		return trans->getOrderActivationTime(orderDescriptor);
	}

	virtual unsigned long getOrderWithdrawTime(unsigned long orderDescriptor) {
		return trans->getOrderWithdrawTime(orderDescriptor);
	}

	virtual unsigned long getOrderExpiry(unsigned long orderDescriptor) {
		return trans->getOrderExpiry(orderDescriptor);
	}

	virtual double getOrderAccruedInt(unsigned long orderDescriptor) {
		return trans->getOrderAccruedInt(orderDescriptor);
	}

	virtual double getOrderYield(unsigned long orderDescriptor) {
		return trans->getOrderYield(orderDescriptor);
	}

	virtual unsigned long getOrderUid(unsigned long orderDescriptor) {
		return trans->getOrderUid(orderDescriptor);
	}

	virtual std::string getOrderUserId(unsigned long orderDescriptor) {
		return trans->getOrderUserId(orderDescriptor);
	}

	virtual std::string getOrderBrokerRef(unsigned long orderDescriptor) {
		return trans->getOrderBrokerRef(orderDescriptor);
	}

	virtual unsigned long getTradeDate(unsigned long tradeDescriptor) {
		return trans->getTradeDate(tradeDescriptor);
	}

	virtual unsigned long getTradeSettleDate(unsigned long tradeDescriptor) {
		return trans->getTradeSettleDate(tradeDescriptor);
	}

	virtual unsigned long getTradeTime(unsigned long tradeDescriptor) {
		return trans->getTradeTime(tradeDescriptor);
	}

	virtual bool getTradeIsMarginal(unsigned long tradeDescriptor) {
		return trans->getTradeIsMarginal(tradeDescriptor);
	}

	virtual double getTradeAccruedInt(unsigned long tradeDescriptor) {
		return trans->getTradeAccruedInt(tradeDescriptor);
	}

	virtual double getTradeYield(unsigned long tradeDescriptor) {
		return trans->getTradeYield(tradeDescriptor);
	}

	virtual double getTradeTsCommission(unsigned long tradeDescriptor) {
		return trans->getTradeTsCommission(tradeDescriptor);
	}

	virtual double getTradeClearingCenterCommission(unsigned long tradeDescriptor) {
		return trans->getTradeClearingCenterCommission(tradeDescriptor);
	}

	virtual double getTradeExchangeCommission(unsigned long tradeDescriptor) {
		return trans->getTradeExchangeCommission(tradeDescriptor);
	}

	virtual double getTradeTradingSystemCommission(unsigned long tradeDescriptor) {
		return trans->getTradeTradingSystemCommission(tradeDescriptor);
	}

	virtual double getTradePrice2(unsigned long tradeDescriptor) {
		return trans->getTradePrice2(tradeDescriptor);
	}

	virtual double getTradeRepoRate(unsigned long tradeDescriptor) {
		return trans->getTradeRepoRate(tradeDescriptor);
	}

	virtual double getTradeRepoValue(unsigned long tradeDescriptor) {
		return trans->getTradeRepoValue(tradeDescriptor);
	}

	virtual double getTradeRepo2Value(unsigned long tradeDescriptor) {
		return trans->getTradeRepo2Value(tradeDescriptor);
	}

	virtual double getTradeAccruedInt2(unsigned long tradeDescriptor) {
		return trans->getTradeAccruedInt2(tradeDescriptor);
	}

	virtual long getTradeRepoTerm(unsigned long tradeDescriptor) {
		return trans->getTradeRepoTerm(tradeDescriptor);
	}

	virtual double getTradeStartDiscount(unsigned long tradeDescriptor) {
		return trans->getTradeStartDiscount(tradeDescriptor);
	}

	virtual double getTradeLowerDiscount(unsigned long tradeDescriptor) {
		return trans->getTradeLowerDiscount(tradeDescriptor);
	}

	virtual double getTradeUpperDiscount(unsigned long tradeDescriptor) {
		return trans->getTradeUpperDiscount(tradeDescriptor);
	}

	virtual bool getTradeBlockSecurities(unsigned long tradeDescriptor) {
		return trans->getTradeBlockSecurities(tradeDescriptor);
	}

	virtual std::string getTradeCurrency(unsigned long tradeDescriptor) {
		return trans->getTradeCurrency(tradeDescriptor);
	}

	virtual std::string getTradeSettleCurrency(unsigned long tradeDescriptor) {
		return trans->getTradeSettleCurrency(tradeDescriptor);
	}

	virtual std::string getTradeSettleCode(unsigned long tradeDescriptor) {
		return trans->getTradeSettleCode(tradeDescriptor);
	}

	virtual std::string getTradeAccount(unsigned long tradeDescriptor) {
		return trans->getTradeAccount(tradeDescriptor);
	}

	virtual std::string getTradeBrokerRef(unsigned long tradeDescriptor) {
		return trans->getTradeBrokerRef(tradeDescriptor);
	}

	virtual std::string getTradeClientCode(unsigned long tradeDescriptor) {
		return trans->getTradeClientCode(tradeDescriptor);
	}

	virtual std::string getTradeUserId(unsigned long tradeDescriptor) {
		return trans->getTradeUserId(tradeDescriptor);
	}

	virtual std::string getTradeFirmId(unsigned long tradeDescriptor) {
		return trans->getTradeFirmId(tradeDescriptor);
	}

	virtual std::string getTradePartnerFirmId(unsigned long tradeDescriptor) {
		return trans->getTradePartnerFirmId(tradeDescriptor);
	}

	virtual std::string getTradeExchangeCode(unsigned long tradeDescriptor) {
		return trans->getTradeExchangeCode(tradeDescriptor);
	}

	virtual std::string getTradeStationId(unsigned long tradeDescriptor) {
		return trans->getTradeStationId(tradeDescriptor);
	}

	virtual ~JQTransServer() {
		delete trans;
	}

private:
	qtrans::QTrans* trans;

};

	} // end namespace jqtrans
} // end namespace aquila