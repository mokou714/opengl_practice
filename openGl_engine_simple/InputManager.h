#pragma once
#include "gl.h"
#include <unordered_map>

namespace simple_engine {

	enum class KeyCode {
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		ESCAPE = GLFW_KEY_ESCAPE,
		LEFT_MOUSE = GLFW_MOUSE_BUTTON_LEFT,
		RIGHT_MOUSE = GLFW_MOUSE_BUTTON_RIGHT,
		MIDDLE_MOUSE = GLFW_MOUSE_BUTTON_MIDDLE,
	};

	enum class KeyState
	{
		None = -1,
		Pressed = GLFW_PRESS,
		Released = GLFW_RELEASE,
		Repeated = GLFW_REPEAT,
	};
	
	//通过监听来获取输入
	static void glKeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glCursorHandler(GLFWwindow* window, double xpos, double ypos);

	class InputManager
	{
	public:
		void destroy();

		void updateKeyState(KeyCode key, KeyState state);
		KeyState getKeyState(KeyCode key);
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
		std::unordered_map<KeyCode, KeyState> m_keyboardStateMap;
		double m_mouseX;
		double m_mouseY;
		double m_deltaMouseX;
		double m_deltaMouseY;
	};
}


