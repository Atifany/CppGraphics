#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>

#include "stb_image/stb_image.h"
#include "Shader.h"
#include "Texture.h"

class Renderer
{
	public:
		Renderer();
		Renderer(unsigned int textureTarget, const std::string& texturePath);
		Renderer(Texture& _texture);
		~Renderer();
		//Renderer(const Renderer& other);
		//Renderer& operator=(const Renderer& other);

		void	BuildVBO();
		void	BuildVAO();
		void	BuildBuffers();
		void	Draw(Shader& shader, glm::vec3 position, Quaternion quaternion);

		Texture texture;

	private:
		std::vector<float>	vertices;

		unsigned int VBO;
		unsigned int VAO;

};
