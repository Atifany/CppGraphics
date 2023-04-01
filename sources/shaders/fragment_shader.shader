#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D textureToDraw;

void main()
{
	FragColor = texture(textureToDraw, texCoord);
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 0.8f);
}
