#pragma once
#ifndef _CHARACTER_MARIO_H
#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterMario();
	void Update(float deltaTime, SDL_Event e);
private:
protected:
};


#endif // !_CHARACTER_MARIO_H