#include "VectorRenderer2D.h"


OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::VectorRenderer2D(MVP *mvp)
{
	m_MVP = mvp;
}

OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::~VectorRenderer2D()
{

}


void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::add(Renderable2D *obj, std::string name)
{
	OBJ temp_obj;
	temp_obj._obj = obj;
	temp_obj._name = name;

	m_Objects.push_back(temp_obj);
	m_ObjCount++;
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::remove(std::string name)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]._name == name)
		{
			m_Objects.erase(m_Objects.begin() + i);
			return;
		}
	}
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::clear()
{
	m_Objects.clear();
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::render()
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_MVP->SetTextureModelMatrix(m_Objects[i]._obj->GetModelMatrix());
		m_Objects[i]._obj->LegacyDraw();
	}
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::setProjection(glm::mat4 proj)
{
	m_Projection = proj;
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::setView(glm::mat4 view)
{
	m_View = view;
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::submit(Renderable2D *obj)
{
	std::string name = "object" + std::to_string(m_ObjCount);
	add(obj, name);
}

void OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D::flush(glm::mat4 proj, glm::mat4 view, glm::mat4 model)
{
	setProjection(proj);
	setView(view);

	render();
}