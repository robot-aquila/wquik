#pragma once

#include <string>
#include <exception>

using namespace std;

namespace wquik {

class TransactionDriverException : public std::exception {
private:
	string msg;
public:
	TransactionDriverException(string & str) {
		msg = str;
	}

	TransactionDriverException(const char* text) {
		msg = text;
	};

	virtual const char* what() const throw() {
		return msg.c_str();
	};

};

} // end namespace wquik
