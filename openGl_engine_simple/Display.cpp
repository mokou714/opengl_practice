#include "Display.h"
#include "Graphics.h"

using namespace simple_engine;

bool Display::SwapChain::Initialize(const SwapChainDesc& desc)
{
	CONSOLE_PRINTF("Create swap chain, format:%s, width:%d, height:%d\n", 
		PixelFormatStr[desc.format], desc.width, desc.height);
	return true;
}

void Display::SwapChain::Destroy()
{
	CONSOLE_PRINTF("Destroy swap chain\n");
}

bool Display::Initialize()
{	
	if (s_swap_chain != nullptr)
	{
		return false;
	}

	s_swap_chain = new SwapChain();
	SwapChainDesc desc;
	desc.format = PixelFormat::PIXEL_FORMAT_R8G8B8A8_UNORM;
	desc.width = SE_WINDOW_WIDTH;
	desc.height = SE_WINDOW_HEIGHT;
	s_swap_chain->Initialize(desc);
	
	CONSOLE_PRINTF("Initialize Color buffer\n")
	s_color_buffer = new GpuBuffer();

	return true;
}

void Display::SetFullScreen()
{

}

void Display::Resize(unsigned int width, unsigned int height)
{

}

void Display::Present()
{	
	CONSOLE_PRINTF("Present\n");
	IRenderContext* context = Graphics::Instance()->FetchRenderContext();
	context->Present();
}

void Display::Destroy()
{
	delete s_color_buffer;
	s_color_buffer = nullptr;
}