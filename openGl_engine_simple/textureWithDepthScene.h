#pragma once
#include "scene.h"

namespace simple_engine {
	class TextureWithDepthScene : public Scene
	{
	public:
		TextureWithDepthScene(std::string name, Camera* camera);
		bool init() override;

	};
}


