#version 330 core

in vec4 Color;
in vec2 TexCord;

out vec4 f_color;

uniform sampler2D Texture;

void main()
{
	f_color = Color * texture(Texture, TexCord);
}