#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>

#include "stb_image/stb_image.h"
#include "Shader.h"

class Renderer
{
	public:
		Renderer();
		~Renderer();
		//Renderer(const Renderer& other);
		//Renderer& operator=(const Renderer& other);

		void	BuildVBO();
		void	BuildVAO();
		void	BuildBuffers();
		int		BuildTexture();
		void	Draw(Shader& shader, glm::vec3 position, Quaternion quaternion);

		// Draw() will be called in update loop;
		// it would bind VAO/VBO -> bind texture -> build MODEL matrix -> call shaders ->
		// unbind texture -> unbind VAO/VBO
		std::string			texturePath;

	private:
		std::vector<float>	vertices;

		unsigned int VBO;
		unsigned int VAO;
		unsigned int texture;

};
