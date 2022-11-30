#include <stdio.h>
#include "glContext.h"
#include "glDevice.h"

using namespace simple_engine;

GLContext* GLContext::s_glContext = nullptr;

GLContext::GLContext():
	m_vertexArray(0),
	m_vertexBuffer(0),
	m_uvBuffer(0),
	m_normalBuffer(0),
	m_normalBuffer2(0),
	m_colorBuffer(0),
	m_elementBuffer(0)
{	
	is_initialized = false;
}

GLContext* GLContext::Instance() {
	if (s_glContext == nullptr) {
		s_glContext = new GLContext();
	}
	return s_glContext;
}

bool GLContext::Initialize() {
	IRenderContext::Initialize();
	if (!GLDevice::Instance()->Initialized() || is_initialized)
	{
		return false;
	}

	//顶点layout array 
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);


	//顶点layout缓存
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_uvBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_normalBuffer2);
	glGenBuffers(1, &m_elementBuffer);

	is_initialized = true;
	return true;
}

void GLContext::ResetPipelineState() {
	IRenderContext::ResetPipelineState();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SE_WINDOW_WIDTH, SE_WINDOW_HEIGHT);
	glClearColor(0.0, 0.0, 0.3, 0.0);
	glEnable(GL_CULL_FACE);
	glDepthMask(true);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDisable(GL_BLEND);
	glCullFace(GL_BACK); 
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDepthFunc(GL_LESS);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLContext::SetPipelineState(const PipelineStateObject& state)
{
	IRenderContext::SetPipelineState(state);
	if (state.depth_test_enable)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(DepthStencilMap[state.depth_func]);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	glDepthMask(state.depth_write_enable);
	
	if (state.stencil_test_enable)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilMask(state.stencil_mask);
		glStencilFunc(DepthStencilMap[state.stencil_func], state.stencil_ref, state.stencil_mask);
		glStencilOp(DepthStencilMap[state.stencil_op_failed], DepthStencilMap[state.stencil_op_only_depth_failed], DepthStencilMap[state.stencil_op_passed]);
	}
	else
	{
		glDisable(GL_STENCIL_TEST);
	}

	if (state.culling_enable) {
		glEnable(GL_CULL_FACE);
		glCullFace(CullMap[state.culling_mode]);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (state.blend_enable)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}
	glColorMask(state.color_mask_r, state.color_mask_g, state.color_mask_b, state.color_mask_a);
}


