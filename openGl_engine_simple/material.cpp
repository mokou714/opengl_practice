#include "material.h"

using namespace simple_engine;

Material::Material(): 
	m_vertex_shader(""),
	m_pixel_shader(""),
	m_glShaderProgram(0)
{

}

void Material::setCubemapTextureFiles(const char* uniform_name, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back) {
	// 6’≈ÕºµƒÀ≥–Ú+x, -x, +y, -y, +z, -z
	m_cubemapTextures[uniform_name] = std::vector<const char*>{
		right, left, top, bottom, back, front
	};
}

