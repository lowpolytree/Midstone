#version 330 core
layout (location = 0) in vec3 inPos;

out float clampedTime;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;

uniform float time;

void main()
{
	clampedTime = clamp(time, 0.0, 1.0);
	float yOffset = mix(0.0, 10.0, clampedTime);
	vec3 newPos = vec3(inPos.x, inPos.y + yOffset, inPos.z);

	mat4 mvp = projM * viewM * modelM; 
	gl_Position = mvp * vec4(newPos, 1.0);
}