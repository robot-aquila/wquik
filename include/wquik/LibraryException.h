#pragma once

#include <string>
#include <exception>

using namespace std;

namespace wquik {

class LibraryException : public std::exception {
private:
	string msg;
public:
	LibraryException(string & str) {
		msg = str;
	}

	LibraryException(const char* text) {
		msg = text;
	};

	virtual const char* what() const throw() {
		return msg.c_str();
	};

};

} // end namespace wquik
