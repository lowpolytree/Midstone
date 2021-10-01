#version 330 core

in vec2 texCoord;
in vec3 lightDir;
in vec3 normEye;
in vec3 halfEye;

out vec4 FragColor;

uniform sampler2D tex01;

void main()
{
	float shininess = 20.0;

	vec3 N = normalize(normEye);
	vec3 L = normalize(lightDir);
	vec3 H = normalize(halfEye);

	float ambient = 0.2;
	float diffuse = max(0.0, dot(N, L));
	float specular = max(0.0, dot(H, N));
	specular = pow(specular, shininess);
	specular *= diffuse;

	vec3 tex = texture(tex01, texCoord).xyz;
	float final = min(ambient + diffuse + specular, 1.0);

	vec3 lightColor = vec3(1.0, 0.86, 0.5);

	FragColor = vec4(tex * final, 1.0);
	//FragColor = vec4(vec3(specular), 1.0);
}