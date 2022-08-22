#pragma once
#include <vector>
#include "deviceCommon.h"

using namespace std;

namespace simple_engine {
	/*
	* û���ⲿģ�͡������ļ�������mesh�;��������gameobject��mesh�����������ڲ�����
	*/

	class Mesh {

	public:
		Mesh() = default;

		void setVertices(const glm::vec3 vertices[], size_t size);
		void setIndices(const unsigned short indices[], size_t size);

		vector<glm::vec3> getVertices() { return m_vertices; }
		vector<unsigned short> getIndices() { return m_indices; }
		std::vector<glm::vec3> getNormals() { return m_normals; }
		std::vector<glm::vec2> getCoords() {return m_coords; }

	protected:
		std::vector<glm::vec3> m_vertices;
		std::vector<unsigned short> m_indices;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_coords;
	};


}