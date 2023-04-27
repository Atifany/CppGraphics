#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>

#include "stb_image/stb_image.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Component.h"
#include "GameObject.h"

class Renderer : public Component
{
	public:
		Renderer();
		Renderer(Texture* _texture, Material* _material, Shader* _shader);
		~Renderer();
		//Renderer(const Renderer& other);
		//Renderer& operator=(const Renderer& other);

		void	BuildBuffers();
		void	Draw(GameObject* camera);

		Texture*	texture;
		Material*	material;
		Shader*		shader;

	private:
		std::vector<float>	vertices;

		unsigned int VBO;
		unsigned int VAO;

};
