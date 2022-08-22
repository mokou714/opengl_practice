#pragma once
#include "material.h"
#include <map>

namespace simple_engine {

	enum class SKYBOX_TYPE {
		ECOSYSTEM,
		HEAVEN,
		POLLUTED_EARTH,
	};

	class SkyboxMat : public Material
	{
	public:
		SkyboxMat(SKYBOX_TYPE type);

	private:
		SKYBOX_TYPE m_type;
		const static std::unordered_map<SKYBOX_TYPE, std::vector<const char*>> type_resources_map;

	};

}


