#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 m_Projection = mat4(1.0f);
uniform mat4 m_View = mat4(1.0f);
uniform mat4 m_Model = mat4(1.0f);

void main()
{
	mat4 mvp = m_Projection * m_View * m_Model;
	gl_Position =  mvp * position;
}