#version 330 core
layout (location = 0) in vec3 inPos;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;

void main()
{
	mat4 mvp = projM * viewM * modelM;
	gl_Position = mvp * vec4(inPos, 1.0);
}