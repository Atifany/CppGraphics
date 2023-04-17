#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 spreadConstants;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	float cutOff;
	float outerCutOff;
	vec3 direction;
	vec3 position;
	vec3 spreadConstants;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

#define NBR_OF_DIRLIGHTS_ALLOWED 8
#define NBR_OF_POINTLIGHTS_ALLOWED 32
#define NBR_OF_SPOTLIGHTS_ALLOWED 32

uniform DirLight	dirLights[NBR_OF_DIRLIGHTS_ALLOWED];
uniform PointLight	pointLights[NBR_OF_POINTLIGHTS_ALLOWED];
uniform SpotLight	spotLights[NBR_OF_SPOTLIGHTS_ALLOWED];
uniform Material	material;
uniform sampler2D	textureToDraw;
uniform vec3		viewPos;

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir);

void main()
{
	vec3 resultLight = vec3(0.0f);
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	
	for (int i = 0; dirLights[i].ambient.x >= 0.0f; i++)
		resultLight += CalcDirLight(dirLights[i], norm, viewDir);
	for (int i = 0; pointLights[i].ambient.x >= 0.0f; i++)
		resultLight += CalcPointLight(pointLights[i], norm, viewDir);
	for (int i = 0; spotLights[i].ambient.x >= 0.0f; i++)
		resultLight += CalcSpotLight(spotLights[i], norm, viewDir);

	FragColor = texture(textureToDraw, texCoord) * vec4(resultLight, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 ambientComponent = light.ambient * material.ambient;
	vec3 diffuseComponent = diff * light.diffuse * material.diffuse;
	vec3 specularComponent = light.specular * spec * material.specular;
	vec3 resultLight = ambientComponent + diffuseComponent + specularComponent;

	return resultLight;
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f /
		(light.spreadConstants.x +
		light.spreadConstants.y * distance +
		light.spreadConstants.z * distance * distance);
	
	vec3 ambientComponent = light.ambient * material.ambient;
	vec3 diffuseComponent = diff * light.diffuse * material.diffuse;
	vec3 specularComponent = light.specular * spec * material.specular;
	vec3 resultLight = ambientComponent + diffuseComponent + specularComponent;

	return resultLight;
}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f /
		(light.spreadConstants.x +
		light.spreadConstants.y * distance +
		light.spreadConstants.z * distance * distance);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	vec3 ambientComponent = light.ambient * material.ambient;
	vec3 diffuseComponent = diff * light.diffuse * material.diffuse;
	vec3 specularComponent = light.specular * spec * material.specular;

	ambientComponent *= attenuation * intensity;
	diffuseComponent *= attenuation * intensity;
	specularComponent *= attenuation * intensity;
	vec3 resultLight = ambientComponent + diffuseComponent + specularComponent;

	return resultLight;
}
