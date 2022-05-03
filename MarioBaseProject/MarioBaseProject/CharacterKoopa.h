#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
private:
	//koopa variables
	FACING m_facing_direction;
	float m_movement_speed;

	//flip and damaged behaviours
	bool m_injured;
	float m_injured_time;
	void FlipRightwayUp();
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath,
		Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Turn();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	bool GetInjured() { return m_injured; }
};

