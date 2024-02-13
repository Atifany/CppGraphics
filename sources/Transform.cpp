#include "../inc/Transform.h"

extern Transform* origin;

Transform::Transform()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->quaternion = Quaternion();
	this->children = std::vector<Transform*>();
	this->parent = NULL;
	if (origin != 0)
		this->SetParent(origin);
	else
		this->SetParent(NULL);
	this->gameObject = NULL;
}

Transform::Transform(GameObject* gm)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->quaternion = Quaternion();
	this->parent = NULL;
	this->SetParent(origin);
	this->children = std::vector<Transform*>();
	this->gameObject = gm;
}

Transform::Transform(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->quaternion = Quaternion(other.quaternion);
	this->parent = NULL;
	this->SetParent(other.parent);
	this->children = std::vector<Transform*>(other.children);
	this->gameObject = other.gameObject;
}

Transform::~Transform()
{
	std::cout << "Debug: Transform destructor called\n";
	// set this's parent to this's children's parent.
	if (this->children.size() != 0)
	{
		std::vector<Transform*>::iterator it = this->children.begin();
		for (it; it != this->children.end(); ++it)
		{
			(*it)->parent = this->parent;
			if (this->parent != NULL)
				this->parent->children.push_back(*it);
		}
		this->children.clear();
	}

	// remove this from previous parent's children list.
	if (this->parent != NULL)
	{
		std::vector<Transform*>::iterator it = this->parent->children.begin();
		for (it; it != this->parent->children.end(); ++it)
		{
			if (*it == this)
			{
				this->parent->children.erase(it);
				break;
			}
		}
	}

	this->SetParent(NULL);
}

Transform& Transform::operator=(const Transform& other)
{
	this->position = glm::vec3(other.position);
	this->quaternion = Quaternion(other.quaternion);
	this->parent = NULL;
	this->SetParent(other.parent);
	this->children = std::vector<Transform*>(other.children);
	this->gameObject = other.gameObject;
	return *this;
}

Transform* Transform::GetWorldCoords()
{
	if (this->parent == NULL)
		return (new Transform(*this));

	Transform* globalTransform = new Transform(*this);
	Transform* parentGlobal = this->parent->GetWorldCoords();
	globalTransform->children.clear();
	globalTransform->SetParent(NULL);
	parentGlobal->children.clear();
	parentGlobal->SetParent(NULL);
	globalTransform->position += parentGlobal->position;
	globalTransform->quaternion += parentGlobal->quaternion;

	delete parentGlobal;
	parentGlobal = NULL;
	return globalTransform;
}

void Transform::SetParent(Transform* _parent)
{
	// set new parent.
	if (this->parent == NULL)
	{
		this->parent = _parent;
		if (_parent != NULL)
			_parent->children.push_back(this);
		return ;
	}

	// remove this from previous parent's children list.
	std::vector<Transform*>::iterator it = this->parent->children.begin();
	for (it; it != this->parent->children.end(); ++it)
	{
		if (*it == this)
		{
			this->parent->children.erase(it);
			break;
		}
	}

	// set new parent and add this to his children.
	this->parent = _parent;
	if (_parent != NULL)
		_parent->children.push_back(this);
}

Transform* Transform::GetParent()
{
	return (this->parent);
}

