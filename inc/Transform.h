#pragma once

#include "Quaternion.h"

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
