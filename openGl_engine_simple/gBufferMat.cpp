#include "gBufferMat.h"

using namespace simple_engine;

GBufferMat::GBufferMat(): Material()
{
	m_vertex_shader = "materials/GBuffer.vs";
	m_pixel_shader = "materials/GBuffer.ps";

	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;

	m_uniforms3f["base_color"] = vec3(0.0f, 0.0f, 0.0f);
	m_uniforms1f["base_color_factor"] = 0.0f;
}