#include "../inc/GameObject.h"
#include "../inc/Renderer.h"

std::vector<GameObject*> lightSources;

GameObject::GameObject()
{
	this->components = std::vector<Component*>();
	Transform* transform = new Transform();
	this->AddComponent(transform);
}

GameObject::~GameObject()
{
	delete this->GetComponent<Transform>();
}

void GameObject::CallUpdates(GameObject* camera)
{
	this->RenderMe(camera);
	for (Component* component : this->components)
	{
		component->Update();
	}
	Transform* t = this->GetComponent<Transform>();
	for (Transform* child : t->children)
	{
		child->gameObject->CallUpdates(camera);
	}
}

void GameObject::RenderMe(GameObject* camera)
{
	Renderer *renderer = this->GetComponent<Renderer>();
	if (renderer != NULL)
		renderer->Draw(camera);
}
