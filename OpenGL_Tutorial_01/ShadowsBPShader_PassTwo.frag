#version 430 core

in vec2 texCoord;
in vec4 shadowCoords;

layout (binding = 1) uniform sampler2DShadow shadowTex;
uniform sampler2D tex01;

in vec3 lightDir;
in vec3 normEye;
in vec3 halfEye;

out vec4 FragColor;

void main()
{
	float shininess = 20.0;

	vec3 N = normalize(normEye);
	vec3 L = normalize(lightDir);
	vec3 H = normalize(halfEye);

	float ambient = 0.1;
	float diffuse = max(0.0, dot(N, L));
	float specular = max(0.0, dot(H, N));
	specular = pow(specular, shininess);
	specular *= diffuse;

	//In shadow if 0 and not in shadow if 1
	float notInShadow = textureProj(shadowTex, shadowCoords);
	//float notInShadow = 1.0f;

	vec3 tex = texture(tex01, texCoord).xyz;
	float final = min(ambient + (diffuse + specular) * notInShadow, 1.0);

	vec3 lightColor = vec3(1.0, 0.86, 0.5);

	FragColor = vec4(vec3(final), 1.0);
	//FragColor = vec4(tex * final, 1.0);
	FragColor = vec4(vec3(notInShadow), 1.0);
}