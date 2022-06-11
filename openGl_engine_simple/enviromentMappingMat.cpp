#include "enviromentMappingMat.h"

using namespace simple_engine;

EnviromentMappingMat::EnviromentMappingMat(): Material(){
	m_vertex_shader = "materials/EnviromentMapping.vs";
	m_pixel_shader = "materials/EnviromentMapping.ps";
	m_cubemapTextures["envirmentTexture"] = {
		"textures/cubemap/exosystem/exosystem_rt.jpg",
		"textures/cubemap/exosystem/exosystem_lf.jpg",
		"textures/cubemap/exosystem/exosystem_up_.jpg",
		"textures/cubemap/exosystem/exosystem_dn_.jpg",
		"textures/cubemap/exosystem/exosystem_bk.jpg",
		"textures/cubemap/exosystem/exosystem_ft.jpg",
	};

	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
	m_semanticsMap["eye_w"] = SHADER_SEMANTICS::CAMERA_POSITION;
}
