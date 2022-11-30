#pragma once
#include "mesh.h"

namespace simple_engine {
	class Sphere : public Mesh
	{
	public:
		Sphere(float radius, int stacks, int sectors);	//stack 行格子数 sectors 列格子数

	private:
		float m_radius;
		int m_stacks;
		int m_sectors;
		
	};
}

