#include "planeObj.h"
#include "baseColorMat.h"

using namespace simple_engine;

PlaneObj::PlaneObj(std::string name) : GameObject(name)
{
	m_meshes.push_back(Plane());
	m_material = BaseColorMat();
}
