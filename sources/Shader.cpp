#include "../inc/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

extern std::vector<GameObject*> lightSources;

static unsigned int CompileShader(unsigned int type, const std::string& src);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
static void SetDirLightUniform(Shader& shader, DirectionalLight* dirLight, int nbrOfDirLights);
static void SetPointLightUniform(Shader& shader, GameObject* gm, PointLight* pointLight, int nbrOfPointLights);
static void SetSpotLightUniform(Shader& shader, GameObject* gm, SpotLight* spotLight, int nbrOfSpotLights);
static void SetEndLightUniform(Shader& shader, int nbrOfDirLights, int nbrOfPointLights, int nbrOfSpotLights);

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

void Shader::UpdateViewMatrix(GameObject* camera)
{
	Camera* cameraComp = camera->GetComponent<Camera>();
	Transform* transform = camera->GetComponent<Transform>();
	this->viewMatrix = glm::lookAt(
		transform->position,
		transform->position + transform->quaternion.Forward(),
		cameraComp->upDirection);
}

void Shader::UpdateProjectionMatrix(CoreData& c_d, GameObject* camera)
{
	if (camera != NULL)
	{
		Camera* cameraComp = camera->GetComponent<Camera>();
		this->projectionMatrix = glm::perspective(glm::radians(cameraComp->fov),
			(float)c_d.windowWidth / (float)c_d.windowHeight, 0.1f, 100.0f);
		return;
	}
	this->projectionMatrix = glm::ortho(0.0f, (float)(c_d.windowWidth), 0.0f, (float)(c_d.windowHeight), 0.1f, 100.0f);
}

void Shader::UpdateLightUniforms()
{
	LightSource*		lightSource;
	DirectionalLight*	dirLight;
	PointLight*			pointLight;
	SpotLight*			spotLight;
	int nbrOfDirLights = 0;
	int nbrOfPointLights = 0;
	int nbrOfSpotLights = 0;
	for (GameObject* gm : lightSources)
	{
		lightSource = gm->GetComponent<LightSource>();
		
		dirLight = dynamic_cast<DirectionalLight*>(lightSource);
		if (dirLight != NULL)
		{
			SetDirLightUniform(*this, dirLight, nbrOfDirLights);
			nbrOfDirLights++;
		}
		pointLight = dynamic_cast<PointLight*>(lightSource);
		if (pointLight != NULL)
		{
			SetPointLightUniform(*this, gm, pointLight, nbrOfPointLights);
			nbrOfPointLights++;
		}
		spotLight = dynamic_cast<SpotLight*>(lightSource);
		if (spotLight != NULL)
		{
			SetSpotLightUniform(*this, gm, spotLight, nbrOfSpotLights);
			nbrOfSpotLights++;
		}
	}
	SetEndLightUniform(*this, nbrOfDirLights, nbrOfPointLights, nbrOfSpotLights);
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

static void SetDirLightUniform(Shader& shader, DirectionalLight* dirLight, int nbrOfDirLights)
{
	char buf[64];
	sprintf(buf, "dirLights[%i].direction", nbrOfDirLights);
	shader.UniformSetVec3(buf, dirLight->direction);
	sprintf(buf, "dirLights[%i].ambient", nbrOfDirLights);
	shader.UniformSetVec3(buf, dirLight->ambient * dirLight->diffuseStrength);
	sprintf(buf, "dirLights[%i].diffuse", nbrOfDirLights);
	shader.UniformSetVec3(buf, dirLight->diffuse * dirLight->diffuseStrength);
	sprintf(buf, "dirLights[%i].specular", nbrOfDirLights);
	shader.UniformSetVec3(buf, dirLight->specular * dirLight->specularStrength);
}

static void SetPointLightUniform(Shader& shader, GameObject* gm, PointLight* pointLight, int nbrOfPointLights)
{
	char buf[64];
	sprintf(buf, "pointLights[%i].position", nbrOfPointLights);
	shader.UniformSetVec3(buf, gm->GetComponent<Transform>()->position);
	sprintf(buf, "pointLights[%i].spreadConstants", nbrOfPointLights);
	shader.UniformSetVec3(buf, pointLight->spreadConstants);
	sprintf(buf, "pointLights[%i].ambient", nbrOfPointLights);
	shader.UniformSetVec3(buf, pointLight->ambient * pointLight->diffuseStrength);
	sprintf(buf, "pointLights[%i].diffuse", nbrOfPointLights);
	shader.UniformSetVec3(buf, pointLight->diffuse * pointLight->diffuseStrength);
	sprintf(buf, "pointLights[%i].specular", nbrOfPointLights);
	shader.UniformSetVec3(buf, pointLight->specular * pointLight->specularStrength);
}

static void SetSpotLightUniform(Shader& shader, GameObject* gm, SpotLight* spotLight, int nbrOfSpotLights)
{
	char buf[64];
	sprintf(buf, "spotLights[%i].position", nbrOfSpotLights);
	shader.UniformSetVec3(buf, gm->GetComponent<Transform>()->position);
	sprintf(buf, "spotLights[%i].direction", nbrOfSpotLights);
	shader.UniformSetVec3(buf, spotLight->direction);
	sprintf(buf, "spotLights[%i].cutOff", nbrOfSpotLights);
	shader.UniformSetFloat(buf, spotLight->cutOff);
	sprintf(buf, "spotLights[%i].outerCutOff", nbrOfSpotLights);
	shader.UniformSetFloat(buf, spotLight->outerCutOff);
	sprintf(buf, "spotLights[%i].spreadConstants", nbrOfSpotLights);
	shader.UniformSetVec3(buf, spotLight->spreadConstants);
	sprintf(buf, "spotLights[%i].ambient", nbrOfSpotLights);
	shader.UniformSetVec3(buf, spotLight->ambient * spotLight->diffuseStrength);
	sprintf(buf, "spotLights[%i].diffuse", nbrOfSpotLights);
	shader.UniformSetVec3(buf, spotLight->diffuse * spotLight->diffuseStrength);
	sprintf(buf, "spotLights[%i].specular", nbrOfSpotLights);
	shader.UniformSetVec3(buf, spotLight->specular * spotLight->specularStrength);
}

// set last light in array to indicate array end.
static void SetEndLightUniform(Shader& shader, int nbrOfDirLights, int nbrOfPointLights, int nbrOfSpotLights)
{
	char buf[64];
	sprintf(buf, "dirLights[%i].ambient", nbrOfDirLights);
	shader.UniformSetVec3(buf, glm::vec3(-1.0f, -1.0f, -1.0f));
	sprintf(buf, "pointLights[%i].ambient", nbrOfPointLights);
	shader.UniformSetVec3(buf, glm::vec3(-1.0f, -1.0f, -1.0f));
	sprintf(buf, "spotLights[%i].ambient", nbrOfSpotLights);
	shader.UniformSetVec3(buf, glm::vec3(-1.0f, -1.0f, -1.0f));
}
