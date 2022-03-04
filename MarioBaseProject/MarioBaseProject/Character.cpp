#include "Character.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position,
	LevelMap* map)
{
	m_collision_radius = 15.0f;
	m_current_level_map = map;
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

float Character::GetCollisionRadius()
{
	return m_collision_radius;
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

	//Collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / 
		TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	//add gravity

	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		std::cout << foot_position << "\n" << centralX_position << std::endl;
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground
		m_can_jump = true;
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