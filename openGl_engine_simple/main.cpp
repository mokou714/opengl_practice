#include "scene.h"
#include "sceneManager.h"
#include "cameraManager.h"
#include "engine.h"
#include "InputManager.h"

using namespace simple_engine;

int main() {
	if (!Engine::Instance()->init()) {
		return 0;
	}

	Camera* mainCam =CameraManager::Instance()->createCameraByDefault("mainCam");
	Scene* mainScene = SceneManager::Instance()->createAndAddScene("mainScene", mainCam, TemplateScene::FirstSampleScene);

	if(mainScene){
		SceneManager::Instance()->setCurrentScene(mainScene);
		mainScene->init();
	}
	else {
		delete mainCam;
		return 0;
	}
	
	//主循环
	Engine::Instance()->run();
	

	//主循环退出后清除资源
	SceneManager::Instance()->removeScene("mainScene");
	CameraManager::Instance()->removeCamera("mainCam");
	SceneManager::Instance()->destroy();
	CameraManager::Instance()->destroy();
	Engine::Instance()->destroy();

	return 0;
}