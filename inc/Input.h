#pragma once

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#define I_KEY_NOT_PRESSED	0
#define I_KEY_SINGLE_PRESS	1
#define I_KEY_CONT_PRESS	2
#define I_KEY_HOLD			3
#define I_KEY_RELEASE		4

// This class contains a list of all keys currently pressed.
// To retrieve key's state use function GetKey().
class Input
{
	public:
		Input();
		~Input();

		void KeyCallback(int key, int action);
		void MouseCallBack(GLFWwindow* window, double xpos, double ypos);
		void KeyCallBackProcess();
		int GetKey(int key);
		glm::vec2 GetMousePos();
		
	private:
		glm::vec2 mousePos;
//               key  mode
		std::map<int, int> keysPressed;
};
