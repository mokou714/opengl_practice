#include "scene.h"
#include "sceneManager.h"
#include "cameraManager.h"
#include "engine.h"
#include "InputManager.h"

using namespace simple_engine;

int main() {
	if (!Engine::Instance()->Initialize()) {
		return 0;
	}

	Camera* mainCam =CameraManager::Instance()->createCameraByDefault("mainCam");
	//Scene* mainScene = SceneManager::Instance()->createAndAddScene("mainScene", mainCam, TemplateScene::FirstSampleScene);
	Scene* mainScene = SceneManager::Instance()->createAndAddScene("mainScene", mainCam, TemplateScene::GraphicHW3);

	if(mainScene){
		SceneManager::Instance()->setCurrentScene(mainScene);
		mainScene->init();
	}
	else {
		delete mainCam;
		return 0;
	}
	
	//主循环
	Engine::Instance()->Run();
	
	//主循环退出后清除资源
	SceneManager::Instance()->removeScene("mainScene");
	CameraManager::Instance()->removeCamera("mainCam");
	SceneManager::Instance()->Destroy();
	CameraManager::Instance()->Destroy();
	Engine::Instance()->Destroy();

	return 0;
}