#include "winApp.h"
#include "scene.h"
#include "sceneManager.h"
#include "cameraManager.h"
#include "engine.h"
#include "InputManager.h"
#include "Graphics.h"

using namespace simple_engine;

TCHAR WinApp::szWindowClass[] = _T("DesktopApp");
TCHAR WinApp::szTitle[] = _T("Windows Desktop Guided Tour Application");
HWND WinApp::s_window = nullptr;
WinApp* WinApp::s_instance = nullptr;

LRESULT CALLBACK WinApp::WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (message)
	{
	case WM_CREATE:
		// Initialize the window. 
		return 0;

	case WM_PAINT:
		// Paint the window's client area. 
		return 0;

	case WM_SIZE:
		// Set the size and position of the window. 
		return 0;

	case WM_DESTROY:
		// Clean up window-specific data objects. 
		return 0;

		// 
		// Process other messages. 
		// 

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

WinApp::WinApp()
{

}

WinApp* WinApp::Instance()
{
	if (WinApp::s_instance == nullptr)
	{
		WinApp::s_instance = new WinApp();
	}
	return WinApp::s_instance;
}

WinApp::~WinApp()
{

}

void WinApp::Destroy()
{
	if (WinApp::s_instance != nullptr)
	{
		delete WinApp::s_instance;
		WinApp::s_instance = nullptr;

	}
}

void WinApp::Initialize(HINSTANCE hInstance, int nCmdWindow)
{
	if (Graphics::GetRenderAPI() == RENDER_API::OPENGL)
		return;
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	RegisterClassEx(&wcex);

	s_window = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		this
	);

	ShowWindow(s_window, nCmdWindow);
}

int WinApp::Run()
{

	if (!Engine::Instance()->Initialize()) {
		return 0;
	}

	Camera* mainCam = CameraManager::Instance()->createCameraByDefault("mainCam");
	TemplateScene usingTemplate = TemplateScene::RayMarching;
	Scene* mainScene = SceneManager::Instance()->createAndAddScene("mainScene", mainCam, usingTemplate);

	if (mainScene) {
		SceneManager::Instance()->setCurrentScene(mainScene, usingTemplate);
		mainScene->init();
	}
	else {
		delete mainCam;
		return 0;
	}

	//主循环
	Engine::Instance()->Run();

	//主循环退出后清除资源
	SceneManager::Instance()->removeScene("mainScene");
	CameraManager::Instance()->removeCamera("mainCam");
	SceneManager::Instance()->Destroy();
	CameraManager::Instance()->Destroy();
	Engine::Instance()->Destroy();

	return 0;

	//MSG msg = {};
	//while (msg.message != WM_QUIT)
	//{
	//	// Process any messages in the queue.
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}

	//return (int)msg.wParam;
}
