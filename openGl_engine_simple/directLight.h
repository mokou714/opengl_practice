#pragma once
#include "baseLight.h"

namespace simple_engine {
	class DirectLight : public BaseLight
	{
	public:
		DirectLight();
		glm::vec3 getLightDir() { return m_lightDir; }

	private:
		glm::vec3 m_lightDir;
	};
}


