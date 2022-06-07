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
	//����glfwSetKeyCallback�ڳ�ʼ��glContext���ò����� ��ʼ��ѭ���������þ�û������
	//����������ʼ��InputManager
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
		// ����gl�¼�callback
		//todo callback���ӡ �鿴pollevents��ô�����¼���
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
	//�����߼�֡
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->logic();
}

void Engine::doRender() {
	//������Ⱦ֡
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->render();
}

void Engine::beginFrame() {
	// �����ù���״̬
	GLContext::Instance()->resetPipelineState();

	// ��ѯ�������
	InputManager::Instance()->pollInputEvents();
}

void Engine::endFrame() {
	GLContext::Instance()->present();
	if (InputManager::Instance()->getKeyState(KeyCode::ESCAPE) == KeyState::Pressed)
	{
		stop();
	}
}

