#include "rayMarching.h"
#include "cornellBoxObj.h"
#include "sphereObj.h"
#include "cubeObj.h"
#include "SSR_GBuffer.h"
#include "Graphics.h"

using namespace simple_engine;

RayMarching::RayMarching(const std::string name, Camera* camera):DeferredRenderingScene(name, camera)
{
	m_screen_fbo = GLFrameBufferObject(SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT);
	m_final_screen_fbo = GLFrameBufferObject(SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT);
	m_final_screen_quad = DeferredQuadObj("Deferred Render Quad");
}

bool RayMarching::init()
{
	if (!Scene::init())
		return false;

	mainCamera->setPositionZ(30.0f);

	initGBufferFBO();
	initScreenFBO();
	initQuad();

	SSR_GBuffer gBufferMat;

	auto* cornell_box = new CornellBoxObj("Cornell Box");
	gBufferMat = SSR_GBuffer();
	cornell_box->setMaterial(gBufferMat);
	cornell_box->setScale(15.0f);
	m_gameObjects.push_back(cornell_box);

	auto* sphere = new SphereObj("sphere");
	gBufferMat = SSR_GBuffer();
	sphere->setMaterial(gBufferMat);
	sphere->setScale(1.0f);
	sphere->setPositionX(7.0f);
	sphere->setPositionY(-10.0f);
	sphere->setPositionZ(-3.0f);
	sphere->getMaterial().setUniform4f("base_color", glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	m_gameObjects.push_back(sphere);

	auto* cube = new CubeObj("cube");
	gBufferMat = SSR_GBuffer();
	cube->setMaterial(gBufferMat);
	cube->setScale(5.0f);
	cube->setPositionX(-7.0f);
	cube->setPositionY(-10.0f);
	cube->setPositionZ(-3.0f);
	cube->getMaterial().setUniform4f("base_color", glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	m_gameObjects.push_back(cube);

	return true;
}

void RayMarching::initQuad()
{
	DeferredRenderingScene::initQuad();
	m_render_quad.getMaterial().setShaderFiles("materials/DeferredSSR.vs", "materials/DeferredSSR.ps");
	m_render_quad.getMaterial().addOtherTexture("last_frame_tex", m_final_screen_fbo.GetTexture("color0"));

	// 输出target不能作为输入 额外draw一个quad
	
	m_final_screen_quad.getMaterial().setShaderFiles("materials/DrawScreenQuad.vs", "materials/DrawScreenQuad.ps");
	m_final_screen_quad.getMaterial().addOtherTexture("tex0", m_screen_fbo.GetTexture("color0"));
}

void RayMarching::initGBufferFBO()
{
	m_GBuffer_fbo.AttachColorBuffer("position_rt", 0, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_GBuffer_fbo.AttachColorBuffer("albedo_rt", 1, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_GBuffer_fbo.AttachColorBuffer("normal_rt", 2, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_GBuffer_fbo.AttachDepthBuffer("depth");
	m_GBuffer_fbo.Finalize();
}

void RayMarching::initScreenFBO()
{
	m_screen_fbo.AttachColorBuffer("color0", 0, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_screen_fbo.Finalize();

	m_final_screen_fbo.AttachColorBuffer("color0", 0, PixelFormat::PIXEL_FORMAT_R32G32B32_FLOAT);
	m_final_screen_fbo.Finalize();
}

void RayMarching::setToScreenFBO()
{
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->ClearFrameBufferObject(m_screen_fbo);
	context->SetFrameBufferObject(m_screen_fbo);
}

void RayMarching::setToFinalScreenFBO()
{
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->ClearFrameBufferObject(m_final_screen_fbo);
	context->SetFrameBufferObject(m_final_screen_fbo);
}

void RayMarching::render()
{	
	//draw到ssr的quad上
	DeferredRenderingScene::render();

	//用ssr的out color单独draw一次屏幕quad
	setToFinalScreenFBO();
	m_final_screen_quad.Draw();

	//blit屏幕quad到back buffer
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->BlitFrameBuffer(&m_final_screen_fbo, nullptr);
}
