#include "PingPong_example.h"

PingPong::PingPong()
{
	init();
}

PingPong::~PingPong()
{

}

void PingPong::Run()
{
	while (glfwWindowShouldClose(m_Window.getWindowHandler()) == false)
	{
		m_Window.Update();
		Update();
		Render();
		m_Window.RenderImGUI();
	}
}

void PingPong::Render()
{
	m_MVP.SetBasicModelMatrix(m_Paddle->GetModelMatrix());
	m_Paddle->LegacyDraw();
	m_MVP.SetBasicModelMatrix(m_CompPaddle->GetModelMatrix());
	m_CompPaddle->LegacyDraw();

	m_MVP.SetBasicModelMatrix(m_Ball->GetModelMatrix());
	m_Ball->LegacyDraw();
}

void PingPong::Update()
{
	UpdateInput();
	if (m_CurrentState != PAUSE)
	{
		UpdatePaddle();
		UpdateBall();
		UpdateCompPaddle();
	}
}

bool up_collide = 0;
bool down_collide = 0;

void PingPong::CheckPaddleColisionBorders()
{
	// initialize temp point... acting as the top points of the paddle
	glm::vec4 temp_pointup;
	temp_pointup.x = m_PaddleLayout._center.x;
	temp_pointup.y = m_PaddleLayout._center.y + (m_PaddleLayout._size.y / 2);
	temp_pointup.z = 0.0f;
	temp_pointup.w = 1.0f;

	// multiply the vector with the model matrix...to manipulate the the shader
	// calc of the vertices
	temp_pointup = (m_Paddle->GetModelMatrix()) *  temp_pointup;
	
	// initialize temp point... acting as the top points of the paddle
	glm::vec4 temp_pointdown;
	temp_pointdown.x = m_PaddleLayout._center.x;
	temp_pointdown.y = m_PaddleLayout._center.y - (m_PaddleLayout._size.y / 2);
	temp_pointdown.z = 0.0f;
	temp_pointdown.w = 1.0f;

	// multiply the vector with the model matrix...to manipulate the the shader
	// calc of the vertices
	temp_pointdown = (m_Paddle->GetModelMatrix()) *  temp_pointdown;

	if (temp_pointup.y >= m_Window.getWindowHeight())
		up_collide = true;
	else up_collide = false;

	if (temp_pointdown.y < 0)
		down_collide = true;
	else down_collide = false;
}

void PingPong::CheckBallColisionBorders()
{
	glm::vec4 temp_ballPointUp;
	temp_ballPointUp.x = m_BallLayout._center.x + (m_BallLayout._size.x / 2);
	temp_ballPointUp.y = m_BallLayout._center.y + (m_BallLayout._size.y / 2);
	temp_ballPointUp.z = 0.0f;
	temp_ballPointUp.w = 1.0f;

	temp_ballPointUp = (m_Ball->GetModelMatrix()) * temp_ballPointUp;


	glm::vec4 temp_ballPointDown;
	temp_ballPointDown.x = m_BallLayout._center.x - (m_BallLayout._size.x / 2);
	temp_ballPointDown.y = m_BallLayout._center.y - (m_BallLayout._size.y / 2);
	temp_ballPointDown.z = 0.0f;
	temp_ballPointDown.w = 1.0f;

	temp_ballPointDown = (m_Ball->GetModelMatrix()) * temp_ballPointDown;

	if (temp_ballPointUp.y >= m_Window.getWindowHeight())
		m_BallCollideBordersUp = true;
	else m_BallCollideBordersUp = false;

	if (temp_ballPointDown.y < 0)
		m_BallCollideBordersDown = true;
	else m_BallCollideBordersDown = false;
}

void PingPong::CheckBallColisionPaddle1()
{
	glm::vec4 temp_paddlePoint;
	temp_paddlePoint.x = m_PaddleLayout._center.x + (m_PaddleLayout._size.x / 2);
	temp_paddlePoint.y = m_PaddleLayout._center.y;
	temp_paddlePoint.z = 0.0f;
	temp_paddlePoint.w = 1.0f;
	
	temp_paddlePoint = (m_Paddle->GetModelMatrix()) * temp_paddlePoint;
	float temp_paddleYRangeUP = temp_paddlePoint.y + (m_PaddleLayout._size.y / 2);
	float temp_paddleYRangeDOWN = temp_paddlePoint.y - (m_PaddleLayout._size.y / 2);

	glm::vec4 temp_ballPoint;
	temp_ballPoint.x = m_BallLayout._center.x - (m_BallLayout._size.x / 2);
	temp_ballPoint.y = m_BallLayout._center.y;
	temp_ballPoint.z = 0.0f;
	temp_ballPoint.w = 1.0f;

	temp_ballPoint = (m_Ball->GetModelMatrix()) * temp_ballPoint;

	if (temp_paddlePoint.x == temp_ballPoint.x)
		if(temp_paddleYRangeUP > temp_ballPoint.y && temp_paddleYRangeDOWN < temp_ballPoint.y)
		m_BallCollidePaddle1 = true;
	else m_BallCollidePaddle1 = false;
}

