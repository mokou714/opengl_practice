#pragma once
#include "GameObject.h"

namespace simple_engine {
	class CubeObj : public GameObject
	{
	public:
		CubeObj(std::string name);
		void Update() override;
	};
}


