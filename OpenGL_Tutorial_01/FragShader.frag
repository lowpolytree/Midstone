#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex01;

void main()
{
	FragColor = texture(tex01, texCoord);
}