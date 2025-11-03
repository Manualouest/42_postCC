#version 330 core
#extension GL_ARB_gpu_shader_int64 : enable


uint64_t POS_MASK = 1048575u;
uint64_t TPOS_MASK = 8388607u;
uint64_t N_MASK = 1023u;
uint64_t T_MASK = 63u;

uint64_t POS_SIZE = 20u;
uint64_t X_OFFSET = 42u;
uint64_t Y_OFFSET = 21u;

uint64_t TPOS_SIZE = 23u;
uint64_t N_OFFSET = 54u;
uint64_t T_OFFSET = 48u;
uint64_t TX_OFFSET = 24u;

layout (location = 0) in uint64_t info1;
layout (location = 1) in uint64_t info2;

vec3		pos;
vec3		tpos;
vec3		normal;

uniform mat4	view;
uniform mat4	proj;
uniform mat4	model;
uniform vec3	normals[900];

out vec3	texCoord;
out vec3	Opos;
out vec3	Onormal;

void	decodePos()
{
	pos = vec3(float((info1 >> X_OFFSET) & POS_MASK) / 100000.0, float((info1 >> Y_OFFSET) & POS_MASK) / 100000.0, float(info1 & POS_MASK) / 100000.0);

	if ((((info1 >> X_OFFSET) >> (POS_SIZE)) & 1u) == 1u)
		pos.x = pos.x * -1;
	if ((((info1 >> Y_OFFSET) >> (POS_SIZE)) & 1u) == 1u)
		pos.y = pos.y * -1;
	if (((info1 >> (POS_SIZE)) & 1u) == 1u)
		pos.z = pos.z * -1;
}

void	decodeTex()
{
	tpos = vec3(float((info2 >> TX_OFFSET) & TPOS_MASK) / 1000000.0, float(info2 & TPOS_MASK) / 1000000.0, float((info2 >> T_OFFSET) & T_MASK));

	//if ((((info2 >> TX_OFFSET) >> (TPOS_SIZE)) & 1u) == 1u)
	//	tpos.x = tpos.x * -1;
	//if (((info2 >> (TPOS_SIZE)) & 1u) == 1u)
	//	tpos.y = tpos.y * -1;
}

void main()
{
	decodePos();
	Opos = pos;

	decodeTex();
	texCoord = tpos;

	Onormal = mat3(transpose(inverse(model))) * normals[int(info2 >> N_OFFSET & N_MASK)];

	gl_Position = proj * view * model * vec4(pos, 1.0);
}