#version 430 core
in vec2 texPos;
out vec4 FragColor;

uniform vec4 Colour;
uniform sampler2D tex;

void main()
{
	FragColor = Colour * texture(tex,texPos);
}