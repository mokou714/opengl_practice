#pragma once
#include "IRenderDevice.h"
#include "IRenderContext.h"
#include "GpuBuffer.h"

namespace simple_engine
{
	class Graphics
	{
	public:
		Graphics();
		static Graphics* Instance();
		void Destroy();
		bool Initialize();
		IRenderContext* FetchRenderContext();
		IRenderDevice* FetchRenderDevice();

		std::vector<VertexBuffer> m_vertex_buffers;
		std::vector<ElementBuffer> m_element_buffers;

	private:
		static Graphics* s_graphics;
		static const RENDER_API s_render_api = RENDER_API::OPENGL;
	};
}


