#pragma once

#include "glm/glm.hpp"
#include "Transform.h"

class Camera
{
	public:
		Camera();
		~Camera();
		Camera(const Camera& other);
		Camera& operator=(const Camera& other);

		Transform	transform;

		glm::vec3	viewDirection;
		glm::vec3	upDirection;
		float		sensivity;

	private:
};
