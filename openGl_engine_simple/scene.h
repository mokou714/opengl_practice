#pragma once
#include <string>
#include <vector>
#include "gameObject.h"
#include "camera.h"

namespace simple_engine {
	/*
	* û�г����ļ��������ض�������scene����������ʵ�֣�������ͬ����������
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

		virtual bool init() { inited = true; return true; }
		
		//��Ⱦ֡ �߼�֡
		virtual void render();
		virtual void logic();

	protected:
		bool inited;
		Camera* mainCamera;
		std::string m_name;
		std::vector<GameObject*> m_gameObjects;
		GameObject* m_skybox;
	};
}