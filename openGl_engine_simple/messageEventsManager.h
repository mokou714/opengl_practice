#pragma once
#include <Windows.h>

namespace simple_engine
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class MessageEventsManager
	{
	public:
		static MessageEventsManager* Instance();

	private:
		static MessageEventsManager* s_messageEventsManager;

	};

}

