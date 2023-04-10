#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

#include "../inc/stb_image/stb_image.h"
#include "../inc/Shader.h"
#include "../inc/Camera.h"
#include "../inc/CoreData.h"
#include "../inc/Input.h"
#include "../inc/process_input.h"
#include "../inc/Cube.h"
#include "../inc/Texture.h"

static const float fov = 90.0f;

static const std::string vertexShaderPath = "../shaders/vertex_shader.shader";
static const std::string fragmentShaderPath = "../shaders/fragment_shader.shader";
static const std::string texturePath = "../textures/GrassBlock.png";

float deltaTime = 0.0f;
static float lastFrame = 0.0f;

// Setup camera
float cameraSpeed = 4.0f; // player movespeed
Camera camera;

CoreData c_d;
Input input;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void CalculateDeltaTime();

static int InitGLFWWindow()
{
	// create context.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window.
	c_d.window = glfwCreateWindow(c_d.windowWidth, c_d.windowHeight, "ft_minecraft", NULL, NULL);
	if (c_d.window == NULL)
	{
		std::cout << "Error: failed to initialize window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(c_d.window);
	// Set Viewport and adjust it with window resize.
	glfwSetFramebufferSizeCallback(c_d.window, framebuffer_size_callback);
	std::cout << "Debug: window object created.\n";
	return 0;
}

static int InitGLAD()
{
	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: failed to initialize GLAD.\n";
		return -1;
	}
	std::cout << "Debug: GLAD initialized.\n";
	return 0;
}

int main()
{
	c_d.windowWidth = 1920;
	c_d.windowHeight = 1080;
	int errorCode = 0;

	errorCode = InitGLFWWindow();
	if (errorCode != 0)
		return errorCode;
	
	errorCode = InitGLAD();
	if (errorCode != 0)
		return errorCode;

	Shader shader(vertexShaderPath, fragmentShaderPath);
	if (shader.program == 0)
		return -1;
	shader.Use();
	shader.UniformSetInt("textureToDraw", 0);
	
	camera.transform.position.x = -2.0f;

	// User input callbacks
	glfwSetKeyCallback(c_d.window, KeyCallbackSet);
	glfwSetInputMode(c_d.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(c_d.window, MouseCallback);

	// Enable transparency component
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable Depth-tetsing
	glEnable(GL_DEPTH_TEST);

	Texture grassBlock = Texture(GL_TEXTURE_2D, texturePath);
	grassBlock.Load();

	std::vector<Cube> cubes;
	for (int x = 0; x < 50 ; x++)
	{
		for (int z = 0; z < 50 ; z++)
		{
			Cube cube(grassBlock);
			cube.transform.position = glm::vec3(x, 0.0f, z);
			cubes.push_back(cube);
		}
	}

	std::cout << "Debug: starting main loop.\n";
	// run the app
	while (!glfwWindowShouldClose(c_d.window))
	{
		CalculateDeltaTime();

		// Clears the window.
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.UpdateViewMatrix(camera);
		shader.UpdateProjectionMatrix(c_d, camera);

		for (Cube& cube : cubes)
		{
			cube.transform.position.y =
				sin((glfwGetTime() + cube.transform.position.x + cube.transform.position.z) / 10.0f) * 1.5f;
			cube.DrawMe(shader);
		}

		// Swaps front and back screen buffers.
		glfwSwapBuffers(c_d.window);
		// Process callbacks and events.
		glfwPollEvents();

		// User input.
		KeyReciever();
		// set values to keys.
		input.KeyCallBackProcess();
	}
	glfwSetInputMode(c_d.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwTerminate();
	std::cout << "Debug: program finished.\n";
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void CalculateDeltaTime()
{
	float curTime = glfwGetTime();
	deltaTime = curTime - lastFrame;
	lastFrame = curTime;
}
