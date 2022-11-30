#include "stylizedMat.h"

using namespace simple_engine;

StylizedMat::StylizedMat() : Material()
{
	m_vertex_shader = "materials\\StylizedOutline.vs";
	m_pixel_shader = "materials\\StylizedOutline.ps";
	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
	m_semanticsMap["v"] = SHADER_SEMANTICS::V;
	m_semanticsMap["p"] = SHADER_SEMANTICS::P;
	m_semanticsMap["camera_pos"] = SHADER_SEMANTICS::CAMERA_POSITION;
}
