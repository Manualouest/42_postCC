#version 330 core

in vec3	texCoord;
in vec3	Opos;
in vec3	Onormal;

out vec4 FragColor;

uniform sampler2D text;
uniform sampler2DArray texts;

void main()
{
	//FragColor = vec4(abs(Onormal), 1);
	//FragColor = texture(text, (texCoord.xy));
	FragColor = texture(texts, texCoord);
	//FragColor = vec4(texCoord.xy, 0, 1);
}