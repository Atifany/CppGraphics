#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>

#include "stb_image/stb_image.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

class Renderer
{
	public:
		Renderer();
		Renderer(unsigned int textureTarget, const std::string& texturePath, Material& _material);
		Renderer(Texture& _texture, Material& _material);
		~Renderer();
		//Renderer(const Renderer& other);
		//Renderer& operator=(const Renderer& other);

		void	BuildVBO();
		void	BuildVAO();
		void	BuildBuffers();
		void	Draw(Shader& shader, glm::vec3 position, Quaternion quaternion);

		Texture texture;
		Material material;

	private:
		std::vector<float>	vertices;

		unsigned int VBO;
		unsigned int VAO;

};
