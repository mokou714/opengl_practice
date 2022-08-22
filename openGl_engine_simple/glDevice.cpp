#include "glDevice.h"

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
