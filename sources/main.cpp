#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

#include "core_data.h"
#include "process_input.h"
#include "shader.h"

static const std::string vertexShaderPath = "sources/shaders/vertex_shader.shader";
static const std::string fragmentShaderPath = "sources/shaders/fragment_shader.shader";

CoreData cd = CoreData();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(CoreData& cd);

static int InitGLFWWindow()
{
	// create context.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window.
	cd.window = glfwCreateWindow(800, 600, "CppGraphics", NULL, NULL);
	if (cd.window == NULL)
	{
		std::cout << "Error: failed to initialize window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(cd.window);
	// Set Viewport and adjust it with window resize.
	glfwSetFramebufferSizeCallback(cd.window, framebuffer_size_callback);
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

	// User input callbacks
	glfwSetKeyCallback(cd.window, KeyCallback);

	// Sample verticies
	float verticies[] = {
		0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Generate objects
	unsigned int VBO, VAO, EBO;
	// Defines vertex attributes only once in here and not every frame.
	glGenVertexArrays(1, &VAO);
	// Stores vertecies in GPU.
	glGenBuffers(1, &VBO);
	// Stores indices in GPU.
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// defines what a vertex is. In here it is just vec3 of type float.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Not allowed to unbind EBO before VAO.
	// While VAO is bound it stores all EBO bounds and unbounds.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// Not nessecary unbinding.
	// glBindVertexArray(0);

	std::cout << "Debug: starting main loop.\n";
	// keep the screen changing costantly
	float redColor = 0.0f;
	float speed = 0.01f;
	// run the app
	while (!glfwWindowShouldClose(cd.window))
	{
		// Activating shaders.
		glUseProgram(shader.program);

		float curTime = glfwGetTime();
		float blueColorValue = (sin(curTime) / 2.0f + 0.5f);
		std::vector<float> vertexColor{0.0f, 0.0f, blueColorValue, 1.0f};
		shader.UniformSetFloatV("vertexColor", vertexColor);

		// Clears the window.
		glClearColor(redColor, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		redColor += speed;
		if (redColor > 0.5f)
			speed = -0.01f;
		if (redColor < 0.0f)
			speed = 0.01f;

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(verticies)/sizeof(*verticies), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Process callbacks and events.
		glfwPollEvents();
		// Swaps front and back screen buffers.
		glfwSwapBuffers(cd.window);
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader.program);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

