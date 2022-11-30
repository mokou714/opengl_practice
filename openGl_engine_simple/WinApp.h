#pragma once
#include <Windows.h>
#include <tchar.h>

class WinApp
{
public:
	static WinApp* Instance();
	void Destroy();
	static TCHAR szWindowClass[];
	static TCHAR szTitle[];
	static HWND s_window;

	static LRESULT CALLBACK WndProc(
		_In_ HWND   hWnd,
		_In_ UINT   message,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	);

	void Initialize(HINSTANCE hInstance, int nCmdWindow);

	int Run();

private:
	WinApp();
	~WinApp();
	static WinApp* s_instance;

};

