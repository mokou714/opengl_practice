#include "cameraManager.h"

using namespace simple_engine;

CameraManager* CameraManager::s_cameraManager = nullptr;

CameraManager::CameraManager():
	currentCameraIndex(-1)
{
}

CameraManager* CameraManager::Instance() {
	if (s_cameraManager == nullptr) {
		s_cameraManager = new CameraManager();
	}
	return s_cameraManager;
}

void CameraManager::destroy() {
	if (s_cameraManager) {
		delete s_cameraManager;
		s_cameraManager = nullptr;
	}
}

Camera* CameraManager::createCameraByDefault(std::string name)
{
	return new Camera(name);
}


//Camera* CameraManager::createCameraWithConfig(const CameraConfig& config) {
//
//}

bool CameraManager::removeCamera(std::string name) {
	auto iter = m_cameras.end();
	for (auto start = m_cameras.begin(); start != m_cameras.end(); ++start) {
		if ((*start)->getName() == name)
			iter = start;
	}
	if (iter != m_cameras.end()) {
		m_cameras.erase(iter);
		return true;
	}
	return false;
}