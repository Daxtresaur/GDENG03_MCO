#include "Window.h"
#include "Utilities.h"
#include <stdexcept>

#include "EngineTime.h"

const HMODULE moduleHandle = GetModuleHandle(nullptr);

#include <cstdio>
#include <iostream>
#include <ostream>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window()
{
	m_is_running = false;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch(msg)
	{
	case WM_CREATE:
		{
		// Event fired when the window is created
		// collected here..
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		
		break;
		}
	case WM_DESTROY:
		{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
		}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}


bool Window::init()
{
	const LPCWSTR class_name = L"My GameEngine";
	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) // if Class Registration fails the function returns false
		throw std::runtime_error(Utilities::GetErrorStr());

	//Window Creation
	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", class_name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	if (!m_hwnd)
		throw std::runtime_error(Utilities::GetErrorStr());

	//Shows the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	// Flag is set to indicate that the window is initialized and running
	m_is_running = true;

	return true;
}

bool Window::broadcast()
{
	EngineTime::LogFrameStart();
	this->onUpdate(); // ensure that a final frame update is made (to flush values) before releasing the resources

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}

bool Window::release()
{
	//Destroys the window
	if (!::DestroyWindow(m_hwnd))
		// DestroyWindow fails.
		throw std::runtime_error(Utilities::GetErrorStr());

	return true;
}

bool Window::isRunning()
{
	return m_is_running;
}


RECT Window::getClientWindowRect()
{
	RECT rc;
	GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onDestroy()
{
	m_is_running = false;
}

HWND Window::getHWND()
{
	return m_hwnd;
}

Window::~Window()
{
	
}
