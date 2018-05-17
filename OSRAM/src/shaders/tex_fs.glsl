#version 430 core

in vec4 Color;
in vec2 TexCord;

out vec4 f_color;

uniform sampler2D Texture;

void main()
{
	f_color = texture(Texture, TexCord) * Color;
}