#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormals;

out vec2 outTexCoord;
out vec3 outLightDirEye;
out vec3 normalEye;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;
uniform mat4 normalM;
uniform mat4 dirLightModelM;
//uniform vec3 lightPos;

vec4 dirLight = vec4(0.0, -1.0, 0.0, 0.0);

void main()
{
	outTexCoord = inTexCoord; 

	outLightDirEye = (viewM * dirLightModelM * dirLight).xyz; 

	vec3 vertPosEye = (viewM * modelM * vec4(inPos, 1.0)).xyz; //vertex position in eye space

    normalEye = (viewM * normalM * vec4(inNormals, 1.0f)).xyz; //normals in eye space

	mat4 mvp = projM * viewM * modelM; 
	gl_Position = mvp * vec4(inPos, 1.0);
}