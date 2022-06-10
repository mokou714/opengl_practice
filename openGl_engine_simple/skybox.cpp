#include "skybox.h"
#include "cube.h"
#include "skyboxMat.h"

using namespace simple_engine;

Skybox::Skybox(std::string name) :GameObject(name) {
	m_meshes.push_back(Cube());
	m_material = SkyboxMat();
	m_scale = 1000.0f;
}

void Skybox::Draw() {
	
	//todo 用个更好结构封装每个dp前的管线状态设置
	GLContext::Instance()->setFaceCulling(false, false);

	GameObject::Draw();

	GLContext::Instance()->setFaceCulling(true, true);
}
