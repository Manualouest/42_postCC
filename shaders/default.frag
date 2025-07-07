#version 330 core
out vec4 FragColor;

//in int gl_PrimitiveID;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLight;
in float totalVertexes;
in vec4 clipSpace;

uniform sampler2D uText;
uniform sampler2D uShadow;
uniform int uNbFaces;

vec3 lightColor = vec3(1, 1, 1);
vec3 lightPos = FragPosLight.xyz;

void main()
{
	vec2 pos = clipSpace.xy / clipSpace.w;
	pos = pos / 2 + 0.5;

	//AMBIENT
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;


	//DIFFUSE
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	//TORCH
	vec3 torch = vec3(clamp(1 - (pow(pos.x - 0.5, 2) + pow(pos.y - 0.5, 2)) * 30, 0, 1.0));


	float shadow = 0.0f;
	vec3 lightCoords = FragPosLight.xyz / FragPosLight.w;
	float closestDepth;
	float currentDepth;
	vec3 lightDirection = normalize(lightPos);
	if (lightCoords.z <= 1.0f)
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

	vec3 result = ambient + (diffuse * (1.0f - shadow));// + torch;

	//if (pos.x > 0.5)
	//	FragColor = vec4(vec3(closestDepth), 1.0f);
	//else
	//	FragColor = vec4(vec3(lightCoords.z), 1.0f);
	//FragColor = vec4(vec3(10.f - shadow), 1.0f);

	//FragColor = texture(uShadow, texCoord).rrrw;
	FragColor = vec4(result.xyz, 1.0) * texture(uText, texCoord);
	//FragColor = vec4(vec3(float(uNbFaces) / totalVertexes), 1.0);
}