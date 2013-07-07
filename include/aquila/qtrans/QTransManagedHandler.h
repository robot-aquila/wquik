/**
 * ============================================================================
 * Данный файл содержит определения обработчика событий от TRANS2QUIK.dll,
 * выполненного в виде класса. Использование управляемого кода позволяет
 * выполнять связывание обратных вызовов с экземпляром класса. Обработчик
 * передает управление неуправляемому обработчику.
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

#ifdef _DUMP_HANDLE_TIME
#pragma message("Enable handle time dumping")
static LARGE_INTEGER timerFreqMu;

#define _DUMP_HANDLE_TIME_BEG \
		LARGE_INTEGER beg, end; \
		QueryPerformanceCounter(&beg);

#define _DUMP_HANDLE_TIME_END(name) QueryPerformanceCounter(&end); \
		printf("%s: %d\n", name, (end.QuadPart - beg.QuadPart) / timerFreqMu.QuadPart);

#else
#define _DUMP_HANDLE_TIME_BEG
#define _DUMP_HANDLE_TIME_END(name)
#endif



public ref class QTransManagedHandler {
public:
	QTransManagedHandler(QTransHandler* handler) {
		pHandler = handler;
		dConnStatus = gcnew ConnStatusDlg(this, &QTransManagedHandler::OnConnectionStatus);
		dTransReply = gcnew TransReplyDlg(this, &QTransManagedHandler::OnTransactionReply);
		dOrderStatus = gcnew OrderStatusDlg(this, &QTransManagedHandler::OnOrderStatus);
		dTradeStatus = gcnew TradeStatusDlg(this, &QTransManagedHandler::OnTradeStatus);
#ifdef _DUMP_HANDLE_TIME
		if ( QueryPerformanceFrequency(&timerFreqMu) ) {
			timerFreqMu.QuadPart /= 1000000;
		} else {
			timerFreqMu.QuadPart = -1;
		}
#endif
	}

	virtual ~QTransManagedHandler() {

	}

	void OnConnectionStatus(long connEvent, long errCode, LPSTR lpstr) {
		_DUMP_HANDLE_TIME_BEG
		pHandler->OnConnectionStatus(connEvent, errCode,
			lpstr == 0 ? "" : lpstr);
		_DUMP_HANDLE_TIME_END("OnConnectionStatus");
	}

	void OnTransactionReply(long transResult, long errCode, long replyCode,
		DWORD dwTransId, double dOrderNum, LPSTR replyMsg)
	{
		_DUMP_HANDLE_TIME_BEG
		pHandler->OnTransactionReply(transResult, errCode, replyCode,
			dwTransId, (long long) dOrderNum,
			replyMsg == 0 ? "" : replyMsg);
		_DUMP_HANDLE_TIME_END("OnTransactionReply");
	}

	void OnOrderStatus(long mode, DWORD transId, double orderId,
		LPSTR classCode, LPSTR secCode, double price, long balance,
		double value, long isSell, long status, long orderDescriptor)
	{
		_DUMP_HANDLE_TIME_BEG
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
		_DUMP_HANDLE_TIME_END("OnOrderStatus");
	}

	void OnTradeStatus(long mode, double dNumber, double dOrderNum,
		LPSTR classCode, LPSTR secCode, double price, long qty,
		double value, long isSell, long tradeDescriptor)
	{
		_DUMP_HANDLE_TIME_BEG
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
		_DUMP_HANDLE_TIME_END("OnTradeStatus");
	}

	/**
	 * Получить указатель на функцию обратного вызова, подходящую для передачи
	 * в функцию связывания библиотеки TRANS2QUIK с обработчиком статуса
	 * подключения и связанную с экземпляром данного класса.
	 */
	TRANS2QUIK_CONNECTION_STATUS_CALLBACK getConnectionStatusFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dConnStatus);
		return (TRANS2QUIK_CONNECTION_STATUS_CALLBACK) p.ToPointer();
	}

	/**
	 * Получить указатель на функцию обратного вызова, подходящую для передачи
	 * в функцию связывания библиотеки TRANS2QUIK с обработчиком результата
	 * транзакции и связанную с экземпляром данного класса.
	 */
	TRANS2QUIK_TRANSACTION_REPLY_CALLBACK getTransactionReplyFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dTransReply);
		return (TRANS2QUIK_TRANSACTION_REPLY_CALLBACK) p.ToPointer();
	}

	/**
	 * Получить указатель на функцию обратного вызова, подходящую для передачи
	 * в функцию связывания библиотеки TRANS2QUIK с обработчиком статуса заявки
	 * и связанную с экземпляром данного класса.
	 */
	TRANS2QUIK_ORDER_STATUS_CALLBACK getOrderStatusFnPtr() {
		IntPtr p = Marshal::GetFunctionPointerForDelegate(dOrderStatus);
		return (TRANS2QUIK_ORDER_STATUS_CALLBACK) p.ToPointer();
	}

	/**
	 * Получить указатель на функцию обратного вызова, подходящую для передачи
	 * в функцию связывания библиотеки TRANS2QUIK с обработчиком статуса сделки
	 * и связанную с экземпляром данного класса.
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
