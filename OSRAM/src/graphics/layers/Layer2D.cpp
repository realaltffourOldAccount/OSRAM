#include "Layer2D.h"


OSRAM::GRAPHICS::LAYERS::Layer2D::Layer2D(RENDERERS::Render2D * renderer)
{
	m_Render2D = renderer;
}

OSRAM::GRAPHICS::LAYERS::Layer2D::~Layer2D()
{

}

void OSRAM::GRAPHICS::LAYERS::Layer2D::SetProjection(glm::mat4 proj)
{
	m_Projection = proj;
}

void OSRAM::GRAPHICS::LAYERS::Layer2D::SetView(glm::mat4 view)
{
	m_View = view;
}

void OSRAM::GRAPHICS::LAYERS::Layer2D::Render()
{
	m_Render2D->flush(m_Projection,m_View);
}