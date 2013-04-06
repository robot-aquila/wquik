/**
 * ============================================================================
 * 2011/07/28
 * $Id: Data.cpp 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/dde/Data.h"

namespace aquila {
	namespace dde {

Data::Data(IInstance* pInstance, IWinApi* pWinApi, HDDEDATA hData)
	: instance(pInstance),
	  winApi(pWinApi),
	  handle(hData)
{

}

Data::~Data() {

}

DWORD Data::getData(LPBYTE dst, DWORD size, DWORD offset) {
	return winApi->DdeGetData(handle, dst, size, offset);
}

DWORD Data::getSize() {
	return winApi->DdeGetData(handle, NULL, 0, 0);
}

HDDEDATA Data::getHandle() {
	return handle;
}

IInstance* Data::getInstance() {
	return instance;
}

IWinApi* Data::getWinApi() {
	return winApi;
}

	} // end namespace dde
} // end namespace aquila