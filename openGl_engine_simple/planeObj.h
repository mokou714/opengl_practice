#pragma once
#include "gameObject.h"

namespace simple_engine {
	class PlaneObj: public GameObject
	{
	public:
		PlaneObj(std::string name);
		void Update() override;
	};
}

