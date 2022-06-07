#include "planeObj.h"
#include "plane.h"

using namespace simple_engine;

PlaneObj::PlaneObj(std::string name) : GameObject(name)
{
	m_material.setShaderFiles("materials/BaseColor.vs", "materials/BaseColor.ps");
	m_meshes.push_back(Plane());
}

void PlaneObj::Update(){
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}