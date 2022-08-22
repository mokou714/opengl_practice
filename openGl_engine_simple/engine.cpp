#include "engine.h"
#include "sceneManager.h"
#include "InputManager.h"
#include "Graphics.h"
#include "Display.h"

using namespace simple_engine;

Engine* Engine::s_engine = nullptr;

Engine::Engine(): is_running(false), m_frame_count(0){

}

Engine* Engine::Instance() {
	if (s_engine == nullptr) {
		s_engine = new Engine();
	}
	return s_engine;
}

bool Engine::Initialize() {
	CONSOLE_PRINTF("Initialize engine\n");
	if (!Graphics::Instance()->Initialize())
	{	
		CONSOLE_PRINTF("Faild to initialize Graphics module")
		return false;
	}
	//发现glfwSetKeyCallback在初始化glContext设置才有用 开始主循环后再设置就没有用了
	//因此在这里初始化InputManager
	InputManager::Instance();
	return true;
}

void Engine::Destroy() {
	if (s_engine != nullptr) {
		delete s_engine;
	}
	Graphics::Instance()->Destroy();
	InputManager::Instance()->destroy();
}

void Engine::Run() {

	is_running = true;

	while (is_running)
	{
		// 触发gl事件callback
		//todo callback里打印 查看pollevents怎么触发事件的
		//glfwPollEvents();

		BeginFrame();
		DoLogic();
		DoRender();
		EndFrame();

	}
}

void Engine::Stop() {
	is_running = false;
}

void Engine::DoLogic() {
	CONSOLE_PRINTF("DoLogic\n");
	//场景逻辑帧
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->logic();
}

void Engine::DoRender() {
	CONSOLE_PRINTF("DoRender\n");
	//场景渲染帧
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->render();
}

void Engine::BeginFrame() {
	CONSOLE_PRINTF("BeginFrame:%d\n", m_frame_count);
	// 先重置管线状态
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->ResetPipelineState();

	// 轮询检查输入
	InputManager::Instance()->pollInputEvents();
}

void Engine::EndFrame() {
	CONSOLE_PRINTF("EndFrame\n");
	Display::Present();
	m_frame_count++;
	if (InputManager::Instance()->getKeyState(CommonKeyCode::ESCAPE) == CommonKeyState::PRESSED)
	{
		Stop();
	}
}

