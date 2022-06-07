#include "plane.h"

using namespace simple_engine;

Plane::Plane(): Mesh() {
	
	// mesh data
	m_vertices = {
		glm::vec3{-1.0f, 0.0f, -1.0f},
		glm::vec3{-1.0f, 0.0f,  1.0f},
		glm::vec3{ 1.0f, 0.0f, -1.0f},
		glm::vec3{ 1.0f, 0.0f,  1.0f},

	};

	//counter clockwise
	m_indices = {
		0, 1, 3, 0, 3, 2
	};

}