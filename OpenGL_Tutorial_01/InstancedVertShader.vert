#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 modelM[30];
uniform mat4 viewM;
uniform mat4 projM;
uniform float deltatime;

mat4 translateMatrix(float x, float y, float z);

void main()
{
	gl_Position = projM * viewM * modelM[gl_InstanceID] * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	texCoord = inTexCoord;
}

