#pragma once

#include "glm/glm.hpp"
#include "Transform.h"

class Camera : public Component
{
	public:
		Camera();
		~Camera();
		Camera(const Camera& other);
		Camera& operator=(const Camera& other);

		glm::vec3	upDirection;
		float		sensivity;
		float		fov;

	private:
};
