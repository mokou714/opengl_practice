#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "material.h"
#include "gl.h"
#include "utils.h"

/*
 	engine在主循环里调用glContext的函数，执行gl指令
*/

namespace simple_engine {

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

	class GLContext {
	public:
		static GLContext* Instance();
		void destroy();
		bool init();

		/*直接改变管线状态的操作*/
		void resetPipelineState();
		void present();
		void drawCommand(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& coords,
			const std::vector<glm::vec3>& normals, const std::vector<unsigned short>& indices);
		void setMaterial(Material& mat);
		void setFaceCulling(bool enbaled, bool is_back);

		/*创建/销毁资源的操作*/
		GLuint createTexture();
		Material createMaterial(std::string vs, std::string ps);
		void deleteMaterial(Material& material);

		/*从文件创建资源*/
		GLuint loadTextureFromDDS(const char* file_path);
		GLuint createShaderProgram(const char* vs_path, const char* ps_path);
		
		/*输入控制*/
		void setInputKeyHandler(GLFWkeyfun);
		void setCursorHandler(GLFWcursorposfun);
		void setCursorPos(double xpos, double ypos);
		void getCursorPos(double& xpos, double& ypos);
		int getKeyState(int key);

	private:
		GLContext();
		bool is_inited;

		//GL&GPU资源
		static GLContext* s_glContext;
		static GLFWwindow* s_glWindow;
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