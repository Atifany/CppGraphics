#include "../inc/Renderer.h"

extern std::vector<GameObject*> lightSources;

std::vector<float> defaultCube = {
	// position	in world   // normal vector     // texture coordinates
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   2.0f/4, 0.0f/3,
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f/4, 0.0f/3,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f/4, 1.0f/3,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f/4, 1.0f/3,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   2.0f/4, 1.0f/3,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   2.0f/4, 0.0f/3,

	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   2.0f/4, 3.0f/3,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f/4, 3.0f/3,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f/4, 2.0f/3,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f/4, 2.0f/3,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   2.0f/4, 2.0f/3,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   2.0f/4, 3.0f/3,

	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   2.0f/4, 2.0f/3,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   2.0f/4, 1.0f/3,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   3.0f/4, 1.0f/3,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   3.0f/4, 1.0f/3,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   3.0f/4, 2.0f/3,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   2.0f/4, 2.0f/3,

	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f/4, 2.0f/3,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f/4, 1.0f/3,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f/4, 1.0f/3,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f/4, 1.0f/3,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f/4, 2.0f/3,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f/4, 2.0f/3,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   3.0f/4, 1.0f/3,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   4.0f/4, 1.0f/3,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   4.0f/4, 2.0f/3,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   4.0f/4, 2.0f/3,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   3.0f/4, 2.0f/3,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   3.0f/4, 1.0f/3,

	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   2.0f/4, 1.0f/3,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f/4, 1.0f/3,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f/4, 2.0f/3,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f/4, 2.0f/3,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   2.0f/4, 2.0f/3,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   2.0f/4, 1.0f/3};

Renderer::Renderer()
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = new Texture();
	this->material = new Material();
	this->shader = NULL;

	this->BuildBuffers();
}

Renderer::Renderer(Texture* _texture, Material* _material, Shader* _shader)
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = _texture;
	this->material = _material;
	this->shader = _shader;

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Release bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::Draw(GameObject* camera)
{
	glm::vec3 worldPos = this->gameObject->GetComponent<Transform>()->GetWorldPos();
	this->texture->Bind(GL_TEXTURE0);

	this->shader->Use();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, worldPos);
	glm::vec4 axisAngle = this->gameObject->GetComponent<Transform>()->quaternion.AxisRotation();
	modelMatrix = glm::rotate(modelMatrix, axisAngle.w,
		glm::normalize(glm::vec3(axisAngle.x, axisAngle.y, axisAngle.z)));

	glm::mat4 MVPmatrix = this->shader->projectionMatrix * this->shader->viewMatrix * modelMatrix;
	this->shader->UniformSetMat4("MVPmatrix", MVPmatrix);
	this->shader->UniformSetMat4("Mmatrix", modelMatrix);
	this->shader->UniformSetVec3("viewPos", camera->GetComponent<Transform>()->position);

	this->shader->UniformSetVec3("material.ambient", this->material->ambient);
	this->shader->UniformSetVec3("material.diffuse", this->material->diffuse);
	this->shader->UniformSetVec3("material.specular", this->material->specular);
	this->shader->UniformSetFloat("material.shininess", this->material->shininess);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 5);
	std::cout << "Debug: renderer passed.\n";
}

