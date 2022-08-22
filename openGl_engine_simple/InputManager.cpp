#include <math.h>
#include "InputManager.h"
#include "engine.h"
#include "graphics.h"


using namespace simple_engine;

InputManager* InputManager::s_inputManager = nullptr;

//static void simple_engine::glKeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
//	auto mgr = InputManager::Instance();
//	mgr->updateKeyState((KeyCode)key, (KeyState)action);
//}
//
//static void simple_engine::glCursorHandler(GLFWwindow* window, double xpos, double ypos) {
//	auto mgr = InputManager::Instance();
//	mgr->updateMousePos(xpos, ypos);
//}

InputManager* InputManager::Instance() {
	if (s_inputManager == nullptr) {
		s_inputManager = new InputManager();
	}
	return s_inputManager;
}

InputManager::InputManager():
	m_keyboardStateMap{
		{CommonKeyCode::W,				CommonKeyState::NONE},
		{CommonKeyCode::A,				CommonKeyState::NONE},
		{CommonKeyCode::S,				CommonKeyState::NONE},
		{CommonKeyCode::D,				CommonKeyState::NONE},
		{CommonKeyCode::ESCAPE,			CommonKeyState::NONE},
		{CommonKeyCode::LEFT_MOUSE,		CommonKeyState::NONE},
		{CommonKeyCode::RIGHT_MOUSE,	CommonKeyState::NONE},
		{CommonKeyCode::MIDDLE_MOUSE,	CommonKeyState::NONE},
		{CommonKeyCode::LEFT_ARROW,		CommonKeyState::NONE},
		{CommonKeyCode::RIGHT_ARROW,	CommonKeyState::NONE},
		{CommonKeyCode::UP_ARROW,		CommonKeyState::NONE},
		{CommonKeyCode::DOWN_ARROW,		CommonKeyState::NONE},
	},
	m_mouseX(SE_WINDOW_WIDTH / 2.0), m_mouseY(SE_WINDOW_HEIGHT / 2.0), m_deltaMouseX(0), m_deltaMouseY(0)
{
	Graphics::Instance()->FetchRenderContext()->setCursorPos(SE_WINDOW_WIDTH / 2.0, SE_WINDOW_HEIGHT / 2.0);
	// 监听的方法会导致每帧之间多次触发事件 影响表现 先注释掉
	//GLContext::Instance()->setInputKeyHandler(glKeyHandler);
	//GLContext::Instance()->setCursorHandler(glCursorHandler);
}

void InputManager::pollInputEvents() {
	for (auto itr = m_keyboardStateMap.cbegin(); itr != m_keyboardStateMap.cend(); ++itr) {
		auto cur_state = m_keyboardStateMap[itr->first];
		auto new_state = Graphics::Instance()->FetchRenderContext()->getKeyState(itr->first);
		if (cur_state == CommonKeyState::RELEASED && new_state == CommonKeyState::RELEASED) {
			//连续两帧都是release状态，state更新为None
			m_keyboardStateMap[itr->first] = CommonKeyState::NONE;
		}
		else {
			m_keyboardStateMap[itr->first] = new_state;
		}
	}
	double new_x, new_y;
	Graphics::Instance()->FetchRenderContext()->getCursorPos(new_x, new_y);
	m_deltaMouseX = new_x - m_mouseX;
	m_deltaMouseY = new_y - m_mouseY;
	m_mouseX = new_x;
	m_mouseY = new_y;
}

CommonKeyState InputManager::getKeyState(CommonKeyCode key) {
	if (m_keyboardStateMap.count(key)) {
		return m_keyboardStateMap[key];
	}
	return CommonKeyState::NONE;
}

void InputManager::destroy() {
	if (s_inputManager != nullptr) {
		delete s_inputManager;
	}
}

void InputManager::updateKeyState(CommonKeyCode key, CommonKeyState action) {
	if (m_keyboardStateMap.count(key)) {
		m_keyboardStateMap[key] = action;
	}
}

void InputManager::resetAllKeysState() {
	for (auto itr = m_keyboardStateMap.begin(); itr != m_keyboardStateMap.end(); itr++) {
		m_keyboardStateMap[itr->first] = CommonKeyState::NONE;
	}
}

void InputManager::updateMousePos(double xpos, double ypos) {
	m_deltaMouseX = xpos - m_mouseX;
	m_deltaMouseY = ypos - m_mouseY;
	m_mouseX = xpos;
	m_mouseY = ypos;
}

void InputManager::resetMouseState() {
	m_deltaMouseX = m_deltaMouseY = 0;
}
