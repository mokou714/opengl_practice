#pragma once
#include "glHelper.h"
#include "deviceCommon.h"
#include <unordered_map>

namespace simple_engine
{
	static std::unordered_map<CommonKeyCode, UINT> glKeyCodeMap =
	{
		{CommonKeyCode::A,				GLFW_KEY_A},
		{CommonKeyCode::B,				GLFW_KEY_B},
		{CommonKeyCode::C,				GLFW_KEY_C},
		{CommonKeyCode::D,				GLFW_KEY_D},
		{CommonKeyCode::E,				GLFW_KEY_E},
		{CommonKeyCode::F,				GLFW_KEY_F},
		{CommonKeyCode::G,				GLFW_KEY_G},
		{CommonKeyCode::H,				GLFW_KEY_H},
		{CommonKeyCode::I,				GLFW_KEY_I},
		{CommonKeyCode::J,				GLFW_KEY_J},
		{CommonKeyCode::K,				GLFW_KEY_K},
		{CommonKeyCode::L,				GLFW_KEY_L},
		{CommonKeyCode::M,				GLFW_KEY_M},
		{CommonKeyCode::N,				GLFW_KEY_N},
		{CommonKeyCode::O,				GLFW_KEY_O},
		{CommonKeyCode::P,				GLFW_KEY_P},
		{CommonKeyCode::Q,				GLFW_KEY_Q},
		{CommonKeyCode::R,				GLFW_KEY_R},
		{CommonKeyCode::S,				GLFW_KEY_S},
		{CommonKeyCode::T,				GLFW_KEY_T},
		{CommonKeyCode::U,				GLFW_KEY_U},
		{CommonKeyCode::V,				GLFW_KEY_V},
		{CommonKeyCode::W,				GLFW_KEY_W},
		{CommonKeyCode::X,				GLFW_KEY_X},
		{CommonKeyCode::Y,				GLFW_KEY_Y},
		{CommonKeyCode::Z,				GLFW_KEY_Z},
		{CommonKeyCode::ESCAPE,			GLFW_KEY_ESCAPE},
		{CommonKeyCode::LEFT_MOUSE,		GLFW_MOUSE_BUTTON_LEFT},
		{CommonKeyCode::RIGHT_MOUSE,	GLFW_MOUSE_BUTTON_RIGHT},
		{CommonKeyCode::MIDDLE_MOUSE,	GLFW_MOUSE_BUTTON_MIDDLE},
		{CommonKeyCode::LEFT_ARROW,		GLFW_KEY_LEFT},
		{CommonKeyCode::RIGHT_ARROW,	GLFW_KEY_RIGHT},
		{CommonKeyCode::UP_ARROW,		GLFW_KEY_UP},
		{CommonKeyCode::DOWN_ARROW,		GLFW_KEY_DOWN},
	};

	static std::unordered_map<int, CommonKeyState> glKeyStateMap = {
		{-1,			CommonKeyState::NONE},
		{GLFW_PRESS,	CommonKeyState::PRESSED},
		{GLFW_RELEASE,	CommonKeyState::RELEASED},
		{GLFW_REPEAT,	CommonKeyState::REPEATED},
	};
}


