#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "deviceCommon.h"
#include "utils.h"
#include "glHelper.h"
#include "IRenderContext.h"
#include "glCommon.h"
#include "GpuBuffer.h"

/*
 	engine在主循环里调用glContext的函数，执行gl指令
*/

namespace simple_engine {

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

	static std::unordered_map<DepthStencilOption, UINT>  DepthStencilMap
	{
		{DepthStencilOption::FUNC_LESS, GL_LESS},
		{DepthStencilOption::FUNC_EQUAL, GL_EQUAL},
		{DepthStencilOption::FUNC_GREATER, GL_GREATER},
		{DepthStencilOption::FUNC_NOT_EQUAL, GL_NOTEQUAL},
		{DepthStencilOption::FUNC_ALWAYS, GL_ALWAYS},
		{DepthStencilOption::OP_STENCIL_KEEP, GL_KEEP},
		{DepthStencilOption::OP_STENCIL_ZERO, GL_ZERO},
		{DepthStencilOption::OP_STENCIL_REPLACE, GL_REPLACE},
		{DepthStencilOption::OP_STENCIL_INCR, GL_INCR},
		{DepthStencilOption::OP_STENCIL_INCR_WRAP, GL_INCR_WRAP},
		{DepthStencilOption::OP_STENCIL_DECR, GL_DECR},
		{DepthStencilOption::OP_STENCIL_DECR_WRAP, GL_DECR_WRAP},
		{DepthStencilOption::OP_STENCIL_INVERT, GL_INVERT},
	};

	static std::unordered_map<CullOption, UINT> CullMap
	{
		{CullOption::CULL_FACE_FRONT, GL_FRONT},
		{CullOption::CULL_FACE_BACK, GL_BACK}
	};

	static std::unordered_map<RaterizerOption, UINT> RasterizerMap
	{

	};


	class GLContext: public IRenderContext {
	public:
		static GLContext* Instance();
		void Destroy() override;
		bool Initialize() override;

		/*直接改变管线状态的操作*/
		void DrawCommand(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& coords,
			const std::vector<glm::vec3>& normals, const std::vector<unsigned short>& indices) override;

		void SetMaterial(Material& mat) override;
		void DrawIndexed(unsigned int ElementCount, unsigned int StartVertexOffset) override;
		void ResetPipelineState() override;
		void Present() override;
		void SetPipelineState(const PipelineStateObject&) override;
		void SetVertexBuffer(const VertexBuffer& buf) override;
		void SetElementBuffer(const ElementBuffer& buf) override;

		/*从文件创建资源*/
		GLuint loadTextureFromDDS(const char* file_path);
		GLuint createShaderProgram(const char* vs_path, const char* ps_path);
		
		/*输入控制*/
		void setInputKeyHandler(GLFWkeyfun);
		void setCursorHandler(GLFWcursorposfun);
		void setCursorPos(double xpos, double ypos) override;
		void getCursorPos(double& xpos, double& ypos) override;
		CommonKeyState getKeyState(CommonKeyCode key) override;

	private:
		GLContext();

		//GL&GPU资源
		static GLContext* s_glContext;
		GLuint m_vertexArray;
		GLuint m_vertexBuffer;
		GLuint m_uvBuffer;
		GLuint m_normalBuffer;
		GLuint m_colorBuffer;
		GLuint m_elementBuffer;
		//program_id -> <uniform name, uniform location>
		std::unordered_map<GLuint, std::unordered_map<std::string, GLuint>> m_programs_info_map;
		//texture_id -> uniform name
		std::vector<GLuint> m_textures;
		std::vector<GLuint> m_cubemapTextures;

	};

}