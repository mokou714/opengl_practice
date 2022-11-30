#pragma once
#include <string>
#include <map>
#include "glDevice.h"
#include "glCommon.h"


//todo 临时做法 之后需去掉gl依赖 改为调用IDevice和IContext 统一上层逻辑

namespace simple_engine
{
	class GLFrameBufferObject
	{
	public:
		GLFrameBufferObject() = default;
		GLFrameBufferObject(unsigned int width, unsigned int height);	// 不考虑rt的size不同的情况
		void AttachColorBuffer(const char* buffer_name, unsigned int attachment, PixelFormat pixel_format);
		void AttachDepthBuffer(const char* buffer_name);
		GLuint GetTexture(const char* buffer_name);
		const GLuint& GetFrameBufferObject() { return m_fbo; }
		void Destroy();
		void Finalize();
		unsigned int GetWidth() { return m_width; }
		unsigned int GetHeight() { return m_height; }
	private:
		GLuint m_fbo;
		std::map<std::string, GLuint> m_buffers;	//每个attachment对应的texture
		std::vector<GLenum> m_attachments;			//fbo的所有attachment 具体draw的rt和排序以这里面的为准
		unsigned int m_width, m_height;
	};
}


