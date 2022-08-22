#include "sceneManager.h"
#include "firstScene.h"
#include "magicDoorScene.h"

using namespace simple_engine;

SceneManager* SceneManager::s_sceneManager = nullptr;

SceneManager::SceneManager():
	currentScene(nullptr){
}

SceneManager* SceneManager::Instance() {
	if (s_sceneManager == nullptr) {
		s_sceneManager = new SceneManager();
	}
	return s_sceneManager;
}

void SceneManager::Destroy() {
	if (s_sceneManager) {
		delete s_sceneManager;
		s_sceneManager = nullptr;
	}
}


Scene* SceneManager::createAndAddScene(std::string name, Camera* camera, TemplateScene template_scene = TemplateScene::None) {

	Scene* newScene = nullptr;
	switch (template_scene) {
	case TemplateScene::None:
		newScene = new Scene(name, camera);
		break;
	case TemplateScene::FirstSampleScene:
		newScene = new FirstScene(name, camera);
		break;
	case TemplateScene::GraphicHW1:
		newScene = new MagicDoorScene(name, camera);
		break;
	default:
		newScene = new Scene(name, camera);
		break;
	}

	if (newScene)
	{
		if (addScene(newScene))
		{
			return newScene;
		}
		else {
			delete newScene;
			return nullptr;
		}
	}
	return nullptr;
}

bool SceneManager::addScene(Scene* scene) {
	auto result = this->m_scenes.try_emplace(scene->getName(), scene);
	return result.second;
}
bool SceneManager::removeScene(std::string name) {
	if (m_scenes.count(name))
	{	
		Scene* scn = m_scenes[name];
		m_scenes.erase(name);
		delete scn;
		return true;
	}
	return false;
}
void SceneManager::setCurrentScene(Scene* scene) {
	if (scene == nullptr || scene != this->currentScene) {
		currentScene = scene;
	}
}

