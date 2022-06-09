#include "suzanne.h"
#include "utils.h"

using namespace simple_engine;

Suzanne::Suzanne() {
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> coords;
	if (!Utils::loadOBJ("models/suzanne.obj", vertices, coords, normals)) {
		CONSOLE_PRINTF("Loading model Suzanne failed !");
	}
	Utils::indexVBO(std::move(vertices), std::move(coords), std::move(normals),
		m_indices, m_vertices, m_coords, m_normals);
}