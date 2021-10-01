#version 330 core

in vec2 outTexCoord;

out vec4 FragColor;

uniform sampler2D tex01;
uniform vec3 color;

void main()
{
	FragColor = vec4(color, 1.0) * texture(tex01, outTexCoord);
	//FragColor = vec4(1.0);
}