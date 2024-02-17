#include "../inc/ChunkLoader.h"

extern Renderer* cubeRenderer;

ChunkLoader::ChunkLoader()
{
	this->chunkLoadingDistance = 1;
	this->loadedChunks;
	this->cameraPrevPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

ChunkLoader::ChunkLoader(const ChunkLoader& other)
{
	this->chunkLoadingDistance = other.chunkLoadingDistance;
	this->loadedChunks = std::list<GameObject*>(other.loadedChunks); // not sure if this is a correct way to deep copy an std::list
	this->cameraPrevPos = glm::vec3(other.cameraPrevPos);
}

ChunkLoader& ChunkLoader::operator=(const ChunkLoader& other)
{
	this->chunkLoadingDistance = other.chunkLoadingDistance;
	this->loadedChunks = std::list<GameObject*>(other.loadedChunks); // not sure if this is a correct way to deep copy an std::list
	this->cameraPrevPos = glm::vec3(other.cameraPrevPos);

	return *this;
}

void ChunkLoader::LoadChunk(int xChunk, int zChunk)
{
	GameObject* chunk = new GameObject();
	chunk->GetComponent<Transform>()->position = glm::vec3(xChunk*16, xChunk+zChunk, zChunk*16);
	this->loadedChunks.push_back(chunk);

	GameObject* cube;

	std::cout << "Loading chunk at " << xChunk << " " << zChunk << "\n";

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			cube = new GameObject();
			cube->AddComponent(new Renderer(*cubeRenderer));
			cube->GetComponent<Transform>()->position = glm::vec3(x, 0.0f, z);
			cube->GetComponent<Transform>()->SetParent(chunk->GetComponent<Transform>());
		}
	}
}

void ChunkLoader::Update()
{
	glm::vec3 cameraPos = this->gameObject->GetComponent<Transform>()->position;

	if (this->loadedChunks.empty() == true)
	{
		for (int x = cameraPos.x/16 - this->chunkLoadingDistance; x <= cameraPos.x/16 + this->chunkLoadingDistance + 1; x++)
		{
			for (int z = cameraPos.z/16 - this->chunkLoadingDistance; z <= cameraPos.z/16 + this->chunkLoadingDistance; z++)
			{
				// run through loaded chunks and see if there is a chunk with x z coords. Or make a stuff with prevPos savings.
				this->LoadChunk(x, z);
			}
		}
	}
}
