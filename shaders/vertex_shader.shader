#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVPmatrix;
uniform mat4 Mmatrix;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

void main()
{
	texCoord = aTexCoord;
	normal = mat3(transpose(inverse(Mmatrix))) * aNormal;
	fragPos = vec3(Mmatrix * vec4(aPos, 1.0f));

	gl_Position = MVPmatrix * vec4(aPos, 1.0f);
}
