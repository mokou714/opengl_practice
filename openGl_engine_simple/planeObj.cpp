#include "planeObj.h"
#include "plane.h"

using namespace simple_engine;

PlaneObj::PlaneObj(std::string name) : GameObject(name)
{
	//材质属性设置
	m_material.setShaderFiles("materials/BaseColor.vs", "materials/BaseColor.ps");
	m_material.setUniform3f("base_color", glm::vec3(0.8, 0.8, 0.8));

	//mesh网格设置
	m_meshes.push_back(Plane());

	/*m_rotation.x = -40.0;
	m_rotation.y = -40.0;
	m_rotation.z = -40.0;*/
	m_scale = 5;

}

void PlaneObj::Update(){
	GameObject::Update();
	m_material.setUniformMat4("world_view_projection", getModelViewProjectionMatrix());
}