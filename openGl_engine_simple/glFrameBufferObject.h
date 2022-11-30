#pragma once
#include <string>
#include <map>
#include "glDevice.h"
#include "glCommon.h"


//todo ��ʱ���� ֮����ȥ��gl���� ��Ϊ����IDevice��IContext ͳһ�ϲ��߼�

namespace simple_engine
{
	class GLFrameBufferObject
	{
	public:
		GLFrameBufferObject() = default;
		GLFrameBufferObject(unsigned int width, unsigned int height);	// ������rt��size��ͬ�����
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
		std::map<std::string, GLuint> m_buffers;	//ÿ��attachment��Ӧ��texture
		std::vector<GLenum> m_attachments;			//fbo������attachment ����draw��rt���������������Ϊ׼
		unsigned int m_width, m_height;
	};
}


