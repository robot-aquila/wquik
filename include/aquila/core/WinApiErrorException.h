/**
 * ============================================================================
 * 2011/07/24
 * $Id: WinApiErrorException.h 92 2011-07-31 07:45:42Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include <exception>
#include <windows.h>
#include <string>
#include "aquila/core/IWinApi.h"

namespace aquila {
	namespace core {

class WinApiErrorException : public std::exception {
private:
	std::string msg;
	DWORD dwErrorCode;
public:

	WinApiErrorException(std::string errorText, IWinApi* pWinApi)
	  : msg(errorText),
		dwErrorCode(pWinApi->GetLastError())
	{
		
	}

	WinApiErrorException(std::string errorText, DWORD errorCode)
	  : msg(errorText),
	    dwErrorCode(errorCode)
	{

	}

	WinApiErrorException(const char* errorText, IWinApi* pWinApi)
	  : msg(errorText),
		dwErrorCode(pWinApi->GetLastError())
	{

	}

	WinApiErrorException(const char* errorText, DWORD errorCode)
	  : msg(errorText),
		dwErrorCode(errorCode)
	{

	}

	virtual const char* what() const throw() {
		char buffer[32];
		sprintf_s(buffer, sizeof(buffer), ": %d", dwErrorCode);
		std::string str(msg);
		str.append(buffer);
		return str.c_str();
	};

	DWORD getErrorCode() {
		return dwErrorCode;
	}

	std::string getErrorText() {
		return msg;
	}

};

	} // end namespace core
} // end namespace aquila