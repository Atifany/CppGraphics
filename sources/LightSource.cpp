#include "../inc/LightSource.h"

LightSource::LightSource() {}

LightSource::~LightSource() {}

DirectionalLight::DirectionalLight()
{
	this->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	this->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	this->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->direction = glm::vec3(0.0f, 1.0f, 0.0f);

	this->diffuseStrength = 1.0f;
	this->specularStrength = 1.0f;
}

DirectionalLight::~DirectionalLight() {}

DirectionalLight::DirectionalLight(
	glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
	float _diffuseStrength, float _specularStrength, glm::vec3 _direction)
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;

	this->diffuseStrength = _diffuseStrength;
	this->specularStrength = _specularStrength;

	this->direction = _direction;
}

PointLight::PointLight()
{
	this->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	this->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	this->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->spreadConstants = glm::vec3(1.0f, 0.09f, 0.032f);

	this->diffuseStrength = 1.0f;
	this->specularStrength = 1.0f;
}

PointLight::~PointLight() {}

PointLight::PointLight(
	glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
	float _diffuseStrength, float _specularStrength, glm::vec3 _spreadConstants)
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;

	this->diffuseStrength = _diffuseStrength;
	this->specularStrength = _specularStrength;

	this->spreadConstants = _spreadConstants;
}

SpotLight::SpotLight()
{
	this->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	this->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	this->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->spreadConstants = glm::vec3(1.0f, 0.09f, 0.032f);
	this->direction = glm::vec3(1.0f, 0.0f, 0.0f);

	this->cutOff = 0.91f;
	this->outerCutOff = 0.82f;
	this->diffuseStrength = 1.0f;
	this->specularStrength = 1.0f;
}

SpotLight::~SpotLight() {}

SpotLight::SpotLight(
	glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
	float _diffuseStrength, float _specularStrength, glm::vec3 _spreadConstants,
	glm::vec3 _direction, float _cutOff, float _outerCutOff)
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
	this->diffuseStrength = _diffuseStrength;
	this->specularStrength = _specularStrength;
	this->spreadConstants = _spreadConstants;
	this->direction = _direction;
	this->cutOff = _cutOff;
	this->outerCutOff = _outerCutOff;
}
