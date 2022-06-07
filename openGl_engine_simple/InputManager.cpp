#include <math.h>
#include "InputManager.h"
#include "engine.h"
#include "glContext.h"


using namespace simple_engine;

InputManager* InputManager::s_inputManager = nullptr;

static void simple_engine::glKeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto mgr = InputManager::Instance();
	mgr->updateKeyState((KeyCode)key, (KeyState)action);
}

static void simple_engine::glCursorHandler(GLFWwindow* window, double xpos, double ypos) {
	auto mgr = InputManager::Instance();
	mgr->updateMousePos(xpos, ypos);
}

InputManager* InputManager::Instance() {
	if (s_inputManager == nullptr) {
		s_inputManager = new InputManager();
	}
	return s_inputManager;
}

InputManager::InputManager():
	m_keyboardStateMap{
		{KeyCode::W,			KeyState::None},
		{KeyCode::A,			KeyState::None},
		{KeyCode::S,			KeyState::None},
		{KeyCode::D,			KeyState::None},
		{KeyCode::ESCAPE,		KeyState::None},
		{KeyCode::LEFT_MOUSE,	KeyState::None},
		{KeyCode::RIGHT_MOUSE,	KeyState::None},
		{KeyCode::MIDDLE_MOUSE, KeyState::None},
	},
	m_mouseX(SE_WINDOW_WIDTH / 2.0), m_mouseY(SE_WINDOW_HEIGHT / 2.0), m_deltaMouseX(0), m_deltaMouseY(0)
{
	GLContext::Instance()->setCursorPos(SE_WINDOW_WIDTH / 2.0, SE_WINDOW_HEIGHT / 2.0);
	// 监听的方法会导致每帧之间多次触发事件 影响表现 先注释掉
	//GLContext::Instance()->setInputKeyHandler(glKeyHandler);
	//GLContext::Instance()->setCursorHandler(glCursorHandler);
}

void InputManager::pollInputEvents() {
	for (auto itr = m_keyboardStateMap.cbegin(); itr != m_keyboardStateMap.cend(); ++itr) {
		auto cur_state = m_keyboardStateMap[itr->first];
		auto new_state = (KeyState) GLContext::Instance()->getKeyState((int)itr->first);
		if (cur_state == KeyState::Released && new_state == KeyState::Released) {
			//连续两帧都是release状态，state更新为None
			m_keyboardStateMap[itr->first] = KeyState::None;
		}
		else {
			m_keyboardStateMap[itr->first] = new_state;
		}
	}
	double new_x, new_y;
	GLContext::Instance()->getCursorPos(new_x, new_y);
	m_deltaMouseX = new_x - m_mouseX;
	m_deltaMouseY = new_y - m_mouseY;
	m_mouseX = new_x;
	m_mouseY = new_y;
}

KeyState InputManager::getKeyState(KeyCode key) {
	if (m_keyboardStateMap.count(key)) {
		return m_keyboardStateMap[key];
	}
	return KeyState::None;
}

void InputManager::destroy() {
	if (s_inputManager != nullptr) {
		delete s_inputManager;
	}
}

void InputManager::updateKeyState(KeyCode key, KeyState action) {
	if (m_keyboardStateMap.count(key)) {
		m_keyboardStateMap[key] = action;
	}
}

void InputManager::resetAllKeysState() {
	for (auto itr = m_keyboardStateMap.begin(); itr != m_keyboardStateMap.end(); itr++) {
		m_keyboardStateMap[itr->first] = KeyState::None;
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
