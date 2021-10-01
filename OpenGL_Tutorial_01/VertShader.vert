#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 mvM;
uniform mat4 projM;

void main()
{
	mat4 mvp = projM * mvM;
	gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	texCoord = inTexCoord;
}