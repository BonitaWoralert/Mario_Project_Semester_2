#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_moving_left = false;
	m_moving_right = false;
	m_facing_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Character.cpp: Failed to load m_texture";
	}

}
Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(GetPosition(), SDL_FLIP_NONE);	
	}
	if (m_facing_direction == FACING_LEFT)
	{
		m_texture->Render(GetPosition(), SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//jumping
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;
		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		//is jump force 0?
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}
	
	//moving left/right
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	//add gravity
	AddGravity(deltaTime);

	////check inputs
	//switch (e.type)
	//{
	//case SDL_KEYDOWN:
	//	switch (e.key.keysym.sym)
	//	{
	//	case SDLK_LEFT:
	//		m_moving_left = true;
	//		break;
	//	case SDLK_RIGHT:
	//		m_moving_right = true;
	//		break;
	//	case SDLK_SPACE:
	//		if (m_can_jump)
	//		{
	//			Jump();
	//			m_jumping = true;
	//			std::cout << "jumping";
	//		}
	//		break;
	//	default:;
	//	}
	//	break;
	//case SDL_KEYUP:
	//	switch (e.key.keysym.sym)
	//	{
	//	case SDLK_LEFT:
	//		m_moving_left = false;
	//		break;
	//	case SDLK_RIGHT:
	//		m_moving_right = false;
	//		break;
	//	default:;
	//	}
	//	break;
	//default:;
	//}
}

void Character::SetPosition(Vector2D new_position)
{
	std::cout << "set pos";
	m_position = new_position;
}
Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::AddGravity(float deltaTime)
{	
	if (m_position.y + m_texture->GetHeight() <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY_STRENGTH * deltaTime;
	}
	else
	{
		m_can_jump = true;
		m_position.y = SCREEN_HEIGHT - m_texture->GetHeight();
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}