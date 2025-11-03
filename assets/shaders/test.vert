#version 330 core
#extension GL_ARB_gpu_shader_int64 : enable

int64_t MASK = 63;

layout (location = 0) in i64vec3 aPos;
layout (location = 1) in i64vec2 aTexI;

uniform mat4 view;
uniform mat4 proj;

out vec2 texCoord;

void main()
{
	gl_Position = proj * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	texCoord = aTexI;
}