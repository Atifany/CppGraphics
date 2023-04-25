#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <iostream>

#include "../inc/CoreData.h"
#include "../inc/Camera.h"
#include "../inc/Input.h"
#include "../inc/GameObject.h"

extern CoreData c_d;
extern Input* input;

void ESCKeyPressed()
{
	// glfwSetWindowShouldClose(cd.window, true);
	static bool isCursorFree = false;
	isCursorFree = !isCursorFree;
	if (isCursorFree == true)
		glfwSetInputMode(c_d.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(c_d.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// Buffer function wich sends all input data from callBack to Input class.
void MouseCallbackSet(GLFWwindow* window, double xpos, double ypos)
{
	input->MouseCallBack(window, xpos, ypos);
}

// Buffer function wich sends all input data from callBack to Input class.
void KeyCallbackSet(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input->KeyCallback(key, action);
}

void KeyReciever()
{
	if (input->GetKey(GLFW_KEY_ESCAPE) == I_KEY_SINGLE_PRESS)
		ESCKeyPressed();
}
