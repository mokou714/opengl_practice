#pragma once
#include <vector>
#include <unordered_map>
#include "gl.h"

namespace simple_engine{

	enum class SHADER_SEMANTICS {
		W,
		V,
		P,
		WVP,
		WV,
		CAMERA_POSITION,
		LIGHT_DIR,
	};


	class Material
	{
	public:
		Material();
		
		void setUniform4f(const char* name, glm::vec4 data) { m_uniforms4f[name] = data; }
		void setUniform3f(const char* name, glm::vec3 data) { m_uniforms3f[name] = data; }
		void setUniformMat4(const char* name, glm::mat4 data) { m_uniformsMat4[name] = data; }
		void setShaderProgram(GLuint program_id) { m_glShaderProgram = program_id; }
		void addGLTexture(std::string uniform_name, GLuint tex_id) { m_glTextures[uniform_name] = tex_id; }

		GLuint getShaderProgram() { return m_glShaderProgram; }
		const std::unordered_map<std::string, GLuint>& getGLTextures() { return m_glTextures;}
		const std::unordered_map<std::string, const char*>& getTextureResources() { return m_textures; }
		const std::unordered_map<std::string, std::vector<const char*>>& getCubemapTextureResources() { return m_cubemapTextures; }
		const std::string& getVSFile() { return m_vertex_shader; }
		const std::string& getPSFile() { return m_pixel_shader; }
		const std::unordered_map<std::string, glm::mat4>& getUniformsMat4() { return m_uniformsMat4; }
		const std::unordered_map<std::string, glm::vec4>& getUniforms4f() { return m_uniforms4f; }
		const std::unordered_map<std::string, glm::vec3>& getUniforms3f() { return m_uniforms3f; }
		const std::unordered_map<std::string, glm::vec2>& getUniforms2f() { return m_uniforms2f; }
		const std::unordered_map<std::string, float>& getUniforms1f() { return m_uniforms1f; }
		const std::unordered_map<std::string, SHADER_SEMANTICS>& getSemanticsMap() { return m_semanticsMap; }
		
		void setShaderFiles(std::string vs, std::string ps) { m_vertex_shader = vs; m_pixel_shader = ps; }
		void setTextureFile(const char* uniform_name, const char* file) { m_textures[uniform_name] = file; }
		void setCubemapTextureFiles(const char* uniform_name, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back);

	protected:
		//uniform name, data
		std::unordered_map<std::string, glm::vec4> m_uniforms4f;
		std::unordered_map<std::string, glm::vec3> m_uniforms3f;
		std::unordered_map<std::string, glm::vec2> m_uniforms2f;
		std::unordered_map<std::string, float> m_uniforms1f;
		std::unordered_map<std::string, glm::mat4> m_uniformsMat4;
		std::unordered_map<std::string, const char*> m_textures;	//uniform名 -> 文件路径
		std::unordered_map<std::string, std::vector<const char*>> m_cubemapTextures;	// right left top bottom back front的顺序 和gl枚举定义顺序一致
		std::string m_vertex_shader;
		std::string m_pixel_shader;
		
		//uniform name -> semantic
		std::unordered_map<std::string, SHADER_SEMANTICS> m_semanticsMap;

		//todo gl设备层的数据是否要放在这？
		GLuint m_glShaderProgram;
		std::unordered_map<std::string, GLuint> m_glTextures;

	};

}