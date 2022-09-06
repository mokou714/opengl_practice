#pragma once
#include "scene.h"
#include <string>
#include <unordered_map>

namespace simple_engine {

	enum TemplateScene {
		None = 0,
		FirstSampleScene,
		GraphicHW1,
		GraphicHW3,
	};


	class SceneManager {
	
	public:
		static SceneManager* Instance();
		Scene* createAndAddScene(std::string name, Camera* camera, TemplateScene template_scene);
		bool addScene(Scene* scene);
		bool removeScene(std::string name);
		void setCurrentScene(Scene* scene);
		Scene* getCurrentScene() { return currentScene; }
		void Destroy();
	private:
		static SceneManager* s_sceneManager;
		SceneManager();
		Scene* currentScene;
		std::unordered_map<std::string, Scene*> m_scenes;
	};

}