#include "interiorMappingMat.h"

using namespace simple_engine;

InteriorMappingMat::InteriorMappingMat() : Material()
{
	m_vertex_shader = "materials/InteriorTexture.vs";
	m_pixel_shader = "materials/InteriorTexture.ps";

	m_semanticsMap["wvp"] = SHADER_SEMANTICS::WVP;
	m_semanticsMap["cam_pos"] = SHADER_SEMANTICS::CAMERA_POSITION;
	m_semanticsMap["w"] = SHADER_SEMANTICS::W;
}

void InteriorMappingMat::addCeiling(vec4 plane, glm::mat4 model_mat)
{
	glm::vec3 normal = glm::normalize(glm::vec3(model_mat * vec4(vec3(plane), 0.0f)));
	float d = glm::dot(glm::vec3(model_mat * (vec4(vec3(plane) * plane.w, 1.0))), normal);

	if (m_uniforms4fv.count("ceilings"))
	{
		m_uniforms4fv["ceilings"].push_back(vec4(normal, d));
	}
	else
	{
		m_uniforms4fv["ceilings"] = { vec4(normal, d) };
	}

	m_uniforms1f["ceiling_count"] = m_uniforms4fv["ceilings"].size();
}

void InteriorMappingMat::addSideWall(vec4 plane, glm::mat4 model_mat)
{
	glm::vec3 normal = glm::normalize(glm::vec3(model_mat * vec4(vec3(plane), 0.0f)));
	float d = glm::dot(glm::vec3(model_mat * (vec4(vec3(plane)*plane.w, 1.0))), normal);

	if (m_uniforms4fv.count("side_walls"))
	{
		m_uniforms4fv["side_walls"].push_back(vec4(normal, d));
	}
	else
	{
		m_uniforms4fv["side_walls"] = { vec4(normal, d) };
	}
	m_uniforms1f["side_wall_count"] = m_uniforms4fv["side_walls"].size();
}

void InteriorMappingMat::addBackWall(vec4 plane, glm::mat4 model_mat)
{
	glm::vec3 normal = glm::normalize(glm::vec3(model_mat * vec4(vec3(plane), 0.0f)));
	float d = glm::dot(glm::vec3(model_mat * (vec4(vec3(plane) * plane.w, 1.0))), normal);

	if (m_uniforms4fv.count("back_walls"))
	{
		m_uniforms4fv["back_walls"].push_back(vec4(normal, d));
	}
	else
	{
		m_uniforms4fv["back_walls"] = { vec4(normal, d) };
	}
	m_uniforms1f["back_wall_count"] = m_uniforms4fv["back_walls"].size();
}