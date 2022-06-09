#pragma once
#include "gameObject.h"

namespace simple_engine {
	class Skybox : public GameObject
	{
	public:
		Skybox(std::string name);
		void Update() override;
		void Draw() override;
	};
}


