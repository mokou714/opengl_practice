#pragma once
#include <vector>
#include <unordered_map>
#include "gl.h"

namespace simple_engine{

	class Material
	{
	public:
		Material();
		
		void setUniform4f(const char* name, glm::vec4 data) { m_uniforms4f[name] = data; }
		void setUniform3f(const char* name, glm::vec3 data) { m_uniforms3f[name] = data; }
		void setUniformMat4(const char* name, glm::mat4 data) { m_uniformsMat4[name] = data; }
		void setShaderProgram(GLuint program_id) { m_shaderProgram = program_id; }

		GLuint getShaderProgram() { return m_shaderProgram; }
		std::string getVSFile() { return m_vertex_shader; }
		std::string getPSFile() { return m_pixel_shader; }
		std::unordered_map<std::string, glm::vec4>& getUniforms4f() { return m_uniforms4f; }
		std::unordered_map<std::string, glm::vec3>& getUniforms3f() { return m_uniforms3f; }
		std::unordered_map<std::string, glm::mat4>& getUniformsMat4() { return m_uniformsMat4; }
		void setShaderFiles(std::string vs, std::string ps) { m_vertex_shader = vs; m_pixel_shader = ps; }

	private:
		//uniform name, data
		std::unordered_map<std::string, glm::vec4> m_uniforms4f;
		std::unordered_map<std::string, glm::vec3> m_uniforms3f;
		std::unordered_map<std::string, glm::mat4> m_uniformsMat4;
		std::string m_vertex_shader;
		std::string m_pixel_shader;

		//todo 设备层的数据是否要放在这？
		GLuint m_shaderProgram;

	};

}