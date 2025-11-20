#version 330 core

in vec3	Opos;
in vec3	Onormal;
in vec3	FragPos;

out vec4 FragColor;

void main()
{


	vec3 lightDir = normalize(vec3(40, 200, 7.5) - FragPos);
	float diff = max(dot(Onormal, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1, 1, 1);




	FragColor = vec4(Opos.x / 32.0, Opos.y / 200.0, Opos.z / 32.0, 1);
	FragColor = vec4(abs(Onormal) - 0.4, 1) * vec4(diffuse, 1);
}