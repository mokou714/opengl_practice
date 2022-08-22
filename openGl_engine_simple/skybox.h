#pragma once
#include "gameObject.h"
#include "cube.h"
#include "skyboxMat.h"

namespace simple_engine {

	class Skybox : public GameObject
	{
	public:
		Skybox(std::string name, SKYBOX_TYPE type);
	};
}


