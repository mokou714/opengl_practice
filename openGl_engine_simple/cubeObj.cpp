#include "cubeObj.h"
#include "cube.h"

using namespace simple_engine;

CubeObj::CubeObj(std::string name) : GameObject(name) {
	m_meshes.push_back(Cube());
	m_material.setShaderFiles("materials/BaseColor.vs", "materials/BaseColor.ps");
	m_material.setUniform3f("base_color", glm::vec3(0.8, 0.8, 0.0));
}

void CubeObj::Update()  {
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}