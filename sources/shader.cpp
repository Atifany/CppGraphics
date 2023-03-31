#include "shader.h"

#include "glad.h"

#include <fstream>
#include <sstream>
#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& src);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
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
	std::cout << "Debug: shader program created.\n";
}

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
