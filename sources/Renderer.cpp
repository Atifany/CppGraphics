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

	LightSource*		lightSource;
	DirectionalLight*	dirLight;
	PointLight*			pointLight;
	int nbrOfDirLights = 0;
	int nbrOfPointLights = 0;
	char buf[64];
	for (GameObject* gm : lightSources)
	{
		lightSource = gm->GetComponent<LightSource>();
		
		dirLight = dynamic_cast<DirectionalLight*>(lightSource);
		if (dirLight != NULL)
		{
			sprintf(buf, "dirLights[%i].direction", nbrOfDirLights);
			shader.UniformSetVec3(buf, dirLight->direction);
			sprintf(buf, "dirLights[%i].ambient", nbrOfDirLights);
			shader.UniformSetVec3(buf, dirLight->ambient);
			sprintf(buf, "dirLights[%i].diffuse", nbrOfDirLights);
			shader.UniformSetVec3(buf, dirLight->diffuse * dirLight->diffuseStrength);
			sprintf(buf, "dirLights[%i].specular", nbrOfDirLights);
			shader.UniformSetVec3(buf, dirLight->specular * dirLight->specularStrength);
			nbrOfDirLights++;
		}
		pointLight = dynamic_cast<PointLight*>(lightSource);
		if (pointLight != NULL)
		{
			sprintf(buf, "pointLights[%i].position", nbrOfPointLights);
			shader.UniformSetVec3(buf, gm->GetComponent<Transform>()->position);
			sprintf(buf, "pointLights[%i].spreadConstants", nbrOfPointLights);
			shader.UniformSetVec3(buf, pointLight->spreadConstants);
			sprintf(buf, "pointLights[%i].ambient", nbrOfPointLights);
			shader.UniformSetVec3(buf, pointLight->ambient);
			sprintf(buf, "pointLights[%i].diffuse", nbrOfPointLights);
			shader.UniformSetVec3(buf, pointLight->diffuse * pointLight->diffuseStrength);
			sprintf(buf, "pointLights[%i].specular", nbrOfPointLights);
			shader.UniformSetVec3(buf, pointLight->specular * pointLight->specularStrength);
			nbrOfPointLights++;
		}
	}

	// set last light in array to indicate array end.
	sprintf(buf, "dirLights[%i].ambient", nbrOfDirLights);
	shader.UniformSetVec3(buf, glm::vec3(-1.0f, -1.0f, -1.0f));
	sprintf(buf, "pointLights[%i].ambient", nbrOfPointLights);
	shader.UniformSetVec3(buf, glm::vec3(-1.0f, -1.0f, -1.0f));

	shader.UniformSetVec3("material.ambient", this->material.ambient);
	shader.UniformSetVec3("material.diffuse", this->material.diffuse);
	shader.UniformSetVec3("material.specular", this->material.specular);
	shader.UniformSetFloat("material.shininess", this->material.shininess);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 5);
}
