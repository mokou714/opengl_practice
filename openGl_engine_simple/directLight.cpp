#include "directLight.h"

using namespace simple_engine;

DirectLight::DirectLight(std::string name) : BaseLight(name, LIGHT_TYPE::DIRECT)
{
	m_lightDir = glm::vec3(0.0f, 1.0f, 0.0f);
}