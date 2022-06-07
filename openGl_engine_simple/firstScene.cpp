#include "firstScene.h"
#include "planeObj.h"
#include "sphereObj.h"

using namespace simple_engine;

FirstScene::FirstScene(std::string name, Camera* camera) : Scene(name, camera) {

	//²¼ÖÃmainscene
	GameObject* plane = new PlaneObj("plane");
	plane->setScale(100.0f);
	addGameObjects(plane);

	GameObject* sphere = new SphereObj("sphere");
	addGameObjects(sphere);
	sphere->setPosition(glm::vec3(30.0f, 20.0f, 0.0f));
	sphere->setScale(5.0f);
}