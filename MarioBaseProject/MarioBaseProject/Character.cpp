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
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}


	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		default:;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		default:;
		}
		break;
	default:;
	}
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