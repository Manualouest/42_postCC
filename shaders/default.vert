#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 nor;

out vec2 texCoord;
out vec3 normal;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = camMatrix * modelMatrix * vec4(aPos, 1.0);
	texCoord = aTex;
	normal = nor;
}