void GLContext::SetMaterial(Material& mat)
{	
	IRenderContext::SetMaterial(mat);

	SetPipelineState(mat.getPipelineState());

	//创建并绑定shader program
	GLuint program_id = mat.getShaderProgram();
	if (!m_programs_info_map.count(program_id)) {
		DEBUG_PRINTF("Create Shader Program\n")
		program_id = createShaderProgram(mat.getVSFile().c_str(), mat.getPSFile().c_str());
		assert(program_id != 0);
		m_programs_info_map[program_id] = std::unordered_map<std::string, GLuint>();
		mat.setShaderProgram(program_id);
	}

	//DEBUG_PRINTF("Set Shader Program\n")
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

	for (auto& pair : mat.getUniforms4fv())
	{
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform4fv(program_info_map[name], pair.second.size(), &pair.second[0][0]);
	}

	for (auto& pair : mat.getUniforms3f()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform3f(program_info_map[name], pair.second.x, pair.second.y, pair.second.z);
	}

	for (auto& pair : mat.getUniforms3fv()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform3fv(program_info_map[name], pair.second.size(), &pair.second[0][0]);
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

	for (auto& pair : mat.getUniforms1fv()) {
		std::string name = pair.first;
		if (!program_info_map.count(name)) {
			program_info_map[name] = glGetUniformLocation(program_id, pair.first.c_str());
		}
		glUniform1fv(program_info_map[name], pair.second.size(), &pair.second[0]);
	}

	// 绑定gl纹理和采样器到管线
	unsigned short texture_index = 0;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	for (auto& pair : mat.getTextures()) {
		auto uniform_name = pair.first;
		glActiveTexture(GL_TEXTURE0 + texture_index);
		glBindTexture(GL_TEXTURE_2D, pair.second->GetResourceId());
		if (!program_info_map.count(uniform_name))
		{
			program_info_map[uniform_name] = glGetUniformLocation(program_id, uniform_name.c_str());
		}
		glUniform1i(program_info_map[uniform_name], texture_index);
		texture_index++;
	}
	for (auto& pair : mat.getCubemapTextures()) {
		auto uniform_name = pair.first;
		glActiveTexture(GL_TEXTURE0 + texture_index);
		glBindTexture(GL_TEXTURE_CUBE_MAP, pair.second->GetResourceId());
		if (!program_info_map.count(uniform_name))
		{
			program_info_map[uniform_name] = glGetUniformLocation(program_id, uniform_name.c_str());
		}
		glUniform1i(program_info_map[uniform_name], texture_index);
		texture_index++;
	}
	for (auto& pair : mat.getOtherTextures())
	{
		auto uniform_name = pair.first;
		glActiveTexture(GL_TEXTURE0 + texture_index);
		glBindTexture(GL_TEXTURE_2D, pair.second);
		if (!program_info_map.count(uniform_name))
		{
			program_info_map[uniform_name] = glGetUniformLocation(program_id, uniform_name.c_str());
		}
		glUniform1i(program_info_map[uniform_name], texture_index);
		texture_index++;
	}
}

void GLContext::DrawCommand(Mesh& mesh)
{	
	auto vertices = mesh.getVertices();
	auto coords = mesh.getCoords();
	auto normals = mesh.getNormals();
	auto normals_2 = mesh.getVertexColor();
	auto indices = mesh.getIndices();
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

	if (normals_2.size() > 0)
	{
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer2);
		glBufferData(GL_ARRAY_BUFFER, normals_2.size() * sizeof(glm::vec3), &normals_2[0], GL_STATIC_DRAW);

		glVertexAttribPointer(
			3,					// The attribute we want to configure
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

}

void GLContext::DrawIndexed(unsigned int ElementCount, unsigned int StartVertexOffset)
{
	IRenderContext::DrawIndexed(ElementCount, StartVertexOffset);
	glDrawElements(
		GL_TRIANGLES,		// mode
		ElementCount,		// count
		GL_UNSIGNED_SHORT,	// type
		(void*)StartVertexOffset          // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void GLContext::Present() {
	glfwSwapBuffers(GLDevice::GetGLWindow());
	glfwPollEvents();
 }

void GLContext::Destroy() {
	//清除gpu内存数据
	for (auto& pair : m_programs_info_map) {
		glDeleteProgram(pair.first);
	}
	m_programs_info_map.clear();

	if (m_textures.size() > 0)
	{
		glDeleteTextures(m_textures.size(), &m_textures[0]);
		m_textures.clear();
	}

	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_uvBuffer);
	glDeleteBuffers(1, &m_normalBuffer);
	glDeleteBuffers(1, &m_normalBuffer2);
	glDeleteBuffers(1, &m_colorBuffer);
	glDeleteBuffers(1, &m_elementBuffer);
	
	delete s_glContext;
	s_glContext = nullptr;
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
		DEBUG_PRINTF("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vs_path);
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
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		DEBUG_PRINTF("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		DEBUG_PRINTF("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
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
		DEBUG_PRINTF("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void GLContext::SetVertexBuffer(const VertexBuffer& buf)
{
	IRenderContext::SetVertexBuffer(buf);
}

void GLContext::SetElementBuffer(const ElementBuffer& buf)
{
	IRenderContext::SetElementBuffer(buf);
}


void GLContext::setInputKeyHandler(GLFWkeyfun func) {
	glfwSetKeyCallback(GLDevice::GetGLWindow(), func);
}

void GLContext::setCursorHandler(GLFWcursorposfun func) {
	glfwSetCursorPosCallback(GLDevice::GetGLWindow(), func);
}

void GLContext::setCursorPos(double xpos, double ypos) {
	glfwSetCursorPos(GLDevice::GetGLWindow(), xpos, ypos);
}

void GLContext::getCursorPos(double& xpos, double& ypos) {
	glfwGetCursorPos(GLDevice::GetGLWindow(), &xpos, &ypos);
}

CommonKeyState GLContext::getKeyState(CommonKeyCode key) {
	uint gl_key_code = glKeyCodeMap[key];
	uint gl_key_state = glfwGetKey(GLDevice::GetGLWindow(), gl_key_code);
	return glKeyStateMap[gl_key_state];
}

void GLContext::SetFrameBufferObject(GLFrameBufferObject& fbo)
{
	glViewport(0, 0, fbo.GetWidth(), fbo.GetHeight());
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.GetFrameBufferObject());
}

void GLContext::ResetFrameBufferObject()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLContext::ClearFrameBufferObject(GLFrameBufferObject& fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.GetFrameBufferObject());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLContext::BlitFrameBuffer(GLFrameBufferObject* fbo1, GLFrameBufferObject* fbo2)
{
	assert(fbo1 != nullptr);
	UINT width = SE_WINDOW_WIDTH;
	UINT height = SE_WINDOW_HEIGHT;

	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo1->GetFrameBufferObject());
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	if (fbo2 != nullptr)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo2->GetFrameBufferObject());
		glDrawBuffer(GL_BACK);
		width = fbo2->GetWidth();
		height = fbo2->GetHeight();
	}
	else {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glDrawBuffer(GL_BACK);
	}
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
		GL_NEAREST);
		
	//不清楚为什么这里显示正确还有error 可能是之前的command的？
	//DEBUG_PRINTF("GL error after blit frame: %d\n", glGetError());

}

