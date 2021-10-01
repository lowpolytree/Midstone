#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormals;

out vec2 texCoord;
out vec3 lightDir;
out vec3 normEye;
out vec3 halfEye;

uniform mat4 mvM;
uniform mat4 projM;
uniform mat4 normM;
uniform vec3 lightPos;

void main()
{
	texCoord = inTexCoord;

	vec3 vertPosEye = (mvM * vec4(inPos, 1.0)).xyz; //vertex position in eye space
	vec3 lightPosEye = (mvM * vec4(lightPos, 1.0f)).xyz; //light pos in eye space
	lightDir = lightPosEye - vertPosEye;

	normEye = (normM * vec4(inNormals, 1.0f)).xyz; //normals in eye space
	halfEye = lightDir - vertPosEye;

	mat4 mvp = projM * mvM; 
	gl_Position = mvp * vec4(inPos, 1.0);
}