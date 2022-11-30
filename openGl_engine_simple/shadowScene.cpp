#include "shadowScene.h"

using namespace simple_engine;

ShadowScene::ShadowScene(std::string name, Camera* camera) : Scene(name, camera)
{

}

bool ShadowScene::init()
{
	if (!Scene::init())
		return false;

	return true;
}

void ShadowScene::render()
{

}