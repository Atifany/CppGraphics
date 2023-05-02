#include <iostream>

#include "../inc/Input.h"

Input::Input()
{
	this->mousePos = glm::vec2(400.0f, 300.0f);
	this->keysPressed.insert(std::pair<int, int>(-1, 0));
}

Input::~Input() {}

// Detects keys being pressed and released and sets an appropriate state to each key.
void Input::KeyCallback(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		if (this->keysPressed.count(key) == 0)
			this->keysPressed.insert(std::pair<int, int>(key, I_KEY_SINGLE_PRESS));
	}
	if (action == GLFW_RELEASE)
	{
		if (this->keysPressed.count(key) != 0)
			this->keysPressed[key] = I_KEY_RELEASE;
	}
}

// Return the current state of a given key.
int Input::GetKey(int key)
{
	for (auto& x : this->keysPressed)
	{
		if (x.first == key)
			return x.second;
	}
	return I_KEY_NOT_PRESSED;
}

// Automatically decides the state of keys and removes those,
// which are no longer pressed.
void Input::KeyCallBackProcess()
{
	// Change single_press state to cont_press
	for (auto& x : this->keysPressed)
	{
		if (x.second == I_KEY_SINGLE_PRESS)
			x.second = I_KEY_CONT_PRESS;
	}

	// remove all keys marked with release state
	std::map<int, int>::iterator it = this->keysPressed.begin();
	while (it != this->keysPressed.end())
	{
		if ((*it).second == I_KEY_RELEASE)
			it = this->keysPressed.erase(it);
		else
			it++;
	}
}

// Stores latest mouse position
void Input::MouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	this->mousePos.x = xpos;
	this->mousePos.y = ypos;
}

glm::vec2 Input::GetMousePos()
{
	return this->mousePos;
}
