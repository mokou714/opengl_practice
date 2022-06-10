#include "sphereObj.h"
#include "sphere.h"
#include "baseColorMat.h"

using namespace simple_engine;

SphereObj::SphereObj(std::string name): GameObject(name) {
	m_material = BaseColorMat();
	m_meshes.push_back(Sphere(5.0f, 30, 30));
}
