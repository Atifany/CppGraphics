#include "../inc/Cube.h"

Cube::Cube()
{
	this->transform;
	this->renderer;
}

Cube::~Cube() {}

Cube::Cube(const Cube& other)
{
	this->transform = Transform(other.transform);
	this->renderer = Renderer(other.renderer);
}

Cube& Cube::operator= (const Cube& other)
{
	this->transform = Transform(other.transform);
	this->renderer = Renderer(other.renderer);

	return *this;
}

void Cube::DrawMe(Shader& shader)
{
	this->renderer.Draw(shader, this->transform.position, this->transform.quaternion);
}

