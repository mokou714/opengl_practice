#include "messageEventsManager.h"

using namespace simple_engine;

MessageEventsManager* MessageEventsManager::s_messageEventsManager = nullptr;

LRESULT CALLBACK simple_engine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

MessageEventsManager* MessageEventsManager::Instance()
{
	if (MessageEventsManager::s_messageEventsManager == nullptr)
	{
		MessageEventsManager::s_messageEventsManager = new MessageEventsManager();
	}
	return MessageEventsManager::s_messageEventsManager;
}
