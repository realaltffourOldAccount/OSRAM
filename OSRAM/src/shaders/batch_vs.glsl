#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 m_Color;
layout (location = 2) in vec4 m_Modelvec1;
layout (location = 3) in vec4 m_Modelvec2;
layout (location = 4) in vec4 m_Modelvec3;
layout (location = 5) in vec4 m_Modelvec4;

uniform mat4 m_View;
uniform mat4 m_Proj;

out vec4 Color;

void main()
{
	mat4 Model;
	Model[0] = m_Modelvec1;
	Model[1] = m_Modelvec2;
	Model[2] = m_Modelvec3;
	Model[3] = m_Modelvec4;

	gl_Position = (m_Proj * m_View * Model) * position;
	Color = m_Color;
}