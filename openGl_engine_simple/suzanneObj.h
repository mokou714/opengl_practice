#pragma once
#include "gameObject.h"

namespace simple_engine {
	class SuzanneObj : public GameObject
	{
	public:
		SuzanneObj(std::string name);
		void Update() override;
	};
}


