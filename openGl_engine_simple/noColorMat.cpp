#include "noColorMat.h"

using namespace simple_engine;

NoColorMat::NoColorMat()
{
	m_vertex_shader = "materials/NoColor.vs";
	m_pixel_shader = "materials/NoColor.ps";
	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
}