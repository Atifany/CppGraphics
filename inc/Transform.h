#pragma once

#include "Quaternion.h"
#include "Component.h"

class Transform : public Component
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
