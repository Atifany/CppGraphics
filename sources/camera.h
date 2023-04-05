#pragma once

#include "transform.h"
#include "quaternion/quaternion.h"
#include "glm/glm.hpp"

class Camera
{
	public:
		Camera();
		~Camera();
		Camera(const Camera& other);
		Camera& operator=(const Camera& other);

		Transform	transform;
		Quaternion	quaternion;

		glm::vec3	viewDirection;
		glm::vec3	upDirection;
		float		sensivity;

	private:
};
