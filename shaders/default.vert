#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

out vec3 color;

out vec2 texCoord;

uniform mat4 camMatrix;

uniform vec3 indexs[4];

void main()
{
	gl_Position = camMatrix * vec4(aPos.x, aPos.y + gl_InstanceID * 2, aPos.z, 1.0);
	color = aColor;
	texCoord = aTex;
}