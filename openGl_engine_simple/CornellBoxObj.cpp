#include "CornellBoxObj.h"
#include "baseColorMat.h"
#include "cornellBox.h"

using namespace simple_engine;

CornellBoxObj::CornellBoxObj(std::string name) :GameObject(name)
{
	m_material = BaseColorMat();
	m_meshes.push_back(CornellBox());
}

