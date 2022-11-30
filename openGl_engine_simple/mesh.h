#pragma once
#include <vector>
#include "deviceCommon.h"

using namespace std;

namespace simple_engine {
	/*
	* 没有外部模型、材质文件，所有mesh和具体材质由gameobject和mesh的派生类在内部定义
	*/

	class Mesh {

	public:
		Mesh() = default;

		void setVertices(const glm::vec3 vertices[], size_t size);
		void setIndices(const unsigned short indices[], size_t size);

		const vector<glm::vec3>& getVertices() { return m_vertices; }
		const vector<Vertex> getStructedVertices() { return m_structed_vertices; }
		const vector<unsigned short>& getIndices() { return m_indices; }
		const std::vector<glm::vec3>& getNormals() { return m_normals; }
		const std::vector<glm::vec3>& getVertexColor() { return m_vertex_color; }
		const std::vector<glm::vec2>& getCoords() {return m_coords; }

	protected:
		std::vector<Vertex> m_structed_vertices;
		std::vector<glm::vec3> m_vertices;
		std::vector<unsigned short> m_indices;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec3> m_vertex_color;
		std::vector<glm::vec2> m_coords;
	};


}