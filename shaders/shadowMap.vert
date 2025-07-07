#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 uLightProjection;
uniform mat4 uModelMatrix;

void main()
{
	gl_Position = uLightProjection * uModelMatrix * vec4(aPos, 1.0);
}