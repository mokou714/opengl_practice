#include "cubeObj.h"
#include "cube.h"
#include "baseColorMat.h"

using namespace simple_engine;

CubeObj::CubeObj(std::string name) : GameObject(name) {
	m_meshes.push_back(Cube());
	m_material = BaseColorMat();
}
