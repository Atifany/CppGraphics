#pragma once

#include <list>

#include "../../inc/Component.h"
#include "../../inc/Transform.h"
#include "../../inc/GameObject.h"
#include "../../inc/Renderer.h"
#include "../../inc/Material.h"
#include "../../inc/Texture.h"
#include "../../inc/Shader.h"

class ChunkLoader : public Component
{
    public:
        ChunkLoader();
		ChunkLoader(const ChunkLoader& other);
		ChunkLoader& operator=(const ChunkLoader& other);

        void LoadChunk(int xChunk, int zChunk);
		void Update() override;

	private:
		int chunkLoadingDistance; // distance in chunks that shall be rendered
		std::list<GameObject*> loadedChunks;
		glm::vec3 cameraPrevPos;
};
