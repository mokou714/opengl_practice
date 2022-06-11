#pragma once
#include "gl.h"
#include <string>

namespace simple_engine {
	enum class LIGHT_TYPE {
		DIRECT,
		POINT,
		PROJECTION
	};

	class BaseLight
	{
	public:
		BaseLight(std::string name, LIGHT_TYPE type);

		void setLightPosition(glm::vec3 pos) { m_position = pos; }
		void setLightDir(glm::vec3 dir) { m_lightDir = dir; }
		void setLightColor(glm::vec3 color) { m_lightColor = color; }
		void setBeingControlled(bool flag) { m_beingControlled = flag; }

		glm::vec3 getPosition() { return m_position; }
		LIGHT_TYPE getLightType() { return m_type; }
		glm::vec3 getLightDir();
		glm::vec3 getLightColor() { return m_lightColor; }
		bool isBeingControlled() { return m_beingControlled; }

		virtual void Update();

	protected:
		LIGHT_TYPE m_type;
		glm::vec3 m_position;
		std::string m_name;
		glm::vec3 m_lightDir;
		glm::vec3 m_lightColor;
		bool m_beingControlled;

		quat m_rotation;
	};

}


