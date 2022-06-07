#pragma once
#include "camera.h"
#include <string>
#include <vector>

namespace simple_engine {

	struct CameraConfig {
		std::string name;
	};

	class CameraManager {

	public:
		static CameraManager* Instance();
		Camera* createCameraByDefault(std::string name);
		//Camera* createCameraWithConfig(const CameraConfig& config);
		bool removeCamera(std::string name);
		void destroy();
			
	private:
		static CameraManager* s_cameraManager;
		CameraManager();
		std::vector<Camera*> m_cameras;
		int currentCameraIndex;
	};

}