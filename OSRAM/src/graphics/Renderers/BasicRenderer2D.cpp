#include "BasicRenderer2D.h"

OSRAM::GRAPHICS::RENDERERS::BasicRenderer2D::BasicRenderer2D(OSRAM::GRAPHICS::MVP * mvp)
{
	m_MVP = mvp;
}

void OSRAM::GRAPHICS::RENDERERS::BasicRenderer2D::submit(Renderable2D* obj)
{
	m_ObjArray[m_Counter] = obj;
	m_Counter++;
}

void OSRAM::GRAPHICS::RENDERERS::BasicRenderer2D::flush(glm::mat4 proj, glm::mat4 view, glm::mat4 model)
{
	m_MVP->SetBasicViewMatrix(view);
	m_MVP->SetBasicProjectionMatrix(proj);
	m_MVP->SetBasicModelMatrix(model);

	int m_TempCounter = m_Counter;
	for (int i = 0; i < m_TempCounter; i++)
	{
		m_ObjArray[i]->LegacyDraw();
		m_Counter--;
	}
}
