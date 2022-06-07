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
		//ǰ
		0, 3, 1,
		0, 2, 3,

		//��
		5, 7, 4,
		4, 7, 6,

		//��
		4, 1, 5,
		0, 1, 4,
		
		//��
		2, 7, 3,
		2, 6, 7,

		//��
		1, 7, 5,
		1, 3, 7,

		//��
		0, 4, 6,
		0, 6, 2,
	};
}
