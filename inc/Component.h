#pragma once

class GameObject;

class Component
{
	public:
		Component();
		virtual ~Component() {}
		
		virtual void Update() {}

		GameObject* gameObject;

	private:

};
