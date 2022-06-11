#include "suzanneObj.h"
#include "suzanne.h"
#include "phongShadingMat.h"

using namespace simple_engine;

SuzanneObj::SuzanneObj(std::string name):GameObject(name) {
	m_meshes.push_back(Suzanne());
	m_material = PhongShadingMat();
	m_material.setTextureFile("diffuseMap", "textures/uvmap.dds");
}
