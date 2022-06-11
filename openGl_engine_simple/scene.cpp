#include "scene.h"

using namespace simple_engine;

Scene::Scene(const std::string name, Camera* camera) :
	m_name(name),
	mainCamera(camera),
	inited(false),
	m_skybox(nullptr)
{
	m_gameObjects.push_back(camera);
}

Scene::~Scene() {
	for (auto obj : m_gameObjects) {
		delete obj;
	}
	m_gameObjects.clear();
	for (auto light : m_lights) {
		delete light;
	}
	m_lights.clear();

	mainCamera = nullptr;
	if (m_skybox) {
		delete m_skybox;
	}
	m_skybox = nullptr;
}

void Scene::addGameObjects(GameObject* gameObject) {
	m_gameObjects.emplace_back(gameObject);
}
bool Scene::removeGameObject(GameObject* gameObject) {
	auto found = m_gameObjects.end();
	for (; found != m_gameObjects.end(); ++found) {}
	if (found != m_gameObjects.end()) {
		m_gameObjects.erase(found);
		return true;
	}
	return false;
}
bool Scene::removeGameObjectByName(std::string name){
	for (auto s = m_gameObjects.begin(); s != m_gameObjects.end(); ++s) {
		if((*s)->getName() == name) {
			m_gameObjects.erase(s);
			return true;
		}
	}
	return false;
}
std::string Scene::getName() { return m_name; }

const std::vector<GameObject*>& Scene::getGameObjects() {
	return m_gameObjects;
}

void Scene::logic() {
	if (!inited) {
		CONSOLE_PRINTF("ERROR! update scene before initializing.")
		return;
	}

	for (auto light : getLights()) {
		light->Update();
	}

	for (auto obj : getGameObjects()) {
		obj->Update();
	}

	if (m_skybox) {
		m_skybox->Update();
	}
}

void Scene::render() {
	if (!inited) {
		CONSOLE_PRINTF("ERROR! render scene before initializing.")
		return;
	}

	for (auto& obj : getGameObjects()) {
		obj->Draw();
	}

	if (m_skybox) {
		m_skybox->Draw();
	}
}