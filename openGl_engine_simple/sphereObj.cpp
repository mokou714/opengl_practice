#include "sphereObj.h"
#include "sphere.h"

using namespace simple_engine;

SphereObj::SphereObj(std::string name): GameObject(name) {
	m_material.setShaderFiles("materials/BaseColor.vs", "materials/BaseColor.ps");
	
	m_meshes.push_back(Sphere(5.0f, 30, 30));
}

void SphereObj::Update() {
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}