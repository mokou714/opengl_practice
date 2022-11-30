#include "Pyramid.h"

using namespace simple_engine;

Pyramid::Pyramid()
{
	m_vertices = {
		{-1.0, 0.0, -1.0},
		{1.0, 0.0, -1.0,},
		{-1.0, 0.0, 1.0},
		{1.0, 0.0, 1.0},
		{0.0, 1.0, 0.0},
	};

	m_indices = {
		0, 1, 2,
		1, 3, 2,
		0, 2, 4,
		1, 4, 3,
		2, 3, 4,
		0, 4, 1,
	};

	m_normals = {
		glm::normalize(glm::vec3(-0.5, 0.5, 0) + glm::vec3(0.0, 0.5, -0.5) + glm::vec3(0.0, -1.0, 0.0)),
		glm::normalize(glm::vec3( 0.5, 0.5, 0) + glm::vec3(0.0, 0.5, -0.5) + glm::vec3(0.0, -1.0, 0.0)),
		glm::normalize(glm::vec3(-0.5, 0.5, 0) + glm::vec3(0.0, 0.5,  0.5) + glm::vec3(0.0, -1.0, 0.0)),
		glm::normalize(glm::vec3( 0.5, 0.5, 0) + glm::vec3(0.0, 0.5,  0.5) + glm::vec3(0.0, -1.0, 0.0)),
		glm::vec3(0.0, 1.0, 0.0),
	};
}