/**
 * ============================================================================
 * 2013-01-26
 * $Id: QTransException.h 455 2013-01-29 08:53:40Z whirlwind $
 * ============================================================================
 */

#pragma once
#include <string>
#include <exception>
#include <sstream>

using namespace std;

namespace aquila {
	namespace qtrans {

class QTransException : public std::exception {
public:

	QTransException(string & str) {
		msg = str;
	}

	QTransException(const char* text) {
		msg = text;
	}

	QTransException(long errCode, const char* str) {
		std::ostringstream stream;
		stream << str << ": " << errCode;
		msg = stream.str();
	}

	virtual const char* what() const throw() {
		return msg.c_str();
	}

private:
	string msg;

};

	} // end namespace qtrans
} // end namespace aquila
