#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#define SE_WINDOW_WIDTH 1024
#define SE_WINDOW_HEIGHT 768

#define DEBUG_PRINTF(...) {char cad[512]; sprintf(cad, __VA_ARGS__);  OutputDebugStringA(cad);}
#define CONSOLE_PRINTF(...) printf(__VA_ARGS__);

#ifndef SE_DEBUG_MODE
#define SE_DEBUG_MODE true
#endif