#ifndef _CHARACTER_LUIGI_H
#define _CHARACTER_LUIGI_H
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position,
		LevelMap* map);
	~CharacterLuigi();
	void Update(float deltaTime, SDL_Event e);
};


#endif // !_CHARACTER_LUIGI_H