#include "../inc/Renderer.h"

std::vector<float> defaultCube = {
	// position	in world  // texture coordinates
	-0.5f, -0.5f, -0.5f,  2.0f/4, 0.0f/3,
	 0.5f, -0.5f, -0.5f,  1.0f/4, 0.0f/3,
	 0.5f,  0.5f, -0.5f,  1.0f/4, 1.0f/3,
	 0.5f,  0.5f, -0.5f,  1.0f/4, 1.0f/3,
	-0.5f,  0.5f, -0.5f,  2.0f/4, 1.0f/3,
	-0.5f, -0.5f, -0.5f,  2.0f/4, 0.0f/3,

	-0.5f, -0.5f,  0.5f,  2.0f/4, 3.0f/3,
	 0.5f, -0.5f,  0.5f,  1.0f/4, 3.0f/3,
	 0.5f,  0.5f,  0.5f,  1.0f/4, 2.0f/3,
	 0.5f,  0.5f,  0.5f,  1.0f/4, 2.0f/3,
	-0.5f,  0.5f,  0.5f,  2.0f/4, 2.0f/3,
	-0.5f, -0.5f,  0.5f,  2.0f/4, 3.0f/3,

	-0.5f,  0.5f,  0.5f,  2.0f/4, 2.0f/3,
	-0.5f,  0.5f, -0.5f,  2.0f/4, 1.0f/3,
	-0.5f, -0.5f, -0.5f,  3.0f/4, 1.0f/3,
	-0.5f, -0.5f, -0.5f,  3.0f/4, 1.0f/3,
	-0.5f, -0.5f,  0.5f,  3.0f/4, 2.0f/3,
	-0.5f,  0.5f,  0.5f,  2.0f/4, 2.0f/3,

	 0.5f,  0.5f,  0.5f,  1.0f/4, 2.0f/3,
	 0.5f,  0.5f, -0.5f,  1.0f/4, 1.0f/3,
	 0.5f, -0.5f, -0.5f,  0.0f/4, 1.0f/3,
	 0.5f, -0.5f, -0.5f,  0.0f/4, 1.0f/3,
	 0.5f, -0.5f,  0.5f,  0.0f/4, 2.0f/3,
	 0.5f,  0.5f,  0.5f,  1.0f/4, 2.0f/3,

	-0.5f, -0.5f, -0.5f,  3.0f/4, 1.0f/3,
	 0.5f, -0.5f, -0.5f,  4.0f/4, 1.0f/3,
	 0.5f, -0.5f,  0.5f,  4.0f/4, 2.0f/3,
	 0.5f, -0.5f,  0.5f,  4.0f/4, 2.0f/3,
	-0.5f, -0.5f,  0.5f,  3.0f/4, 2.0f/3,
	-0.5f, -0.5f, -0.5f,  3.0f/4, 1.0f/3,

	-0.5f,  0.5f, -0.5f,  2.0f/4, 1.0f/3,
	 0.5f,  0.5f, -0.5f,  1.0f/4, 1.0f/3,
	 0.5f,  0.5f,  0.5f,  1.0f/4, 2.0f/3,
	 0.5f,  0.5f,  0.5f,  1.0f/4, 2.0f/3,
	-0.5f,  0.5f,  0.5f,  2.0f/4, 2.0f/3,
	-0.5f,  0.5f, -0.5f,  2.0f/4, 1.0f/3};

Renderer::Renderer()
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = Texture();

	this->BuildBuffers();
}

Renderer::Renderer(unsigned int textureTarget, const std::string& texturePath)
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = Texture(textureTarget, texturePath);

	this->BuildBuffers();
}

Renderer::Renderer(Texture& _texture)
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = Texture(_texture);

	this->BuildBuffers();
}

Renderer::~Renderer() {}

void Renderer::BuildBuffers()
{
	// breaking this order of thing causes gDrawArrays to segfault!
	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->VBO));

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	float verticesBuf[this->vertices.size()];
	std::copy(this->vertices.begin(), this->vertices.end(), verticesBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBuf), verticesBuf, GL_STATIC_DRAW);

	// defines what a vertex is. In here it is just vec3 of type float.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Renderer::Draw(Shader& shader, glm::vec3 position, Quaternion quaternion)
{
	this->texture.Bind(GL_TEXTURE0);

	shader.Use();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	glm::vec4 axisAngle = quaternion.AxisRotation();
	modelMatrix = glm::rotate(modelMatrix, axisAngle.w,
		glm::normalize(glm::vec3(axisAngle.x, axisAngle.y, axisAngle.z)));

	glm::mat4 MVPmatrix = shader.projectionMatrix * shader.viewMatrix * modelMatrix;
	shader.UniformSetMat4("MVPmatrix", MVPmatrix);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 5);
}
