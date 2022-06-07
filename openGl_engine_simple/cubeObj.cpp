#include "cubeObj.h"
#include "cube.h"

using namespace simple_engine;

CubeObj::CubeObj(std::string name) : GameObject(name) {
	m_meshes.push_back(Cube());
	m_material.setShaderFiles("materials/BaseColor.vs", "materials/BaseColor.ps");
}

void CubeObj::Update()  {
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}