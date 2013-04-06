/**
 * ============================================================================
 * 2011/07/27
 * $Id: HelperWindowController.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#pragma warning(disable:4290)
#include "aquila/core/auto_grab.h"
#include "aquila/ddesvr/IHelperWindowController.h"
#include "aquila/ddesvr/IHelperWindow.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * Реализация контроллера вспомогательного окна.
 * Класс транслирует вызовы методов в соответствующие оконные сообщения.
 */
class HelperWindowController : public IHelperWindowController {
public:

	HelperWindowController(IWinApi* pWinApi, HWND hWnd);

	virtual ~HelperWindowController();

	void registerService(long serviceId) throw (WinApiErrorException);

	void unregisterService(long serviceId) throw (WinApiErrorException);

	void close() throw (WinApiErrorException);

	IWinApi* getWinApi();

	HWND getWindowHandle();

private:
	auto_grab<IWinApi> winApi;
	HWND hWnd;

};

	} // end namespace ddesvr
} // end namespace aquila