void PingPong::CheckBallColisionPaddle2()
{
	glm::vec4 temp_compPaddlePoint;
	temp_compPaddlePoint.x = m_CompPaddleLayout._center.x - (m_CompPaddleLayout._size.x / 2);
	temp_compPaddlePoint.y = m_CompPaddleLayout._center.y;
	temp_compPaddlePoint.z = 0.0f;
	temp_compPaddlePoint.w = 1.0f;

	temp_compPaddlePoint = (m_CompPaddle->GetModelMatrix()) * temp_compPaddlePoint;
	float temp_paddleYRangeUP = temp_compPaddlePoint.y + (m_CompPaddleLayout._size.y / 2);
	float temp_paddleYRangeDOWN = temp_compPaddlePoint.y - (m_CompPaddleLayout._size.y / 2);

	glm::vec4 temp_ballPoint;
	temp_ballPoint.x = m_BallLayout._center.x + (m_BallLayout._size.x / 2);
	temp_ballPoint.y = m_BallLayout._center.y;
	temp_ballPoint.z = 0.0f;
	temp_ballPoint.w = 1.0f;

	temp_ballPoint = (m_Ball->GetModelMatrix()) * temp_ballPoint;

	if (temp_compPaddlePoint.x == temp_ballPoint.x)
		if (temp_paddleYRangeUP > temp_ballPoint.y && temp_paddleYRangeDOWN < temp_ballPoint.y)
			m_BallCollidePaddle2 = true;
		else m_BallCollidePaddle2 = false;
}

void PingPong::UpdateInput()
{
	bool action_done = false;
	if (m_Input.isKeyPressed(GLFW_KEY_P) == true)
	{
		if (m_CurrentState != PAUSE || m_CurrentState != START || m_CurrentState != GAME_OVER_WIN || m_CurrentState != GAME_OVER_LOSE)
		{
			m_CurrentState = RESUMED;
			std::cout << "[PING_PONG] Game Has Paused Press L to resume . . . " << std::endl;
		}
	}
	if (m_Input.isKeyPressed(GLFW_KEY_L) == true)
	{
		if (m_CurrentState != RESUMED || m_CurrentState != START || m_CurrentState != GAME_OVER_WIN || m_CurrentState != GAME_OVER_LOSE)
		{
			if (action_done == false)
			{
				m_CurrentState = PAUSE;
				std::cout << "[PING_PONG] Game Has Resumed Press P to pause . . . " << std::endl;
			}
		}

	}
	if (m_Input.isKeyPressed(GLFW_KEY_ESCAPE) == true)
	{
		glfwSetWindowShouldClose(m_Window.getWindowHandler(), true);
	}
}

void PingPong::UpdatePaddle()
{
	CheckPaddleColisionBorders();
	CheckBallColisionPaddle1();
	CheckBallColisionPaddle2();

	if (m_Input.isKeyPressed(GLFW_KEY_W) == true)
	{
		if (up_collide != true)
		{
			m_Paddle->moveYAccelerated();
		}
	}
	else if (m_Input.isKeyPressed(GLFW_KEY_W) == false && m_Input.isKeyPressed(GLFW_KEY_S) == false
		&& m_Input.isKeyPressed(GLFW_KEY_D) == false && m_Input.isKeyPressed(GLFW_KEY_A) == false)
	{
			m_Paddle->ResetSpeedPosY();	
	}
	if (m_Input.isKeyPressed(GLFW_KEY_S) == true)
	{
		if (down_collide != true)
		{
			m_Paddle->moveNegYAccelerated();
		}
	}
	else if (m_Input.isKeyPressed(GLFW_KEY_S) == false && m_Input.isKeyPressed(GLFW_KEY_W) == false
		&& m_Input.isKeyPressed(GLFW_KEY_D) == false && m_Input.isKeyPressed(GLFW_KEY_A) == false)
	{
		m_Paddle->ResetSpeedNegY();
	}
}

void PingPong::UpdateCompPaddle()
{
	if (m_BallGoingLeft == false)
	{
		glm::vec4 temp_ballPoint;
		temp_ballPoint.x = m_BallLayout._center.x - (m_BallLayout._size.x / 2);
		temp_ballPoint.y = m_BallLayout._center.y;
		temp_ballPoint.z = 0.0f;
		temp_ballPoint.w = 1.0f;

		temp_ballPoint = (m_Ball->GetModelMatrix()) * temp_ballPoint;

		glm::vec4 temp_compPaddlePoint;
		temp_compPaddlePoint.x = m_CompPaddleLayout._center.x + (m_CompPaddleLayout._size.x / 2);
		temp_compPaddlePoint.y = m_CompPaddleLayout._center.y;
		temp_compPaddlePoint.z = 0.0f;
		temp_compPaddlePoint.w = 1.0f;

		temp_compPaddlePoint = (m_CompPaddle->GetModelMatrix()) * temp_compPaddlePoint;
		float temp_paddleYRangeUP = temp_compPaddlePoint.y + (m_CompPaddleLayout._size.y / 2);
		float temp_paddleYRangeDOWN = temp_compPaddlePoint.y - (m_CompPaddleLayout._size.y / 2);

		if (temp_ballPoint.y > temp_paddleYRangeUP)
			m_CompPaddle->moveYAccelerated();
		else if (temp_ballPoint.y < temp_paddleYRangeDOWN)
			m_CompPaddle->moveNegYAccelerated();
	}
	else
	{

	}
}

