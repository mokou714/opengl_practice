#pragma once

namespace simple_engine
{	
	class BufferData
	{

	};

	class BufferView
	{
		
	};


	class GpuBuffer
	{
	public:
		GpuBuffer();
		~GpuBuffer();
		void BindData(unsigned char* data, size_t size, unsigned int element_size);
		void UnBindData();
		size_t GetBufferSize() const { return m_buffer_size; }
		unsigned int GetElementCount() const { return m_element_count; }
		unsigned int GetElementSize() const { return m_element_size; }

	protected:
		unsigned int m_buffer_id;
		size_t m_buffer_size;
		unsigned int m_element_count;
		unsigned int m_element_size;
		BufferView m_buffer_view;
	};

	class VertexBuffer : GpuBuffer
	{
	public:

	};

	class ElementBuffer : GpuBuffer
	{
	public:
	};

}


