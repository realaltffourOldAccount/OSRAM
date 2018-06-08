#pragma once

#include "..\..\src\graphics\Window.h"
#include "..\..\src\graphics\Shaders.h"
#include "..\..\src\graphics\MVP.h"
#include "..\..\src\input\Input.h"
#include "..\..\src\graphics\Sprite2DTex.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/mat4x4.hpp>
#include <vector>
#include <iostream>

using namespace OSRAM;
using namespace OSRAM::GRAPHICS;
using namespace OSRAM::INPUT;

#define ENTITIES 50
#define MAP_MULTI 50
#define MAP_PIXELS 800
#define MAP_SIZE MAP_PIXELS*MAP_MULTI

using namespace OSRAM;
using namespace OSRAM::GRAPHICS::RENDERERS;


struct Entity
{
	Renderable2D::DATA_Tex _data;
	OSRAM::GRAPHICS::Sprite2DTex *_spriteTex = NULL;
};

struct MAP
{
	Renderable2D::DATA_Tex _ground;
	Renderable2D::DATA_Tex _background;
	OSRAM::GRAPHICS::Sprite2DTex *_GroundTex = NULL;
	OSRAM::GRAPHICS::Sprite2DTex *_BackgroundTex = NULL;
};

class Platformer2D
{
private:
	Window *m_Window;
	Shaders *m_Shaders;
	MVP *m_MVP;
	Input *m_Input;

	Sprite2DTex *m_Platformer;
	Sprite2DTex *m_VirtualPlatformer;

	Renderable2D::DATA_Tex m_PlatformerDATA;


	glm::mat4 Projection = glm::mat4(1.0f);
	glm::mat4 Platformer_Model = glm::mat4(1.0f);

	bool platformer_onGround = true;
	bool platformer_inAir = false;
	bool platformer_collided = false;
	bool game_Started = false;

	std::vector<Entity> m_Entities;
	std::vector<MAP> m_Map;

	void Update();
	void Render();

	void init();

	void updatePlatformer();
	void CheckCollision();
	void CheckStart();

	void DrawEntities();
	void DrawMap();
	void UpdateMap();
public:
	Platformer2D();
	~Platformer2D();

	void Run();
};