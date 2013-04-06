#include <exception>
#include "wquik/WQuik.h"
#include "aquila/core/SleshLibrary.h"
#include "wquik/QuikCallbackAPI.h"
#include "wquik/Trans2QuikAPI.h"
#include "wquik/TransactionDriver.h"

using namespace aquila::core;

namespace wquik {

#define DROPIF(x) if ( x != 0 ) x->drop();

ITransactionDriver* WQuik::createDriver() {
	IDll* libQuik = 0;
	IDll* libCallback = 0;
	IQuikCallbackAPI* apiCallback = 0;
	ITrans2QuikAPI* apiQuik = 0;
	ITransactionDriver* driver = 0;

	try {
		libQuik = new SleshLibrary("TRANS2QUIK.dll");
		apiQuik = new Trans2QuikAPI(libQuik);
		libCallback = new SleshLibrary("QuikCallback.dll");
		apiCallback = new QuikCallbackAPI(libCallback);
		driver = new TransactionDriver(apiQuik, apiCallback);

		DROPIF(libQuik);
		DROPIF(libCallback);
		DROPIF(apiQuik);
		DROPIF(apiCallback);
	} catch ( LibraryException e ) {
		DROPIF(libQuik);
		DROPIF(libCallback);
		DROPIF(apiQuik);
		DROPIF(apiCallback);
		throw WQuikException(e.what());
	} catch ( TransactionDriverException e ) {
		DROPIF(libQuik);
		DROPIF(libCallback);
		DROPIF(apiQuik);
		DROPIF(apiCallback);
		throw WQuikException(e.what());
	}
	return driver;
}

};
