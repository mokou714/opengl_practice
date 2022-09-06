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

void Material::setCubemapTextureFiles(const char* uniform_name, std::vector<const char*> texture_files) {
	m_cubemapTextures[uniform_name] = texture_files;
}


void Material::setTextureFile(const char* uniform_name, const char* file) {
	m_textures[uniform_name] = file; 
}