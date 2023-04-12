#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

uniform sampler2D	textureToDraw;
uniform vec4		ambientLight;
uniform vec3		lightPos;
uniform vec3		viewPos;
uniform float		specularStrength;
uniform float		shininess;

void main()
{
	vec3 lightColor = vec3(ambientLight.x, ambientLight.y, ambientLight.z);
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	// ambient component
	vec3 ambientComponent = vec3(lightColor * ambientLight.w);
	
	// diffuse component
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseComponent = diff * lightColor;

	// specular component
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
	vec3 specularComponent = specularStrength * spec * lightColor;

	vec3 resultLight = ambientComponent + diffuseComponent + specularComponent;

	FragColor = texture(textureToDraw, texCoord) * vec4(resultLight, 1.0f);
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 0.8f);
}
