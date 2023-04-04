#include "input.h"

#include <iostream>

Input::Input() {}
Input::~Input() {}

void Input::KeyCallback(int key,int action)
{
	//std::cout << "Debug: Caution warning START!\n";


	//this->ClearSinglePresses();


	//std::cout << "Debug: Caution warning MIDDLE!\n";


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



	//std::cout << "Debug: Caution warning END!\n";
}

int Input::GetKey(int key)
{
	for (auto& x : this->keysPressed)
	{
		if (x.first == key)
			return x.second;
	}
	return I_KEY_NOT_PRESSED;
}

void Input::KeyCallBackProcess()
{
	for (auto& x : this->keysPressed)
	{
		if (x.second == I_KEY_SINGLE_PRESS)
			x.second = I_KEY_CONT_PRESS;
	}

	std::map<int, int>::iterator it = this->keysPressed.begin();
	while (it != this->keysPressed.end())
	{
		if ((*it).second == I_KEY_RELEASE)
			it = this->keysPressed.erase(it);
		else
			it++;
	}
}
