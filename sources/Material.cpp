#include "../inc/Material.h"

Material::Material()
{
	this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	this->specular = glm::vec3(0.0f, 0.0f, 0.0f);
	this->shininess = 0.0f;
}

Material::~Material() {}

Material::Material(const Material& other)
{
	this->ambient = other.ambient;
	this->diffuse = other.diffuse;
	this->specular = other.specular;
	this->shininess = other.shininess;
}

Material Material::operator=(const Material& other)
{
	this->ambient = other.ambient;
	this->diffuse = other.diffuse;
	this->specular = other.specular;
	this->shininess = other.shininess;

	return *this;
}

Material::Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess)
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
	this->shininess = _shininess;
}