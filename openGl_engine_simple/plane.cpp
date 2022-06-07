#include "plane.h"

using namespace simple_engine;

Plane::Plane(): Mesh() {
	
	// mesh data
	glm::vec3 vertices[] = {
		glm::vec3{-1.0f, 0.0f, -1.0f},
		glm::vec3{-1.0f, 0.0f,  1.0f},
		glm::vec3{ 1.0f, 0.0f, -1.0f},
		glm::vec3{ 1.0f, 0.0f,  1.0f},

	};

	auto size = sizeof(vertices)/sizeof(glm::vec3);

	setVertices(std::move(vertices), size);

	//counter clockwise
	unsigned short indices[] = {
		0, 1, 3, 0, 3, 2
	};
	size = sizeof(indices)/sizeof(unsigned short);

	setIndices(std::move(indices), size);

}