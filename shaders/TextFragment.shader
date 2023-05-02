#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, texCoords).r);
	color = sampled * vec4(textColor, 1.0f);
	// kostil to make transparent fragments not block the view
	if (color.w < 0.1f)
		discard;
}
