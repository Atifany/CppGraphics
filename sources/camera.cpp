#include "camera.h"

Camera::Camera()
{
	this->transform = Transform();
	this->quaternion = Quaternion(glm::vec3(0.0f, 0.0f, 0.0f));
	// look forward
	this->viewDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	this->upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	this->sensivity = 0.15f;
}

Camera::~Camera() {}

Camera::Camera(const Camera& other)
{
	this->transform = Transform(other.transform);
	this->viewDirection = glm::vec3(other.viewDirection);
	this->upDirection = glm::vec3(other.upDirection);
	this->sensivity = other.sensivity;
}

Camera& Camera::operator=(const Camera& other)
{
	this->transform = Transform(other.transform);
	this->viewDirection = glm::vec3(other.viewDirection);
	this->upDirection = glm::vec3(other.upDirection);
	this->sensivity = other.sensivity;

	return *this;
}

