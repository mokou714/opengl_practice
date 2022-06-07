#include "FrameBufferObject.h"
using namespace simple_engine;
FrameBuffer::FrameBuffer() {
	mFBO = 0;
	glGenFramebuffers(1, &mFBO);
}

void FrameBuffer::AttachColorBuffer(const char* bufferName, GLenum attachment, GLenum datatype, int width, int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	GLuint colorTexture;
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (datatype == GL_RGBA32F)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, datatype, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT, NULL);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, datatype, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, colorTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer status failed");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	mDrawBuffers.emplace_back(attachment);
	mBuffers.emplace(std::pair<std::string, GLuint>(bufferName, colorTexture));
}

void FrameBuffer::AttachDepthBuffer(const char* bufferName, int width, int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer status failed");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	mBuffers.emplace(std::pair<std::string, GLuint>(bufferName, depthTexture));
}


GLuint FrameBuffer::GetTexture(const char* bufferName) {
	auto iter = mBuffers.find(bufferName);
	if (iter != mBuffers.end()) {
		return iter->second;
	}
	return NULL;
}

void FrameBuffer::Finish() {
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	if (mDrawBuffers.size() > 0) {
		glDrawBuffers(mDrawBuffers.size(), &mDrawBuffers[0]);
		mDrawBuffers.clear();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Clear() {
	for (auto pair : mBuffers) {
		glDeleteTextures(1, &(pair.second));
	}
	mBuffers.clear();
	mDrawBuffers.clear();
	glDeleteBuffers(1, &mFBO);
}

