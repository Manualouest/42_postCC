#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLight;
out float totalVertexes;
out vec4 clipSpace;
out vec3 position;
flat out int switchText;
flat out int switchType;
flat out float switchTextMix;
flat out float switchTypeMix;

uniform mat4 uCamMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uLightProjection;
uniform float uTextMix;
uniform float uTypeMix;
uniform vec3 uMixWay;
uniform float uObjMin;
uniform float uObjMax;

void main()
{
	gl_Position = uCamMatrix * uModelMatrix * vec4(aPos, 1.0);
	clipSpace = gl_Position;
	texCoord = aTex;
	Normal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
	FragPos = vec3(uModelMatrix * vec4(aPos, 1.0));
	FragPosLight = uLightProjection * vec4(vec3(uModelMatrix * vec4(aPos, 1.0f)), 1.0f);
	totalVertexes = float(gl_VertexID);
	position = vec3(aPos);
	vec3 mPos = position * uMixWay;
	switchTextMix = 1 - clamp((uObjMin - (mPos.x + mPos.y + mPos.z)) / (uObjMax - uObjMin) + (uTextMix + 1), 0.0f, 1.0f);
	switchTypeMix = 1 - clamp((uObjMin - (mPos.x + mPos.y + mPos.z)) / (uObjMax - uObjMin) + (uTypeMix + 1), 0.0f, 1.0f);
}