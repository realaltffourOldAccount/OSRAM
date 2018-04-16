#version 330 core

in vec4 position;

uniform mat4 m_M = mat4(1.0f);
uniform mat4 m_V = mat4(1.0f);
uniform mat4 m_P = mat4(1.0f);

void main()
{
	gl_Position = (m_P * m_V * m_M) * position;
}