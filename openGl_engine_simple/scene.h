#pragma once
#include <string>
#include <vector>
#include "gameObject.h"
#include "camera.h"

namespace simple_engine {
	/*
	* 没有场景文件，所有特定场景在scene的派生类里实现，创建不同场景里的物件
	*/

	class Scene {
	public:
		Scene(std::string name, Camera* camera);
		virtual ~Scene();
		void addGameObjects(GameObject* gameObject);
		bool removeGameObject(GameObject* gameObject);
		bool removeGameObjectByName(std::string name);
		const std::vector<GameObject*>& getGameObjects();
		Camera* getMainCamera() { return mainCamera; };
		void setMainCamera(Camera* camera) { mainCamera = camera; }
		std::string getName();

	private:
		Camera* mainCamera;
		std::string m_name;
		std::vector<GameObject*> m_gameObjects;
	};
}