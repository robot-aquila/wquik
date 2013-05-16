/**
 * ============================================================================
 * ������ ���� �������� ����������� ����������� ������� �� TRANS2QUIK.dll,
 * ������������ � ���� ������. ������������� ������������ ���� ���������
 * ��������� ���������� �������� ������� � ����������� ������. ����������
 * �������� ���������� �������������� �����������.
 *
 * 2013-01-26
 * $Id: QTransManagedHandler.h 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */
#pragma once
#include <windows.h>
#include <vcclr.h>
#pragma unmanaged
#include "aquila/qtrans/trans2quik_api.h"
#pragma managed
#include "aquila/qtrans/QTransHandler.h"
#include "aquila/qtrans/QTransStruct.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace aquila {
	namespace qtrans {

public delegate void ConnStatusDlg(long, long, LPSTR);
public delegate void TransReplyDlg(long, long, long, DWORD, double, LPSTR);
public delegate void OrderStatusDlg(long, DWORD, double, LPSTR, LPSTR,
	double, long, double, long, long, long);
public delegate void TradeStatusDlg(long, double, double, LPSTR, LPSTR,
	double, long, double, long, long);

public ref class QTransManagedHandler {
public:
	QTransManagedHandler(QTransHandler* handler) {
		pHandler = handler;
		dConnStatus = gcnew ConnStatusDlg(this, &QTransManagedHandler::OnConnectionStatus);
		dTransReply = gcnew TransReplyDlg(this, &QTransManagedHandler::OnTransactionReply);
		dOrderStatus = gcnew OrderStatusDlg(this, &QTransManagedHandler::OnOrderStatus);
		dTradeStatus = gcnew TradeStatusDlg(this, &QTransManagedHandler::OnTradeStatus);
	}

	virtual ~QTransManagedHandler() {

	}

	void OnConnectionStatus(long connEvent, long errCode, LPSTR lpstr) {
		pHandler->OnConnectionStatus(connEvent, errCode,
			lpstr == 0 ? "" : lpstr);
	}

	void OnTransactionReply(long transResult, long errCode, long replyCode,
		DWORD dwTransId, double dOrderNum, LPSTR replyMsg)
	{
		pHandler->OnTransactionReply(transResult, errCode, replyCode,
			dwTransId, (long long) dOrderNum,
			replyMsg == 0 ? "" : replyMsg);
	}

	void OnOrderStatus(long mode, DWORD transId, double orderId,
		LPSTR classCode, LPSTR secCode, double price, long balance,
		double value, long isSell, long status, long orderDescriptor)
	{
		QTransOrderStatus arg;
		arg.mode = mode;
		arg.transId = transId;
		arg.orderId = (long long) orderId;
		arg.classCode = (classCode == 0 ? "" : classCode);
		arg.secCode = (secCode == 0 ? "" : secCode);
		arg.price = price;
		arg.balance = balance;
		arg.value = value;
		arg.isSell = (isSell == 1 ? true : false);
		arg.status = status;
		arg.orderDescriptor = orderDescriptor;
		pHandler->OnOrderStatus(arg);
	}

	void OnTradeStatus(long mode, double dNumber, double dOrderNum,
		LPSTR classCode, LPSTR secCode, double price, long qty,
		double value, long isSell, long tradeDescriptor)
	{
		QTransTradeStatus arg;
		arg.mode = mode;
		arg.id = (long long) dNumber;
		arg.orderId = (long long) dOrderNum;
		arg.classCode = (classCode == 0 ? "" : classCode);
		arg.secCode = (secCode == 0 ? "" : secCode);
		arg.price = price;
		arg.qty = qty;
		arg.value = value;
		arg.isSell = (isSell == 1 ? true : false);
		arg.tradeDescriptor = tradeDescriptor;
		pHandler->OnTradeStatus(arg);
	}

	/**
	 * �������� ��������� �� ������� ��������� ������, ���������� ��� ��������
	 * � ������� ���������� ���������� TRANS2QUIK � ������������ �������
	 * ����������� � ��������� � ����������� ������� ������.
	 */
	TRANS2QUIK_CONNECTION_STATUS_CALLBACK getConnectionStatusFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dConnStatus);
		return (TRANS2QUIK_CONNECTION_STATUS_CALLBACK) p.ToPointer();
	}

	/**
	 * �������� ��������� �� ������� ��������� ������, ���������� ��� ��������
	 * � ������� ���������� ���������� TRANS2QUIK � ������������ ����������
	 * ���������� � ��������� � ����������� ������� ������.
	 */
	TRANS2QUIK_TRANSACTION_REPLY_CALLBACK getTransactionReplyFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dTransReply);
		return (TRANS2QUIK_TRANSACTION_REPLY_CALLBACK) p.ToPointer();
	}

	/**
	 * �������� ��������� �� ������� ��������� ������, ���������� ��� ��������
	 * � ������� ���������� ���������� TRANS2QUIK � ������������ ������� ������
	 * � ��������� � ����������� ������� ������.
	 */
	TRANS2QUIK_ORDER_STATUS_CALLBACK getOrderStatusFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dOrderStatus);
		return (TRANS2QUIK_ORDER_STATUS_CALLBACK) p.ToPointer();
	}

	/**
	 * �������� ��������� �� ������� ��������� ������, ���������� ��� ��������
	 * � ������� ���������� ���������� TRANS2QUIK � ������������ ������� ������
	 * � ��������� � ����������� ������� ������.
	 */
	TRANS2QUIK_TRADE_STATUS_CALLBACK getTradeStatusFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dTradeStatus);
		return (TRANS2QUIK_TRADE_STATUS_CALLBACK) p.ToPointer();
	}

private:
	QTransHandler *pHandler;
	ConnStatusDlg^ dConnStatus;
	TransReplyDlg^ dTransReply;
	OrderStatusDlg^ dOrderStatus;
	TradeStatusDlg^ dTradeStatus;
};

	} // end namespace qtrans
} // end namespace aquila
