#include "../inc/Text.h"

extern std::map<char, Character> Characters;

Text::Text(Shader* _shader)
{
	this->text = "";
	this->x = 0.0f;
	this->y = 0.0f;
	this->scale = 1.0f;
	this->color = glm::vec3(0.0f, 0.0f, 0.0f);
	this->shader = _shader;

	this->BuildBuffers();
}

Text::Text(Shader* _shader, std::string _text)
{
	this->text = _text;
	this->x = 0.0f;
	this->y = 0.0f;
	this->scale = 1.0f;
	this->color = glm::vec3(0.0f, 0.0f, 0.0f);
	this->shader = _shader;

	this->BuildBuffers();
}

Text::~Text() {}

void Text::BuildBuffers()
{
	// breaking this order of thing causes gDrawArrays to segfault!
	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->VBO));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// Each quad requires 6 verticies with 4 floats each of space
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	// defines what a vertex is. In here it is just vec3 of type float.
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Release bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::DrawText()
{
	// activate proper shader
	this->shader->Use();
	this->shader->UniformSetMat4("projection", this->shader->projectionMatrix);
	this->shader->UniformSetVec3("textColor", this->color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	float xBuf = this->x;

	// iterate through all the text.
	std::string::const_iterator c;
	for (c = this->text.begin(); c != this->text.end(); c++)
	{
		Character ch = Characters[*c];
		float xpos = xBuf + ch.bearing.x * this->scale;
		float ypos = this->y - (ch.size.y - ch.bearing.y) * this->scale;

		float w = ch.size.x * this->scale;	
		float h = ch.size.y * this->scale;

		// set VBO for each character
		float verticies[6][4] = {
			{xpos    , ypos + h, 0.0f, 0.0f},
			{xpos    , ypos    , 0.0f, 1.0f},
			{xpos + w, ypos    , 1.0f, 1.0f},
			{xpos    , ypos + h, 0.0f, 0.0f},
			{xpos + w, ypos    , 1.0f, 1.0f},
			{xpos + w, ypos + h, 1.0f, 0.0f},
		};
		glBindTexture(GL_TEXTURE_2D, ch.textureId);
		// Put new VBO to memory
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticies), verticies);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// draw quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// move imaginary cursor to the next glyph
		xBuf += (ch.advance >> 6) * this->scale;
	}
	// release all binds
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
