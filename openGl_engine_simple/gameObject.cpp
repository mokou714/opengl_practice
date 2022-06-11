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

	//todo 换个更好的地方更新语义 区分动态和静态的数据 静态数据的语义不用每个update都更新
	for (auto& pair : m_material.getSemanticsMap()) {
		auto uniform_name = pair.first;
		auto semantic_type = pair.second;
		switch (semantic_type)
		{
		case SHADER_SEMANTICS::W:
		{ 
			m_material.setUniformMat4(uniform_name.c_str(), getModelMatrix());
		}
		break;

		case SHADER_SEMANTICS::V:
		{
			m_material.setUniformMat4(uniform_name.c_str(), getViewMatrix());
		}
		break;

		case SHADER_SEMANTICS::P:
		{
			m_material.setUniformMat4(uniform_name.c_str(), getProjectionMatrix());
		}
		break;

		case SHADER_SEMANTICS::WV:
		{
			m_material.setUniformMat4(uniform_name.c_str(), getModelViewMatrix());
		}
		break;

		case SHADER_SEMANTICS::WVP:
		{
			m_material.setUniformMat4(uniform_name.c_str(), getModelViewProjectionMatrix());
		}
		break;

		case SHADER_SEMANTICS::CAMERA_POSITION:
		{
			auto current_scene = SceneManager::Instance()->getCurrentScene();
			auto main_camera = current_scene->getMainCamera();
			m_material.setUniform3f(uniform_name.c_str(), main_camera->getPosition());
		}
		break;

		case SHADER_SEMANTICS::LIGHT_DIR:
		{
			//todo
		}
		break;

		default:
			break;
		}
	}
}

void GameObject::Draw() {
	/*
	* 每个sub mesh设置shader program参数，然后draw
	*/
	for (auto& mesh : m_meshes)
	{
		GLContext::Instance()->setMaterial(m_material);
		GLContext::Instance()->drawCommand(mesh.getVertices(), mesh.getCoords(), mesh.getNormals(),  mesh.getIndices());
	}
}

glm::mat4 GameObject::getModelViewMatrix() {
	auto current_scene = SceneManager::Instance()->getCurrentScene();
	auto main_camera = current_scene->getMainCamera();
	return main_camera->getViewMatrix() * getModelMatrix();
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

glm::mat4 GameObject::getViewMatrix() {
	auto current_scene = SceneManager::Instance()->getCurrentScene();
	auto main_camera = current_scene->getMainCamera();
	return main_camera->getViewMatrix();
}

glm::mat4 GameObject::getProjectionMatrix() {
	auto current_scene = SceneManager::Instance()->getCurrentScene();
	auto main_camera = current_scene->getMainCamera();
	return main_camera->getProjectionMatrix();
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