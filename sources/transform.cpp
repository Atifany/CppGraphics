#include "transform.h"

Transform::Transform()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->quaternion = Quaternion();
}

Transform::Transform(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->quaternion = Quaternion(other.quaternion);
}

Transform::~Transform() {}

Transform& Transform::operator=(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->quaternion = Quaternion(other.quaternion);;
	return *this;
}
