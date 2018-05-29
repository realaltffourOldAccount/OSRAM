#pragma once

#include "..\src\graphics\Window.h"
#include "..\src\graphics\Sprite2D.h"
#include "..\src\graphics\BasicRenderer2D.h"
#include "..\src\graphics\MVP.h"
#include "..\src\graphics\Shaders.h"
#include "..\src\input\Input.h"


#include <GLM\glm.hpp>
#include <GLFW\glfw3.h>

using namespace OSRAM;

class PingPong
{
private:
	enum STATE
	{
		START = 0,RESUMED = 1, PAUSE = 2,
		GAME_OVER_WIN = 3, GAME_OVER_LOSE = 4
	};
	GRAPHICS::Window m_Window = GRAPHICS::Window(760,560,"PingPong_Example 1.0v");
	INPUT::Input m_Input = INPUT::Input(m_Window.getWindowHandler(), GLFW_CURSOR_NORMAL);
	GRAPHICS::Shaders m_Shaders = GRAPHICS::Shaders();
	GRAPHICS::MVP m_MVP = GRAPHICS::MVP(&m_Shaders);
	
	GRAPHICS::Sprite2D *m_Paddle;
	GRAPHICS::Sprite2D *m_CompPaddle;
	GRAPHICS::Sprite2D *m_Ball;
	GRAPHICS::Sprite2D::DATA m_PaddleLayout;
	GRAPHICS::Sprite2D::DATA m_CompPaddleLayout;
	GRAPHICS::Sprite2D::DATA m_BallLayout;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	void Update();
	void Render();
	
	void init();

	void UpdateInput();
	void UpdatePaddle();
	void UpdateCompPaddle();
	void UpdateBall();

	int m_CurrentState = RESUMED;

	bool m_BallCollideBordersUp = false;
	bool m_BallCollideBordersDown = false;
	bool m_BallCollidePaddle1 = false;
	bool m_BallCollidePaddle2 = false;

	bool m_BallGoingLeft = false;
	bool m_BallGoingUp = true;

	void CheckPaddleColisionBorders();

	// Ball Collision
	void CheckBallColisionBorders();
	void CheckBallColisionPaddle1();
	void CheckBallColisionPaddle2();

public:
	PingPong();
	~PingPong();

	void Run();
};