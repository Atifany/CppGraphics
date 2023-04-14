#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Light		light;
uniform Material	material;
uniform sampler2D	textureToDraw;
uniform vec3		viewPos;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);

	// ambient component
	vec3 ambientComponent = light.ambient * material.ambient;
	
	// diffuse component
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseComponent = diff * light.diffuse * material.diffuse;

	// specular component
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specularComponent = light.specular * spec * material.specular;

	vec3 resultLight = ambientComponent + diffuseComponent + specularComponent;

	FragColor = texture(textureToDraw, texCoord) * vec4(resultLight, 1.0f);
}
