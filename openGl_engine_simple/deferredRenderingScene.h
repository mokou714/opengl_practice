#pragma once
#include "scene.h"
#include "glFrameBufferObject.h"
#include "deferredQuadObj.h"

using namespace simple_engine;

class DeferredRenderingScene : public Scene
{
public:
	DeferredRenderingScene(std::string name, Camera* cam);
	~DeferredRenderingScene() override;

	bool init() override;
	void render() override;
	void logic() override;

	virtual void setToGBufferFBO();
	virtual void setToScreenFBO();

protected:
	virtual void initGBufferFBO();
	virtual void initScreenFBO();
	virtual void initQuad();
	GLFrameBufferObject m_GBuffer_fbo;
	DeferredQuadObj m_render_quad;
	std::vector<GameObject*> m_alpha_blend_objs;
};

