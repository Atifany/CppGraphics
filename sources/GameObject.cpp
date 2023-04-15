#include "../inc/GameObject.h"

std::vector<GameObject*> lightSources;

GameObject::GameObject()
{
	this->components = std::vector<Component*>();
	Transform* transform = new Transform();
	this->AddComponent(transform);
}

