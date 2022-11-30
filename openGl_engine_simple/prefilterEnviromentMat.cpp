#include "prefilterEnviromentMat.h"

using namespace simple_engine;

PrefilterEnviromentMat::PrefilterEnviromentMat(): Material()
{
	m_vertex_shader = "materials/PrefilterEnviroment.vs";
	m_pixel_shader = "materials/PrefilterEnviroment.ps";

	m_cubemapTextures["envir_map"] = new ITexture({
		"textures/cubemap/hdr/px.hdr",
		"textures/cubemap/hdr/nx.hdr",
		"textures/cubemap/hdr/py.hdr",
		"textures/cubemap/hdr/ny.hdr",
		"textures/cubemap/hdr/pz.hdr",
		"textures/cubemap/hdr/nz.hdr",
		});
	m_uniforms1f["roughness"] = 0.2f;
}