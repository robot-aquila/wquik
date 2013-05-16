/**
 * ============================================================================
 * 2013/01/28
 * $Id: JQTransHandler.h 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */

#pragma once

#include "aquila/qtrans/QTransHandler.h"
#include <iostream>

namespace aquila {
	namespace jqtrans {

class JQTransHandler : public qtrans::QTransHandler {
public:
	JQTransHandler() {

	}

	virtual ~JQTransHandler() {

	}

	virtual void
		OnConnectionStatus(long connEvent, long errCode, std::string errMsg)
	{
		printf("JQTransHandler::OnConnectionStatus native stub\n");
	}

	virtual void OnTransactionReply(long resultCode, long errCode,
		long replyCode, unsigned long transId, long long orderId,
		std::string replyMsg)
	{
		printf("JQTransHandler::OnTransactionReply native stub\n");
	}

	virtual void OnOrderStatus(QTransOrderStatus& status) {
		printf("JQTransHandler::OnOrderStatus native stub\n");
	}

	virtual void OnTradeStatus(QTransTradeStatus& status) {
		printf("JQTransHandler::OnTradeStatus native stub\n");
	}

};

	} // end namespace jqtrans
} // end namespace aquila
