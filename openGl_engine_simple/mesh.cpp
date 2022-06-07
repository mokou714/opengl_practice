#include "mesh.h"

using namespace simple_engine;

void Mesh::setVertices(const glm::vec3 vertices[], size_t size) {
	m_vertices = vector<glm::vec3>(vertices, vertices + size);
}

void Mesh::setIndices(const unsigned short indices[], size_t size) {
	m_indices = vector<unsigned short>(indices, indices + size);
}