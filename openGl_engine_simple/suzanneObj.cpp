#include "suzanneObj.h"
#include "suzanne.h"

using namespace simple_engine;

SuzanneObj::SuzanneObj(std::string name):GameObject(name) {
	m_meshes.push_back(Suzanne());
	m_material.setShaderFiles("materials/PhongShading.vs", "materials/PhongShading.ps");
	m_material.setTextureFile("baseMap", "textures/uvmap.dds");
}

void SuzanneObj::Update() {
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
	m_material.setUniformMat4("world_view", getModelViewMatrix());
}