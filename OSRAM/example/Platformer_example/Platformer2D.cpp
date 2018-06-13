#include "Platformer2D.h"


Platformer2D::Platformer2D()
{
	init();
}


Platformer2D::~Platformer2D()
{

}

void Platformer2D::CheckStart()
{
	if (m_Input->isKeyPressed(GLFW_KEY_SPACE))
		game_Started = true;
}

void Platformer2D::Run()
{
	while (!glfwWindowShouldClose(m_Window->getWindowHandler()))
	{
		m_Window->Update();
		Render();
		CheckStart();
		if (game_Started == true)
		{
			if (!platformer_collided == true)
			{
				Update();
				Render();
			}
		}
		m_Window->RenderImGUI();
	}
}

void Platformer2D::Render()
{
	m_MVP->SetTextureProjectionMatrix(Projection);
	DrawMap();
	DrawEntities();

//	m_MVP->SetTextureViewMatrix(Camera);
	m_MVP->SetTextureModelMatrix(m_Platformer->GetModelMatrix());
	m_Platformer->LegacyDraw();
}

void Platformer2D::DrawEntities()
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		m_Entities[i]._spriteTex->LegacyDraw();
	}
}
void Platformer2D::DrawMap()
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		m_MVP->SetTextureModelMatrix(m_Map[i]._BackgroundTex->GetModelMatrix());
		m_Map[i]._BackgroundTex->LegacyDraw();

		m_MVP->SetTextureModelMatrix(m_Map[i]._GroundTex->GetModelMatrix());
		m_Map[i]._GroundTex->LegacyDraw();
	}
}

void Platformer2D::Update()
{
	UpdateMap();
	m_VirtualPlatformer->moveX();
	updatePlatformer();
	CheckCollision();
}

void Platformer2D::UpdateMap()
{
	for (int i = 0; i < m_Map.size(); i++)
	{
		m_Map[i]._BackgroundTex->moveNegX();
		m_Map[i]._GroundTex->moveNegX();
	}
}

void Platformer2D::updatePlatformer()
{
	if (m_Input->isKeyPressed(GLFW_KEY_SPACE) == true)
	{
			m_Platformer->moveY();
			m_VirtualPlatformer->moveY();
			platformer_onGround = false;
	}
	else if (platformer_onGround == false)
	{
		m_Platformer->moveNegY();
		m_VirtualPlatformer->moveNegY();
		glm::vec4 temp;
		temp.x = m_PlatformerDATA._center.x;
		temp.y = (m_PlatformerDATA._center.y - (m_PlatformerDATA._size.y/2));
		temp.z = 0.0f;
		temp.w = 1.0f;

		temp = m_Platformer->GetModelMatrix() * temp;

		if (temp.y == 100)
			platformer_onGround = true;
	}
	//m_Platformer->accelerateX(true);
	//m_VirtualPlatformer->accelerateX(true);
}

void Platformer2D::CheckCollision()
{
	glm::vec4 platformerCenter, platformerFCornerUP, platformerFCornerDown
		, platformerBCornerDown;

	platformerCenter.x = m_PlatformerDATA._center.x;
	platformerCenter.y = m_PlatformerDATA._center.y;
	platformerCenter.z = 0.0f;
	platformerCenter.w = 1.0f;

	// TODO: Check for platformer movement throught the matrix
	//platformerCenter = m_VirtualPlatformer->GetModelMatrix() * platformerCenter;
	platformerCenter = m_VirtualPlatformer->GetModelMatrix() * platformerCenter;

	platformerFCornerUP.x = platformerCenter.x + (m_PlatformerDATA._size.x / 2);
	platformerFCornerUP.y = platformerCenter.y + (m_PlatformerDATA._size.y / 2);
	platformerFCornerUP.z = 0.0f;
	platformerFCornerUP.w = 1.0f;

	platformerFCornerDown.x = platformerCenter.x + (m_PlatformerDATA._size.x / 2);
	platformerFCornerDown.y = platformerCenter.y - (m_PlatformerDATA._size.y / 2);
	platformerFCornerDown.z = 0.0f;
	platformerFCornerDown.w = 1.0f;

	platformerBCornerDown.x = platformerCenter.x - (m_PlatformerDATA._size.x / 2);
	platformerBCornerDown.y = platformerCenter.y - (m_PlatformerDATA._size.y / 2);
	platformerBCornerDown.z = 0.0f;
	platformerBCornerDown.w = 1.0f;



	for (int i = 0; i < m_Entities.size(); i++)
	{
		glm::vec4 entityCenter, entityBCornerUP, entityBCornerDown,
			entityFCornerUP;
		//////////FRONT SIDE OF PLATFORMER COLLISION TEST///////////////
		entityCenter = glm::vec4(m_Entities[i]._data._center, 0.0f, 1.0f);

		entityBCornerUP.x = entityCenter.x - (m_Entities[i]._data._size.x/2);
		entityBCornerUP.y = entityCenter.y + (m_Entities[i]._data._size.y/2);
		entityBCornerUP.z = 0.0f;
		entityBCornerUP.w = 1.0f;

		entityBCornerDown.x = entityCenter.x - (m_Entities[i]._data._size.x / 2);
		entityBCornerDown.y = entityCenter.y - (m_Entities[i]._data._size.y / 2);
		entityBCornerDown.z = 0.0f;
		entityBCornerDown.w = 1.0f;

		entityFCornerUP.x = entityCenter.x + (m_Entities[i]._data._size.x / 2);
		entityFCornerUP.y = entityCenter.y - (m_Entities[i]._data._size.y / 2);
		entityFCornerUP.z = 0.0f;
		entityFCornerUP.w = 1.0f;

		if (platformerFCornerUP.x >= entityBCornerUP.x && platformerBCornerDown.x < entityFCornerUP.x)
 			if (platformerFCornerDown.y < entityBCornerUP.y /*&& platformerFCornerDown.y >= entityBCornerDown.y)*/)
        				platformer_collided = true;
	}
}

