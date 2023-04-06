#pragma once

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
		void KeyCallBackProcess();
		int GetKey(int key);
		
	private:

//               key  mode
		std::map<int, int> keysPressed;
};
