#pragma once
#include "material.h"

namespace simple_engine
{
	class InteriorMappingMat : public Material
	{
	public:
		InteriorMappingMat();
		void addCeiling(glm::vec4 plane, glm::mat4 model_mat);
		void addSideWall(glm::vec4 plane, glm::mat4 model_mat);
		void addBackWall(glm::vec4 plane, glm::mat4 model_mat);
	};

}

