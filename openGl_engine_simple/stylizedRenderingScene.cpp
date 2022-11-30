#include "stylizedRenderingScene.h"
#include "cubeObj.h"
#include "planeObj.h"
#include "stylizedMat.h"
#include "SilhouetteOutline.h"

using namespace simple_engine;

StylizedRenderingScene::StylizedRenderingScene(std::string name, Camera* camera): Scene(name, camera)
{
	camera->setPositionY(10.0f);
	camera->setPositionZ(30.0f);
	camera->setRotationX(glm::radians(-15.0f));
}

bool StylizedRenderingScene::init()
{
	if (!Scene::init())
		return false;

	GameObject* cube = new CubeObj("cube");
	Material cube_mat = StylizedMat();
	cube_mat.setUniform4f("base_color", glm::vec4(13 / 255.0f, 206 / 255.0f, 209 / 255.0f, 1.0f));
	cube_mat.setUniform1f("back_face_pass", 0.0f);
	cube->setMaterial(cube_mat);
	cube->setPositionY(5.0f);
	cube->setScale(3.0f);
	GameObject* plane = new PlaneObj("plane");
	plane->getMaterial().setUniform4f("base_color", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	plane->setScale(20.0f);

	m_gameObjects.push_back(cube);
	m_gameObjects.push_back(plane);
	return true;
}

void StylizedRenderingScene::render()
{
	//Scene::render();
	for (auto& obj : getGameObjects()) {
		if (obj->getName() == "cube")
		{
			Tech_Silhouette::Draw(obj);
		}
		else
		{
			obj->Draw();
		}
	}
}
