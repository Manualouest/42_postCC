#version 330 core

in vec3	texCoord;
in vec3	Opos;
in vec3 Onormal;

out vec4 FragColor;

uniform sampler2DArray texts;

void main()
{
	//FragColor = vec4(abs(Onormal), 1);
	FragColor = texture(texts, vec3(texCoord.xy, 2));
	//FragColor = vec4(texCoord, 1);
}