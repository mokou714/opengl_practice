#include "cornellBox.h"

using namespace simple_engine;

CornellBox::CornellBox() : Mesh()
{
	m_vertices = {
		// +x
		glm::vec3{ 1, -1, -1}, glm::vec3{ 1,  1,  1}, glm::vec3{ 1,  1, -1},
		glm::vec3{ 1, -1, -1}, glm::vec3{ 1, -1,  1}, glm::vec3{ 1,  1,  1},

		// -x
		glm::vec3{-1, -1, -1}, glm::vec3{-1,  1,  1}, glm::vec3{-1, -1,  1},
		glm::vec3{-1, -1, -1}, glm::vec3{-1,  1, -1}, glm::vec3{-1,  1,  1},

		// +y
		glm::vec3{-1,  1, -1}, glm::vec3{ 1,  1, -1}, glm::vec3{-1,  1,  1},
		glm::vec3{-1,  1,  1}, glm::vec3{ 1,  1, -1}, glm::vec3{ 1,  1,  1},

		// -y
		glm::vec3{-1, -1, -1}, glm::vec3{-1, -1,  1}, glm::vec3{ 1, -1, -1},
		glm::vec3{-1, -1,  1}, glm::vec3{ 1, -1,  1}, glm::vec3{ 1, -1, -1},

		// -z
		glm::vec3{-1, -1, -1}, glm::vec3{ 1,  1, -1}, glm::vec3{-1,  1, -1},
		glm::vec3{-1, -1, -1}, glm::vec3{ 1, -1, -1}, glm::vec3{ 1,  1, -1},
	};

	m_coords = {
		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),
		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),

		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),
		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),

		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),
		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),

		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),
		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),

		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),
		glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0),
	};

	m_normals = {
		glm::vec3{-1, 0, 0}, glm::vec3{-1, 0, 0}, glm::vec3{-1, 0, 0},
		glm::vec3{-1, 0, 0}, glm::vec3{-1, 0, 0}, glm::vec3{-1, 0, 0},

		glm::vec3{ 1, 0, 0}, glm::vec3{ 1, 0, 0}, glm::vec3{ 1, 0, 0},
		glm::vec3{ 1, 0, 0}, glm::vec3{ 1, 0, 0}, glm::vec3{ 1, 0, 0},

		glm::vec3{ 0, -1, 0}, glm::vec3{ 0, -1, 0}, glm::vec3{ 0, -1, 0},
		glm::vec3{ 0, -1, 0}, glm::vec3{ 0, -1, 0}, glm::vec3{ 0, -1, 0},

		glm::vec3{ 0, 1, 0}, glm::vec3{ 0, 1, 0}, glm::vec3{ 0, 1, 0},
		glm::vec3{ 0, 1, 0}, glm::vec3{ 0, 1, 0}, glm::vec3{ 0, 1, 0},


		glm::vec3{ 0, 0, 1}, glm::vec3{ 0, 0, 1}, glm::vec3{ 0, 0, 1},
		glm::vec3{ 0, 0, 1}, glm::vec3{ 0, 0, 1}, glm::vec3{ 0, 0, 1},
	};

	glm::vec3 n_x = glm::vec3{ 171 / 255.0, 58 / 255.0, 194 / 255.0 };
	glm::vec3 p_x = glm::vec3{ 17 / 255.0, 166 / 255.0, 81 / 255.0 };
	glm::vec3 n_z = glm::vec3{ 0.9, 0.9, 0.9 };
	glm::vec3 p_y = glm::vec3{ 0.9, 0.9, 0.9 };
	glm::vec3 n_y = glm::vec3{ 0.3, 0.3, 0.3 };

	m_vertex_color = {
		// +x
		p_x, p_x, p_x,
		p_x, p_x, p_x,

		// -x
		n_x, n_x, n_x,
		n_x, n_x, n_x,

		// +y
		p_y, p_y, p_y,
		p_y, p_y, p_y,

		// -y
		n_y, n_y, n_y,
		n_y, n_y, n_y,

		// -z
		n_z, n_z, n_z,
		n_z, n_z, n_z,
	};

	for (int i = 0; i < m_vertices.size(); ++i)
	{
		m_indices.push_back(i);
	}
}
