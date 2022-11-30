#pragma once
#include "deviceCommon.h"

namespace simple_engine
{	
	class TextureData
	{

	};

	class ITextureView
	{

	};

	class ITexture
	{
	public:
		ITexture();
		ITexture(const char* file_path);
		ITexture(std::vector<const char*> cubemap_file_paths);
		virtual ~ITexture();
		virtual void SetTextureResource(const char* file_path);
		RUID GetResourceId() { return m_resource_id; }


	protected:
		RUID m_resource_id;


	};
}



