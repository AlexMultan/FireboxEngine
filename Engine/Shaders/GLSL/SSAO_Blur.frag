#version 460

out float FragColor;

uniform sampler2D u_SSAOTexture;

in vec2 TexCoords;

void main()
{
	vec2 texelSize = 1.0 / vec2(textureSize(u_SSAOTexture, 0));
	float result = 0.0;

	for(int i = -2; i < 2; i++)
	{
		for(int j = -2; j < 2; j++)
		{
			vec2 offset = vec2(float(i), float(j)) * texelSize;
			result += texture(u_SSAOTexture, TexCoords + offset).r;
		}
	}
	FragColor = result / 16.0;
}