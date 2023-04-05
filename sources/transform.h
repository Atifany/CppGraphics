#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class Transform
{
	public:
		Transform();
		~Transform();
		Transform(const Transform& other);
		Transform& operator=(const Transform& other);

		glm::vec3 position;
		glm::vec3 rotation;

	private:

};
