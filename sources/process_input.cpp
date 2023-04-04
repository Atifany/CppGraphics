#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <iostream>

#include "core_data.h"
#include "camera.h"
#include "input.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

extern CoreData cd;
extern Input input;

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

// Buffer function wich sends all input data from callBack to Input class.
void KeyCallbackSet(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input.KeyCallback(key, action);
}

/* TODO:
Think of where to store direction vector: in transform or camera class?
^^ 
It would be stored in transform.

After that add .Forward() .Left() .Right() and .Backwards() function to return
a corresponding vector calculated from direction vector define before.
*/

void KeyReciever()
{
	if (input.GetKey(GLFW_KEY_ESCAPE) == I_KEY_SINGLE_PRESS)
		ESCKeyPressed();
	if (input.GetKey(GLFW_KEY_R) == I_KEY_SINGLE_PRESS)
		WireFrameKeyPressed();

	if (input.GetKey(GLFW_KEY_W) == I_KEY_CONT_PRESS ||
		input.GetKey(GLFW_KEY_W) == I_KEY_SINGLE_PRESS) // not even noticeble
		MoveCamera(camera.viewDirection * cameraSpeed * deltaTime);
	if (input.GetKey(GLFW_KEY_S) == I_KEY_CONT_PRESS ||
		input.GetKey(GLFW_KEY_S) == I_KEY_SINGLE_PRESS)
		MoveCamera(- camera.viewDirection * cameraSpeed * deltaTime);
	if (input.GetKey(GLFW_KEY_A) == I_KEY_CONT_PRESS ||
		input.GetKey(GLFW_KEY_A) == I_KEY_SINGLE_PRESS)
		MoveCamera(- glm::normalize(glm::cross(camera.viewDirection, camera.upDirection)) * cameraSpeed * deltaTime);
	if (input.GetKey(GLFW_KEY_D) == I_KEY_CONT_PRESS ||
		input.GetKey(GLFW_KEY_D) == I_KEY_SINGLE_PRESS)
		MoveCamera(glm::normalize(glm::cross(camera.viewDirection, camera.upDirection)) * cameraSpeed * deltaTime);

	if (input.GetKey(GLFW_KEY_SPACE) == I_KEY_CONT_PRESS ||
		input.GetKey(GLFW_KEY_SPACE) == I_KEY_SINGLE_PRESS)
		MoveCamera(camera.upDirection * cameraSpeed * deltaTime);
	if (input.GetKey(GLFW_KEY_LEFT_SHIFT) == I_KEY_CONT_PRESS ||
		input.GetKey(GLFW_KEY_LEFT_SHIFT) == I_KEY_SINGLE_PRESS)
		MoveCamera(- camera.upDirection * cameraSpeed * deltaTime);
}
