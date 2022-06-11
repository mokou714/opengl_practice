#include "phongShadingMat.h"

using namespace simple_engine;

PhongShadingMat::PhongShadingMat() {
	m_vertex_shader = "materials/PhongShading.vs";
	m_pixel_shader = "materials/PhongShading.ps";

	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
	m_semanticsMap["view_pos"] = SHADER_SEMANTICS::CAMERA_POSITION;
	m_semanticsMap["light_dir"] = SHADER_SEMANTICS::LIGHT_DIR;

	m_uniforms3f["ambient"] = glm::vec3(0.1f, 0.1f, 0.1f);
	m_uniforms3f["specular"] = glm::vec3(0.2f, 0.2f, 0.2f);
	m_uniforms1f["k_a"] = 1.0f;
	m_uniforms1f["k_d"] = 2.0f;
	m_uniforms1f["k_s"] = 0.5f;
}




