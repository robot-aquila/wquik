/**
 * ============================================================================
 * 2013-01-26
 * $Id: QTransHandler.h 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */

#pragma once
#include <string>
#include "aquila/qtrans/QTransStruct.h"

using namespace std;

namespace aquila {
	namespace qtrans {


class QTransHandler {
public:
	QTransHandler() { }

	virtual ~QTransHandler() { }

	virtual void
		OnConnectionStatus(long connEvent, long errCode, string errMsg) { }

	virtual void OnTransactionReply(long resultCode, long errCode,
		long replyCode, unsigned long transId, long long orderId,
		string replyMsg) { }

	virtual void OnOrderStatus(QTransOrderStatus& status) { }

	virtual void OnTradeStatus(QTransTradeStatus& status) { }

};

	} // ens namespace qtrans
} // end namespace aquila