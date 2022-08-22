#pragma once
#include "scene.h"

namespace simple_engine {
	class MagicDoorScene : public Scene
	{
	public:
		MagicDoorScene(std::string name, Camera* camera);
		bool init() override;
		void render() override;
		void logic() override;
	private:
		GameObject* m_stencil_door;
		uint world_type;
		bool world_z_inversed;
		void updatePipeline();
	};
}


