#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
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

}
void Character::Update(float deltaTime, SDL_Event e)
{

}
void Character::SetPosition(Vector2D new_position)
{

}
Vector2D Character::GetPosition()
{

}