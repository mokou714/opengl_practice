#include "deferredQuadObj.h"
#include "deferredRenderingMat.h"
#include "quad.h"
using namespace simple_engine;

DeferredQuadObj::DeferredQuadObj(std::string name) : GameObject(name)
{
	m_meshes.push_back(Quad());
	m_material = DeferredRenderingMat();
}