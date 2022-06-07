#pragma once
#include "gameObject.h"

namespace simple_engine {

	class Camera :public GameObject {
	public:
		Camera(std::string name);
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();
		void Update() override;
	protected:
		void limitRotation() override;
	private:
		float m_fov;
		float m_near;
		float m_far;
	};
}