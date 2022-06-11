#include "glContext.h"
#include <stdio.h>

using namespace simple_engine;

GLContext* GLContext::s_glContext = nullptr;
GLFWwindow* GLContext::s_glWindow = nullptr;

GLContext::GLContext() 
	:is_inited(false),
	m_vertexArray(0),
	m_vertexBuffer(0),
	m_uvBuffer(0),
	m_normalBuffer(0),
	m_colorBuffer(0),
	m_elementBuffer(0)
{	
}

GLContext* GLContext::Instance() {
	if (s_glContext == nullptr) {
		s_glContext = new GLContext();
	}
	return s_glContext;
}

bool GLContext::init() {
	//initialize glfw
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return false;
	}

	//create window
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	s_glWindow = glfwCreateWindow(SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT, "GL Simple Engine", NULL, NULL);

	if (s_glWindow == nullptr) {
		fprintf(stderr, "Failed to create window");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(s_glWindow);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to init glew");
		getchar();
		glfwTerminate();
		return false;
	}

	glfwSetInputMode(s_glWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(s_glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(s_glWindow, SE_WINDOW_WIDTH / 2, SE_WINDOW_HEIGHT / 2);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


	//顶点layout array 
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);


	//顶点layout缓存
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_uvBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_elementBuffer);


	is_inited = true;
	return true;
}

void GLContext::resetPipelineState() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLContext::setMaterial(Material& mat)
{	
	//创建并绑定shader program
	GLuint program_id = mat.getShaderProgram();
	if (!m_programs_info_map.count(program_id)) {
		program_id = createShaderProgram(mat.getVSFile().c_str(), mat.getPSFile().c_str());
		assert(program_id != 0);
		m_programs_info_map[program_id] = std::unordered_map<std::string, GLuint>();
		mat.setShaderProgram(program_id);
	}

	glUseProgram(program_id);

	auto& program_info_map = m_programs_info_map[program_id];

	//创建并绑定uniform location和uniform数据
	for (auto& pair : mat.getUniformsMat4()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniformMatrix4fv(program_info_map[name], 1, GL_FALSE, &pair.second[0][0]);
	}
	for (auto& pair : mat.getUniforms4f()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform4f(program_info_map[name], pair.second.x, pair.second.y, pair.second.z, pair.second.w);
	}
	for (auto& pair : mat.getUniforms3f()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform3f(program_info_map[name], pair.second.x, pair.second.y, pair.second.z);
	}
	for (auto& pair : mat.getUniforms2f()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform2f(program_info_map[name], pair.second.x, pair.second.y);
	}
	for (auto& pair : mat.getUniforms1f()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform1f(program_info_map[name], pair.second);
	}

	//创建并绑定纹理
	if (mat.getTextureResources().size() > 0 || mat.getCubemapTextureResources().size() > 0) {
		//材质有纹理但未创建gl纹理 (不考虑部分已创建的情况)
		if (mat.getGLTextures().size() == 0) {
			for(auto& pair: mat.getTextureResources()){
				auto uniform_name = pair.first;
				auto texture_file = pair.second;
				GLuint tex_id = Utils::createGLTexture(texture_file);
				if (tex_id) {
					m_textures.push_back(tex_id);
					program_info_map[uniform_name] = glGetUniformLocation(program_id, uniform_name.c_str());
					mat.addGLTexture(uniform_name, tex_id);
				}
				else {
					CONSOLE_PRINTF("GLContext failed to create texture: %s\n", texture_file);
				}
			}

			for (auto& pair : mat.getCubemapTextureResources()) {
				auto uniform_name = pair.first;
				GLuint cubemap_id = Utils::createCubemap(pair.second);
				if (cubemap_id)
				{
					m_cubemapTextures.push_back(cubemap_id);
					program_info_map[uniform_name] = glGetUniformLocation(program_id, uniform_name.c_str());
					mat.addGLTexture(uniform_name, cubemap_id);
				}
				else {
					CONSOLE_PRINTF("GLContext failed to create cubemap: %s\n", pair.second[0]);
				}
				
			}
		}
		
		// 绑定纹理和采样器到管线
		unsigned short texture_index = 0;
		assert(mat.getGLTextures().size() <= 32);
		for (auto& pair : mat.getGLTextures()) {
			auto uniform_name = pair.first;
			auto gl_texture = pair.second;
			glActiveTexture(GL_TEXTURE0 + texture_index);

			if (std::find(m_textures.cbegin(), m_textures.cend(), gl_texture) != m_textures.cend())
			{
				glBindTexture(GL_TEXTURE_2D, gl_texture);
			}
			else if (std::find(m_cubemapTextures.cbegin(), m_cubemapTextures.cend(), gl_texture) != m_cubemapTextures.cend())
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, gl_texture);
			}
			else {
				CONSOLE_PRINTF("glBindTexture type error !\n")
				continue;
			}

			glUniform1i(program_info_map[uniform_name], texture_index);
			texture_index++;
		}
	}

}

