#pragma once
#include "gl.h"

namespace simple_engine {
	class BaseLight
	{
	public:
		BaseLight() = default;
		glm::vec3 getPosition() { return m_position; }

	private:
		glm::vec3 m_position;
	};

}


