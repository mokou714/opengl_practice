#pragma once
#include "deferredRenderingScene.h"

namespace simple_engine
{
	class RayMarching : public DeferredRenderingScene
	{
	public:
		RayMarching(const std::string name, Camera* camera);
		bool init() override;
		void render() override;
		void initQuad() override;
		void initGBufferFBO() override;
		void initScreenFBO() override;
		void setToScreenFBO() override;
		void setToFinalScreenFBO();
		GLFrameBufferObject m_screen_fbo;
		
		DeferredQuadObj m_final_screen_quad;
		GLFrameBufferObject m_final_screen_fbo;
	};
}


