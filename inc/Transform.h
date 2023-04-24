#pragma once

#include <vector>

#include "Quaternion.h"
#include "Component.h"

class GameObject;

class Transform : public Component
{
	public:
		Transform();
		Transform(GameObject* gm);
		~Transform();
		Transform(const Transform& other);
		Transform& operator=(const Transform& other);

		glm::vec3					position;
		Quaternion					quaternion;
		std::vector<Transform*>		children;

		glm::vec3 GetWorldCoords();
		void SetParent(Transform* _parent);

	private:
		Transform*					parent;

};
