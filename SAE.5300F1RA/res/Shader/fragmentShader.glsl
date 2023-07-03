#version 400 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;

uniform sampler2D mainTex;
uniform sampler2D subTex;

uniform float alpha;

void main()
{
	FragColor = mix(texture(mainTex, TexCoords), texture(subTex, TexCoords), 0.5f);
	
}