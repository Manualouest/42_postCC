#version 330 core
out vec4 FragColor;

//in int gl_PrimitiveID;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 clipSpace;
in float totalVertexes;

uniform sampler2D uTex0;
uniform int uNbFaces;

vec3 lightColor = vec3(1, 1, 1);
vec3 lightPos = vec3(10, 1000, 0);

void main()
{
	vec2 pos = clipSpace.xy / clipSpace.w;
	pos = pos / 2 + 0.5;

	//AMBIENT
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;


	//DIFFUSE
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	//TORCH
	vec3 torch = vec3(clamp(1 - (pow(pos.x - 0.5, 2) + pow(pos.y - 0.5, 2)) * 30, 0, 1.0));


	vec3 result = ambient + diffuse + torch;


	FragColor = vec4(result.xyz, 1.0) * texture(uTex0, texCoord);
	//FragColor = vec4(vec3(float(uNbFaces) / totalVertexes), 1.0);
}