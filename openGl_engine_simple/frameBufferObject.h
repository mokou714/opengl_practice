#pragma once
#include <map>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glContext.h"

namespace simple_engine {
	class FrameBuffer {

	public:
		FrameBuffer();
		void AttachColorBuffer(const char* bufferName, GLenum attachment, GLenum datatype, int width, int height);
		void AttachDepthBuffer(const char* bufferName, int width, int height);
		GLuint GetTexture(const char* bufferName);
		void Finish();
		void Clear();

	private:
		GLuint mFBO;
		std::map<std::string, GLuint> mBuffers;
		std::vector<GLenum> mDrawBuffers;

	};
}