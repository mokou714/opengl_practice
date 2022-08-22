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
	//����glfwSetKeyCallback�ڳ�ʼ��glContext���ò����� ��ʼ��ѭ���������þ�û������
	//����������ʼ��InputManager
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
		// ����gl�¼�callback
		//todo callback���ӡ �鿴pollevents��ô�����¼���
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
	//�����߼�֡
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->logic();
}

void Engine::DoRender() {
	CONSOLE_PRINTF("DoRender\n");
	//������Ⱦ֡
	auto currentScene = SceneManager::Instance()->getCurrentScene();
	currentScene->render();
}

void Engine::BeginFrame() {
	CONSOLE_PRINTF("BeginFrame:%d\n", m_frame_count);
	// �����ù���״̬
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->ResetPipelineState();

	// ��ѯ�������
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

