#include "baseColorMat.h"

using namespace simple_engine;

BaseColorMat::BaseColorMat() {
	m_vertex_shader = "materials/BaseColor.vs";
	m_pixel_shader = "materials/BaseColor.ps";
	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
}
