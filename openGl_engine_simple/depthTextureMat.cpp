#include "depthTextureMat.h"

using namespace simple_engine;

DepthTextureMat::DepthTextureMat() : Material()
{
	m_vertex_shader = "materials/DepthTexture.vs";
	m_pixel_shader = "materials/DepthTexture.ps";

	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["cam_pos"] = SHADER_SEMANTICS::CAMERA_POSITION;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
	m_uniforms3f["base_color"] = glm::vec3(0.5f, 0.5f, 0.5f);
}