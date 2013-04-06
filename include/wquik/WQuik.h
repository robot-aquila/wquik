#pragma once
#include "wquik/ITransactionDriver.h"
#include <string>
#include <exception>

using namespace std;

namespace wquik {

class WQuikException : public std::exception {
private:
	string msg;
public:
	WQuikException(string & str) {
		msg = str;
	}

	WQuikException(const char* text) {
		msg = text;
	};

	virtual const char* what() const throw() {
		return msg.c_str();
	};

};


class WQuik {
public:
	// Create standard driver
	static ITransactionDriver* createDriver();
};

} // end namespace wquik
