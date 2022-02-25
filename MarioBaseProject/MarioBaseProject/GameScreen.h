#pragma once
#ifndef _GAMESCREEN_H
#include <SDL.h>

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};


#endif // !_GAMESCREEN_H