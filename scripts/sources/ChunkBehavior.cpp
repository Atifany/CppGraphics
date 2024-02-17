#include "../inc/ChunkBehavior.h"

void ChunkBehavior::GenerateChunk(Texture* texture, Material* material, Shader* shader)
{
	GameObject* cube;
	Renderer* cubeRenderer;

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			cubeRenderer = new Renderer(texture, material, shader);
			cube = new GameObject();
			cube->AddComponent(cubeRenderer);
			cube->GetComponent<Transform>()->position = glm::vec3(x, 0.0f, z);
			cube->GetComponent<Transform>()->SetParent(this->gameObject->GetComponent<Transform>());
		}
	}
}
