#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 outTexCoord;
uniform mat4 model;
uniform mat4 projection;

void main()
{
	outTexCoord = inTexCoord; 

	gl_Position = projection * model * vec4(inPos, 1.0);
}