/**
 * ============================================================================
 * 2011/07/27
 * $Id: HelperWindowTest.cpp 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/auto_grab.h"
#include "aquila/core/WinApi.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/ddesvr/HelperWindow.h"
#include "aquila/ddesvr/MockHelperWindowHandler.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

class HelperWindowTest : public ::testing::Test {
protected:

	std::string getClassName(IHelperWindow* pWindow) {
		char b[128];
		sprintf_s(b, sizeof(b), HELPER_WINDOW_CLASS_NAME, pWindow);
		return b;
	}

	void SetUp() {
		WinApi::setInstance(&winApi);
	}

	void TearDown() {
		WinApi::setInstance(NULL);
	}

protected:
	MockWinApi winApi;
	MockHelperWindowHandler handler;
};

TEST_F(HelperWindowTest, testConstructorIncrementsRefCounters) {{
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));

	ASSERT_EQ(2, winApi.getRefCount());
	ASSERT_EQ(2, handler.getRefCount());
}}

TEST_F(HelperWindowTest, testDestructorDecrementsRefCounters) {{
	HelperWindow* win = new HelperWindow(&winApi, &handler);
	win->drop();

	ASSERT_EQ(1, winApi.getRefCount());
	ASSERT_EQ(1, handler.getRefCount());
}}

TEST_F(HelperWindowTest, testAcessors) {{
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));

	ASSERT_EQ(&winApi, win->getWinApi());
	ASSERT_EQ(&handler, win->getWindowHandler());
}}

TEST_F(HelperWindowTest, testRegisterClass_Ok) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	std::string name(getClassName(win));

	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)11111));
	EXPECT_CALL(winApi, RegisterClass(Pointee(AllOf(
			AllOf(Field(&WNDCLASS::style, 0),
				Field(&WNDCLASS::lpfnWndProc, HelperWindow::WndProc),
				Field(&WNDCLASS::cbClsExtra, 0),
				Field(&WNDCLASS::cbWndExtra, 0),
				Field(&WNDCLASS::hInstance, (HINSTANCE)11111)),
			AllOf(Field(&WNDCLASS::hIcon, (HICON)NULL),
				Field(&WNDCLASS::hCursor, (HCURSOR)NULL),
				Field(&WNDCLASS::hbrBackground, (HBRUSH)NULL),
				Field(&WNDCLASS::lpszClassName, StrEq(name.c_str())),
				Field(&WNDCLASS::lpszMenuName, (LPCTSTR)NULL))
			))))
		.Times(1)
		.WillOnce(Return((ATOM)222222));

	win->registerClass();
}}

TEST_F(HelperWindowTest, testRegisterClass_ThrowsOnGetModuleHandlerError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(123));

	ASSERT_THROW(win->registerClass(), WinApiErrorException);
}}

TEST_F(HelperWindowTest, testRegisterClass_ThrowsOnRegisterClassError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)11111));
	EXPECT_CALL(winApi, RegisterClass(_))
		.Times(1)
		.WillOnce(Return((ATOM)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(123));

	ASSERT_THROW(win->registerClass(), WinApiErrorException);
}}


TEST_F(HelperWindowTest, testCreateWindow_Ok) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	std::string name(getClassName(win));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)4321));
	EXPECT_CALL(winApi, CreateWindowEx(Pointee(AllOf(
			AllOf(Field(&CreateWindowEx_Args::dwExStyle, 0),
				Field(&CreateWindowEx_Args::lpClassName, StrEq(name.c_str())),
				Field(&CreateWindowEx_Args::lpWindowName, StrEq(name.c_str())),
				Field(&CreateWindowEx_Args::dwStyle, WS_OVERLAPPEDWINDOW),
				Field(&CreateWindowEx_Args::x, CW_USEDEFAULT)),
			AllOf(Field(&CreateWindowEx_Args::y, CW_USEDEFAULT),
				Field(&CreateWindowEx_Args::nWidth, CW_USEDEFAULT),
				Field(&CreateWindowEx_Args::nHeight, CW_USEDEFAULT),
				Field(&CreateWindowEx_Args::hWndParent, HWND_MESSAGE),
				Field(&CreateWindowEx_Args::hMenu, (HMENU)NULL)),
			AllOf(Field(&CreateWindowEx_Args::hInstance, (HINSTANCE)4321),
				Field(&CreateWindowEx_Args::lpParam, (LPVOID)win.get()))
			))))
		.Times(1)
		.WillOnce(Return((HWND)8765));
	EXPECT_CALL(winApi, SetLastError(0))
		.Times(1);
	EXPECT_CALL(winApi, SetWindowLongPtr((HWND)8765, GWLP_USERDATA,
			(LONG)win.get()))
		.Times(1)
		.WillOnce(Return(0));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(0));

	auto_drop<IHelperWindowController> ctrl(win->createWindow());
	HelperWindowController* c = (HelperWindowController*)ctrl.get();
	ASSERT_EQ((HWND)8765, c->getWindowHandle());
	ASSERT_EQ(&winApi, c->getWinApi());
}}

TEST_F(HelperWindowTest, testCreateWindow_ThrowsOnGetModuleHandleError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(123));

	ASSERT_THROW(
		auto_drop<IHelperWindowController> ctrl(win->createWindow()),
		WinApiErrorException);
}}

TEST_F(HelperWindowTest, testCreateWindow_ThrowsOnCreateWindowExError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)4321));
	EXPECT_CALL(winApi, CreateWindowEx(_))
		.Times(1)
		.WillOnce(Return((HWND)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345));

	ASSERT_THROW(
		auto_drop<IHelperWindowController> ctrl(win->createWindow()),
		WinApiErrorException);
}}

TEST_F(HelperWindowTest, testCreateWindow_ThrowsOnSetWindowLongPtrError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)4321));
	EXPECT_CALL(winApi, CreateWindowEx(_))
		.Times(1)
		.WillOnce(Return((HWND)8765));
	EXPECT_CALL(winApi, SetLastError(0))
		.Times(1);
	EXPECT_CALL(winApi, SetWindowLongPtr((HWND)8765, GWLP_USERDATA,
			(LONG)win.get()))
		.Times(1)
		.WillOnce(Return(0));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345));
	EXPECT_CALL(winApi, DestroyWindow((HWND)8765))
		.Times(1)
		.WillOnce(Return(TRUE));

	ASSERT_THROW(
		auto_drop<IHelperWindowController> ctrl(win->createWindow()),
		WinApiErrorException);
}}


TEST_F(HelperWindowTest, testUnregisterClass_Ok) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	std::string name(getClassName(win));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)4321));
	EXPECT_CALL(winApi, UnregisterClass(StrEq(name.c_str()), (HINSTANCE)4321))
		.Times(1)
		.WillOnce(Return(TRUE));

	win->unregisterClass();
}}

TEST_F(HelperWindowTest, testUnregisterClass_ThrowsOnGetModuleHandleError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	std::string name(getClassName(win));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(8765));

	ASSERT_THROW(win->unregisterClass(), WinApiErrorException);
}}

TEST_F(HelperWindowTest, testUnregisterClass_ThrowsOnUnregisterClassError) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	std::string name(getClassName(win));
	EXPECT_CALL(winApi, GetModuleHandle(NULL))
		.Times(1)
		.WillOnce(Return((HMODULE)7654));
	EXPECT_CALL(winApi, UnregisterClass(StrEq(name.c_str()), (HINSTANCE)7654))
		.Times(1)
		.WillOnce(Return(FALSE));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(1234));

	ASSERT_THROW(win->unregisterClass(), WinApiErrorException);
}}

TEST_F(HelperWindowTest, testMessageLoop) {{
	// TODO: ”казатель на msg не провер€етс€ на соответствие между вызовами
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetMessage(_, NULL, 0, 0))
		.Times(1)
		.WillOnce(Return(TRUE));
	EXPECT_CALL(winApi, TranslateMessage(_))
		.Times(1);
	EXPECT_CALL(winApi, DispatchMessage(_))
		.Times(1);
	EXPECT_CALL(winApi, GetMessage(_, NULL, 0, 0))
		.Times(1)
		.WillOnce(Return(TRUE));
	EXPECT_CALL(winApi, TranslateMessage(_))
		.Times(1);
	EXPECT_CALL(winApi, DispatchMessage(_))
		.Times(1);
	EXPECT_CALL(winApi, GetMessage(_, NULL, 0, 0))
		.Times(1)
		.WillOnce(Return(FALSE));

	win->messageLoop();
}}

TEST_F(HelperWindowTest, testWndProc_UnhandledMessage) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	EXPECT_CALL(winApi, GetWindowLongPtr((HWND)1123, GWLP_USERDATA))
		.Times(1)
		.WillOnce(Return((LONG_PTR)win.get()));
	EXPECT_CALL(winApi, DefWindowProc((HWND)1123, WM_USER + 10, 0, 1))
		.Times(1)
		.WillOnce(Return((LRESULT)345));

	ASSERT_EQ((LRESULT)345,
		HelperWindow::WndProc((HWND)1123, WM_USER + 10, 0, 1));
}}

TEST_F(HelperWindowTest, testWndProc_WM_NCCREATE) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	CREATESTRUCT cs;
	cs.lpCreateParams = (LPVOID)win.get();

	EXPECT_CALL(handler, onBeforeCreate())
		.Times(1);

	ASSERT_EQ(TRUE,
		HelperWindow::WndProc((HWND)12345, WM_NCCREATE, 0, (LPARAM)&cs));
}}

TEST_F(HelperWindowTest, testOnMessage_WM_CREATE) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	CREATESTRUCT cs;
	cs.lpCreateParams = (LPVOID)win.get();

	EXPECT_CALL(handler, onCreate())
		.Times(1);

	ASSERT_EQ((LRESULT)0,
		HelperWindow::WndProc((HWND)12345, WM_CREATE, 0, (LPARAM)&cs));
}}


TEST_F(HelperWindowTest, testWndProc_WM_HELPER_EXIT) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));

	EXPECT_CALL(winApi, GetWindowLongPtr((HWND)12345, GWLP_USERDATA))
		.Times(1)
		.WillOnce(Return((ULONG_PTR)win.get()));
	EXPECT_CALL(handler, onDestroy())
		.Times(1);
	EXPECT_CALL(winApi, PostMessage((HWND)12345, WM_CLOSE, 0, 0))
		.Times(1)
		.WillOnce(Return(TRUE));

	ASSERT_EQ((LRESULT)0,
		HelperWindow::WndProc((HWND)12345, WM_HELPER_EXIT, 0, 0));
}}

TEST_F(HelperWindowTest, testWndProc_WM_CLOSE) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));
	std::string name(getClassName(win));

	EXPECT_CALL(winApi, GetWindowLongPtr((HWND)12345, GWLP_USERDATA))
		.Times(1)
		.WillOnce(Return((ULONG_PTR)win.get()));
	EXPECT_CALL(winApi, DestroyWindow((HWND)12345))
		.Times(1)
		.WillOnce(Return(TRUE));

	ASSERT_EQ((LRESULT)0,
		HelperWindow::WndProc((HWND)12345, WM_CLOSE, 0, 0));
}}

TEST_F(HelperWindowTest, testWndProc_WM_NCDESTROY) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));

	EXPECT_CALL(winApi, GetWindowLongPtr((HWND)12345, GWLP_USERDATA))
		.Times(1)
		.WillOnce(Return((ULONG_PTR)win.get()));
	EXPECT_CALL(handler, onAfterDestroy())
		.Times(1);
	EXPECT_CALL(winApi, PostQuitMessage(0))
		.Times(1);

	ASSERT_EQ(0,
		HelperWindow::WndProc((HWND)12345, WM_NCDESTROY, 0, 0));
}}

TEST_F(HelperWindowTest, testWndProc_WM_HELPER_REGISTER) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));

	EXPECT_CALL(winApi, GetWindowLongPtr((HWND)12345, GWLP_USERDATA))
		.Times(1)
		.WillOnce(Return((ULONG_PTR)win.get()));
	EXPECT_CALL(handler, onRegisterService(18))
		.Times(1);

	ASSERT_EQ(0,
		HelperWindow::WndProc((HWND)12345, WM_HELPER_REGISTER, 0, 18));
}}

TEST_F(HelperWindowTest, testWndProc_WM_HELPER_UNREGISTER) {{
	InSequence s;
	auto_drop<HelperWindow> win(new HelperWindow(&winApi, &handler));

	EXPECT_CALL(winApi, GetWindowLongPtr((HWND)12345, GWLP_USERDATA))
		.Times(1)
		.WillOnce(Return((ULONG_PTR)win.get()));
	EXPECT_CALL(handler, onUnregisterService(21))
		.Times(1);

	ASSERT_EQ(0,
		HelperWindow::WndProc((HWND)12345, WM_HELPER_UNREGISTER, 0, 21));
}}

	} // end namespace ddesvr
} // end namespace aquila