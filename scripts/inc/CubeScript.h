#pragma once

#include <GLFW/glfw3.h>

#include "../../inc/Component.h"
#include "../../inc/GameObject.h"
#include "../../inc/Transform.h"

class CubeScript : public Component
{
	public:
		void Update() override;		
};
