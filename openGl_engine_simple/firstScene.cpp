#include "firstScene.h"
#include "planeObj.h"
#include "sphereObj.h"
#include "cubeObj.h"

using namespace simple_engine;

FirstScene::FirstScene(std::string name, Camera* camera) : Scene(name, camera) 
{
}

bool FirstScene::init() {
	if (!Scene::init())
		return false;

	//²¼ÖÃmainscene
	GameObject* plane = new PlaneObj("plane");
	plane->setScale(100.0f);
	addGameObjects(plane);

	GameObject* sphere = new SphereObj("sphere");
	addGameObjects(sphere);
	sphere->setPosition(glm::vec3(30.0f, 20.0f, 0.0f));
	sphere->setScale(5.0f);

	GameObject* cube = new CubeObj("cube");
	cube->setScale(10.0f);
	addGameObjects(cube);

	return true;
}