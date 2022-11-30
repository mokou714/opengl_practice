#pragma once
#include "scene.h"

namespace simple_engine
{
	class ShadowScene : public Scene
	{
	public:
		ShadowScene(std::string name, Camera* camera);
		bool init() override;
		void render() override;
	};
}


