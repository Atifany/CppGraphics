#include "../inc/Camera.h"

Camera::Camera()
{
	this->upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	this->sensivity = 0.15f;
	this->fov = 45.0f;
	this->isWireFrameModeOn = false;
	this->input = NULL;
}

Camera::~Camera() {}

Camera::Camera(const Camera& other)
{
	this->upDirection = glm::vec3(other.upDirection);
	this->sensivity = other.sensivity;
	this->fov = other.fov;
	this->isWireFrameModeOn = other.isWireFrameModeOn;
	this->input = other.input;
}

Camera& Camera::operator=(const Camera& other)
{
	this->upDirection = glm::vec3(other.upDirection);
	this->sensivity = other.sensivity;
	this->fov = other.fov;
	this->isWireFrameModeOn = other.isWireFrameModeOn;
	this->input = other.input;

	return *this;
}


static void WireFrameKeyPressed(Camera* me);

void Camera::Update()
{
	if (this->input->GetKey(GLFW_KEY_R) == I_KEY_SINGLE_PRESS)
		WireFrameKeyPressed(this);
}

static void WireFrameKeyPressed(Camera* me)
{
	me->isWireFrameModeOn = !me->isWireFrameModeOn;
	if (me->isWireFrameModeOn == true)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

