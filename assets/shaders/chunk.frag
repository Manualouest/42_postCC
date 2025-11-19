#version 330 core

in vec3	Opos;
in vec3	Onormal;

out vec4 FragColor;

void main()
{
	FragColor = vec4(Opos.x / 32.0, Opos.y / 200.0, Opos.z / 32.0, 1);
	FragColor = vec4(abs(Onormal) - 0.4, 1);
}