void Platformer2D::init()
{
	m_Window = new Window(800,500,"Platformer_Example | OSRAM V1.2");
	m_Shaders = new Shaders(m_Window);
	m_MVP = new MVP(m_Shaders);
	m_Input = new Input(m_Window, GLFW_CURSOR_NORMAL);
	m_Shaders->UseTextureProgram();
	Projection = glm::ortho((float)0, (float)m_Window->getWindowWidth(), (float)0, (float)m_Window->getWindowHeight());
	
	for (int i = 0; i < MAP_MULTI; i++)
	{
		MAP map;

		if (i == 0)
			map._background._center.x = (800 / 2);
		else map._background._center.x = m_Map[i-1]._background._center.x + (800);

		map._background._center.y = 500 / 2;
		map._background._size.x = MAP_PIXELS;
		map._background._size.y = 500;
		map._background._color[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._background._color[1] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._background._color[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._background._color[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._background._texCord[0] = glm::vec2(1.0f, 1.0f);
		map._background._texCord[1] = glm::vec2(1.0f, 0.0f);
		map._background._texCord[2] = glm::vec2(0.0f, 0.0f);
		map._background._texCord[3] = glm::vec2(0.0f, 1.0f);
		map._background._texturePATH = "res\\background.jpg";
		map._BackgroundTex = new Sprite2DTex(map._background, m_Window);

		if (i == 0)
			map._ground._center.x = (800 / 2);
		else map._ground._center.x =  m_Map[i-1]._background._center.x + (800);

		map._ground._center.y =  50;
		map._ground._size.x = MAP_PIXELS;
		map._ground._size.y = 100;
		map._ground._color[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._ground._color[1] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._ground._color[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._ground._color[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		map._ground._texCord[0] = glm::vec2(1.0f, 1.0f);
		map._ground._texCord[1] = glm::vec2(1.0f, 0.0f);
		map._ground._texCord[2] = glm::vec2(0.0f, 0.0f);
		map._ground._texCord[3] = glm::vec2(0.0f, 1.0f);
		map._ground._texturePATH = "res\\ground.jpg";
		map._GroundTex = new Sprite2DTex(map._ground, m_Window);
		
		map._GroundTex->SetSpeedNegX(-8.5f);
		map._BackgroundTex->SetSpeedNegX(-8.5f);

		m_Map.push_back(map);
	}
	m_PlatformerDATA._center = glm::vec2(150, 100 + (90/2));
	m_PlatformerDATA._size.x = 90;
	m_PlatformerDATA._size.y = 90;
	m_PlatformerDATA._color[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_PlatformerDATA._color[1] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_PlatformerDATA._color[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_PlatformerDATA._color[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_PlatformerDATA._texCord[0] = glm::vec2(1.0f, 1.0f);
	m_PlatformerDATA._texCord[1] = glm::vec2(1.0f, 0.0f);
	m_PlatformerDATA._texCord[2] = glm::vec2(0.0f, 0.0f);
	m_PlatformerDATA._texCord[3] = glm::vec2(0.0f, 1.0f);
	m_PlatformerDATA._texturePATH = "res\\platformer.jpg";
	m_Platformer = new Sprite2DTex(m_PlatformerDATA, m_Window);
	m_Platformer->SetSpeedPosY(10.0f);
	m_Platformer->SetSpeedNegY(-10.0f);
	//m_Platformer->SetSpeedPosX(1.0f);
	//m_Platformer->SetSpeedNegX(-1.0f);
	m_VirtualPlatformer = new Sprite2DTex(m_PlatformerDATA, m_Window);
	m_VirtualPlatformer->SetSpeedPosY(10.0f);
	m_VirtualPlatformer->SetSpeedNegY(-10.0f);

	m_VirtualPlatformer->SetSpeedPosX(8.5f);

	

	for (int i = 0; i < ENTITIES; i++)
	{
		Entity temp;
		temp._data._center.x = (MAP_SIZE / ENTITIES) * (i + 1);
		temp._data._center.y = 100 + (120/2);
		temp._data._size.x = 120;
		temp._data._size.y = 120;
		temp._data._color[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		temp._data._color[1] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		temp._data._color[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		temp._data._color[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		temp._data._texCord[0] = glm::vec2(1.0f, 1.0f);
		temp._data._texCord[1] = glm::vec2(1.0f, 0.0f);
		temp._data._texCord[2] = glm::vec2(0.0f, 0.0f);
		temp._data._texCord[3] = glm::vec2(0.0f, 1.0f);
		temp._data._texturePATH = "res\\Cactus.jpg";
		temp._spriteTex = new Sprite2DTex(temp._data, m_Window);

		m_Entities.push_back(temp);
	}
}