void PingPong::UpdateBall()
{
	CheckBallColisionBorders();
	CheckBallColisionPaddle1();
	CheckBallColisionPaddle2();

	if (m_BallCollideBordersUp == true)
	{
		m_BallGoingUp = false;
		m_BallCollideBordersUp = false;
	}
	if (m_BallCollideBordersDown == true)
	{
		m_BallGoingUp = true;
		m_BallCollideBordersDown = false;
	}
	if (m_BallCollidePaddle1 == true)
	{
		m_BallGoingLeft = false;
		m_BallCollidePaddle1 = false;
	}
	if (m_BallCollidePaddle2 == true)
	{
		m_BallGoingLeft = true;
		m_BallCollidePaddle2 = false;
	}

	if (m_BallGoingLeft == true)
	{
		m_Ball->moveNegX();
	}
	else if (m_BallGoingLeft == false)
	{
		m_Ball->moveX();
	}

	if (m_BallGoingUp == true)
	{
		m_Ball->moveY();
	}
	else if (m_BallGoingUp == false)
	{
		m_Ball->moveNegY();
	}
}

void PingPong::init()
{
	m_Projection = glm::ortho((float)0, (float)m_Window.getWindowWidth(), (float)0, (float)m_Window.getWindowHeight());
	m_View = glm::mat4(1.0f);

	m_Shaders.UseBasicProgram();
	m_MVP.SetBasicViewMatrix(m_View);
	m_MVP.SetBasicProjectionMatrix(m_Projection);

	m_PaddleLayout._center.x = 25;
	m_PaddleLayout._center.y = m_Window.getWindowHeight()/2;
	m_PaddleLayout._size.x = 15;
	m_PaddleLayout._size.y = 85;
	m_PaddleLayout._color[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_PaddleLayout._color[1] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_PaddleLayout._color[2] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_PaddleLayout._color[3] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_Paddle = new GRAPHICS::Sprite2D(m_PaddleLayout, &m_Shaders);
	m_CompPaddleLayout._center.x = m_Window.getWindowWidth() - 25;
	m_CompPaddleLayout._center.y = m_Window.getWindowHeight() / 2;
	m_CompPaddleLayout._size.x = 15;
	m_CompPaddleLayout._size.y = 85;
	m_CompPaddleLayout._color[0] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_CompPaddleLayout._color[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_CompPaddleLayout._color[2] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_CompPaddleLayout._color[3] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_CompPaddle = new GRAPHICS::Sprite2D(m_CompPaddleLayout, &m_Shaders);

	m_BallLayout._center.x = m_Window.getWindowWidth() / 2;
	m_BallLayout._center.y = m_Window.getWindowHeight() / 2;
	m_BallLayout._size.x = 25;
	m_BallLayout._size.y = 25;
	m_BallLayout._color[0] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_BallLayout._color[1] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_BallLayout._color[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_BallLayout._color[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_Ball = new GRAPHICS::Sprite2D(m_BallLayout, &m_Shaders);

	m_Ball->SetSpeedPosX(1.0f);
	m_Ball->SetSpeedPosY(2.0f);
	m_Ball->SetSpeedNegX(-1.0f);
	m_Ball->SetSpeedNegY(-2.0f);
	//m_Ball->SetChangerSpeedPosY(0.05f);
	//m_Ball->SetChangerSpeedNegY(-0.05f);
	//m_Ball->SetChangerSpeedPosX(0.0005f);
	//m_Ball->SetChangerSpeedNegX(-0.0005f);

	m_Paddle->SetSpeedPosX(0.5f);
	m_Paddle->SetSpeedPosY(0.5f);
	m_Paddle->SetSpeedNegX(0.5f);
	m_Paddle->SetSpeedNegY(0.5f);

	m_Paddle->SetChangerSpeedPosY(0.5f);
	m_Paddle->SetChangerSpeedNegY(-0.5f);

	m_CompPaddle->SetSpeedPosX(0.5f);
	m_CompPaddle->SetSpeedPosY(0.5f);
	m_CompPaddle->SetSpeedNegX(0.5f);
	m_CompPaddle->SetSpeedNegY(0.5f);
	  
	m_CompPaddle->SetChangerSpeedPosY(0.5f);
	m_CompPaddle->SetChangerSpeedNegY(-0.5f);
}