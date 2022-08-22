#include "Graphics.h"
#include "Display.h"
#include "glDevice.h"
#include "glContext.h"

using namespace simple_engine;

Graphics* Graphics::s_graphics = nullptr;

Graphics* Graphics::Instance()
{
	if (Graphics::s_graphics == nullptr)
	{
		Graphics::s_graphics = new Graphics();
	}
	return Graphics::s_graphics;
}

Graphics::Graphics()
{

}

bool Graphics::Initialize()
{
	switch (Graphics::s_render_api)
	{
	case RENDER_API::DX11:
	case RENDER_API::DX12:
	case RENDER_API::OPENGL:
	default:
		if (!GLDevice::Instance()->Initialize() || !GLContext::Instance()->Initialize())
			return false;
	}
	if (!Display::Initialize())
		return false;

	//create all context owned buffers
	//VertexBuffer vertex_buffer = VertexBuffer();
	//VertexBuffer uv_buffer = VertexBuffer();
	//VertexBuffer normal_buffer = VertexBuffer();

	//m_vertex_buffers.push_back(vertex_buffer);

	return true;
}

void Graphics::Destroy()
{	
	m_vertex_buffers.clear();
	m_element_buffers.clear();

	Display::Destroy();
	GLContext::Instance()->Destroy();
	GLDevice::Instance()->Destroy();
}

IRenderContext* Graphics::FetchRenderContext()
{
	switch (Graphics::s_render_api)
	{
	case RENDER_API::DX11:
	case RENDER_API::DX12:
	case RENDER_API::OPENGL:
	default:
		return GLContext::Instance();
	}
}
IRenderDevice* Graphics::FetchRenderDevice()
{
	switch (Graphics::s_render_api)
	{
	case RENDER_API::DX11:
	case RENDER_API::DX12:
	case RENDER_API::OPENGL:
	default:
		return GLDevice::Instance();
	}
}