#version 330 core

in float clampedTime;

out vec4 FragColor;
uniform sampler2D tex01;

void main()
{
	vec3 fireColorRed = vec3(0.72, 0.36, 0.2);
	vec3 fireColorYellow = vec3(1.0, 0.92, 0.0);

	vec3 newColor = mix(fireColorRed, fireColorYellow, clampedTime);

	FragColor = vec4(newColor, 1.0);
}