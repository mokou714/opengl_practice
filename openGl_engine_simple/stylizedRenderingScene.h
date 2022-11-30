#pragma once
#include "scene.h"

namespace simple_engine
{
	class StylizedRenderingScene : public Scene
	{
	public:
		StylizedRenderingScene(std::string name, Camera* camera);
		bool init() override;
		void render() override;
	};
}


