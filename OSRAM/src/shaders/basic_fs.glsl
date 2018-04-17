#version 330 core

in vec4 Color;
in vec2 TexCoord;

out vec4 f_color;

uniform sampler2D tex;

void main()
{
	f_color = texture(tex, TexCoord);
}