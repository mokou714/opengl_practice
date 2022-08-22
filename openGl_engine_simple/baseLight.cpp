#include "baseLight.h"
#include "InputManager.h"

using namespace simple_engine;

BaseLight::BaseLight(std::string name, LIGHT_TYPE type) :m_name(name), m_type(type), m_beingControlled(false) {
	//灯光方向默认竖直朝下
	m_rotation = glm::angleAxis<double, highp>(glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
};

glm::vec3 BaseLight::getLightDir() {
	return m_rotation * glm::vec3(0.0, 0.0, -1.0);
}

void BaseLight::Update() {
	
	if (!m_beingControlled)
		return;

	auto input_manager = InputManager::Instance();
	auto x_axis = glm::vec3(1.0, 0.0, 0.0);
	auto z_axis = glm::vec3(0.0, 0.0, -1.0);

	// 方向键旋转控制(依世界空间坐标轴)
	auto up_state = input_manager->getKeyState(CommonKeyCode::UP_ARROW);
	auto left_state = input_manager->getKeyState(CommonKeyCode::LEFT_ARROW);
	auto down_state = input_manager->getKeyState(CommonKeyCode::DOWN_ARROW);
	auto right_state = input_manager->getKeyState(CommonKeyCode::RIGHT_ARROW);
	float delta_x = 0.0f;
	float delta_z = 0.0f;
	if (up_state == CommonKeyState::PRESSED || up_state == CommonKeyState::REPEATED)
	{
		delta_x += 8.0f;
	}
	if (down_state == CommonKeyState::PRESSED || down_state == CommonKeyState::REPEATED)
	{
		delta_x -= 8.0f;
	}
	if (left_state == CommonKeyState::PRESSED || left_state == CommonKeyState::REPEATED)
	{
		delta_z += 8.0f;
	}
	if (right_state == CommonKeyState::PRESSED || right_state == CommonKeyState::REPEATED)
	{
		delta_z -= 8.0f;
	}

	glm::quat rotation_to_x = glm::normalize(glm::angleAxis<double, highp>(-delta_x / 700.0, x_axis));
	glm::quat rotation_to_z = glm::normalize(glm::angleAxis<double, highp>(-delta_z / 700.0, z_axis));

	//quat相乘顺序 rotZ * rotY * rotX * ori_orient
	m_rotation = glm::normalize(rotation_to_z * rotation_to_x * m_rotation);

}
