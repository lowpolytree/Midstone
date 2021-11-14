#version 330 core

in vec2 outTexCoord;
in vec3 outLightDirEye;
in vec3 normalEye;

out vec4 FragColor;

uniform sampler2D tex01;
uniform bool isIntersectedOnce;
uniform bool isLast;
uniform bool isBlock;

void main()
{

	vec3 N = normalize(normalEye);
	vec3 L = normalize(outLightDirEye);

	float ambient = 0.2;
	float diffuse = max(0.0, dot(N, L));

	vec3 tex = texture(tex01, outTexCoord).xyz;

	//FragColor = vec4(tex * final, 1.0);
	//FragColor = vec4(vec3(specular), 1.0);
	//FragColor = vec4(tex * min(ambient + diffuse, 1.0), 1.0);

	float final = min(ambient + diffuse, 1.0);

	if (isIntersectedOnce && !isBlock){
		FragColor = vec4(tex * 0.7, 1.0);
	} else {
		FragColor = vec4(final * tex, 1.0);
	}
}