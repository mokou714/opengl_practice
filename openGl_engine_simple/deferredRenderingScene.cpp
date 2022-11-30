#include "deferredRenderingScene.h"
#include "suzanneObj.h"
#include "planeObj.h"
#include "gBufferMat.h"
#include "Graphics.h"
#include "pyramid.h"
#include "sphere.h"
#include "cube.h"
#include "baseColorMat.h"
#include "OIT.h"

using namespace simple_engine;

/*
	forward rendering
		- pre depth pass(optional)
		- per-object shading pass
	deferred rendeering
		- GBuffer pass
		- screen-space shading pass
	forward+
		- pre depth pass(required)
		- light culling pass(build light lists per tile)
		- tile based per-light per-material shading pass
*/

DeferredRenderingScene::DeferredRenderingScene(std::string name, Camera* cam) : Scene(name, cam) 
{
	m_GBuffer_fbo = GLFrameBufferObject(SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT);
	m_render_quad = DeferredQuadObj("Deferred Render Quad");
}

DeferredRenderingScene::~DeferredRenderingScene()
{
	Scene::~Scene();
	for (auto obj : m_alpha_blend_objs)
	{
		delete obj;
	}
	m_alpha_blend_objs.clear();
}

bool DeferredRenderingScene::init()
{
	if (!Scene::init())
		return false;

	mainCamera->setPositionY(80.0f);
	mainCamera->setPositionZ(70.0f);
	mainCamera->setRotationX(glm::radians(-40.0f));

	initGBufferFBO();
	initScreenFBO();
	initQuad();

	//Scene Objects
	GBufferMat gBufferMat;
	BaseColorMat baseColorMat;

	GameObject* suzzanne = new SuzanneObj("Suzanne");
	baseColorMat = BaseColorMat();
	baseColorMat.setTextureFile("tex0", "textures/uvmap.dds");
	baseColorMat.getPipelineState().blend_enable = true;
	baseColorMat.setUniform4f("base_color", glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	baseColorMat.addOtherTexture("depth_tex", m_GBuffer_fbo.GetTexture("depth"));
	suzzanne->setMaterial(baseColorMat);
	suzzanne->setScale(30.0);
	suzzanne->setPositionY(40.0f);
	suzzanne->setPositionX(100.0f);
	suzzanne->setPositionZ(90.0f);


	GameObject* plane = new PlaneObj("floor");
	gBufferMat = GBufferMat();
	gBufferMat.setUniform4f("base_color", glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	gBufferMat.setUniform1f("base_color_factor", 1.0f);
	plane->setScale(150.0f);
	plane->setMaterial(gBufferMat);
	plane->setPositionY(20.0f);
	plane->setPositionX(10.0f);
	plane->setPositionZ(0.0f);

	GameObject* pyramid = new GameObject("pyramid");
	gBufferMat = GBufferMat();
	gBufferMat.setUniform4f("base_color", glm::vec4(0.5f, 0.3f, 0.1f, 1.0f));
	gBufferMat.setUniform1f("base_color_factor", 1.0f);
	pyramid->addMesh(Pyramid());
	pyramid->setScale(45.0);
	pyramid->setMaterial(gBufferMat);
	pyramid->setPositionY(30.0f);
	pyramid->setPositionX(80.0f);
	pyramid->setPositionZ(20.0f);

	GameObject* sphere = new GameObject("sphere");
	gBufferMat = GBufferMat();
	gBufferMat.setUniform4f("base_color", glm::vec4(0.2f, 0.5f, 0.8f, 1.0f));
	gBufferMat.setUniform1f("base_color_factor", 1.0f);
	sphere->addMesh(Sphere(1.0, 20, 20));
	sphere->setScale(20.0);
	sphere->setMaterial(gBufferMat);
	sphere->setPositionY(40.0f);
	sphere->setPositionX(-20.0f);
	sphere->setPositionZ(-10.0f);

	GameObject* alpha_blend_cube_1 = new GameObject("a_cube_1");
	baseColorMat = BaseColorMat();
	baseColorMat.getPipelineState().blend_enable = true;
	baseColorMat.setUniform4f("base_color", glm::vec4(235.0f/255.0f, 237.0f/255.0f, 90.0f/255.0f, 0.5f));
	baseColorMat.addOtherTexture("depth_tex", m_GBuffer_fbo.GetTexture("depth"));
	alpha_blend_cube_1->setMaterial(baseColorMat);
	alpha_blend_cube_1->addMesh(Cube());
	alpha_blend_cube_1->setScale(20.0f);
	alpha_blend_cube_1->setPositionY(40.0f);
	alpha_blend_cube_1->setPositionX(-55.0f);
	alpha_blend_cube_1->setPositionZ(-55.0f);

	GameObject* alpha_blend_cube_2 = new GameObject("a_cube_2");
	baseColorMat = BaseColorMat();
	baseColorMat.getPipelineState().blend_enable = true;
	baseColorMat.setUniform4f("base_color", glm::vec4(235.0f/255.0f, 52.0f / 255.0f, 161.0f / 255.0f, 0.5f));
	baseColorMat.addOtherTexture("depth_tex", m_GBuffer_fbo.GetTexture("depth"));
	alpha_blend_cube_2->setMaterial(baseColorMat);
	alpha_blend_cube_2->addMesh(Cube());
	alpha_blend_cube_2->setScale(20.0f);
	alpha_blend_cube_2->setPositionY(60.0f);
	alpha_blend_cube_2->setPositionX(-35.0f);
	alpha_blend_cube_2->setPositionZ(-45.0f);

	GameObject* alpha_blend_sphere_1 = new GameObject("a_sphere_1");
	baseColorMat = BaseColorMat();
	baseColorMat.getPipelineState().blend_enable = true;
	baseColorMat.setUniform4f("base_color", glm::vec4(235.0f / 255.0f, 52.0f / 255.0f, 161.0f / 255.0f, 0.5f));
	baseColorMat.addOtherTexture("depth_tex", m_GBuffer_fbo.GetTexture("depth"));
	alpha_blend_sphere_1->setMaterial(baseColorMat);
	alpha_blend_sphere_1->addMesh(Sphere(1.0, 20, 20));
	alpha_blend_sphere_1->setScale(20.0f);
	alpha_blend_sphere_1->setPositionY(40.0f);
	alpha_blend_sphere_1->setPositionX(-65.0f);
	alpha_blend_sphere_1->setPositionZ(75.0f);

	m_gameObjects.push_back(plane);
	m_gameObjects.push_back(pyramid);
	m_gameObjects.push_back(sphere);
	m_alpha_blend_objs.push_back(alpha_blend_cube_1);
	m_alpha_blend_objs.push_back(alpha_blend_cube_2);
	m_alpha_blend_objs.push_back(alpha_blend_sphere_1);
	m_alpha_blend_objs.push_back(suzzanne);

	return true;
}

void DeferredRenderingScene::initGBufferFBO()
{
	//GBuffer
	m_GBuffer_fbo.AttachColorBuffer("position_rt", 0, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_GBuffer_fbo.AttachColorBuffer("albedo_rt", 1, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_GBuffer_fbo.AttachColorBuffer("normal_rt", 2, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_GBuffer_fbo.AttachDepthBuffer("depth");
	m_GBuffer_fbo.Finalize();
}

void DeferredRenderingScene::initQuad()
{
	//Deferred Quad Material
	Material& deferred_mat = m_render_quad.getMaterial();
	deferred_mat.addOtherTexture("position_rt", m_GBuffer_fbo.GetTexture("position_rt"));
	deferred_mat.addOtherTexture("albedo_rt", m_GBuffer_fbo.GetTexture("albedo_rt"));
	deferred_mat.addOtherTexture("normal_rt", m_GBuffer_fbo.GetTexture("normal_rt"));
	deferred_mat.addOtherTexture("depth_rt", m_GBuffer_fbo.GetTexture("depth"));
}

void DeferredRenderingScene::setToGBufferFBO()
{	
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->ClearFrameBufferObject(m_GBuffer_fbo);
	context->SetFrameBufferObject(m_GBuffer_fbo);
}

void DeferredRenderingScene::setToScreenFBO()
{
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->ResetFrameBufferObject();
}

void DeferredRenderingScene::initScreenFBO()
{

}


void DeferredRenderingScene::logic()
{
	m_render_quad.Update();
	Scene::logic();
	for (auto obj : m_alpha_blend_objs)
	{
		obj->Update();
	}
}

void DeferredRenderingScene::render()
{	
	//GBuffer Pass
	setToGBufferFBO();
	Scene::render();
	//Lighting Pass
	setToScreenFBO();
	m_render_quad.Draw();
	//Forward Pass
	for (auto obj : m_alpha_blend_objs)
	{
		Tech_OIT::Draw(obj);
	}
}