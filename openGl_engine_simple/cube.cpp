#include "cube.h"

using namespace simple_engine;

Cube::Cube() : Mesh() {
	m_vertices = {
		glm::vec3{-1, -1,  1},
		glm::vec3{-1,  1,  1},
		glm::vec3{ 1, -1,  1},
		glm::vec3{ 1,  1,  1},
		glm::vec3{-1, -1, -1},
		glm::vec3{-1,  1, -1},
		glm::vec3{ 1, -1, -1},
		glm::vec3{ 1,  1, -1},
	};

	m_indices = {
		//前
		0, 3, 1,
		0, 2, 3,

		//后
		5, 7, 4,
		4, 7, 6,

		//左
		4, 1, 5,
		0, 1, 4,
		
		//右
		2, 7, 3,
		2, 6, 7,

		//上
		1, 7, 5,
		1, 3, 7,

		//下
		0, 4, 6,
		0, 6, 2,
	};
}
