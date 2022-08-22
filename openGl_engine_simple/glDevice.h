#pragma once

#include "deviceCommon.h"
#include "IRenderDevice.h"
#include "glHelper.h"

namespace simple_engine
{
	class GLDevice : public IRenderDevice
	{
	public:
		GLDevice();
		static GLDevice* Instance();
		void Destroy() override;
		bool Initialize() override;
		void CreateTexture(TextureDesc desc, TextureData data, ITexture& tex_out) override;
		unsigned int CreateBuffer() override;
		void DeleteBuffer(unsigned int buffer_id) override;
		static GLFWwindow* GetGLWindow() { return s_glWindow;}
	private:
		static GLDevice* s_glDevice;
		static GLFWwindow* s_glWindow;
	};
}

