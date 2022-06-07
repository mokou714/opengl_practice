#include "scene.h"

using namespace simple_engine;

Scene::Scene(const std::string name, Camera* camera) :
	m_name(name),
	mainCamera(camera)
{
	m_gameObjects.push_back(camera);
}

Scene::~Scene() {
	for (auto obj : m_gameObjects) {
		delete obj;
	}
	m_gameObjects.clear();
	mainCamera = nullptr;
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