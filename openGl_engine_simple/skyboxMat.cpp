#include "skyboxMat.h"

using namespace simple_engine;

SkyboxMat::SkyboxMat() {
	m_vertex_shader = "materials/Skybox.vs";
	m_pixel_shader = "materials/Skybox.ps";
	
	//todo ��ö�����Ӹ������͵�skybox����
	m_cubemapTextures["skyCubemap"] = {
		"textures/cubemap/exosystem/exosystem_rt.jpg",
		"textures/cubemap/exosystem/exosystem_lf.jpg",
		"textures/cubemap/exosystem/exosystem_up_.jpg",
		"textures/cubemap/exosystem/exosystem_dn_.jpg",
		"textures/cubemap/exosystem/exosystem_bk.jpg",
		"textures/cubemap/exosystem/exosystem_ft.jpg",
	};

	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
}