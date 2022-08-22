#include "skyboxMat.h"

using namespace simple_engine;

const std::unordered_map<SKYBOX_TYPE, std::vector<const char*>> SkyboxMat::type_resources_map = {
	{
		SKYBOX_TYPE::ECOSYSTEM,
		{
			"textures/cubemap/exosystem/exosystem_rt.jpg",
			"textures/cubemap/exosystem/exosystem_lf.jpg",
			"textures/cubemap/exosystem/exosystem_up_.jpg",
			"textures/cubemap/exosystem/exosystem_dn_.jpg",
			"textures/cubemap/exosystem/exosystem_bk.jpg",
			"textures/cubemap/exosystem/exosystem_ft.jpg"
		},
	},

	{
		SKYBOX_TYPE::HEAVEN,
		{
			"textures/cubemap/heaven/heaven_rt.jpg",
			"textures/cubemap/heaven/heaven_lf.jpg",
			"textures/cubemap/heaven/heaven_up.jpg",
			"textures/cubemap/heaven/heaven_dn.jpg",
			"textures/cubemap/heaven/heaven_bk.jpg",
			"textures/cubemap/heaven/heaven_ft.jpg",
		}
	},

	{
		SKYBOX_TYPE::POLLUTED_EARTH,
		{
			"textures/cubemap/polluted_earth/polluted_earth_rt.jpg",
			"textures/cubemap/polluted_earth/polluted_earth_lf.jpg",
			"textures/cubemap/polluted_earth/polluted_earth_up.jpg",
			"textures/cubemap/polluted_earth/polluted_earth_dn.jpg",
			"textures/cubemap/polluted_earth/polluted_earth_bk.jpg",
			"textures/cubemap/polluted_earth/polluted_earth_ft.jpg",
		}
	}
};

SkyboxMat::SkyboxMat(SKYBOX_TYPE type): m_type(type) {
	m_vertex_shader = "materials/Skybox.vs";
	m_pixel_shader = "materials/Skybox.ps";
	m_cubemapTextures["skyCubemap"] = SkyboxMat::type_resources_map.at(type);
	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
}