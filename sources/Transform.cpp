#include "../inc/Transform.h"

extern Transform* origin;

Transform::Transform()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->quaternion = Quaternion();
	this->SetParent(origin);
	this->children = std::vector<Transform*>();
	this->gameObject = NULL;
}

Transform::Transform(GameObject* gm)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->quaternion = Quaternion();
	this->SetParent(origin);
	this->children = std::vector<Transform*>();
	this->gameObject = gm;
}

Transform::Transform(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->quaternion = Quaternion(other.quaternion);
	this->SetParent(other.parent);
	this->children = std::vector<Transform*>(other.children);
	this->gameObject = other.gameObject;
}

Transform::~Transform() {}

Transform& Transform::operator=(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->quaternion = Quaternion(other.quaternion);
	this->SetParent(other.parent);
	this->children = std::vector<Transform*>(other.children);
	this->gameObject = other.gameObject;
	return *this;
}

glm::vec3 Transform::GetWorldCoords()
{
	glm::vec3 worldCoords = this->position;

	Transform* _parent = this->parent;
	while (_parent != NULL)
	{
		worldCoords += _parent->position;
		_parent = _parent->parent;
	}
	return worldCoords;
}

void Transform::SetParent(Transform* _parent)
{
	this->parent = _parent;
	if (_parent == NULL)
		return ;
	_parent->children.push_back(this);
}

