#pragma once
#include "gameObject.h"
#include <vector>
#include <string>

namespace simple_engine {
	enum RendererType
	{
		NORMAL,
		SHADOW_MAP,
		POSTPROCESS,
	};

	class BaseRenderer {

	public:
		BaseRenderer(std::string name);
		void AddGameObject();
		void setRendererTypo(RendererType type);
		RendererType getRendererType();

	private:
		std::string name;
		RendererType _rendererType;
		std::vector<GameObject> _gameObjects;
	};
}