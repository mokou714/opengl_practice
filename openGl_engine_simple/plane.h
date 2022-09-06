#pragma once
#include "mesh.h"

namespace simple_engine {
	class Plane : public Mesh {

	public:
		Plane();
		float getSideSize();
	};
}