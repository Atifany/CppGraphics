#pragma once

#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"

class Cube
{
	public:
		Cube();
		Cube(Texture texture);
		~Cube();
		Cube(const Cube& other);
		Cube& operator=(const Cube& other);

		void DrawMe(Shader& shader);

		Transform	transform;
		Renderer	renderer;

	private:

};
