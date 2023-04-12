#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D	textureToDraw;
uniform vec4		ambientLight;

void main()
{
	float ambientLightX = ambientLight.x * ambientLight.w;
	float ambientLightY = ambientLight.y * ambientLight.w;
	float ambientLightZ = ambientLight.z * ambientLight.w;
	FragColor = texture(textureToDraw, texCoord) * vec4(ambientLightX, ambientLightY, ambientLightZ, 1.0);
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 0.8f);
}
