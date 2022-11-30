#pragma once
#include "scene.h"
#include "glFrameBufferObject.h"

namespace simple_engine
{
	class OfflineOutputScene : public Scene
	{
	public:
		OfflineOutputScene(std::string name, Camera* cam);

		bool init() override;
		void render() override;
		void logic() override;

	private:
		GLFrameBufferObject m_fbo;

	};

}

