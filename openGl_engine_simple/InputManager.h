#pragma once
#include "deviceCommon.h"
#include <unordered_map>

namespace simple_engine {

	//ͨ����������ȡ����
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

		void pollInputEvents();	//ÿ���߼�֡������ѯ���룬����״̬(�ͼ�������ѡһ��)

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


