#pragma once

#include <vector>
#include <iostream>
#include <typeinfo>

#include "Component.h"
#include "Transform.h"
#include "LightSource.h"

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
		// std::cout << this->components.size() << " " << c << " " << component << "\n";
		if (c != NULL)
			return c;
	}
	return NULL;
}

template <typename T>
void GameObject::AddComponent(T* component)
{
	// std::cout << "Add called\n";
	Component* buf = component;
	this->components.push_back(buf);
	if (dynamic_cast<LightSource*>(component) != NULL)
		lightSources.push_back(this);
}
