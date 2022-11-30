#include "skybox.h"

using namespace simple_engine;

Skybox::Skybox(std::string name, SKYBOX_TYPE type) :GameObject(name) {
	m_meshes.push_back(Cube());
	m_material = SkyboxMat(type);
	m_scale = 1000.0f;
	m_material.getPipelineState().culling_enable = false;
}
