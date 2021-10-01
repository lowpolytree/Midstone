#version 430 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormals;

uniform mat4 shadowMVP;

void main()
{
	gl_Position = shadowMVP * vec4(inPos, 1.0);
}