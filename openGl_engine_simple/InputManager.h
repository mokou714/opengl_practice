#pragma once
#include "deviceCommon.h"
#include <unordered_map>

namespace simple_engine {

	//通过监听来获取输入
	//static void glKeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
	//static void glCursorHandler(GLFWwindow* window, double xpos, double ypos);

	class InputManager
	{
	public:
		void destroy();

		void updateKeyState(CommonKeyCode key, CommonKeyState state);
		CommonKeyState getKeyState(CommonKeyCode key);
		void resetAllKeysState();

		void updateMousePos(double xpos, double ypos);
		double getMouseX() { return m_mouseX; }
		double getMouseY() { return m_mouseY; }
		double getDeltaMouseX() { return m_deltaMouseX; }
		double getDeltaMouseY() { return m_deltaMouseY; }
		void resetMouseState();

		void pollInputEvents();	//每个逻辑帧主动查询输入，更新状态(和监听方法选一种)

		static InputManager* Instance();

	private:
		InputManager();
		static InputManager* s_inputManager;
		std::unordered_map<CommonKeyCode, CommonKeyState> m_keyboardStateMap;
		double m_mouseX;
		double m_mouseY;
		double m_deltaMouseX;
		double m_deltaMouseY;
	};
}


