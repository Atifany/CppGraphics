#pragma once

#include <GLFW/glfw3.h>

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

class CubeScript : public Component
{
	public:
		void Update() override
		{
			Transform* t = this->gameObject->GetComponent<Transform>();
			t->position.y =
				sin((glfwGetTime() + t->position.x + t->position.z) / 10.0f) * 15.0f;
		}		
};
