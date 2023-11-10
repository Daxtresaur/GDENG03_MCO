#include"GWindow.h"
#include"GlobalProperties.h"

GWindow* window = nullptr;

LRESULT CALLBACK GWndProc(HWND window_handle, UINT msg, WPARAM w_param, LPARAM l_param) {
	switch (msg) {
	case WM_CREATE: {
		window->setWindowHandle(window_handle);
		window->onCreate();
		break;
	}
	case WM_DESTROY: {
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}
	default: return ::DefWindowProc(window_handle, msg, w_param, l_param);
	}

	return NULL;
}

GWindow::GWindow() {}

GWindow::~GWindow() {}

bool GWindow::initialize() {
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;

	wc.lpszClassName = L"GWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &GWndProc;

	if (!::RegisterClassEx(&wc)) return false;

	if (!window) window = this;
	mWindowHandle = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"GWindowClass",
		L"Game View",
		WS_OVERLAPPED | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GlobalProperties::GAME_VIEW_WIDTH,
		GlobalProperties::GAME_VIEW_HEIGHT,
		NULL,
		NULL,
		NULL,
		NULL
	);
	if (!mWindowHandle) return false;

	::ShowWindow(mWindowHandle, SW_SHOW);
	::UpdateWindow(mWindowHandle);

	mIsRunning = true;

	return true;
}

bool GWindow::broadcast() {
	window->onUpdate();

	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}

bool GWindow::release() {
	if (!::DestroyWindow(mWindowHandle)) return false;

	return true;
}

bool GWindow::isRunning() {
	return mIsRunning;
}

RECT GWindow::getWindowRect() {
	RECT windowRect;
	::GetClientRect(mWindowHandle, &windowRect);
	return windowRect;
}

void GWindow::setWindowHandle(HWND window_handle) {
	mWindowHandle = window_handle;
}

void GWindow::onCreate() {}

void GWindow::onUpdate() {}

void GWindow::onDestroy() {
	mIsRunning = false;
}