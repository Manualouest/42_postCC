#version 330 core
#extension GL_ARB_gpu_shader_int64 : enable

uint64_t X_MASK = 4095u;
uint64_t Y_MASK = 32767u;
uint64_t Z_MASK = 4095u;

uint64_t N_OFFSET = 39u;
uint64_t X_OFFSET = 27u;
uint64_t Y_OFFSET = 12u;
uint64_t Z_OFFSET = 0u;

layout (location = 0) in uint64_t info1;

vec3		pos;
vec3		tpos;
vec3		normal;

uniform mat4	view;
uniform mat4	proj;
uniform mat4	model;

out vec3	Opos;
out vec3	Onormal;

void	decodePos()
{
	pos = vec3(float((info1 >> X_OFFSET) & X_MASK) / 100.0, float((info1 >> Y_OFFSET) & Y_MASK) / 100.0, float(info1 & Z_MASK) / 100.0);
}

void main()
{
	decodePos();
	Opos = pos;

	gl_Position = proj * view * model * vec4(pos, 1.0);
}