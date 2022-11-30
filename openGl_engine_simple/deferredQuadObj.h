#pragma once
#include "gameObject.h"

namespace simple_engine
{
	class DeferredQuadObj : public GameObject
	{
	public:
		DeferredQuadObj() = default;
		DeferredQuadObj(std::string name);
	};
}


