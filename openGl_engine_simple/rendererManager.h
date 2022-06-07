#pragma once
#include "baseRenderer.h"
#include <vector>
namespace simple_engine {

	class RendererManager {

	public:
		static RendererManager Instance();
		void addRenderer(BaseRenderer* renderer);
		std::vector<BaseRenderer*> getRenderersByType(RendererType type);
		std::vector<BaseRenderer*> allRenderers();
		bool removeRendererByName(std::string name);
		bool removeRenderersByType(RendererType type);

	private:
		static RendererManager s_rendererManager;
		std::vector<BaseRenderer*> renderers;

	};

}