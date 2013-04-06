#pragma once
#include <string>
#include <exception>

using namespace std;

namespace aquila {
	namespace xltable {

	class XltException : public std::exception {
	public:
		XltException(const char* text) : std::exception(text) { }
	};

	} // end namespace xltable
} // end namespace aquila

