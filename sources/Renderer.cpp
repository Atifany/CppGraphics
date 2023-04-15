#include "../inc/Renderer.h"

extern Camera camera;
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
	this->texture = Texture();
	this->material = Material();

	this->BuildBuffers();
}

Renderer::Renderer(unsigned int textureTarget, const std::string& texturePath, Material& _material)
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = Texture(textureTarget, texturePath);
	this->material = Material(_material);

	this->BuildBuffers();
}

Renderer::Renderer(Texture& _texture, Material& _material)
{
	this->vertices = defaultCube;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = Texture(_texture);
	this->material = Material(_material);

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
	shader.UniformSetMat4("Mmatrix", modelMatrix);
	shader.UniformSetVec3("viewPos", camera.transform.position);

	// dirLights
	DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(
		lightSources[0]->GetComponent<LightSource>());
	shader.UniformSetVec3("dirLights[0].direction", dirLight->direction);
	shader.UniformSetVec3("dirLights[0].ambient", dirLight->ambient);
	shader.UniformSetVec3("dirLights[0].diffuse", dirLight->diffuse * dirLight->diffuseStrength);
	shader.UniformSetVec3("dirLights[0].specular", dirLight->specular * dirLight->specularStrength);

	shader.UniformSetVec3("dirLights[1].direction", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("dirLights[1].ambient", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("dirLights[1].diffuse", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("dirLights[1].specular", glm::vec3(-1.0f, -1.0f, -1.0f));

	// pointLights
	PointLight* pointLight1 = dynamic_cast<PointLight*>(
		lightSources[1]->GetComponent<LightSource>());
	shader.UniformSetVec3("pointLights[0].position", lightSources[1]->GetComponent<Transform>()->position);
	shader.UniformSetVec3("pointLights[0].spreadConstants", pointLight1->spreadConstants);
	shader.UniformSetVec3("pointLights[0].ambient", pointLight1->ambient);
	shader.UniformSetVec3("pointLights[0].diffuse", pointLight1->diffuse * pointLight1->diffuseStrength);
	shader.UniformSetVec3("pointLights[0].specular", pointLight1->specular * pointLight1->specularStrength);

	PointLight* pointLight2 = dynamic_cast<PointLight*>(
		lightSources[2]->GetComponent<LightSource>());
	shader.UniformSetVec3("pointLights[1].position", lightSources[2]->GetComponent<Transform>()->position);
	shader.UniformSetVec3("pointLights[1].spreadConstants", pointLight2->spreadConstants);
	shader.UniformSetVec3("pointLights[1].ambient", pointLight2->ambient);
	shader.UniformSetVec3("pointLights[1].diffuse", pointLight2->diffuse * pointLight2->diffuseStrength);
	shader.UniformSetVec3("pointLights[1].specular", pointLight2->specular * pointLight2->specularStrength);

	shader.UniformSetVec3("pointLights[2].position", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("pointLights[2].spreadConstants", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("pointLights[2].ambient", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("pointLights[2].diffuse", glm::vec3(-1.0f, -1.0f, -1.0f));
	shader.UniformSetVec3("pointLights[2].specular", glm::vec3(-1.0f, -1.0f, -1.0f));

	shader.UniformSetVec3("material.ambient", this->material.ambient);
	shader.UniformSetVec3("material.diffuse", this->material.diffuse);
	shader.UniformSetVec3("material.specular", this->material.specular);
	shader.UniformSetFloat("material.shininess", this->material.shininess);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 5);
}