void GLContext::drawCommand(
	const std::vector<glm::vec3>& vertices,
	const std::vector<glm::vec2>& coords,
	const std::vector<glm::vec3>& normals,
	const std::vector<unsigned short>& indices	
)
{
	assert(vertices.size() > 0);
	assert(indices.size() > 0);

	//顶点posistion数据
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,					// The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	if (coords.size() > 0)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec2), &coords[0], GL_STATIC_DRAW);

		glVertexAttribPointer(
			1,					// The attribute we want to configure
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
	}
	
	if (normals.size() > 0)
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

		glVertexAttribPointer(
			2,					// The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
	}

	//顶点索引数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void GLContext::present() {
	glfwSwapBuffers(s_glWindow);
	glfwPollEvents();
 }

void GLContext::destroy() {
	//清除gpu内存数据
	for (auto& pair : m_programs_info_map) {
		glDeleteProgram(pair.first);
	}
	m_programs_info_map.clear();

	glDeleteTextures(m_textures.size(), &m_textures[0]);
	m_textures.clear();

	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_uvBuffer);
	glDeleteBuffers(1, &m_normalBuffer);
	glDeleteBuffers(1, &m_colorBuffer);
	glDeleteBuffers(1, &m_elementBuffer);
	
	//关闭gl设备, s_glwindow在里面已经释放了
	glfwTerminate();
	delete s_glContext;
	s_glContext = nullptr;
	s_glWindow = nullptr;
}

GLuint GLContext::loadTextureFromDDS(const char* dds_path) {
	unsigned char header[124];

	FILE* fp;

	/* try to open the file */
	fp = fopen(dds_path, "rb");
	if (fp == NULL) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", dds_path); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char* buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}

	free(buffer);

	return textureID;
}

GLuint GLContext::createShaderProgram(const char* vs_path, const char* ps_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vs_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vs_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(ps_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", ps_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", ps_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void GLContext::setInputKeyHandler(GLFWkeyfun func) {
	assert(s_glWindow != nullptr);
	glfwSetKeyCallback(s_glWindow, func);
}

void GLContext::setCursorHandler(GLFWcursorposfun func) {
	assert(s_glWindow != nullptr);
	glfwSetCursorPosCallback(s_glWindow, func);
}

void GLContext::setCursorPos(double xpos, double ypos) {
	assert(s_glWindow != nullptr);
	glfwSetCursorPos(s_glWindow, xpos, ypos);
}

void GLContext::getCursorPos(double& xpos, double& ypos) {
	assert(s_glWindow != nullptr);
	glfwGetCursorPos(s_glWindow, &xpos, &ypos);
}

int GLContext::getKeyState(int key) {
	assert(s_glWindow != nullptr);
	return glfwGetKey(s_glWindow, key);
}

void GLContext::setFaceCulling(bool enabled, bool is_back) {
	if (enabled) {
		glEnable(GL_CULL_FACE);
		glCullFace(is_back ? GL_BACK : GL_FRONT);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
}