#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <iostream>

#include "core_data.h"
#include "camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

extern CoreData cd;

extern float cameraSpeed;
extern Camera camera;

extern float deltaTime;

float cameraSensivity = 0.15f;

void ESCKeyPressed()
{
	// glfwSetWindowShouldClose(cd.window, true);
	static bool isCursorFree = false;
	isCursorFree = !isCursorFree;
	if (isCursorFree == true)
		glfwSetInputMode(cd.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(cd.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WireFrameKeyPressed()
{
	cd.isWireFrameModeOn = !cd.isWireFrameModeOn;
	if (cd.isWireFrameModeOn == true)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MoveCamera(glm::vec3 newPos)
{
	camera.transform.position += newPos;
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	static bool isFirstTime = true;
	static float lastX = 400.0f;
	static float lastY = 300.0f;
	static float cameraYaw = 0.0f;
	static float cameraPitch = 0.0f;
	
	if (isFirstTime == true)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstTime = false;
	}

	float xoffset =   (xpos - lastX) * cameraSensivity;
	float yoffset = - (ypos - lastY) * cameraSensivity;
	lastX = xpos;
	lastY = ypos;

	cameraYaw += xoffset;
	cameraPitch += yoffset;

	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;

	glm::vec3 cameraDirection;
	cameraDirection.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	cameraDirection.y = sin(glm::radians(cameraPitch));
	cameraDirection.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	camera.viewDirection = glm::normalize(cameraDirection);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		ESCKeyPressed();
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		WireFrameKeyPressed();
	if (key == GLFW_KEY_W)
		MoveCamera(camera.viewDirection * cameraSpeed * deltaTime);
	if (key == GLFW_KEY_A)
		MoveCamera(- glm::normalize(glm::cross(camera.viewDirection, camera.upDirection)) * cameraSpeed * deltaTime);
	if (key == GLFW_KEY_S)
		MoveCamera(- camera.viewDirection * cameraSpeed * deltaTime);
	if (key == GLFW_KEY_D)
		MoveCamera(glm::normalize(glm::cross(camera.viewDirection, camera.upDirection)) * cameraSpeed * deltaTime);
	if (key == GLFW_KEY_SPACE)
		MoveCamera(camera.upDirection * cameraSpeed * deltaTime);
	if (key == GLFW_KEY_LEFT_SHIFT)
		MoveCamera(- camera.upDirection * cameraSpeed * deltaTime);
}
