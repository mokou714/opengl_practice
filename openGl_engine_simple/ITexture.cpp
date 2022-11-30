#include "ITexture.h"
#include "Graphics.h"

using namespace simple_engine;

ITexture::ITexture() :m_resource_id(0)
{

}



ITexture::ITexture(const char* file_path)
{
	IRenderDevice* device = Graphics::Instance()->FetchRenderDevice();
	m_resource_id = device->CreateTexture(file_path);
}

ITexture::ITexture(std::vector<const char*> cubemap_file_paths)
{
	IRenderDevice* device = Graphics::Instance()->FetchRenderDevice();
	m_resource_id = device->CreateCubemapTexture(cubemap_file_paths);
}

ITexture::~ITexture()
{
	IRenderDevice* device = Graphics::Instance()->FetchRenderDevice();
	device->DeleteTexture(m_resource_id);
}

void ITexture::SetTextureResource(const char* file_path)
{	
	IRenderDevice* device = Graphics::Instance()->FetchRenderDevice();
	if (m_resource_id != 0)
	{
		device->DeleteTexture(m_resource_id);
	}
	m_resource_id = device->CreateTexture(file_path);
}
