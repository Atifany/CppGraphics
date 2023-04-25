#include "../inc/CubeScript.h"

void CubeScript::Update()
{
	Transform* t = this->gameObject->GetComponent<Transform>();
	t->position.y =
		sin((glfwGetTime() + t->position.x + t->position.z) / 1.5f) * 1.5f;
}
