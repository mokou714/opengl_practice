#include "sphereObj.h"
#include "sphere.h"

using namespace simple_engine;

SphereObj::SphereObj(std::string name): GameObject(name) {
	//材质属性设置
	m_material.setShaderFiles("materials/BaseColor.vs", "materials/BaseColor.ps");
	m_material.setUniform3f("base_color", glm::vec3(1.0, 0.4, 0.3));
	//mesh网格设置
	m_meshes.push_back(Sphere(5.0f, 30, 30));
}

void SphereObj::Update() {
	GameObject::Update();
	//cpu更新uniforms
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}