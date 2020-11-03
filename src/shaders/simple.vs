#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texPos;

uniform mat4 MVP;

void main()
{
texPos = aTex;
    gl_Position = MVP * vec4(aPos,1.0f);
}