/**
 * ============================================================================
 * 2011/08/06
 * $Id: String.cpp 96 2011-08-11 17:36:58Z whirlwind $
 * ============================================================================
 */
#include "aquila/dde/String.h"

namespace aquila {
	namespace dde {

String::String(IInstance* pInstance, IWinApi* pWinApi, HSZ hSz, int iCodePage)
: codePage(iCodePage),
  handle(hSz),
  instance(pInstance),
  winApi(pWinApi),
  allocated(false)
{

}

String::String(IInstance* pInstance, IWinApi* pWinApi, std::string str,
	int iCodePage)
 : codePage(iCodePage),
   instance(pInstance),
   winApi(pWinApi),
   allocated(true)
{
	handle = winApi->DdeCreateStringHandle
		(instance->getId(), str.c_str(), codePage);
}

String::~String() {
	if ( allocated ) {
		winApi->DdeFreeStringHandle(instance->getId(), handle);
	}
}

HSZ String::getHandle() const {
	return handle;
}

std::string String::getString() {
	char buffer[256];
	winApi->DdeQueryString
		(instance->getId(), handle, buffer, sizeof(buffer), codePage);
	return buffer;
}

int String::getCodePage() const {
	return codePage;
}

IInstance* String::getInstance() {
	return instance;
}

IWinApi* String::getWinApi() {
	return winApi;
}

	} // end namespace dde
} // end namespace aquila