#pragma once
#include "deviceCommon.h"
#include "GpuBuffer.h"

namespace simple_engine
{
	namespace Display
	{	
		struct SwapChainDesc
		{
			unsigned int width;
			unsigned int height;
			PixelFormat format;
		};

		class SwapChain
		{
		public:
			bool Initialize(const SwapChainDesc& desc);
			void Destroy();
		};

		static SwapChain* s_swap_chain = nullptr;
		static GpuBuffer* s_color_buffer = nullptr;
		bool Initialize();
		void Present();
		void SetFullScreen();
		void Resize(unsigned int width, unsigned int height);
		void Destroy();
	}
}

