#version 400 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;
uniform bool isTexture;
uniform bool isColor;

uniform sampler2D main_Texture;
uniform sampler2D sub_Texture;

uniform float alpha;

void main()
{
	if (isTexture && isColor)
		FragColor = mix(texture(main_Texture, TexCoords), texture(sub_Texture, TexCoords), alpha) * vec4(colors,1.0f);
	else if(isTexture && !isColor)
		FragColor = mix(texture(main_Texture, TexCoords), texture(sub_Texture, TexCoords), alpha);
	else if(!isTexture && isColor)
		FragColor = vec4(colors,1.0f);
	else
		FragColor = vec4(1.0f);
}