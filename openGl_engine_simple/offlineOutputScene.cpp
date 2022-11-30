#include "offlineOutputScene.h"
#include "Graphics.h"
#include "suzanne.h"
#include "prefilterEnviromentMat.h"
#include "quad.h"

using namespace simple_engine;

OfflineOutputScene::OfflineOutputScene(std::string name, Camera* cam): Scene(name, cam)
{

}

bool OfflineOutputScene::init()
{
	if (!Scene::init())
		return false;

	m_fbo = GLFrameBufferObject(4096, 2048);
	m_fbo.AttachColorBuffer("main_color", 0, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);

	PrefilterEnviromentMat mat = PrefilterEnviromentMat();
	GameObject* obj = new GameObject();
	obj->addMesh(Quad());
	obj->setMaterial(mat);

	m_gameObjects.push_back(obj);

	return true;
}

void OfflineOutputScene::logic()
{
	Scene::logic();
}

void OfflineOutputScene::render()
{
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	GLDevice* device = (GLDevice*) Graphics::Instance()->FetchRenderDevice();
	context->ClearFrameBufferObject(m_fbo);
	context->SetFrameBufferObject(m_fbo);
	Scene::render();


	device->OutputTextureToFile(m_fbo.GetTexture("main_color"), 4096, 2048);
}

