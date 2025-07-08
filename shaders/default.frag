#version 330 core
out vec4 FragColor;

//in int gl_PrimitiveID;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLight;
in float totalVertexes;
in vec4 clipSpace;
in vec3 position;
flat in int switchText;
flat in int switchType;
flat in float switchTextMix;
flat in float switchTypeMix;

uniform sampler2D uText0;
uniform sampler2D uText1;
uniform float uTextMix;
uniform float uTypeMix;
uniform sampler2D uShadow;
uniform int uNbFaces;
uniform bool uLight;
uniform bool uShadows;
uniform bool uTorch;
uniform vec3 uLightPos;
uniform mat4 uModelMatrix;
uniform mat4 uCamMatrix;
uniform vec3 uLightColor;

void main()
{
	vec2 pos = clipSpace.xy / clipSpace.w;
	pos = pos / 2 + 0.5;

	vec3 result = vec3(0);

	vec3 ambient = vec3(0);
	vec3 diffuse = vec3(0);
	if (uLight)
	{
		//AMBIENT
		float ambientStrength = 0.1;
		ambient = ambientStrength * vec3(1.0f);
		result += ambient;

		//DIFFUSE
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(uLightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = diff * uLightColor;
		if (!uShadows)
			result += diffuse;
	}


	//TORCH
	if (uTorch)
		result += vec3(clamp(1 - (pow(pos.x - 0.5, 2) + pow(pos.y - 0.5, 2)) * 30, 0, 1.0));


	//SHADOWS
	float shadow = 0.0f;
	vec3 lightCoords = FragPosLight.xyz / FragPosLight.w;
	float closestDepth;
	float currentDepth;
	vec3 lightDirection = normalize(uLightPos);
	if (uShadows && uLight && lightCoords.z <= 1.0f)
	{
		lightCoords = (lightCoords + 1.0f) / 2.0f;
		currentDepth = lightCoords.z;

		float bias = max(0.005 * (1.0f - dot(Normal, lightDirection)), 0.0005f);

		int sampleRadius = 2;
		vec2 pixelSize = 1.0 / textureSize(uShadow, 0);
		for (int y = -sampleRadius; y <= sampleRadius; y++)
		{
			for (int x = -sampleRadius; x <= sampleRadius; x++)
			{
				float closestDepth = texture(uShadow, lightCoords.xy + vec2(x, y) * pixelSize).r;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;
			}
		}
		shadow /= pow((sampleRadius * 2 + 1), 2);
	}
	if (uShadows && uLight)
		result += (diffuse * (1.0f - shadow));

	if (!uLight && !uTorch)
		result = vec3(1);

	FragColor = mix(mix(vec4(result, 1.0) * texture(uText0, texCoord), vec4(result, 1.0) * texture(uText1, texCoord), switchTextMix),
				mix(vec4(result, 1.0) * vec4(vec3(clamp(uNbFaces / (totalVertexes * 3.0f) + 0.2f, 0.0f, 0.8f)), 1.0), vec4(result, 1.0) * vec4(Normal, 1.0f), switchTextMix),
				switchTypeMix);
}