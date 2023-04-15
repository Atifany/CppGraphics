#include "../inc/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& src);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	this->viewMatrix = glm::mat4(1.0f);
	this->projectionMatrix = glm::mat4(1.0f);

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertexFile.open(vertexShaderPath);
		std::stringstream vertexShaderStream;
		vertexShaderStream << vertexFile.rdbuf();
		vertexCode = vertexShaderStream.str();
		vertexFile.close();

		fragmentFile.open(fragmentShaderPath);
		std::stringstream fragmentShaderStream;
		fragmentShaderStream << fragmentFile.rdbuf();
		fragmentCode = fragmentShaderStream.str();
		fragmentFile.close();
	}
	catch(std::ifstream::failure& e)
	{
		std::cout << "Error: failed to read shader files: " << e.what() << "\n";
		this->program = 0;
		return ;
	}
	
	this->program = CreateShader(vertexCode, fragmentCode);
	if (this->program != 0)
		std::cout << "Debug: shader program created.\n";
}

Shader::~Shader() {}

void Shader::Use()
{
	glUseProgram(this->program);
}

void Shader::UniformSetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->program, name.c_str()), (int)value);
}

void Shader::UniformSetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->program, name.c_str()), value);
}

void Shader::UniformSetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->program, name.c_str()), value);
}

void Shader::UniformSetFloatV(const std::string& name, std::vector<float> value) const
{
	switch (value.size())
	{
		case 0:
			std::cout << "Warning: insering empty vector into uniform!\n";
		case 1:
			glUniform1f(glGetUniformLocation(this->program, name.c_str()), value[0]);
		case 2:
			glUniform2f(glGetUniformLocation(this->program, name.c_str()), value[0],
			value[1]);
		case 3:
			glUniform3f(glGetUniformLocation(this->program, name.c_str()), value[0],
			value[1], value[2]);
		case 4:
			glUniform4f(glGetUniformLocation(this->program, name.c_str()), value[0],
			value[1], value[2], value[3]);
	}
}

void Shader::UniformSetVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(this->program, name.c_str()), value[0],
		value[1]);
}

void Shader::UniformSetVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(this->program, name.c_str()), value[0],
		value[1], value[2]);
}

void Shader::UniformSetVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(this->program, name.c_str()), value[0],
		value[1], value[2], value[3]);
}

void Shader::UniformSetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()),
		1, GL_FALSE, glm::value_ptr(value));
}

void Shader::UpdateViewMatrix(Camera& camera)
{
	this->viewMatrix = glm::lookAt(
		camera.transform.position,
		camera.transform.position + camera.transform.quaternion.Forward(),
		camera.upDirection);
}

void Shader::UpdateProjectionMatrix(CoreData& c_d, Camera& camera)
{
	this->projectionMatrix = glm::perspective(glm::radians(camera.fov),
		(float)c_d.windowWidth / (float)c_d.windowHeight, 0.1f, 100.0f);
}


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