#include "glDevice.h"
#include "utils.h"
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace simple_engine;

GLDevice* GLDevice::s_glDevice = nullptr;
GLFWwindow* GLDevice::s_glWindow = nullptr;

GLDevice::GLDevice()
{
	is_initialized = false;
}

GLDevice* GLDevice::Instance()
{
	if (GLDevice::s_glDevice == nullptr)
	{
		GLDevice::s_glDevice = new GLDevice();
	}
	return GLDevice::s_glDevice;
}

bool GLDevice::Initialize()
{	
	IRenderDevice::Initialize();
	if (is_initialized)
		return false;

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

	is_initialized = true;
	return true;
}

void GLDevice::Destroy()
{
	//关闭gl设备, s_glwindow在里面已经释放了
	glfwTerminate();
	s_glWindow = nullptr;
	delete s_glDevice;
	s_glDevice = nullptr;
}

void GLDevice::CreateTexture(TextureDesc desc, TextureData data, ITexture& tex_out)
{

}

unsigned int GLDevice::CreateBuffer()
{
	IRenderDevice::CreateBuffer();
	GLuint result;
	glGenBuffers(1, &result);
	return result;
}
void GLDevice::DeleteBuffer(unsigned int buffer_id)
{
	IRenderDevice::DeleteBuffer(buffer_id);
	glDeleteBuffers(1, &buffer_id);
}

RUID GLDevice::CreateTexture(const char* file_path)
{
	std::string file_str{ file_path };
	//stbi加载不了dds glfw加载不了tga 分开处理
	if (file_str.substr(file_str.find_last_of(".") + 1) == "dds")
	{
		return Utils::loadDDS(file_path);
	}
	else {
		GLuint texture;
		int width, height, comp;
		unsigned char* image_data = stbi_load(file_path, &width, &height, &comp, STBI_rgb_alpha);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image_data);
		return texture;
	}
}

RUID GLDevice::CreateCubemapTexture(std::vector<const char*> files)
{
	GLuint tex_id;
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);

	int width, height, nrChannels;
	unsigned char* data;
	for (unsigned int i = 0; i < files.size(); i++)
	{
		GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		if (target == GL_TEXTURE_CUBE_MAP_POSITIVE_Y || target == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y) {
			stbi_set_flip_vertically_on_load(0);
		}
		else {
			stbi_set_flip_vertically_on_load(0);
		}
		data = stbi_load(files[i], &width, &height, &nrChannels, 0);
		glTexImage2D(
			target,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return tex_id;
}

void GLDevice::DeleteTexture(RUID resource_id)
{
	glDeleteTextures(1, &resource_id);
}

void GLDevice::OutputTextureToFile(RUID texture, int width, int height)
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	int data_size = width * height * 4;
	GLubyte* pixels = new GLubyte[width * height * 4];
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);

	//stbi_write_bmp("myfile.bmp", width, height, 4, pixels);
	stbi_write_tga("outputs/myfile.tga", width, height, 4, pixels);

	delete pixels;
}