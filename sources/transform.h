#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "quaternion/quaternion.h"

class Transform
{
	public:
		Transform();
		~Transform();
		Transform(const Transform& other);
		Transform& operator=(const Transform& other);

		glm::vec3	position;
		Quaternion	quaternion;

	private:

};
