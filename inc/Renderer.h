#pragma once

#include <vector>

class Renderer
{
	public:
		Renderer();
		~Renderer();
		//Renderer(const Renderer& other);
		//Renderer& operator=(const Renderer& other);

		// build VBO & VAO ()
		// build texture ()
		// Draw(shaderProgram) ->
		// bind/unbind VBO & VAO ()
		// Draw(shaderProgram) ->
		// bind/unbind texture ()

		// Draw() will be called in update loop;
		// it would bind VAO/VBO -> bind texture -> build MODEL matrix -> call shaders ->
		// unbind texture -> unbind VAO/VBO

	private:
		std::vector<float> vertices;

};
