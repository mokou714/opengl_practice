#include "gameObject.h"
#include "sceneManager.h"

using namespace simple_engine;

GameObject::GameObject(std::string name)
	:
	m_position({ 0,0,0 }),
	m_scale(1.0),
	m_name(name)
{
}

void GameObject::addMesh(Mesh mesh) {
	m_meshes.push_back(mesh);
}

void GameObject::Update() {
	//更新transform
	m_position += m_inputDeltaTranslation;
	m_rotation *= m_inputDeltaRotation;

	limitTranslation();
	limitRotation();

	m_inputDeltaTranslation = glm::vec3(0.0, 0.0, 0.0);
	m_inputDeltaRotation = glm::quat();
}

void GameObject::Draw() {
	/*
	* 每个sub mesh设置shader program参数，然后draw
	*/
	for (auto& mesh : m_meshes)
	{
		GLContext::Instance()->setMaterial(m_material);
		GLContext::Instance()->drawCommand(mesh.getVertices(), mesh.getIndices());
	}
}

glm::mat4 GameObject::getModelViewProjectionMatrix() {
	auto current_scene = SceneManager::Instance()->getCurrentScene();
	auto main_camera = current_scene->getMainCamera();
	return main_camera->getProjectionMatrix() * main_camera->getViewMatrix() * getModelMatrix();
}

glm::mat4 GameObject::getModelMatrix() {
	glm::mat4 rotation_mat = glm::toMat4(m_rotation);
	glm::mat4 translation_mat = glm::translate(glm::mat4(), getPosition());
	glm::mat4 scaling_mat = glm::scale(glm::mat4(), glm::vec3(getScale()));
	return translation_mat * rotation_mat * scaling_mat;
}

void GameObject::HandleInputTranslation(const glm::vec3& deltaTranslation)
{
	m_inputDeltaTranslation += deltaTranslation;
}

void GameObject::HandleInputRotation(const glm::vec3& deltaRotation)
{	
	//todo
	//m_inputDeltaRotation += deltaRotation;
}

glm::vec4 GameObject::getForward() {
	return glm::normalize(glm::toMat4(m_rotation) * glm::vec4(0.0, 0.0, -1.0, 0.0));
}

glm::vec4 GameObject::getRight() {
	return glm::normalize(glm::toMat4(m_rotation) * glm::vec4(1.0, 0.0, 0.0, 0.0));
}

glm::vec4 GameObject::getUp() {
	return glm::normalize(glm::toMat4(m_rotation) * glm::vec4(0.0, 1.0, 0.0, 0.0));
}