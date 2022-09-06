#include "displacementTexMat.h"

using namespace simple_engine;

DisplacementTexMat::DisplacementTexMat() : Material()
{
	m_vertex_shader = "materials/DisplacementTexture.vs";
	m_pixel_shader = "materials/DisplacementTexture.ps";
	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
	m_semanticsMap["cam_pos"] = SHADER_SEMANTICS::CAMERA_POSITION;
}