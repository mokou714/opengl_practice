#pragma once
#include "deviceCommon.h"
#include "GpuBuffer.h"
#include "ITexture.h"

/* responsible for creating all other gpu objects */

namespace simple_engine
{	
	class IRenderDevice
	{
	public:
		virtual bool Initialize();
		virtual void Destroy() = 0;
		virtual void CreateTexture(TextureDesc desc, TextureData data, ITexture& tex_out) = 0;
		virtual RUID CreateTexture(const char*) = 0;
		virtual RUID CreateCubemapTexture(std::vector<const char*> files) = 0;
		virtual void DeleteTexture(unsigned int tex_id) = 0;
		virtual unsigned int CreateBuffer();
		virtual void DeleteBuffer(unsigned int buffer_id);
		virtual bool Initialized() { return is_initialized; }
	protected:
		bool is_initialized;
	};

}

