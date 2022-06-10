#include "phongShadingMat.h"

using namespace simple_engine;

PhongShadingMat::PhongShadingMat() {
	m_vertex_shader = "materials/PhongShading.vs";
	m_pixel_shader = "materials/PhongShading.ps";
	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["wv"] = SHADER_SEMANTICS::WV;
}


