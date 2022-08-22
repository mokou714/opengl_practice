#include "GpuBuffer.h"
#include "Graphics.h"

using namespace simple_engine;

GpuBuffer::GpuBuffer():
	m_buffer_size(0),
	m_element_size(0),
	m_element_count(0)
{
	IRenderDevice* device = Graphics::Instance()->FetchRenderDevice();
	m_buffer_id = device->CreateBuffer();
}

GpuBuffer::~GpuBuffer()
{
	IRenderDevice* device = Graphics::Instance()->FetchRenderDevice();
	device->DeleteBuffer(m_buffer_id);
}

void GpuBuffer::BindData(unsigned char* data, size_t size, unsigned int element_size)
{
	m_buffer_size = size;
	m_element_size = element_size;
	m_element_count = size / element_size;
}

void GpuBuffer::UnBindData()
{
	m_buffer_size = m_element_size = m_element_count = 0;
}