#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <iostream>

#include "core_data.h"

extern CoreData cd;

void ESCKeyPressed()
{
	glfwSetWindowShouldClose(cd.window, true);
}

void SpaceKeyPressed()
{
	cd.isWireFrameModeOn = !cd.isWireFrameModeOn;
	if (cd.isWireFrameModeOn == true)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		ESCKeyPressed();
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		SpaceKeyPressed();
}
