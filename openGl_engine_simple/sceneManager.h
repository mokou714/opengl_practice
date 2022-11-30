#pragma once
#include "scene.h"
#include <string>
#include <unordered_map>

namespace simple_engine {

	enum class TemplateScene {
		None = 0,
		FirstSampleScene,
		GraphicHW1,
		GraphicHW3,
		GraphicHW4,
		OfflineOutputScene,
		Shadow,
		Stylized,
		RayMarching,
	};


	class SceneManager {
	
	public:
		static SceneManager* Instance();
		Scene* createAndAddScene(std::string name, Camera* camera, TemplateScene template_scene);
		bool addScene(Scene* scene);
		bool removeScene(std::string name);
		void setCurrentScene(Scene* scene, TemplateScene scene_template);
		Scene* getCurrentScene() { return currentScene; }
		TemplateScene getCurrentSceneTemplate() { return currentSceneTemplate; }
		void Destroy();
	private:
		static SceneManager* s_sceneManager;
		SceneManager();
		Scene* currentScene;
		TemplateScene currentSceneTemplate;
		std::unordered_map<std::string, Scene*> m_scenes;
	};

}