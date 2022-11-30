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
		RUID CreateTexture(const char* file_path) override;
		RUID CreateCubemapTexture(std::vector<const char*> files) override;
		void DeleteTexture(RUID tex_id) override;
		unsigned int CreateBuffer() override;
		void DeleteBuffer(unsigned int buffer_id) override;
		
		void OutputTextureToFile(RUID texture, int width, int height);

		static GLFWwindow* GetGLWindow() { return s_glWindow;}
	private:
		static GLDevice* s_glDevice;
		static GLFWwindow* s_glWindow;
	};
}

