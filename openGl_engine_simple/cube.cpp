#include "cube.h"

using namespace simple_engine;

Cube::Cube() : Mesh() {
	m_structed_vertices = {
		// +z
		Vertex{glm::vec3{-1, -1,  1}, glm::vec2(0, 0), glm::vec3{0, 0, 1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1,  1}, glm::vec2(0, 0), glm::vec3{0, 0, 1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1,  1}, glm::vec2(0, 0), glm::vec3{0, 0, 1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1, -1,  1}, glm::vec2(0, 0), glm::vec3{0, 0, 1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1,  1}, glm::vec2(0, 0), glm::vec3{0, 0, 1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1,  1}, glm::vec2(0, 0), glm::vec3{0, 0, 1}, glm::vec3{0, 0, 0}},

		// -z
		Vertex{glm::vec3{-1, -1, -1}, glm::vec2(0, 0), glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1, -1}, glm::vec2(0, 0), glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1, -1}, glm::vec2(0, 0), glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1, -1, -1}, glm::vec2(0, 0), glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1, -1}, glm::vec2(0, 0), glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1, -1}, glm::vec2(0, 0), glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}},

		// +x
		Vertex{glm::vec3{ 1, -1,  1}, glm::vec2(0, 0), glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1, -1}, glm::vec2(0, 0), glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1,  1}, glm::vec2(0, 0), glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1,  1}, glm::vec2(0, 0), glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1, -1}, glm::vec2(0, 0), glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1, -1}, glm::vec2(0, 0), glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}},

		// -x
		Vertex{glm::vec3{-1, -1, -1}, glm::vec2(0,0), glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1,  1}, glm::vec2(0,0), glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1, -1}, glm::vec2(0,0), glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1, -1, -1}, glm::vec2(0,0), glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1, -1,  1}, glm::vec2(0,0), glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1,  1}, glm::vec2(0,0), glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 0}},

		// +y
		Vertex{glm::vec3{-1,  1,  1}, glm::vec2(0, 0), glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1, -1}, glm::vec2(0, 0), glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1, -1}, glm::vec2(0, 0), glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1,  1,  1}, glm::vec2(0, 0), glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1,  1}, glm::vec2(0, 0), glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1,  1, -1}, glm::vec2(0, 0), glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}},

		// -y
		Vertex{glm::vec3{-1, -1,  1}, glm::vec2(0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1, -1, -1}, glm::vec2(0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1, -1}, glm::vec2(0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{-1, -1,  1}, glm::vec2(0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1, -1}, glm::vec2(0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, 0, 0}},
		Vertex{glm::vec3{ 1, -1,  1}, glm::vec2(0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, 0, 0}},
	};

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

	m_normals = {
		//ƽ������
		glm::vec3{-1, -1,  1},
		glm::vec3{-1,  1,  1},
		glm::vec3{ 1, -1,  1},
		glm::vec3{ 1,  1,  1},
		glm::vec3{-1, -1, -1},
		glm::vec3{-1,  1, -1},
		glm::vec3{ 1, -1, -1},
		glm::vec3{ 1,  1, -1},
	};


	uint count = 0;
	m_vertices.clear();
	m_coords.clear();
	m_normals.clear();
	m_indices.clear();
	for (auto vtx : m_structed_vertices)
	{
		m_vertices.push_back(vtx.position);
		m_coords.push_back(vtx.coord);
		m_indices.push_back(count++);
		m_normals.push_back(vtx.normal);
		m_vertex_color.push_back(glm::normalize(vtx.position)); //cube�����������ƽ��normal
	}
}

float Cube::getSideSize()
{
	return 2.0f;
}
