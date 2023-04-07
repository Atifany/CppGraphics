#include "../inc/Camera.h"

Camera::Camera()
{
	this->transform = Transform();
	this->upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	this->sensivity = 0.15f;
	this->fov = 45.0f;
}

Camera::~Camera() {}

Camera::Camera(const Camera& other)
{
	this->transform = Transform(other.transform);
	this->upDirection = glm::vec3(other.upDirection);
	this->sensivity = other.sensivity;
	this->fov = other.fov;
}

Camera& Camera::operator=(const Camera& other)
{
	this->transform = Transform(other.transform);
	this->upDirection = glm::vec3(other.upDirection);
	this->sensivity = other.sensivity;
	this->fov = other.fov;

	return *this;
}

