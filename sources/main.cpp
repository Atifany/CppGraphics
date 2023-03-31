#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexShader.h"
#include "fragmentShader.h"

#include "core_data.h"
#include "process_input.h"

CoreData cd = CoreData();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(CoreData& cd);

static unsigned int CompileShader(unsigned int type, const std::string& src)
{
	unsigned int id = glCreateShader(type);
	const char* c_src = src.c_str();
	glShaderSource(id, 1, &c_src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Error compiling ";
		switch (type)
		{
			case GL_VERTEX_SHADER:
				std::cout << "vertex shader: ";
				break;
			case GL_FRAGMENT_SHADER:
				std::cout << "fragment shader: ";
				break;
		}
		std::cout << message << "\n";
		return 0;
	}
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	if (vs == 0 || fs == 0)
	{
		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteProgram(program);
		return 0;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
	int link_result;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Error linking shader program " << message << "\n";

		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteProgram(program);
		return 0;
	}
	
	glValidateProgram(program);
	int validate_result;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_result);
	if (validate_result == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Error compiling shader program " << message << "\n";

		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

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

	unsigned int shaderProgram = CreateShader(vertexShader, fragmentShader);
	if (shaderProgram == 0)
	{
		glDeleteProgram(shaderProgram);
		glfwTerminate();
		return -1;
	}
	std::cout << "Debug: shader program created.\n";

	// User input callbacks
	glfwSetKeyCallback(cd.window, KeyCallback);

	// Sample verticies
	float verticies[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		// Clears the window.
		glClearColor(redColor, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		redColor += speed;
		if (redColor > 0.5f)
			speed = -0.01f;
		if (redColor < 0.0f)
			speed = 0.01f;

		glUseProgram(shaderProgram);
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
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

