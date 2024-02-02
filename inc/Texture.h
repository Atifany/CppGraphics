#pragma once

#include <string>
#include <iostream>
#include "glad/include/glad/glad.h"

#include "stb_image/stb_image.h"

class Texture
{
	public:
		Texture();
		~Texture();
		Texture(unsigned int textureTarget, const std::string& texturePath);
		Texture(const Texture& other);
		Texture& operator=(const Texture& other);

		int		Load();
		void	Bind(unsigned int textureUnit);

	private:
		std::string		path;
		unsigned int	target;
		unsigned int	ID;
};
