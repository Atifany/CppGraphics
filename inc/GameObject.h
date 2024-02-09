#pragma once

#include <vector>
#include <iostream>
#include <typeinfo>

#include "Component.h"
#include "LightSource.h"
#include "Transform.h"

class GameObject
{
	public:
		GameObject();
		// I dont know how to deallocate components...
		~GameObject();
		

		template <typename T>
		T*		GetComponent();

		template <typename T>
		void	AddComponent(T* component);

		void	CallUpdates(GameObject* camera);
		void	RenderMe(GameObject* camera);

	private:
		std::vector<Component*> components;
};

extern std::vector<GameObject*> lightSources;

template <typename T>
T* GameObject::GetComponent()
{
	for (Component* component : this->components)
	{
		T* c = dynamic_cast<T*>(component);
		if (c != NULL)
			return c;
	}
	return NULL;
}

template <typename T>
void GameObject::AddComponent(T* component)
{
	Component* buf = component;
	buf->gameObject = this;
	this->components.push_back(buf);
	if (dynamic_cast<LightSource*>(component) != NULL)
		lightSources.push_back(this);
}
