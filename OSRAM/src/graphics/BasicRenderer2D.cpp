#include "BasicRenderer2D.h"

void OSRAM::GRAPHICS::BasicRenderer2D::submit(Renderable2D* obj)
{
	m_ObjArray[m_Counter] = obj;
	m_Counter++;
}

void OSRAM::GRAPHICS::BasicRenderer2D::flush()
{
	int m_TempCounter = m_Counter;
	for (int i = 0; i < m_TempCounter; i++)
	{
		m_ObjArray[i]->LegacyDraw();
		m_Counter--;
	}
}
