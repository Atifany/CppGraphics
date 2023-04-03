#include "transform.h"

Transform::Transform()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

Transform::Transform(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->rotation = glm::vec3(other.rotation);
}

Transform::~Transform() {}

Transform& Transform::operator=(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->rotation = glm::vec3(other.rotation);
	return *this;
}
