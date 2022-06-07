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

	//����mainscene
	GameObject* plane = new PlaneObj("plane");
	plane->setScale(100.0f);
	plane->getMaterial().setUniform3f("base_color", glm::vec3(0.8, 0.8, 0.8));
	addGameObjects(plane);

	GameObject* sphere = new SphereObj("sphere");
	addGameObjects(sphere);
	sphere->setPosition(glm::vec3(30.0f, 20.0f, 0.0f));
	sphere->setScale(5.0f);
	sphere->getMaterial().setUniform3f("base_color", glm::vec3(1.0, 0.4, 0.3));

	GameObject* cube = new CubeObj("cube");
	cube->setScale(10.0f);
	cube->setPosition(glm::vec3(-20.0f, 30.0f, 0.0f));
	cube->getMaterial().setUniform3f("base_color", glm::vec3(0.8, 0.8, 0.0));
	addGameObjects(cube);

	return true;
}