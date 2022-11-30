#include "DeferredRenderingMat.h"

using namespace simple_engine;

DeferredRenderingMat::DeferredRenderingMat(): Material()
{
	m_vertex_shader = "materials/DeferredRendering.vs";
	m_pixel_shader = "materials/DeferredRendering.ps";

	m_semanticsMap["cam_pos"] = SHADER_SEMANTICS::CAMERA_POSITION;
	m_semanticsMap["view"] = SHADER_SEMANTICS::V;
	m_semanticsMap["proj"] = SHADER_SEMANTICS::P;
	m_pipeline_state.depth_write_enable = false;
}