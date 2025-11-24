#version 330 core

in vec3	Opos;
in vec3	Onormal;
in vec3	FragPos;

out vec4 FragColor;

void main()
{
	vec3 lightDir = normalize(vec3(40, 200, 7.5) - FragPos);
	float diff = max(dot(Onormal, lightDir), 0.0);
	vec3 diffuse = max(vec3(diff), vec3(0.6));


	if (Onormal.y > 0)
		FragColor = vec4(vec3(0.07, 0.52, 0.06) * diffuse, 1);
	else
		FragColor = vec4(vec3(0.25, 0.16, 0.02) * diffuse, 1);

}