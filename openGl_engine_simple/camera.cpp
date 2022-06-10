#include "camera.h"
#include "InputManager.h"

using namespace simple_engine;

Camera::Camera(std::string name): GameObject(name), m_fov(45.0f), m_near(0.01f), m_far(2000.0f)
{
	m_position.z += 80;
	m_position.y += 100;

	m_rotation *= glm::angleAxis(glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::Update()
{
	GameObject::Update();

	// 移动控制
	auto input_manager = InputManager::Instance();
	auto w_state = input_manager->getKeyState(KeyCode::W);
	auto a_state = input_manager->getKeyState(KeyCode::A);
	auto s_state = input_manager->getKeyState(KeyCode::S);
	auto d_state = input_manager->getKeyState(KeyCode::D);

	glm::vec3 delta_forward;
	glm::vec3 delta_right;
	glm::vec3 forward = glm::vec3(getForward());
	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 right = glm::vec3(getRight());

	if (w_state == KeyState::Pressed || w_state == KeyState::Repeated)
	{
		delta_forward = forward * 1.0f;
		CONSOLE_PRINTF("Moving forward by dir: %f, %f, %f\n", delta_forward.x, delta_forward.y, delta_forward.z)
	}
	if (s_state == KeyState::Pressed || s_state == KeyState::Repeated)
	{
		delta_forward = -forward * 1.0f;
		CONSOLE_PRINTF("Moving forward by dir: %f, %f, %f\n", delta_forward.x, delta_forward.y, delta_forward.z)
	}
	if (a_state == KeyState::Pressed || a_state == KeyState::Repeated)
	{
		delta_right = -right * 1.0f;
		CONSOLE_PRINTF("Moving left by dir: %f, %f, %f\n", delta_right.x, delta_right.y, delta_right.z)
	}
	if (d_state == KeyState::Pressed || d_state == KeyState::Repeated)
	{
		delta_right = right * 1.0f;
		CONSOLE_PRINTF("Moving left by dir: %f, %f, %f\n", delta_right.x, delta_right.y, delta_right.z)
	}
	m_inputDeltaTranslation += glm::vec3(delta_forward)  + glm::vec3(delta_right);

	// 视角控制
	double delta_x = input_manager->getDeltaMouseX();
	double delta_y = input_manager->getDeltaMouseY();
	glm::quat rotation_to_up, rotation_to_right;
	if (delta_x != 0.0)
	{
		rotation_to_up = glm::normalize(glm::angleAxis<double, highp>(-delta_x / 700.0, up));
	}
	if (delta_y != 0.0)
	{
		rotation_to_right = glm::normalize(glm::angleAxis<double, highp>(-delta_y / 700.0, right));
	}

	//quat相乘顺序 rotZ * rotY * rotX * ori_orient
	m_rotation = glm::normalize(rotation_to_up * rotation_to_right * m_rotation);

	if (SE_DEBUG_MODE && ( delta_x != 0.0 || delta_y != 0.0) )
	{
		CONSOLE_PRINTF("Mouse delta X: %f, delta Y: %f\n", delta_x, delta_y);
		CONSOLE_PRINTF("Up rotation quat: %f, %f, %f, %f\n", rotation_to_up.x, rotation_to_up.y, rotation_to_up.z, rotation_to_up.w);
		CONSOLE_PRINTF("Right rotation quat: %f, %f, %f, %f\n", rotation_to_right.x, rotation_to_right.y, rotation_to_right.z, rotation_to_right.w);
		CONSOLE_PRINTF("Forward dir: %f, %f, %f\n", forward.x, forward.y, forward.z);
		CONSOLE_PRINTF("Right dir: %f, %f, %f\n", right.x, right.y, right.z);
		CONSOLE_PRINTF("Up dir: %f, %f, %f,\n", up.x, up.y, up.z);
		CONSOLE_PRINTF("m_rotation: %f, %f, %f,\n", m_rotation.x, m_rotation.y, m_rotation.z);
		CONSOLE_PRINTF("-------------------------------------\n");
	}

}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspective(glm::radians(m_fov), 4.0f / 3.0f, m_near, m_far);
}

glm::mat4 Camera::getViewMatrix() {
	auto pitch = glm::pitch(m_rotation);
	auto yaw = glm::yaw(m_rotation);
	auto roll = glm::roll(m_rotation);
	glm::vec4 forward = getForward();
	glm::vec3 _forward = glm::vec3(forward.x, forward.y, forward.z);
	return glm::lookAt(getPosition(), getPosition() + _forward, glm::vec3(0, 1, 0));
}

void Camera::limitRotation() {
	//m_rotation.x = glm::clamp<double>(m_rotation.x, -60.0, 60.0);
	//m_rotation.y = glm::clamp<double>(m_rotation.y, -80.0, 80.0);
}