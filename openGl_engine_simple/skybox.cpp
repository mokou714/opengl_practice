#include "skybox.h"
#include "cube.h"

using namespace simple_engine;

Skybox::Skybox(std::string name) :GameObject(name) {
	m_meshes.push_back(Cube());
	m_material.setShaderFiles("materials/Skybox.vs", "materials/Skybox.ps");
	m_scale = 500.0f;
}

void Skybox::Update() {
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}

void Skybox::Draw() {
	
	//todo 用个更好结构封装每个dp前的管线状态设置
	GLContext::Instance()->setFaceCulling(true, false);

	GameObject::Draw();

	GLContext::Instance()->setFaceCulling(true, true);
}
