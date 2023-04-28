#pragma once

#include <string>

#include "character.h"

#include "Component.h"
#include "Shader.h"

class Text : public Component
{
	public:
		Text(Shader* _shader);
		Text(Shader* _shader, std::string _text);
		virtual ~Text();

		void BuildBuffers();
		void DrawText();

		// text it contains
		std::string text;
		float x, y;
		float scale;
		glm::vec3 color;

		// shader to display text
		Shader* shader;

	private:
		unsigned int VBO;
		unsigned int VAO;

};
