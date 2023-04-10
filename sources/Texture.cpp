#include "../inc/Texture.h"

Texture::Texture()
{
	this->path = "";
	this->target = 0;
	this->ID = 0;
}

Texture::~Texture() {}

Texture::Texture(unsigned int textureTarget, const std::string& texturePath)
{
	this->path = texturePath;
	this->target = textureTarget;
	this->ID = 0;
}

Texture::Texture(const Texture& other)
{
	this->path = other.path;
	this->target = other.target;
	this->ID = other.ID;
}

Texture& Texture::operator=(const Texture& other)
{
	this->path = other.path;
	this->target = other.target;
	this->ID = other.ID;

	return *this;
}

int Texture::Load()
{
	int ret = 0;

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(this->path.c_str(), &width, &height, &nrChannels, 0);
	if (imageData == NULL)
	{
		std::cout << "Warning: failed to load texture from " << this->path
			<< " " << stbi_failure_reason() << "\n";
		ret = 1;
	}
	else
	{
		glGenTextures(1, &(this->ID));
		glBindTexture(this->target, this->ID);

		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(this->target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(this->target);
	}
	
	stbi_image_free(imageData);
	glBindTexture(this->target, 0);
	return ret;
}

void Texture::Bind(unsigned int textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(this->target, this->ID);
}
