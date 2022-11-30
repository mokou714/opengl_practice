#pragma once
#include "deviceCommon.h"
#include <vector>
#include <unordered_map>
#include "PipelineStateObject.h"
#include "ITexture.h"



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

	enum class TEXTURE_MAP_TYPE {
		DEFAUT,
		CUBEMAP,
	};


	class Material
	{
	public:
		Material();
		
		void setUniform4f(const char* name, glm::vec4 data) { m_uniforms4f[name] = data; }
		void setUniform4fv(const char* name, std::vector<glm::vec4> data) { m_uniforms4fv[name] = data; }
		void setUniform3f(const char* name, glm::vec3 data) { m_uniforms3f[name] = data; }
		void setUniform3fv(const char* name, std::vector<glm::vec3> data) { m_uniforms3fv[name] = data; }
		void setUniformMat4(const char* name, glm::mat4 data) { m_uniformsMat4[name] = data; }
		void setUniform1f(const char* name, float data) { m_uniforms1f[name] = data; }
		void setUniform1fv(const char* name, std::vector<float> data) { m_uniforms1fv[name] = data; }
		void setShaderProgram(RUID program_id) { m_glShaderProgram = program_id; }
		void setPipelineState(PipelineStateObject state) { m_pipeline_state = state; }
		void addOtherTexture(const char* name, RUID resource_id) { m_other_texture_resources[name] = resource_id; }

		RUID getShaderProgram() { return m_glShaderProgram; }
		const std::string& getVSFile() { return m_vertex_shader; }
		const std::string& getPSFile() { return m_pixel_shader; }
		const std::unordered_map<std::string, glm::mat4>& getUniformsMat4() { return m_uniformsMat4; }
		const std::unordered_map<std::string, glm::vec4>& getUniforms4f() { return m_uniforms4f; }
		const std::unordered_map<std::string, std::vector<glm::vec4>>& getUniforms4fv() { return m_uniforms4fv; }
		const std::unordered_map<std::string, glm::vec3>& getUniforms3f() { return m_uniforms3f; }
		const std::unordered_map<std::string, std::vector<glm::vec3>>& getUniforms3fv() { return m_uniforms3fv; }
		const std::unordered_map<std::string, glm::vec2>& getUniforms2f() { return m_uniforms2f; }
		const std::unordered_map<std::string, float>& getUniforms1f() { return m_uniforms1f; }
		const std::unordered_map<std::string, std::vector<float>>& getUniforms1fv() { return m_uniforms1fv; }
		const std::unordered_map<std::string, SHADER_SEMANTICS>& getSemanticsMap() { return m_semanticsMap; }
		PipelineStateObject& getPipelineState() { return m_pipeline_state; }
		std::unordered_map<std::string, ITexture*>& getTextures() { return m_textures; }
		std::unordered_map<std::string, ITexture*>& getCubemapTextures() { return m_cubemapTextures; }
		std::unordered_map<std::string, RUID>& getOtherTextures() { return m_other_texture_resources; }
		
		void setShaderFiles(std::string vs, std::string ps) { m_vertex_shader = vs; m_pixel_shader = ps; }
		void setTextureFile(const char* uniform_name, const char* file);
		void setCubemapTextureFiles(const char* uniform_name, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back);
		void setCubemapTextureFiles(const char* uniform_name, std::vector<const char*> texture_files);

		// Material的texture资源不跟随object的生命周期 由外部手动调用销毁
		void releaseAllTextures();

	protected:
		//uniform name, data
		std::unordered_map<std::string, glm::vec4> m_uniforms4f;
		std::unordered_map<std::string, std::vector<glm::vec4>> m_uniforms4fv;
		std::unordered_map<std::string, glm::vec3> m_uniforms3f;
		std::unordered_map<std::string, std::vector<glm::vec3>> m_uniforms3fv;
		std::unordered_map<std::string, glm::vec2> m_uniforms2f;
		std::unordered_map<std::string, float> m_uniforms1f;
		std::unordered_map<std::string, glm::mat4> m_uniformsMat4;
		std::unordered_map<std::string, std::vector<float>> m_uniforms1fv;

		std::unordered_map<std::string, ITexture*> m_textures;
		std::unordered_map<std::string, ITexture*> m_cubemapTextures;
		std::unordered_map<std::string, RUID> m_other_texture_resources;	// todo 其他来源的GPU Texture也用ITexture封装 并且用引用计数管理

		std::string m_vertex_shader;
		std::string m_pixel_shader;
		PipelineStateObject m_pipeline_state;

		//uniform name -> semantic
		std::unordered_map<std::string, SHADER_SEMANTICS> m_semanticsMap;

		//todo gl设备层的数据是否要放在这？
		RUID m_glShaderProgram;

	};

}