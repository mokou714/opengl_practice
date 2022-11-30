#include "glFrameBufferObject.h"

using namespace simple_engine;

GLFrameBufferObject::GLFrameBufferObject(unsigned int width, unsigned int height): m_width(width), m_height(height)
{
	m_fbo = 0;
	glGenFramebuffers(1, &m_fbo);
}

void GLFrameBufferObject::Destroy()
{
	for (auto& buf : m_buffers)
	{
		glDeleteTextures(1, &buf.second);
	}
		 
	glDeleteFramebuffers(1, &m_fbo);
}

void GLFrameBufferObject::AttachColorBuffer(const char* buffer_name, unsigned int attachment, PixelFormat pixel_format)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	GLuint color_texture;
	glGenTextures(1, &color_texture); 
	glBindTexture(GL_TEXTURE_2D, color_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLenum gl_pixel_format = glPixelFormatMap[pixel_format];
	if (gl_pixel_format == GL_RGBA32F)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, gl_pixel_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_SHORT, NULL);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, gl_pixel_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, color_texture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		DEBUG_PRINTF("Framebuffer status failed\n");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_attachments.emplace_back(GL_COLOR_ATTACHMENT0 + attachment);
	m_buffers.emplace(std::pair<std::string, GLuint>(buffer_name, color_texture));
}
void GLFrameBufferObject::AttachDepthBuffer(const char* buffer_name)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	GLuint depth_texture;
	glGenTextures(1, &depth_texture);
	glBindTexture(GL_TEXTURE_2D, depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		DEBUG_PRINTF("Framebuffer status failed\n");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_buffers.emplace(std::pair<std::string, GLuint>(buffer_name, depth_texture));
}
GLuint GLFrameBufferObject::GetTexture(const char* buffer_name)
{
	auto iter = m_buffers.find(buffer_name);
	if (iter != m_buffers.end()) {
		return iter->second;
	}
	return NULL;
}

void GLFrameBufferObject::Finalize()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	if (m_attachments.size() > 0) {
		glDrawBuffers(m_attachments.size(), &m_attachments[0]);
		m_attachments.clear();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
