// QTrans.ManualTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "aquila/qtrans/QTrans.h"
#include "aquila/qtrans/QTransHandler.h"

using namespace std;
using namespace aquila::qtrans;

public class Handler : public QTransHandler {
public:
	Handler() : QTransHandler() {
	
	}

	virtual ~Handler() {

	}

	virtual void OnConnectionStatus(long connEvent, long errCode, string errMsg) {
		string status;
		switch ( connEvent ) {
			case TRANS2QUIK_QUIK_CONNECTED: status = "QUIK connected"; break;
			case TRANS2QUIK_QUIK_DISCONNECTED: status = "QUIK disconnected"; break;
			case TRANS2QUIK_DLL_CONNECTED: status = "DLL connected"; break;
			case TRANS2QUIK_DLL_DISCONNECTED: status = "DLL disconnected"; break;
			default: status = "Unknown";
		}
		cout << "Conn.Status: " << status;
		if ( errCode != 0 || errMsg.size() > 0 ) {
			cout << " error: " << errCode << ": " << errMsg << ")";
		}
		cout << endl;
	}

	virtual void OnTransactionReply(long resultCode, long errCode, long replyCode,
		long transId, double orderId, string replyMsg)
	{
		string result;
		switch ( resultCode ) {
			case TRANS2QUIK_SUCCESS: result = "OK"; break;
			case TRANS2QUIK_DLL_NOT_CONNECTED: result = "DLL not connected"; break;
			case TRANS2QUIK_QUIK_NOT_CONNECTED: result = "QUIK not connected"; break;
			case TRANS2QUIK_FAILED: result = "FAIL"; break;
			default: result = "UNK";
		}

		cout << "Reply: " << transId << " "
			<< result << "(" << resultCode << ")"
			<< " errCode=" << errCode
			<< " replCode=" << replyCode
			<< " ordId=" << orderId
			<< " replMsg=" << replyMsg << endl;
	}

};

void help() {
	cout << "Available commands:" << endl
		<< "   ?, h, help       - show this help" << endl
		<< "   q, quit, e, exit - exit the program" << endl
		<< "   c, connect       - make connection to QUIK e.g.: connect C:\\quik\\" << endl
		<< "   d, disconect     - disconnect from QUIK" << endl
		<< "   Any other string interprets as QUIK transaction" << endl;
}

int _tmain(int argc, _TCHAR* argv[]) {
	Handler handler;
	QTrans driver(&handler, "TRANS2QUIK.dll");
	driver.init();
	help();
	string command;
	for ( ;; ) {
		cout << ": ";
		getline(cin, command);
		if ( command.compare("q") == 0 ||
			 command.compare("e") == 0 ||
			 command.compare("exit") == 0 ||
			 command.compare("quit") == 0 )
		{
			break;
		} else
		if ( command.compare("?") == 0 ||
			 command.compare("h") == 0 ||
			 command.compare("help") == 0 )
		{
			help();
		} else
		if ( command.compare("d") == 0 ||
			 command.compare("disconnect") == 0 )
		{
			try {
				driver.disconnect();
			} catch ( exception & e ) {
				cout << "Exception: " << e.what() << endl;
			}
		} else
		if ( command.find("c ") == 0 ||
			 command.find("connect ") == 0 )
		{
			command = command.substr(command.find("c ") == 0 ? 2 : 8);
			try {
				driver.connect(command);
			} catch ( exception & e ) {
				cout << "Exception: " << e.what() << endl;
			}
		} else {
			try {
				driver.send(command);
			} catch ( exception & e ) {
				cout << "Exception: " << e.what() << endl;
			}
		}
	}

	return 0;
}


