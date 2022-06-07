#include "engine.h"
#include "sceneManager.h"
#include "InputManager.h"
#include "glContext.h"

using namespace simple_engine;

Engine* Engine::s_engine = nullptr;

Engine::Engine(): is_running(false) {

}

Engine* Engine::Instance() {
	if (s_engine == nullptr) {
		s_engine = new Engine();
	}
	return s_engine;
}

bool Engine::init() {
	if (!GLContext::Instance()->init()) {
		return false;
	}
	//发现glfwSetKeyCallback在初始化glContext设置才有用 开始主循环后再设置就没有用了
	//因此在这里初始化InputManager
	InputManager::Instance();
	return true;
}

void Engine::destroy() {
	if (s_engine != nullptr) {
		delete s_engine;
	}
	GLContext::Instance()->destroy();
	InputManager::Instance()->destroy();
}

void Engine::run() {

	is_running = true;

	while (is_running)
	{
		// 触发gl事件callback
		//todo callback里打印 查看pollevents怎么触发事件的
		glfwPollEvents();

		beginFrame();
		doLogic();
		doRender();
		endFrame();

	}
}

void Engine::stop() {
	is_running = false;
}

void Engine::doLogic() {
	//场景逻辑帧
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->logic();
}

void Engine::doRender() {
	//场景渲染帧
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->render();
}

void Engine::beginFrame() {
	// 先重置管线状态
	GLContext::Instance()->resetPipelineState();

	// 轮询检查输入
	InputManager::Instance()->pollInputEvents();
}

void Engine::endFrame() {
	GLContext::Instance()->present();
	if (InputManager::Instance()->getKeyState(KeyCode::ESCAPE) == KeyState::Pressed)
	{
		stop();
	}
}

