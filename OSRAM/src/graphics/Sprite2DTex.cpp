#include "Sprite2DTex.h"

OSRAM::GRAPHICS::Sprite2DTex::Sprite2DTex(DATA_Tex data)
{
	_TexSpec = data;
}

OSRAM::GRAPHICS::Sprite2DTex::~Sprite2DTex()
{

}

void OSRAM::GRAPHICS::Sprite2DTex::LegacyDraw()
{

}

void OSRAM::GRAPHICS::Sprite2DTex::init()
{
	glGenVertexArrays(1, &m_VertexArray);
	glGenBuffers(1, &m_DataBuff);
	glGenBuffers(1, &m_IndicesBuff);
	glGenTextures(1, &m_TextureID);

	m_Buffer = new float[8*4] {
		// Vertex Data																			 // Color Data																			 // TexCord Data
		_TexSpec._center.x - (_TexSpec._size.x / 2), _TexSpec._center.y - (_TexSpec._size.y / 2), _TexSpec._color[0].x, _TexSpec._color[0].y, _TexSpec._color[0].z, _TexSpec._color[0].w, _TexSpec._texCord[0].x, _TexSpec._texCord[0].y,
		_TexSpec._center.x + (_TexSpec._size.x / 2), _TexSpec._center.y - (_TexSpec._size.y / 2), _TexSpec._color[1].x, _TexSpec._color[1].y, _TexSpec._color[1].z, _TexSpec._color[1].w, _TexSpec._texCord[1].x, _TexSpec._texCord[1].y,
		_TexSpec._center.x - (_TexSpec._size.x / 2), _TexSpec._center.y + (_TexSpec._size.y / 2), _TexSpec._color[2].x, _TexSpec._color[2].y, _TexSpec._color[2].z, _TexSpec._color[2].w, _TexSpec._texCord[2].x, _TexSpec._texCord[2].y,
		_TexSpec._center.x + (_TexSpec._size.x / 2), _TexSpec._center.y + (_TexSpec._size.y / 2), _TexSpec._color[3].x, _TexSpec._color[3].y, _TexSpec._color[3].z, _TexSpec._color[3].w, _TexSpec._texCord[3].x, _TexSpec._texCord[3].y,
	};

	m_Vertices[0] = _TexSpec._center.x - (_TexSpec._size.x / 2);
	m_Vertices[1] = _TexSpec._center.y - (_TexSpec._size.y / 2);
	m_Vertices[2] = _TexSpec._center.x + (_TexSpec._size.x / 2);
	m_Vertices[3] = _TexSpec._center.y - (_TexSpec._size.y / 2);
	m_Vertices[4] = _TexSpec._center.x - (_TexSpec._size.x / 2);
	m_Vertices[5] = _TexSpec._center.y + (_TexSpec._size.y / 2);
	m_Vertices[6] = _TexSpec._center.y + (_TexSpec._size.y / 2);

	m_Colors[0] = _TexSpec._color[0].x;
	m_Colors[1] = _TexSpec._color[0].y;
	m_Colors[2] = _TexSpec._color[0].z;
	m_Colors[3] = _TexSpec._color[0].w;

	m_Colors[4] = _TexSpec._color[1].x;
	m_Colors[5] = _TexSpec._color[1].y;
	m_Colors[6] = _TexSpec._color[1].z;
	m_Colors[7] = _TexSpec._color[1].w;


	m_Colors[8] =  _TexSpec._color[2].x;
	m_Colors[9] =  _TexSpec._color[2].y;
	m_Colors[10] = _TexSpec._color[2].z;
	m_Colors[11] = _TexSpec._color[2].w;

	m_Colors[12] = _TexSpec._color[3].x;
	m_Colors[13] = _TexSpec._color[3].y;
	m_Colors[14] = _TexSpec._color[3].z;
	m_Colors[15] = _TexSpec._color[3].w;
}