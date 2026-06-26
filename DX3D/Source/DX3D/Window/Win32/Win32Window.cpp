#include <DX3D/Window/Window.h>
#include <Windows.h>
#include <stdexcept>

#include "DX3D/Core/Logger.h"

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// DefWindowProc Default Window Procedure does not assume that the programs ends just because the window is closed
	// Which is why the program has to modify the windowprocedure to 
	switch (msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);

			break;
		}
		// Experiment Lol
		// These are Window Messages. kewl
		case WM_KEYDOWN:
		{
				if (wparam == 'F')
				{
					SetWindowTextA(hwnd, "You key DOWN 'F' ");
				}
				break;
		}
		case WM_KEYUP:
		{ 
			if (wparam == 'F')
			{
				SetWindowTextA(hwnd, "You key UP 'F' ");
			}
			break;
		}

		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}



dx3d::Window::Window(const WindowDesc& desc): Base(desc.base), m_size(desc.size)
{
	// In Windowese, the Window's windows have an internal class and internal instances
	// RegisterWindowClassFunction creates the Window's internal window class
	auto registerWindowClassFunction = []()
		{
			WNDCLASSEX wc{}; // Brace Initialization
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = "DX3DWindow";
			wc.lpfnWndProc = &WindowProcedure;
			return RegisterClassEx(&wc);
		};

	static const auto windowClassId = std::invoke(registerWindowClassFunction);

	if (!windowClassId)
		DX3DLogThrowError("RegisterClassEx failed.");

	RECT rc{ 0,0,m_size.width,m_size.height };
	AdjustWindowRect(
		&rc,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		false
	);

	// I guess this one makes a Window's internal instance of the window class made earlier
	m_handle = CreateWindowEx(
		NULL,
		MAKEINTATOM(windowClassId),
		"CHEN | DX3D Game Engine", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (!m_handle)
		DX3DLogThrowError("CreateWindowEx failed.");

	ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);
}

dx3d::Window::~Window()
{
	DestroyWindow(static_cast<HWND>(m_handle));
}
