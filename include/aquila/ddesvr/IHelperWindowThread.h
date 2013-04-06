/**
 * ============================================================================
 * 2011/08/03
 * $Id: IHelperWindowThread.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/IRunnable.h"
#include "aquila/ddesvr/IHelperWindowController.h"
#include "aquila/ddesvr/IHelperWindow.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

class IHelperWindowThread : public IRunnable {
public:

	virtual ~IHelperWindowThread() { }

	/**
	 * «апустить поток.
	 */
	virtual DWORD run()=0;

	/**
	 * ѕосле запуска потока и создани€ окна создаетс€ контроллер окна.
	 * ѕосле создани€ контроллера, родительский поток уведомл€етс€
	 * с помощью Event.
	 */
	virtual IHelperWindowController* getWindowController()=0;


};

	} // end namespace ddesvr
} // end namespace aquila