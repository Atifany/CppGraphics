#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../inc/Component.h"
#include "../../inc/Transform.h"
#include "../../inc/Camera.h"
#include "../../inc/GameObject.h"
#include "../../inc/Input.h"

class PlayerMovement : public Component
{
	public:
		PlayerMovement() { input = NULL; }

		void Update() override;

		Input*	input;
		float	speed;
};
