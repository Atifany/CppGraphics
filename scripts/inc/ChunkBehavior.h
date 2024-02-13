#pragma once

#include "../../inc/Component.h"
#include "../../inc/Transform.h"
#include "../../inc/GameObject.h"
#include "../../inc/Renderer.h"
#include "../../inc/Material.h"
#include "../../inc/Texture.h"
#include "../../inc/Shader.h"

class ChunkBehavior : public Component
{
    public:
        ChunkBehavior() { };
        void GenerateChunk(Texture* texture, Material* material, Shader* shader);
};
